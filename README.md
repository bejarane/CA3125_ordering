# Prueba de múltiples algoritmos de ordenamiento
## Descripción
En este proyecto se desarrollan 5 algoritmos de búsqueda distintos. Estos consisten del Bubblesort, Insertsort, Quicksort, Mergesort y Radixsort.

Todos los algoritmos se han implementado a través de la interpretación de referencias encontradas en https://www.geeksforgeeks.org - automatic!

## Método de uso
1. Compilar el código fuente con `make`
2. Ejecutar el binario `output.bin` almacenado en el directorio `bin` con un comando como `./bin/output.bin`.
3. Ingresar en consola los valores **a** y **b** que corresponden al número de veces a repetir un ordenamiento y a la cantidad de elementos a ordenar respectivamente.
4. El programa ordenará un conjunto generado aleatoriamente e imprimirá en pantalla el acumulado del tiempo de ejecución para cada método de ordenamiento.

## Funcionamiento
### Algoritmos
El programa utiliza una implementación simple para los algoritmos de Bubblesort, Mergesort y Quicksort derivada de las definiciones teóricas de los mismos.
El algoritmo de Mergesort está basado en el algoritmo presentado en [Geeks for Geeks] (https://www.geeksforgeeks.org/merge-sort/ "Mergesort") al igual que el algoritmo de Radixsort que se encuentra en el mismo [sitio](https://www.geeksforgeeks.org/radix-sort/ "Radixsort").

Cada algoritmo se ejecuta de manera recurrente hasta ordenar todo el conjunto.

### Conjunto aleatorio
El programa genera un conjunto de datos aleatorios a través del algoritmo de Mersenne twister MT19937 (generador de números psuedoaleatorios) utilizando como dato semilla un número aleatorio generado con el método `random_device`.

### Pruebas
El flujo normal del programa es generar un conjunto de datos de prueba de tamaño **b** y utilizar cada uno de los algoritmos para ordenarlo **a** veces. 

Durante el proceso el sistema se encarga de almacenar el tiempo acumulado por cada algoritmo y posteriormente imprimir el resultado debidamente organizado en consola.