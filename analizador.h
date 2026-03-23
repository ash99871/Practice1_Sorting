#include <iostream>
#include <string>
using namespace std;

class analizador {
public:

    static void comparar(
        double tQuick, long mQuick,
        double tHeap, long mHeap,
        double tAVL, long mAVL
    ) {

        cout << "\n========================================" << endl;
        cout << "        ANALISIS COMPARATIVO FINAL      " << endl;
        cout << "========================================" << endl;

        // Mejor tiempo
        string mejorTiempo = "QuickSort";
        double minTiempo = tQuick;

        if (tHeap < minTiempo) {
            minTiempo = tHeap;
            mejorTiempo = "HeapSort";
        }

        if (tAVL < minTiempo) {
            minTiempo = tAVL;
            mejorTiempo = "AVL";
        }

        // Mejor memoria
        string mejorMemoria = "QuickSort";
        long minMemoria = mQuick;

        if (mHeap < minMemoria) {
            minMemoria = mHeap;
            mejorMemoria = "HeapSort";
        }

        if (mAVL < minMemoria) {
            minMemoria = mAVL;
            mejorMemoria = "AVL";
        }

        cout << "\nMejor en TIEMPO: " << mejorTiempo << endl;
        cout << "Mejor en MEMORIA: " << mejorMemoria << endl;

        cout << "\nALGORITMO MAS EFICIENTE: " << mejorTiempo << endl;

        cout << "========================================\n" << endl;
    }
};
