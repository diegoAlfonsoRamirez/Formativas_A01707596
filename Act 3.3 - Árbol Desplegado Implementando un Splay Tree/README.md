# Analisis de Complejidad Temporal
### Add
*En el programa se utilizan una función que agrega el nodo basado en su valor y otro que hace uso de la función splay
(la cual rota el árbol en caso de ser necesario), siendo que su complejidad es de O(log(n))*

### Remove
*Al eliminar un nodo y reasignar los demás nodos, debe de recorrer n pasos, por lo que  la complejidad resulta en O(log(n))*

### Find
*El alogritmo se tiene que repetir n veces a fin de encontrar el valor dado, por lo que su recursividad, en el peor caso, es de O(log(n))*

### Size
*Siendo que la variable que controla el size se actualiza con cada agregación o eliminación, se hace una consulta única, siendo que es un O(1)*
