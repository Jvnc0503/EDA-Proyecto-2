# C. Efecto cascada (Grupo 3)

**Time limit per test:** 5 seconds  
**Memory limit per test:** 512 megabytes

Hasta el momento, hemos visto que es posible realizar consultas sobre cajas en $d$ dimensiones usando $O(n \log^{d-1} n)$ de memoria, $O(n \log^{d-1} n)$ de preprocesamiento para $d \ge 2$ y $O(\log^d n)$ por consulta.

A pesar de ello, al final de la clase de laboratorio 2 de la semana 4, fue mencionado que es posible reducir un factor $O(\log n)$ en la complejidad de consulta. Una técnica que permite ello se llama cross linking o fractional cascading, la cual usa un poco más de memoria (sin afectar la complejidad, solo multiplica por un factor constante) pero nos reduce a $O(\log^{d-1} n)$ por consulta para $d \ge 2$.

Ya que no deseo el odio de mis estudiantes, solicitaré que implementes un Range Tree en 2 dimensiones pero con un tiempo de consulta de $O(\log n)$.

> Nota: Este proyecto tiene fecha límite el día 24 de abril a las 8:00 p.m. Además, se debe presentar un reporte de 1–2 páginas explicando el diseño de implementación, la correctitud algorítmica y el análisis de complejidad de la estructura.

## Input

La primera línea contiene dos enteros $n$ y $q$ $(1 \le n \le 3 \cdot 10^5)$ — la cantidad de puntos y la cantidad de consultas.

Las siguientes $n$ líneas contienen dos enteros $x_i$ e $y_i$ $(|x_i|, |y_i| \le 10^9)$ — la i-ésima línea describe las coordenadas del i-ésimo punto.

Las siguientes $q$ líneas contienen cuatro enteros $l_1$, $r_1$, $l_2$ y $r_2$ $(|l_1|, |l_2|, |r_1|, |r_2| \le 10^9, l_1 \le r_1, l_2 \le r_2)$ — la i-ésima línea describe los dos intervalos de la caja de la i-ésima consulta.

## Output

Para cada consulta, imprime la cantidad de puntos dentro de la caja brindada.

## Example

### Input

```text
6 5
4 -4
-2 -5
3 0
-1 2
4 2
3 -3
2 6 -2 2
2 6 -4 -2
-2 2 -2 2
1 3 0 4
-1 -1 -2 3
```

### Output

```text
2
2
1
1
1
```
