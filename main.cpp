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
    ifstream archivo("words_alpha.txt");
    while (archivo >> palabra) {
        palabras.push_back(palabra);
    }
    archivo.close();
    cout << "Archivo cargado" << endl;

    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir words_alpha.txt" << endl;
        return 1;
    }

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

    //Quicksort
    medidor::ejecutarYMedir(quickSort, std::ref(palabras), 0, (int)palabras.size()-1);

    cout << "Primeras 20 palabras ordenadas del QuickSort:\n" << endl;
    for (int i = 0; i < 20; i++) {
        cout << palabras[i] << endl;
    }

    shuffle(palabras.begin(), palabras.end(), g);
    cout << "Archivo desordenado" << endl;

    //HeapSort
    medidor::ejecutarYMedir(heapSort, palabras);

    cout << "Primeras 20 palabras ordenadas del HeapSort:\n" << endl;
    for (int i = 0; i < 20; i++) {
        cout << palabras[i] << endl;
    }

    shuffle(palabras.begin(), palabras.end(), g);
    cout << "Archivo desordenado" << endl;

    //AVL Tree
    avlTree arbol;
    medidor::ejecutarYMedir( [&]() {
        for (const auto& p: palabras)
            arbol.insertar(p);
    });
    medidor::ejecutarYMedir( [&]() {
        arbol.inorden();
    });

    cout << "Primeras 20 palabras ordenadas del AVL Tree:\n" << endl;
    for (int i = 0; i < 20; i++) {
        cout << palabras[i] << endl;
    }

}