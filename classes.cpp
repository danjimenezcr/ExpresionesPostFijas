//
// Created by danjs on 3/10/2022.
//

#include "classes.h"


ListaSimple::~ListaSimple() {

    nodo aux;

    while(primero){
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }

}

void ListaSimple::mostrar() {

    nodo temp;

    if (primero != NULL){
        temp = primero;

        while(temp){

            cout << temp->datos << " -> ";
            temp = temp->siguiente;
        }
        cout << endl;

    } else{
        cout << "***** Atencion: No hay elementos *****" << endl;
    }



}

int ListaSimple::largoLista() {
    int contador = 0;

    nodo auxiliar;

    if(!vacia()){
        while(auxiliar !=  NULL){
            auxiliar = auxiliar->siguiente;
            contador++;
        }
    } else{
        return contador;
    }

    return contador;

}

bool ListaSimple::vacia() {
    return primero == NULL;
}

void ListaSimple::insertarInicio(string _datos) {
    if (vacia())
        primero = new Nodo(_datos);
    else
        primero = new Nodo (_datos,primero);

}

void ListaSimple::insertarFinal(string _datos) {
    if (vacia()) primero = new Nodo(_datos);
    else{
        nodo auxiliar = primero;
        while ( auxiliar->siguiente != NULL) {
            auxiliar = auxiliar->siguiente;
        }

        auxiliar->siguiente = new Nodo(_datos);
    }
}

bool Cola::vacia() {
    return fondo < frente;

}

void Cola::insertar(nodo _nodo) {

    if(fondo <= 4){
        fondo++;
        cola[fondo] = _nodo;
    }
    else{
        cout<< "***** Atencion: La cola esta llena ******";
    }

}

void Cola::eliminar() {

    if(!vacia()){
        frente++;
    }
    else{
        cout << "***** Atencion: La cola esta vacia *****" << endl;
    }

}

void Cola::resultados() {
    string nombres[5];

    nombres[0] = R"(C:\Users\danjs\Documents\2022 - I Semester\Datos\Homework\ShortHomework1\Arch1.txt)";
    nombres[1] = R"(C:\Users\danjs\Documents\2022 - I Semester\Datos\Homework\ShortHomework1\Arch2.txt)";
    nombres[2] = R"(C:\Users\danjs\Documents\2022 - I Semester\Datos\Homework\ShortHomework1\Arch3.txt)";
    nombres[3] = R"(C:\Users\danjs\Documents\2022 - I Semester\Datos\Homework\ShortHomework1\Arch4.txt)";
    nombres[4] = R"(C:\Users\danjs\Documents\2022 - I Semester\Datos\Homework\ShortHomework1\Arch5.txt)";

    cout << "--------------------------------------------------------------------------" << endl;
    for (int i = 0; i < 5; i++){

        ListaSimple temp;
        ifstream archivo(nombres[i].c_str());
        string linea;

        if(archivo.fail()){
            cout<<"No se pudo abrir el archivo";
            exit(1);
        }

        while(getline(archivo,linea)){
            temp.insertarFinal(linea);
        }
        cola[i] = temp.getPrimero();

        cout << "La lista de la expresion infija es: ";
        temp.mostrar();

        cout << "La lista de la expresion postfija es: ";
        temp.generarListaExpPost().mostrar();


        double resultado;
        resultado = temp.generarListaExpPost().evaluarListaExpPost();
        cout << "EL resultado de evaluar la expresion postFija es: " << resultado << endl;

        cout << "---------------------------------------------------------------------" << endl;


        archivo.close();


    }

}

void Cola::imprimir() {
    for (int i = frente; i < fondo + 1 ; i++ ){
        cout << cola[i]->getDatos() << " -> " ;
    }

    cout<< endl;

}


ListaSimple ListaSimple::generarListaExpPost(){
    ListaSimple resultado;
    Pila temp;
    ListaOperadores operadores;
    nodo aux = primero;


    while(aux != NULL){
        if (operadores.esOperador(aux->datos)){
            if (!temp.empty()){
                if (operadores.compararOperadores(aux->datos, temp.peek()->datos)){
                    temp.push(aux->datos);
                    aux = aux->siguiente;
                } else{
                    resultado.insertarFinal(temp.pop()->datos);
                    temp.push(aux->datos);
                    aux = aux->siguiente;
                }
            }else{
                temp.push(aux->datos);
                aux = aux->siguiente;
            }
        } else if (aux->datos == ")"){
            while(temp.peek()->datos != "("){
                resultado.insertarFinal(temp.pop()->datos);
            }
            temp.pop();
            aux = aux->siguiente;

        } else{
            resultado.insertarFinal(aux->datos);
            aux = aux->siguiente;
        }
    }

    while(!temp.empty()){
        resultado.insertarFinal(temp.pop()->datos);
    }

    return resultado;


}


double ListaSimple::evaluarListaExpPost(){
    double resultado;
    nodo aux = primero;
    Pila temp;
    double num1;
    double num2;
    double resTemp;



    while( aux != NULL ){

        if(aux->datos == "-"){
            num2 = stod(temp.pop()->datos);// 4
            num1 = stod(temp.pop()->datos); // 15
            resTemp = num1 - num2;

            temp.push(to_string(resTemp)); // 11
            aux = aux->siguiente;

        } else if(aux->datos == "+"){
            num2 = stod(temp.pop()->datos);
            num1 = stod(temp.pop()->datos);
            resTemp = num1 + num2;

            temp.push(to_string(resTemp));
            aux = aux->siguiente;

        } else if(aux->datos == "*"){
            num2 = stod(temp.pop()->datos);
            num1 = stod(temp.pop()->datos);
            resTemp = num1 * num2;

            temp.push(to_string(resTemp));
            aux = aux->siguiente;

        }else if(aux->datos == "/"){
            num2 = stod(temp.pop()->datos);
            num1 = stod(temp.pop()->datos);
            resTemp = num1 / num2;

            temp.push(to_string(resTemp));
            aux = aux->siguiente;

        }else if(aux->datos == "^"){
            num2 = stod(temp.pop()->datos);
            num1 = stod(temp.pop()->datos);
            resTemp = pow(num1, num2);

            temp.push(to_string(resTemp));
            aux = aux->siguiente;

        } else{
            temp.push(aux->datos);
            aux = aux->siguiente;

        }




    }

    resultado = stod(temp.pop()->datos);



    return resultado;


}


