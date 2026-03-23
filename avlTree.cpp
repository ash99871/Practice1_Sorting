#include "avlTree.h"
#include <algorithm>
#include <iostream>
using namespace std;

avlTree::avlTree() : raiz(nullptr) {}

avlTree::~avlTree() {
    liberar(raiz);
}

int avlTree::altura(Nodo *n) {
    if (n)
        return n ->altura;
    else
        return 0;
}

int avlTree::factor(Nodo *n) {
    if (n)
        return altura (n -> l) - altura(n -> r);
    else
        return 0;
}

void avlTree::nuevaAltura(Nodo *n) {
    n->altura = 1 + max(altura(n->l), altura(n->r));
}

avlTree::Nodo *avlTree::rotacionDer(Nodo *y) {
    Nodo* x = y->l;
    Nodo* z = x->r;

    x->r = y;
    y->l = z;

    nuevaAltura(y);
    nuevaAltura(x);
    return x;
}

avlTree::Nodo *avlTree::rotacionIzq(Nodo *x) {
    Nodo* y = x->r;
    Nodo* z = y->l;
    y->l = x;
    x->r = z;

    nuevaAltura(x);
    nuevaAltura(y);
    return y;
}

avlTree::Nodo *avlTree::balancear(Nodo *n) {
    nuevaAltura(n);
    int a= factor(n);

    if (a>1 && factor(n->l) >= 0)
        return rotacionDer(n);

    if (a>1 && factor(n->l) <0) {
        n->l = rotacionIzq(n->l);
        return rotacionDer(n);
    }

    if (a < -1 && factor(n->r) <= 0)
        return rotacionIzq(n);

    if (a < -1 && factor(n->r) >0) {
        n->r= rotacionDer(n->r);
        return rotacionIzq(n);
    }

    return n;
}

avlTree::Nodo* avlTree::insertar(Nodo* n, const string& palabra) {
    if(!n) return new Nodo(palabra);
    if (palabra < n->palabra)
        n -> l = insertar(n -> l, palabra);
    else if (palabra > n->palabra)
        n->r= insertar(n -> r, palabra);
    else
        return n;

    return balancear(n);
}

void avlTree::inorden(Nodo* n) {
    if (!n) return;
    inorden(n->l);
    inorden(n->r);
}

void avlTree::liberar(Nodo* n) {
    if (!n) return;
    liberar(n->l);
    liberar(n->r);
    delete n;

}

void avlTree::insertar(const std::string &palabra) {
    raiz = insertar(raiz, palabra);
}

void avlTree::inorden() {
    inorden(raiz);
}

void avlTree::inordenLimitado(Nodo* n, int& i) {
    if (!n || i >= 20) return;

    inordenLimitado(n->l, i);

    if (i < 20) {
        cout << n->palabra << endl;
        i++;
    }

    inordenLimitado(n->r, i);
}

void avlTree::imprimirPrimeros20() {
    int c = 0;
    inordenLimitado(raiz, c);
}
