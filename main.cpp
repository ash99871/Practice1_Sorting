#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

// Funcion que divide el vector alrededor del pivote
int dividir(vector<string>& palabras, int inicio, int fin){
    string pivote = palabras[fin];
    int i = inicio - 1;

    for(int j = inicio; j < fin; j++){
        if(palabras[j] < pivote){
            i++;
            swap(palabras[i], palabras[j]);
        }
    }
    swap(palabras[i + 1], palabras[fin]);

    return i + 1;
}

// Funcion para el QuickSort
void ordenarQuick(vector<string>& palabras, int inicio, int fin){
    if(inicio < fin){
        int posicionPivote = dividir(palabras, inicio, fin);

        ordenarQuick(palabras, inicio, posicionPivote - 1);
        ordenarQuick(palabras, posicionPivote + 1, fin);
    }
}

int main()
{
    // Leer el archivo palabra por palabra
    ifstream archivo("words_alpha.txt");   
    if(!archivo){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    vector<string> palabras(100000);
    
    for(int i = 0; i < 100000; i++){
        getline(archivo, palabras[i]);
    }
    cout << "Archivo cargado" << endl;

    
    // Desordenar palabras
    random_device rd;
    mt19937 g(rd());
    shuffle(palabras.begin(), palabras.end(), g);
    cout << "Archivo desordenado" << endl;

    
    // Medir tiempo QuickSort
    auto inicio = chrono::high_resolution_clock::now();
    ordenarQuick(palabras, 0, palabras.size() - 1);
    auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
    cout << "QuickSort terminado" << endl;
    cout << "Tiempo QuickSort: " << duracion.count() << " microsegundos" << endl;


    // Mostrar algunas palabras de prueba
    for(int i = 0; i < 50; i++)
    {
        cout << palabras[i] << endl;
    }

    return 0;
}
