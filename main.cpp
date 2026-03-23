#include "avlTree.h"
#include "quickSort.h"
#include "heapSort.h"
#include "medidor.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
using namespace std;




int main() {
    vector<string> palabras;
    string palabra;

    // Leer el archivo palabra por palabra
    ifstream archivo("dataset.txt");

    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir dataset.txt" << endl;
        return 1;
    }

    while (archivo >> palabra) {
        palabras.push_back(palabra);
    }


    archivo.close();
    cout << "Archivo cargado" << endl;


    //Desordenar palabras
    random_device rd;
    mt19937 g(rd());
    shuffle(palabras.begin(), palabras.end(), g);
    cout << "Archivo desordenado" << endl;

    //Mostrar algunas palabras de prueba
    cout << "Primeras 20 palabras:\n" << endl;
    for (int i = 0; i < 20; i++) {
        cout << palabras[i] << endl;
    }

    int n = (int)palabras.size();

    //Quicksort
    medidor::MemoriaTeorica("Quicksort", n);
    medidor::ejecutarYMedir(quickSort, std::ref(palabras), 0, (int)palabras.size()-1);

    cout << "Primeras 20 palabras ordenadas del QuickSort:\n" << endl;
    for (int i = 0; i < 20; i++) {
        cout << palabras[i] << endl;
    }

    shuffle(palabras.begin(), palabras.end(), g);
    cout << "Archivo desordenado" << endl;

    //HeapSort
    medidor::MemoriaTeorica("HeapSort", n);
    medidor::ejecutarYMedir(heapSort, palabras);

    cout << "Primeras 20 palabras ordenadas del HeapSort:\n" << endl;
    for (int i = 0; i < 20; i++) {
        cout << palabras[i] << endl;
    }

    shuffle(palabras.begin(), palabras.end(), g);
    cout << "Archivo desordenado" << endl;

    //AVL Tree
    avlTree arbol;
    medidor::MemoriaTeorica("AVLTree", n);
    cout<<"Inserción de las palabras"<<endl;
    medidor::ejecutarYMedir( [&]() {
        for (const auto& p: palabras)
            arbol.insertar(p);
    });

    cout<<"ordenamiento de las palabras"<<endl;
    medidor::ejecutarYMedir( [&]() {
        arbol.inorden();
    });

    cout<<"Primeros 20 resultados ordenados:\n"<<endl;
    arbol.imprimirPrimeros20();


    return 0;
}
