**Análisis de complejidad temporal**

*Selection Sort*

Dado que el algoritmo esta conpuesto por 2 for anidados, en el peor de los casos el algoritmo debera recorrerse a si mismo
para cada elemento, por lo que su complejidad asciende a O(n^2)

*Bubble Sort*

De la misma manera que con el Selection Sort, dado que hay 2 for anidados, en el peor de los casos el algoritmo debera
recorrese a si mismo por cada elemento, siendo esto un O(n^2)

*Merge Sort*

En este caso el algoritmo se recorre a si mismo n veces, pero en cada paso se reduce su longitud a la mitad, por lo que
también tiene un decrecimiento exponencial con lo que su complejidad temporal sería un O(n*log(n))

*Busqueda Secuencial*

En el peor de los casos, y para un arreglo previamente ordenado, el algotirmo deberá buscar a través de todos los n elementos
por lo que su complejidad temporal asciende a O(n)

*Busqueda Binaria*

En el peor de los casos, para un arreglo previamente ordenado, el algoritmo divide su área de busqueda a la mitad por cada paso
por lo que tiene un decrecimiento exponencial, con lo que su complejidad temporal es O(log(n))
