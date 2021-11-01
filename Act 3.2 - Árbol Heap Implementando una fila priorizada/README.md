# Analisis de Complejidad Temporal
### Push
*Al ser un programa que debe recorrer el arreglo completo en el peor de los casos, su complejiddad resultaría en O(n), sin embargo, usando la función
heapify(), podemos reducirla a O(log(n))*

### Pop
*En este caso al hacer uso también de la función heapify() para mantener las propiedades de un árbol heap, la complejidad resulta en O(log(n))*

### Top
*Se regresa un dato en una posición especifica, por lo que la complejidad es simpre la misma, es decir O(1)*

### Empty
*Se verifica una condicón unicamente, por lo que la complejidad temporal es de O(1)*

### Size
*Se regresa el tamaño del arreglo, que se modifica en cada "vuelta", por lo que la complejidad temporal es de O(1)*

### toString
*Convirtiendo cada elemento del arreglo en una cadena de carácteres, debe recorrer toda el arreglo, por lo que tiene complejidad O(n).*
