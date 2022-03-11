//
// Created by danjs on 3/10/2022.
//

#ifndef SHORTHOMEWORK1_CLASSES_H
#define SHORTHOMEWORK1_CLASSES_H

#include <iostream>
#include <utility>
#include <cmath>
#include <fstream>

using namespace std;


class Nodo{
public:

    Nodo(){
        siguiente = NULL;
        datos = "";
    }

    explicit Nodo (string _datos){
        datos = _datos;
        siguiente = NULL;

    }
    explicit Nodo(string _datos, Nodo * _siguiente){
        datos = _datos;
        siguiente = _siguiente;

    }

    string getDatos(){
        return datos;
    }
    Nodo * getSiguiente(){
        return siguiente;
    }

private:
    string datos;
    Nodo * siguiente;


    friend class ListaSimple;
    friend class Cola;
    friend class Pila;
};


typedef Nodo * nodo;




class ListaSimple{

public:
    ListaSimple() { primero = NULL;};
    explicit ListaSimple(Nodo *& _primero){ primero = _primero;};
    ~ListaSimple();



    Nodo * getPrimero(){
        Nodo * referencia = primero;
        return referencia;

    };
    void setPrimero(Nodo * _primero){primero = _primero; };
    void mostrar();
    void insertarInicio(string _datos);
    bool vacia();
    int largoLista();
    void insertarFinal(string _datos);
    ListaSimple generarListaExpPost();
    double evaluarListaExpPost();


private:
    nodo primero;


    friend class Cola;
};



class Cola{


public:
    Cola(){

        frente = 0;
        fondo = -1;
        for (int i = 0; i < 5 ; i++){
            cola[i] = new Nodo();
        }

    }

    bool vacia();
    void insertar(nodo _nodo);
    void eliminar();
    void imprimir();
    void resultados();


private:
    int frente;
    int fondo;
    nodo cola[5]{};

};






class Pila{
public:
    Pila(){
        tope = NULL;
    }


    void push (string dato);
    Nodo * pop (void);
    Nodo * peek(void);
    bool empty(void);
    void imprimir(void);

private:
    nodo tope;

};

class NodoOperadores{
public:
    NodoOperadores(){
        valorFueraCola = 0;
        valorDentroCola = 0;
        operador = "";
        siguiente = NULL;
    }

    explicit NodoOperadores(int _valorFueraCola, int _valorDentroCola, string _operador);


private:
    int valorFueraCola;
    int valorDentroCola;
    string operador;
    NodoOperadores * siguiente;

    friend class ListaOperadores;
};

typedef NodoOperadores * nodooperadores;


class ListaOperadores{
public:
    ListaOperadores(){
        operadores[0] = new NodoOperadores(5,0, "(");
        operadores[1] = new NodoOperadores(1,1, "+");
        operadores[2] = new NodoOperadores(1,1, "-");
        operadores[3] = new NodoOperadores(2,2, "*");
        operadores[4] = new NodoOperadores(2,2, "/");
        operadores[5] = new NodoOperadores(4,3, "^");

    }

    bool compararOperadores(string operadorFC, string operadorDC);
    bool esOperador(string operadorE);


private:
    nodooperadores operadores[6] {};


};




Nodo * archivoALista(string nombreArchivo);
void archivoAList(string nombreArchivo);











#endif //SHORTHOMEWORK1_CLASSES_H
