#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
struct Persona{
    string nombre;
    string papa;
    string hijo1;
    string hijo2;
};

template <class T>
struct Nodo{
    string dato;
    Nodo<T> *der;
    Nodo<T> *medio;
    Nodo<T> *izq;
};

template <class T>
class Arbol{
    private:
    Nodo<T> *raiz = NULL;
    Nodo<T> *NodoABuscar = NULL;

    public:
    Arbol();
    void insertar(T valor, Nodo<T> *&nodo);
    Nodo<T> *regresarAraiz();
    void mostrarArbol(Nodo<T> *newnodo, int espacio);
    void eliminar (T &valor, Nodo<T> *&nodo);
    bool vacio();
    bool vacioNodo(Nodo<T> *nodo);
    bool isLeaf(Nodo<T> *nodo); //Verifica si el nodo es un Hijo o un padre
    void post_orden(Nodo<T> *nodo);
    void in_orden(Nodo<T> *nodo);
    void pre_orden(Nodo<T> *nodo);
    
    Nodo<T> *EncontrarMadre(Nodo<T> *newnodo, T P);
    Nodo<T> *EncontrarSucesor(Nodo<T> *nodo);
    ~Arbol();

};

template <class T>
Arbol<T>::Arbol(){
};

template <class T>
void Arbol<T>::pre_orden(Nodo<T> *newnodo){
    int lista = 0;
    if(newnodo == NULL){
        return ;
    }else{
        cout << newnodo -> dato << " ";
        pre_orden(newnodo-> izq);
        pre_orden(newnodo-> medio);
        pre_orden(newnodo-> der);
    }

}

template <class T>
void Arbol<T>::in_orden(Nodo<T> *newnodo) {
    if(newnodo) {
        in_orden(newnodo->izq);
        std::cout << newnodo->dato << " ";
        pre_orden(newnodo-> medio);
        in_orden(newnodo->der);
    }
}

template <class T>
void Arbol<T>::post_orden(Nodo<T> *newnodo) {
    if (newnodo) {
        post_orden(newnodo->izq);
        pre_orden(newnodo-> medio);
        post_orden(newnodo->der);
        std::cout << newnodo->dato << " ";
    }
}

template <class T>
Nodo<T> *Arbol<T>::regresarAraiz(){
    return raiz;
}

template <class T>
Nodo<T> *Arbol<T>::EncontrarMadre(Nodo<T> *newnodo, T P){
    if (newnodo == NULL){
        return NULL;
    }

    if (P.nombre == newnodo -> der -> dato){
        return newnodo;
    }

    Nodo<T> *madreHijoMedio = EncontrarMadre(newnodo -> medio, P);
    if (madreHijoMedio != NULL){
        return madreHijoMedio;
    }

    return EncontrarMadre(newnodo -> izq, P);
};
template <class T>
void Arbol<T>::mostrarArbol(Nodo<T> *newnodo, int espacio) {
    if (newnodo == NULL) {
        return;
    }

    // Incrementar el espacio entre niveles
    espacio += 9;

    // Mostrar el nodo derecho
    mostrarArbol(newnodo->der, espacio);

    // Imprimir el espacio
    cout << endl;
    for (int i = 3; i < espacio; i++) {
        cout << " ";
    }

    // Mostrar el nodo actual
    cout << newnodo->dato << endl;

    // Mostrar el nodo medio
    mostrarArbol(newnodo->medio, espacio);

    // Mostrar el nodo izquierdo
    mostrarArbol(newnodo->izq, espacio);
};

template <class T>
void Arbol<T>::insertar(T P, Nodo<T> *&newnodo){
    int cont = 0;
    if (newnodo == NULL){
        newnodo = new Nodo<T>();
        newnodo -> dato = P.nombre;

        newnodo -> der = new Nodo <T> ();
        newnodo -> der -> dato = P.papa;

        newnodo -> medio = new Nodo<T>();
        newnodo -> medio -> dato = P.hijo2;

        newnodo -> izq = new Nodo<T>();
        newnodo -> izq -> dato = P.hijo1;
      
    }else if(P.nombre == newnodo -> medio -> dato || P.papa == newnodo -> medio -> dato ){
        newnodo -> medio = NULL;
        insertar(P, newnodo -> medio);

    }else if(P.nombre == newnodo -> izq -> dato || P.papa == newnodo -> izq -> dato ){
        newnodo -> izq = NULL;
        insertar(P, newnodo -> izq);
    }else if (cont == 0){
        cont ++;
        insertar(P, newnodo -> medio);
    }else if (cont == 1 ){
        insertar(P, newnodo -> izq);
    }
}

template <class T>
Arbol<T>::~Arbol(){

};

int main (){
    Arbol <Persona<string>> familia;
    Nodo<Persona<string>> *raizArbol = NULL;

    Persona<string> mujer[10];
    fstream infile;

    string line,word;
    int count = 0;
    int nline = 0;

    infile.open("../familia.txt");

    if(!infile){
        cout << "No se encontro el archivo" << endl;
    }

    while (getline(infile,line)){
        stringstream str(line);

        while(getline (str,word,';')){

            switch(count){
                case 0:
                    mujer[nline].nombre = word;
                break;

                case 1:
                    mujer[nline].papa = word;
                break;

                case 2:
                    mujer[nline].hijo1 = word;
                break;

                case 3:
                    mujer[nline].hijo2 = word;
                break;
            };
            
            count ++; 
        }
        count = 0;
        nline++;
        
    }
    
    familia.insertar(mujer[0], raizArbol);
    familia.insertar(mujer[1], raizArbol);
    familia.insertar(mujer[2], raizArbol);
    familia.insertar(mujer[3], raizArbol);
    
    familia.mostrarArbol(raizArbol, 0);
    familia.pre_orden(raizArbol);
    
}