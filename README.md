# Practice1_Sorting


## Creators:

Maybeth López.
Ashly Robayo.



Proyecto en C++ que compara el rendimiento de tres estructuras y algoritmos de ordenamiento sobre un conjunto grande de palabras en inglés: **QuickSort**, **HeapSort** y **Árbol AVL**. Para cada uno se mide el tiempo de ejecución y el consumo de memoria, permitiendo comparar su eficiencia en condiciones reales.

---

## Descripción general

El programa lee un archivo de texto con palabras (`words_alpha.txt`), las carga en un vector, las desordena aleatoriamente y aplica cada algoritmo o estructura de datos secuencialmente. Después de cada operación se imprime un reporte de rendimiento con el tiempo transcurrido y la memoria utilizada. Al finalizar cada etapa se muestran las primeras 20 palabras para verificar que el ordenamiento fue correcto.

---

## Algoritmos implementados

| Algoritmo | Archivo | Complejidad promedio |
|-----------|---------|----------------------|
| QuickSort | `quickSort.cpp` | O(n log n) |
| HeapSort  | `heapSort.cpp`  | O(n log n) |
| Árbol AVL | `avlTree.cpp`   | O(n log n) inserción |

---

## Estructura del proyecto

```
Cositas/
├── main.cpp          # Punto de entrada y flujo principal
├── quickSort.h/.cpp  # Implementación de QuickSort
├── heapSort.h/.cpp   # Implementación de HeapSort
├── avlTree.h/.cpp    # Implementación del árbol AVL
├── medidor.h         # Utilidad para medir tiempo y memoria
└── CMakeLists.txt    # Configuración de compilación
```

---

## Descripción detallada de los archivos

### `main.cpp`

Es el punto de entrada del programa y coordina todas las operaciones. Su flujo es el siguiente:

1. Abre y lee el archivo `words_alpha.txt` palabra por palabra, almacenándolas en un `vector<string>`.
2. Desordena el vector usando `std::shuffle` con una semilla aleatoria (`std::random_device`), garantizando que el orden sea diferente en cada ejecución.
3. Imprime las primeras 20 palabras antes de ordenar, a modo de muestra del estado desordenado.
4. Ejecuta **QuickSort** sobre el vector completo, envuelto en `medidor::ejecutarYMedir` para capturar tiempo y memoria.
5. Imprime las primeras 20 palabras ya ordenadas.
6. Vuelve a desordenar el vector y repite el proceso con **HeapSort**.
7. Vuelve a desordenar el vector, crea un `avlTree` e inserta todas las palabras una por una, midiendo tanto la inserción como el recorrido inorden.

---

### `quickSort.cpp`

Implementa el algoritmo **QuickSort**, uno de los algoritmos de ordenamiento más eficientes en la práctica para datos en memoria.

El archivo contiene dos funciones:

- **`dividir()`**: selecciona el último elemento del rango como pivote y reorganiza el vector de forma que todos los elementos menores o iguales al pivote queden a su izquierda y los mayores a su derecha. Retorna el índice final del pivote.
- **`quickSort()`**: función recursiva que llama a `dividir()` y luego se aplica recursivamente sobre las dos mitades resultantes (izquierda del pivote y derecha del pivote).

El pivote siempre es el elemento en la posición `fin`, lo cual puede degradar el rendimiento a O(n²) en vectores ya ordenados, aunque al trabajar sobre datos previamente desordenados con `shuffle` este caso es poco probable.

---

### `heapSort.cpp`

Implementa el algoritmo **HeapSort**, basado en la estructura de datos *heap* (montículo).

El archivo contiene dos funciones:

- **`heap()`**: función auxiliar recursiva que mantiene la propiedad de **max-heap** a partir de un nodo `i`. Compara el nodo con sus hijos izquierdo (`2*i+1`) y derecho (`2*i+2`), y si alguno es mayor lo intercambia con el padre, propagando el ajuste hacia abajo recursivamente.
- **`heapSort()`**: primero construye el max-heap completo recorriendo el vector desde la mitad hacia el inicio (fase *build heap*). Luego, en cada iteración, intercambia la raíz del heap (el mayor elemento) con el último elemento no ordenado y reduce el tamaño del heap en uno, restaurando la propiedad de heap con `heap()`. Este proceso se repite hasta ordenar todo el vector.

HeapSort garantiza O(n log n) en el peor caso, a diferencia de QuickSort.

---

### `avlTree.cpp`

