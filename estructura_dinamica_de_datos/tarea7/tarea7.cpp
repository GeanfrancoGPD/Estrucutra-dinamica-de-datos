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
    void eliminar (string &valor, Nodo<T> *&nodo);
    bool vacio();
    bool vacioNodo(Nodo<T> *nodo);
    bool isLeaf(Nodo<T> *nodo); //Verifica si el nodo es un Hijo o un padre
    void post_orden(Nodo<T> *nodo);
    void in_orden(Nodo<T> *nodo);
    void pre_orden(Nodo<T> *nodo);

    int hijoSoltero(Nodo<T> *nodo);
    int parejasSinHijos(Nodo<T> *nodo);
    
    Nodo<T> *EncontrarSucesor(Nodo<T> *nodo);
    ~Arbol();

};

template <class T>
int Arbol<T>::hijoSoltero(Nodo<T> *nodo){
    int cont = 0 ;
    if (nodo == NULL){
        return 0;
    }

    if(nodo -> der == NULL && nodo -> medio == NULL && nodo -> izq == NULL){
        cont++;
    }
    cont += hijoSoltero(nodo -> izq);
    cont += hijoSoltero(nodo -> medio);

    return cont;
}

template <class T>
int Arbol<T>::parejasSinHijos(Nodo<T> *nodo){
    int cont = 0 ;
    if (nodo == NULL){
        return 0;
    }

    if(nodo -> der != NULL && (nodo -> medio == NULL && nodo -> izq == NULL)){
        cont++;
    }
    cont += hijoSoltero(nodo -> izq);
    cont += hijoSoltero(nodo -> medio);

    return cont;

}

template < class T>
void Arbol<T>::eliminar (string &valor, Nodo<T> *&nodo){
    if (nodo == NULL){
        return;
    }

    if (nodo -> dato == valor ){
        cout << "Eliminando..." << endl;
        if (nodo -> der == NULL && (nodo -> medio == NULL && nodo -> izq == NULL)){
            cout << "Eliminando un Nodo" << endl;
            delete nodo;
            nodo = NULL;
            return;
        }else if (nodo -> der != NULL && (nodo -> medio != NULL || nodo -> izq != NULL)){
            cout << "Eliminando a una madre" << endl;

            Nodo<T> *temp = nodo;
            nodo = nodo -> der;
            nodo -> medio = temp -> medio;
            nodo -> izq = temp -> izq;
            delete temp;
            return;

        }else if (nodo -> der != NULL && (nodo -> medio == NULL && nodo -> izq == NULL)){
            cout << "Eliminando a una esposa" << endl;

            Nodo<T> *temp = nodo;
            nodo = nodo -> der;
            delete temp;
        }
        
    }
    eliminar (valor,nodo -> izq);
    eliminar (valor,nodo -> medio);
    eliminar (valor,nodo -> der);

}



template <class T>
Arbol<T>::Arbol(){
};

template <class T>
void Arbol<T>::pre_orden(Nodo<T> *newnodo){
    
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
    string nombreEliminar;
    int count = 0;
    int nline = 0;
    int valor = 0;
    int valor2 = 0;

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
    cout << endl;
    familia.pre_orden(raizArbol);
    
    cout << " " << endl;
    cout << "Ingrese un nombre:" << endl;
    cin >> nombreEliminar;
    familia.eliminar(nombreEliminar, raizArbol);

    cout << endl;
    familia.mostrarArbol(raizArbol, 0);

    /*valor = familia.hijoSoltero(raizArbol);
    cout << "La cantidad de hijos solteros es :" << valor - 3 <<endl;
    valor2 = familia.parejasSinHijos(raizArbol);
    cout << "La cantidad de parejas sin hijos es: " << valor2 << endl;*/
    
}