NodoOperadores::NodoOperadores(int _valorFueraCola, int _valorDentroCola, string _operador) {
    valorDentroCola = _valorDentroCola;
    valorFueraCola = _valorFueraCola;
    operador = _operador;
}

bool ListaOperadores::compararOperadores(string operadorFC, string operadorDC) {
    int respuesta = true; // Tres posibles valores 0 indica que es menos, 1 que es mayor y 2 que es igual
    int posicionFC;
    int posicionDC;


    for (int i = 0; i < 6; i++){
        if( operadores[i]->operador == operadorDC ){
            posicionDC = i;
        }
        if (operadores[i]->operador == operadorFC){
            posicionFC = i;
        }
    }

    if (posicionFC != 0 && posicionDC != 0){
        if(operadores[posicionFC]->valorFueraCola > operadores[posicionDC]->valorDentroCola) {
            respuesta = true;
        } else if(operadores[posicionFC]->valorFueraCola <= operadores[posicionDC]->valorDentroCola){
            respuesta = false;
        }
    }



    return respuesta;
}

bool ListaOperadores::esOperador(string operadorE) {

    for (int i = 0; i < 6; i++){
        if(operadores[i]->operador == operadorE){
            return true;
        }
    }

    return false;
}



void Pila::push (string dato)
{
    // si no hay elementos
    if (empty ())
    {
        // ambos apuntan al nuevo en memoria
        tope = new Nodo(dato);
    }
    else
    {
        Nodo *nuevo = new Nodo(dato);
        // a lo que apunta pN ahora es el segundo
        // por eso, nuevo->siguiente es pN
        nuevo->siguiente = tope;
        // ahora devolvemos pN a que apunte al nuevo
        // y primero de las lista
        tope = nuevo;
        // el puntero nuevo deja de existir, no se libera
        // memoria porque se pierde la info
    }
}

// funcion que elimina el primer elemento de las lista
// entradas: no tiene
// salidas: el puntero al primer nodo. Este puntero
// en siguiente apuntara a null. No se libera memoria

Nodo * Pila::pop(void)
{
    // si no hay elementos, no borra nada, retorna null
    if (empty())
    {
        return NULL;
    }
    else
    {
        // un puntero que apunta al nodo que se
        // "despegara" de la lista y se retorna
        Nodo* borrado = tope;
        // pN se pasa al segundo de la lista
        // porque el primero se eliminara
        tope = tope->siguiente;
        // el nodo borrado, se debe despegar
        // entonces siguiente apunta a null y no
        // al segundo de la lista que ahora es pN
        borrado->siguiente = NULL;
        // aca se deberia liberar la memoria si no se
        // retornara el borrado
        return borrado;
    }
}

bool Pila::empty (void)
{
    if (tope == NULL)
        return true;
    else
        return false;
}

void Pila::imprimir(void)
{
    cout << "tope" << endl;
    // puntero temporal que avanza
    // por toda la lista
    // apunta a los mismo que pN
    Nodo *tmp = tope;

    // mientras tmp no sea nulo, avanza
    while (tmp != NULL)
    {
        // imprime el dato del nodo en el que esta tmp
        cout << tmp->datos << "  " << endl;
        // tmp avanza al siguiente nodo
        // esto no puede faltar porque se encicla
        tmp = tmp->siguiente;
    }
    cout << "fondo" << endl;
}

Nodo * Pila::peek()
{
    return tope;
}



//Pasa el archivo a una lista
Nodo * archivoALista(string nombreArchivo){
    ifstream archivo(nombreArchivo.c_str());
    string linea;

    //Verifica que se abra el archivo
    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    //Crea una lista para guardar los elementos del archivo
    ListaSimple L1;

    //Recorre linea por linea el archivo
    while(getline(archivo,linea)){
        //Guarda en lista
        L1.insertarFinal(linea);

    }

    //Muestra la lista
    Nodo * ref = L1.getPrimero();
    return ref;
}
void archivoAList(string nombreArchivo){
    Cola colaCompleta;
    string nombres[5];

    nombres[0] = R"(C:\Users\danjs\Documents\2022 - I Semester\Datos\Homework\ShortHomework1\Arch1.txt)";
    nombres[1] = R"(C:\Users\danjs\Documents\2022 - I Semester\Datos\Homework\ShortHomework1\Arch2.txt)";
    nombres[2] = R"(C:\Users\danjs\Documents\2022 - I Semester\Datos\Homework\ShortHomework1\Arch3.txt)";
    nombres[3] = R"(C:\Users\danjs\Documents\2022 - I Semester\Datos\Homework\ShortHomework1\Arch4.txt)";
    nombres[4] = R"(C:\Users\danjs\Documents\2022 - I Semester\Datos\Homework\ShortHomework1\Arch5.txt)";

    ifstream archivo(nombreArchivo.c_str());
    string linea;

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    ListaSimple L1;

    while(getline(archivo,linea)){
        //Guarda en lista
        L1.insertarFinal(linea);

    }


    //Muestra la lista
    L1.mostrar();


}
