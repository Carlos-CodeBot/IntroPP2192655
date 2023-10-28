# Solucionador de la Ecuación del Calor - Mejoras del Proyecto

Este programa simula la evolución de un campo de temperatura en un dominio 2D utilizando la ecuación del calor, haciendo uso de la tecnología MPI para distribuir y acelerar los cálculos. La ecuación del calor es una ecuación diferencial parcial, que describe cómo varía la temperatura en un punto con respecto al tiempo y al espacio. 

Se utiliza en una variedad de aplicaciones científicas y de ingeniería para modelar la conducción de calor en sistemas físicos.La capacidad de simular la propagación del calor en un sistema es fundamental en muchas áreas de la física, de la ingeniería y las ciencias de la tierra. 



## Descripción y explicación de la funcionalidad del código

Está compuesto por diez archivos, los cuales se describen los más relevantes

### 1. **heat.h**
Es una cabecera que define la estructura de datos para representar el campo de temperatura (field). Cada objeto field tiene un tamaño (nx, ny) y una matriz de datos (data). Esta estructura se utilizará para representar y manipular el campo de temperatura en el dominio del problema.

### 2. **heat.c**
Contiene funciones para simular la evolución del campo de temperatura utilizando la ecuación del calor. La función evolve() realiza un paso en el tiempo de la simulación. Usa las condiciones de contorno y actualiza el campo de temperatura en función de la derivada laplaciana. Es el núcleo del algoritmo de simulación. 

Por otro lado, initialize_field() establece las condiciones iniciales del campo de temperatura. Esto probablemente representa un instante inicial en la simulación. La función initialize_boundary() establece las condiciones de contorno para los bordes del dominio. Esto es crucial en simulaciones numéricas para garantizar soluciones estables y físicamente relevantes.

### 3. **main.c**
Es el punto de entrada al programa. Configura e inicializa MPI, lee los parámetros de entrada y establece las condiciones iniciales del campo de temperatura. Realiza la simulación de la ecuación del calor durante un número especificado de pasos, intercambiando los campos de temperatura después de cada paso, ocasionalmente imprimiendo el estado. Finalmente, se acaba la ejecución de MPI y se sale del programa.

### 4. **utility.c**
Proporciona varias funciones de utilidad para trabajar con los campos de temperatura. En primer lugar, malloc_2d() y free_2d() reservan y liberan memoria para una matriz 2D, respectivamente; copy_field() copia el contenido de un campo de temperatura en otro; swap_fields() intercambia los datos entre dos campos de temperatura; allocate_field() Reserva memoria para un campo de temperatura y lo inicializa a cero.



## Mejoras Generales
Estas mejoras buscan optimizar el rendimiento y la funcionalidad general del código.


### 1. **Estructura, Legibilidad y Documentación del Código**
El código ha sido modificado para mejorar la estructura general del mismo, buscando una mayor legibilidad. Además, como documentación se comentaron diferentes sentencias con la descripción de su funcionalidad. Por último, se organizó la estructura de las funciones para evitar errores de lógica.

### 2. **Mejoras de Rendimiento**
Se modificaron algunas sentencias de código referentes a la gestión de la memoria, en la asignación y liberación, así como los bucles, los cuales han reducido algunos cálculos innecesarios. Se han mejorado las configuraciones de MPI, para optimizar las capacidades de procesamiento paralelo.

### 3. **Archivo Ejecutable Sbatch**
Se añade un archivo llamado sbatch_file.sbatch, la cual contiene los comandos necesarios para realizar correctamente la ejecución del programa. Se importan los módulos y librerías necesarias, así como el orden correcto de cada sentencia requerida para el resultado final.
