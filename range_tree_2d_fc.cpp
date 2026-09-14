#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Representación de un punto en 2D
struct Point {
    long long x, y;
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

class LayeredRangeTree2D {
private:
    int n;
    vector<Point> pts;
    
    // toLeft[u][i] y toRight[u][i] guardan los índices en los hijos
    vector<vector<int>> toLeft;
    vector<vector<int>> toRight;
    
    // Solo el nodo raíz (u = 1) necesita almacenar explícitamente sus coordenadas Y
    vector<long long> rootY;

    // Construcción recursiva del árbol y cálculo de puentes de cascading
    vector<long long> build(int u, int l, int r) {
        if (l == r) {
            return {pts[l].y};
        }

        int mid = l + (r - l) / 2;
        vector<long long> leftY = build(2 * u, l, mid);
        vector<long long> rightY = build(2 * u + 1, mid + 1, r);

        int nL = leftY.size();
        int nR = rightY.size();
        int nU = nL + nR;

        vector<long long> currentY(nU);
        toLeft[u].resize(nU + 1);
        toRight[u].resize(nU + 1);

        // Mezcla estilo MergeSort
        int pL = 0, pR = 0, idx = 0;
        while (pL < nL && pR < nR) {
            if (leftY[pL] <= rightY[pR]) {
                currentY[idx++] = leftY[pL++];
            } else {
                currentY[idx++] = rightY[pR++];
            }
        }
        while (pL < nL) currentY[idx++] = leftY[pL++];
        while (pR < nR) currentY[idx++] = rightY[pR++];

        // Precomputar punteros toLeft en O(|currentY|)
        int j = 0;
        for (int i = 0; i < nU; ++i) {
            while (j < nL && leftY[j] < currentY[i]) {
                j++;
            }
            toLeft[u][i] = j;
        }
        toLeft[u][nU] = nL;

        // Precomputar punteros toRight en O(|currentY|)
        int k = 0;
        for (int i = 0; i < nU; ++i) {
            while (k < nR && rightY[k] < currentY[i]) {
                k++;
            }
            toRight[u][i] = k;
        }
        toRight[u][nU] = nR;

        if (u == 1) {
            rootY = currentY;
        }

        return currentY;
    }

    int query(int u, int l, int r, int ql, int qr, int yLow, int yHigh) const {
        if (yLow >= yHigh) return 0; // Subrango en Y vacío
        
        // Nodo canónico: rango completamente cubierto en X
        if (ql <= l && r <= qr) {
            return yHigh - yLow;
        }

        int mid = l + (r - l) / 2;
        int count = 0;

        // Descenso hacia el hijo izquierdo con cascading O(1)
        if (ql <= mid) {
            int nextLow = toLeft[u][yLow];
            int nextHigh = toLeft[u][yHigh];
            count += query(2 * u, l, mid, ql, qr, nextLow, nextHigh);
        }

        // Descenso hacia el hijo derecho con cascading O(1)
        if (qr > mid) {
            int nextLow = toRight[u][yLow];
            int nextHigh = toRight[u][yHigh];
            count += query(2 * u + 1, mid + 1, r, ql, qr, nextLow, nextHigh);
        }

        return count;
    }

public:
    LayeredRangeTree2D(vector<Point>& inputPts) {
        pts = inputPts;
        n = pts.size();
        sort(pts.begin(), pts.end());

        toLeft.resize(4 * n);
        toRight.resize(4 * n);

        if (n > 0) {
            build(1, 0, n - 1);
        }
    }

    int query(long long x1, long long x2, long long y1, long long y2) const {
        if (n == 0 || x1 > x2 || y1 > y2) return 0;

        // Búsqueda del intervalo de índices [ql, qr] en el árbol primario por X
        auto compX = [](const Point& p, long long val) { return p.x < val; };
        int ql = lower_bound(pts.begin(), pts.end(), x1, compX) - pts.begin();
        int qr = upper_bound(pts.begin(), pts.end(), x2, compX) - pts.begin() - 1;

        if (ql > qr) return 0;

        // Única búsqueda binaria real en la raíz (O(log n))
        int yLow = lower_bound(rootY.begin(), rootY.end(), y1) - rootY.begin();
        int yHigh = upper_bound(rootY.begin(), rootY.end(), y2) - rootY.begin();

        return query(1, 0, n - 1, ql, qr, yLow, yHigh);
    }
};

int main() {
    // Optimización de I/O estándar
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }

    LayeredRangeTree2D tree(pts);

    while (q--) {
        long long l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << tree.query(l1, r1, l2, r2) << "\n";
    }

    return 0;
}