Implementa un **árbol AVL**, que es un árbol binario de búsqueda (BST) autobalanceado. A diferencia de un BST simple, el árbol AVL garantiza que la diferencia de altura entre los subárboles izquierdo y derecho de cualquier nodo (factor de balance) nunca supere 1, lo que mantiene las operaciones en O(log n).

El archivo implementa los siguientes métodos:

- **`altura()`**: retorna la altura almacenada en un nodo, o 0 si el nodo es nulo.
- **`factor()`**: calcula el factor de balance de un nodo como la diferencia entre la altura del subárbol izquierdo y el derecho.
- **`nuevaAltura()`**: recalcula y actualiza la altura de un nodo a partir de la altura de sus hijos.
- **`rotacionDer()`**: realiza una rotación simple a la derecha sobre un nodo desbalanceado hacia la izquierda.
- **`rotacionIzq()`**: realiza una rotación simple a la izquierda sobre un nodo desbalanceado hacia la derecha.
- **`balancear()`**: evalúa el factor de balance de un nodo y aplica la rotación correspondiente (simple o doble) según el caso: izquierda-izquierda, izquierda-derecha, derecha-derecha o derecha-izquierda.
- **`insertar()`**: inserta recursivamente una nueva palabra siguiendo las reglas del BST (menor a la izquierda, mayor a la derecha) e ignora duplicados. Tras cada inserción llama a `balancear()` para mantener el equilibrio del árbol.
- **`inorden()`**: recorre el árbol en orden (izquierda → raíz → derecha), imprimiendo cada palabra. Al ser un BST, este recorrido produce las palabras en orden alfabético ascendente.
- **`liberar()`**: recorre el árbol en postorden y libera la memoria de cada nodo, llamado desde el destructor.

---

### `medidor.h`

Define la clase `medidor`, una utilidad para medir el rendimiento de cualquier función o bloque de código. Usa una plantilla de función (`template`) que acepta cualquier callable (función, lambda, functor) junto con sus argumentos.

Internamente:
- Captura la memoria del proceso **antes** de ejecutar la función usando `GetProcessMemoryInfo` de la API de Windows (`psapi.h`).
- Registra el tiempo de inicio con `std::chrono::high_resolution_clock`.
- Ejecuta la función con `std::forward` para un reenvío perfecto de argumentos.
- Captura nuevamente el tiempo y la memoria al finalizar.
- Calcula e imprime el tiempo transcurrido en milisegundos y el delta de memoria en KB.

> ⚠️ Este archivo depende de `<windows.h>` y `<psapi.h>`, por lo que el proyecto **solo compila en Windows**.

---

## Requisitos

- **Sistema operativo:** Windows (por dependencia de Win32 API en `medidor.h`)
- **Compilador:** GCC / MinGW o MSVC con soporte C++14
- **CMake:** versión 4.0 o superior
- **Archivo de datos:** `words_alpha.txt` en el directorio de ejecución

> `words_alpha.txt` es una lista de palabras en inglés disponible públicamente. Puedes obtenerla en [dwyl/english-words](https://github.com/dwyl/english-words).

---

## Compilación

```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build .
```

O directamente desde **CLion** abriendo la carpeta del proyecto.

---

## Uso

Coloca `words_alpha.txt` en el mismo directorio que el ejecutable y ejecuta:

```bash
./Cositas
```

### Salida esperada

```
Archivo cargado
Archivo desordenado
Primeras 20 palabras:

quixotism
frowzy
interrenal
...

----------------------------------------
        REPORTE DE RENDIMIENTO
------------------------------------------
 Tiempo:    450.23 ms
 Memoria:   1200 KB (Delta)
 RAM Total: 35000 KB
------------------------------------------

Primeras 20 palabras ordenadas:

a
aa
aah
aahed
...

Archivo desordenado

----------------------------------------
        REPORTE DE RENDIMIENTO
------------------------------------------
 Tiempo:    520.10 ms
 Memoria:   800 KB (Delta)
 RAM Total: 36000 KB
------------------------------------------

...
```

---

## Notas

- El medidor de memoria usa `GetProcessMemoryInfo` de la API de Windows y no es compatible con Linux/macOS.
- El árbol AVL ignora palabras duplicadas al insertar.
- El orden inicial de las palabras varía en cada ejecución por el uso de `std::shuffle` con semilla aleatoria.
- Si `words_alpha.txt` no se encuentra, el programa continuará con un vector vacío sin lanzar ningún error. Se recomienda agregar una validación del archivo al inicio de `main.cpp`.

