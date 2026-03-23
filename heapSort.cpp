
#include "heapSort.h"
using namespace std;

// Creación del heap
void heap(std::vector<std::string>& arr, int n, int i){
    // La raiz debe ser i, y debe ser el maximo
    int max = i;

    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[max])
        max = l;

    if (r < n && arr[r] > arr[max])
        max = r;

    if (max != i) {
        std::swap(arr[i], arr[max]);
        heap(arr, n, max);
    }


}

// Función para el heap sort
void heapSort(vector<string>& arr){
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heap(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heap(arr, i, 0);
    }
}