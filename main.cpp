#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
using namespace std;

// Funcion que divide el vector alrededor del pivote
int dividir(vector<string>& arr, int inicio, int fin) {

    string pivote = arr[fin];
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {

        if (arr[j] <= pivote) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[fin]);
    return i + 1;
}


// Funcion para el QuickSort
void quickSort(vector<string>& arr, int inicio, int fin) {

    if (inicio < fin) {

        int p = dividir(arr, inicio, fin);

        quickSort(arr, inicio, p - 1);
        quickSort(arr, p + 1, fin);
    }
}


// Función para medir el tiempo
long medirTiempo(function<void()> algoritmo) {

    auto inicio = chrono::high_resolution_clock::now();

    algoritmo();

    auto fin = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::microseconds>(fin - inicio).count();
}


//main:
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

    //Desordenar palabras
    random_device rd;
    mt19937 g(rd());
    shuffle(palabras.begin(), palabras.end(), g);
    cout << "Archivo desordenado" << endl;
    
    
    //Ejecutar y medir el tiempo del quickSort
    long tiempoQuick = medirTiempo([&]() {

        quickSort(palabras, 0, palabras.size() - 1);

    });
    
    cout << "QuickSort terminado" << endl;
    cout << "Tiempo QuickSort: " << tiempoQuick << " microsegundos\n" << endl;

    //Mostrar algunas palabras como de prueba
    for (string p : palabras) {
        cout << p << endl;
    }

    return 0;
}
