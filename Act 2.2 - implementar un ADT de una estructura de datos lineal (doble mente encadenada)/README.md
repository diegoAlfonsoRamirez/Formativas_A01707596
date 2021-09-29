# Analisis de Complejidad Temporal
### Insertion
*Al ser un programa que agrega un elemento al final de una lista doblemente ligada, el programa debe recorrer n elementos para llegar al final de la lista
por lo que su complejiddad resulta en O(n)*

### Search
*Este algoritmo busca un elemento x en la lista, en el peor de los casos ese elemento será el último, por lo que su complejidad sería O(n).
También cabe considerar de que, en caso de no encontrar el elemento, el programa expulsará un -1 como respuesta, habíendo recorrido toda la
lista doblemente ligada, nuevamente tendrá una complejidad O(n)*

### Update
*En este caso el algoritmo deberá buscar un elemento en la posición x, para cambiar su valor a z, siendo que la lista es doblemente 
ligada y podemos retroceder, el peor de los casos deberá recorrer la mitad de todo el arreglo, por lo que tendrá complejidad O(n/2).
En caso de introducir una posición mayor que el tamaño de la lista o de ser menor a 0, expulsará un -1 en la primera posición.*

### Delete
*Igual que en los demás casos, la complejidad es O(n), pues en el peor de los casos el algoritmo deberá buscar el último elemento para borrarlo.
Al igual que en los demás casos, si la posición a eliminar supera los límites de la lista, explusará un -1 en la primerra posición. Quise omplementar
al igual que en la anterior función, que buscara apartir del elemento medio, pero no pude.*

### toString
*Convirtiendo cada elemento de la lista en una cadena de carácteres, debe recorrer toda la lista, por lo que tiene complejidad O(n).*
