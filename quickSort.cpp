
#include "quickSort.h"
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