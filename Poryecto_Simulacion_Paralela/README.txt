**********Descripción************

Este programa en C implementa una estructura de datos y funcionalidad asociada para trabajar con listas de adyacencia, 
útiles en la representación de grafos y autómatas, como los Autómatas No Deterministas Finitos (NFA).

*********Características***********

Bibliotecas Utilizadas: El programa utiliza varias bibliotecas estándar de C como stdio.h, stdlib.h, string.h, stdbool.h, math.h, y time.h.

Estructura de Nodo: Define una estructura node para representar nodos en una lista de adyacencia,
cada uno con un dato entero, un puntero al siguiente nodo, y un tipo de borde (edgetype).


Función de Adición: Incluye una función push para añadir bordes a la lista de adyacencia.


**********Compilación**************

Para compilar este programa, se debe usar el siguiente comando en un terminal con GCC instalado:


gcc -fopenmp -Os -std=c99 NFA -o NFA



**********Detalles del Comando de Compilación*************

gcc: Invoca el compilador GCC.

-fopenmp: Habilita el soporte para OpenMP, útil para la programación paralela.

-Os: Optimiza el código para reducir el tamaño del archivo y el uso de la memoria.

-std=c99: Especifica el estándar C99 para la compilación.

NFA: Es el nombre del archivo fuente (asegúrate de que este sea el nombre correcto de tu archivo fuente).

-o NFA: Especifica el nombre del archivo ejecutable generado (en este caso, NFA).


***********Uso***************
Una vez compilado, el programa se puede ejecutar mediante el archivo ejecutable NFA generado.

gcc -Os -std=c99 o_NFA -o o_NFA

(Si se puede correr en local, si se tienen todas las librerias y modulos instalados para su correcto uso.)
