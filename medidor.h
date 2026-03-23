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
    }
};


#endif //SORTING_MEDIDOR_H