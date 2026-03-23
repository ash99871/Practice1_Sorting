#ifndef SORTING_MEDIDOR_H
#define SORTING_MEDIDOR_H

#include <iostream>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <utility>

// Clase para encapsular las mediciones
class medidor {
public:
    // Obtiene la memoria actual usada por el proceso en bytes
    static size_t obtenerMemoria() {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            return pmc.PrivateUsage;
        }
        return 0;
    }

    // Plantilla
    template <typename Func, typename... Args>
    static void ejecutarYMedir(Func func, Args&&... args) {
        // Limpieza previa sugerida para mediciones más estables
        size_t memoriaInicial = obtenerMemoria();
        auto tiempoInicio = std::chrono::high_resolution_clock::now();

        // Ejecución de la función del usuario
        func(std::forward<Args>(args)...);

        auto tiempoFin = std::chrono::high_resolution_clock::now();
        size_t memoriaFinal = obtenerMemoria();

        // Cálculos
        std::chrono::duration<double, std::milli> duracion = tiempoFin - tiempoInicio;
        long long diferenciaMemoria = static_cast<long long>(memoriaFinal) - static_cast<long long>(memoriaInicial);

        // Reporte en consola
        std::cout << "\n----------------------------------------" << std::endl;
        std::cout << "        REPORTE DE RENDIMIENTO          " << std::endl;
        std::cout << "------------------------------------------" << std::endl;
        std::cout << " Tiempo:    " << duracion.count() << " ms" << std::endl;
        std::cout << " Memoria:   " << diferenciaMemoria / 1024 << " KB (Delta)" << std::endl;
        std::cout << " RAM Total: " << memoriaFinal / 1024 << " KB" << std::endl;
        std::cout << "------------------------------------------\n" << std::endl;
    };

    static void MemoriaTeorica(const std::string& algoritmo, int n) {
        std::cout << "\n--------------------------------------" << std::endl;
        std::cout << "             MEMORIA TEÓRICA: " << algoritmo << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << " Elementos (n): " << n << std::endl;

        if (algoritmo == "QuickSort") {
            // Estructura principal: vector<string> — cada string ocupa ~32 bytes (SSO en MSVC)
            size_t tamVector = n * sizeof(std::string);
            // Stack de recursión: O(log n) en promedio, O(n) en peor caso
            size_t stackRecursion = (size_t)(std::log2(n) * (sizeof(int) * 2)); // 2 ints por frame (inicio, fin)

            std::cout << " Estructura:    vector<string>" << std::endl;
            std::cout << " Complejidad:   O(n) espacio principal + O(log n) stack" << std::endl;
            std::cout << " Vector datos:  " << tamVector / 1024 << " KB  (" << n << " x " << sizeof(std::string) << " bytes)" << std::endl;
            std::cout << " Stack recursión (aprox): " << stackRecursion << " bytes" << std::endl;
            std::cout << " Total aprox:   " << (tamVector + stackRecursion) / 1024 << " KB" << std::endl;
        }
        else if (algoritmo == "HeapSort") {
            // Heap implícito sobre el mismo vector — in-place, O(1) extra
            size_t tamVector = n * sizeof(std::string);

            std::cout << " Estructura:    Heap implícito en vector<string>" << std::endl;
            std::cout << " Complejidad:   O(n) solo datos, O(1) espacio extra" << std::endl;
            std::cout << " Vector datos:  " << tamVector / 1024 << " KB  (" << n << " x " << sizeof(std::string) << " bytes)" << std::endl;
            std::cout << " Extra (swap):  " << sizeof(std::string) << " bytes (1 variable temporal)" << std::endl;
            std::cout << " Total aprox:   " << tamVector / 1024 << " KB" << std::endl;
        }
        else if (algoritmo == "AVLTree") {
            // Cada nodo tiene: string + 2 punteros + int altura
            struct NodoAprox { std::string palabra; void* l; void* r; int altura; };
            size_t tamNodo = sizeof(NodoAprox);
            size_t tamTotal = n * tamNodo;
            // Stack de recursión inorden: O(log n)
            size_t stackInorden = (size_t)(std::log2(n) * sizeof(void*));

            std::cout << " Estructura:    Árbol AVL (nodos dinámicos)" << std::endl;
            std::cout << " Complejidad:   O(n) nodos + O(log n) stack recursión" << std::endl;
            std::cout << " Tamaño nodo:   " << tamNodo << " bytes (string + 2 punteros + altura)" << std::endl;
            std::cout << " Nodos totales: " << tamTotal / 1024 << " KB  (" << n << " x " << tamNodo << " bytes)" << std::endl;
            std::cout << " Stack inorden: " << stackInorden << " bytes (aprox)" << std::endl;
            std::cout << " Total aprox:   " << (tamTotal + stackInorden) / 1024 << " KB" << std::endl;
        }

        std::cout << "-------------------------------------------------------------------\n" << std::endl;
    }
};


#endif //SORTING_MEDIDOR_H
