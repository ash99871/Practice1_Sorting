
#ifndef SORTING_AVLTREE_H
#define SORTING_AVLTREE_H
#include <string>


class avlTree
{
private:
    struct Nodo {
        std::string palabra;
        Nodo* l;
        Nodo* r;
        int altura;
        Nodo(const std::string& p)
            : palabra(p), l(nullptr), r(nullptr), altura(1) {}
    };
    Nodo* raiz;

    int    altura(Nodo* n);
    int    factor(Nodo* n);
    void   nuevaAltura(Nodo* n);
    Nodo*  rotacionDer(Nodo* y);
    Nodo*  rotacionIzq(Nodo* x);
    Nodo*  balancear(Nodo* n);
    Nodo*  insertar(Nodo* n, const std::string& palabra);
    void   inorden(Nodo* n);
    void   inordenLimitado(Nodo* n, int& contador);
    void   liberar(Nodo* n);


public:

    avlTree();
    ~avlTree();
    void insertar(const std::string& palabra);
    void inorden();
    void imprimirPrimeros20();

};


#endif //SORTING_AVLTREE_H
