#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
struct Persona{
    string nombre;
    string genero;
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
    string hijo1;
    string hijo2;
    string genero;
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
    void mostrarPlantilla(Nodo<T> *nodo, int nivel);

    //para que diferencie los nombres entre masculino y femenino
    string asignarGenero(string nombre);

    int hijoSoltero(Nodo<T> *nodo);
    int parejasSinHijos(Nodo<T> *nodo);
    
    Nodo<T> *EncontrarSucesor(Nodo<T> *nodo, T P);
    ~Arbol();

};

template <class T>
string Arbol<T>::asignarGenero(string nombre){
    string terminacion = nombre.substr(nombre.length() - 2); // obtiene las 2 ultimas letras de un nombre

    if(terminacion == "ra" || terminacion == "el" || terminacion == "ly" || terminacion == "ia" || terminacion == "ea"){
        return "femenino";
    }else if(terminacion == "am" || terminacion == "ac" || terminacion == "ro" || terminacion == "ar"){
        return "masculino";
    }else{
        return "indeterminado";
    }
}
template <class T>
void Arbol<T>::mostrarPlantilla(Nodo<T> *newnodo, int nivel){
    if (newnodo == NULL){
        return;
    }

    if (newnodo -> dato != ""){

        cout << "_____________________________" << endl;
        cout << "|Nombre: " << newnodo -> dato << "  Nivel:" << nivel << endl;
        if (newnodo -> der != NULL){
            cout << "|Esposo: " << newnodo -> der -> dato << endl;
        }else{
            cout << "|Esposo: " << "Sin valor " << endl;
        }

        if (newnodo -> hijo1 != ""){
            cout << "|Primer hijo: " << newnodo -> hijo1 << endl;
        }else{
            cout << "|Primer hijo: " << " Sin valor " << endl;
        }

        if(newnodo -> hijo2 != ""){
            cout << "|Segundo hijo: " << newnodo -> hijo2 << endl;
        }else{
            cout << "|Segundo hijo: " << " Sin valor" << endl;
        }
       
        cout << "|__________________________|" << endl;
        cout << " " << endl;
    }

    mostrarPlantilla(newnodo -> izq, nivel + 1);
    mostrarPlantilla(newnodo -> medio, nivel + 1);
    
}

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
    string genero;
    
    if (newnodo == NULL || newnodo ->dato == P.nombre ){
        newnodo = new Nodo<T>();
        newnodo -> dato = P.nombre;
        genero = asignarGenero(P.nombre);
        newnodo -> genero = genero;
        

        newnodo -> der = new Nodo <T> ();
        newnodo -> der -> dato = P.papa;
        genero = asignarGenero(P.papa);
        newnodo -> der -> genero = genero;

        newnodo -> medio = new Nodo<T>();
        newnodo -> medio -> dato = P.hijo2;
        newnodo -> hijo2 = P.hijo2;

        newnodo -> izq = new Nodo<T>();
        newnodo -> izq -> dato = P.hijo1;
        
        newnodo -> hijo1 = P.hijo1;
      
    }else if(P.nombre == newnodo -> medio -> dato || P.papa == newnodo -> medio -> dato ){
        newnodo -> medio = NULL;
        insertar(P, newnodo -> medio);

    }else if(P.nombre == newnodo -> izq -> dato || P.papa == newnodo -> izq -> dato ){
        newnodo -> izq = NULL;
        insertar(P, newnodo -> izq);
    }else{
        
        Nodo<T> *nodoBuscar = new Nodo<T>();
        nodoBuscar = EncontrarSucesor(newnodo,  P);
        genero = asignarGenero(P.nombre);
        newnodo -> genero = genero;
        
        nodoBuscar -> dato = P.nombre;
        
        nodoBuscar -> der = new Nodo <T> ();
        nodoBuscar -> der -> dato = P.papa;
        genero = asignarGenero(P.papa);
        nodoBuscar -> der -> genero = genero;

        nodoBuscar -> medio = new Nodo<T>();
        nodoBuscar -> medio -> dato = P.hijo2;
        nodoBuscar -> hijo2 = P.hijo2;

        nodoBuscar -> izq = new Nodo<T>();
        nodoBuscar -> izq -> dato = P.hijo1;

        nodoBuscar -> hijo1 = P.hijo1;

    }
}

template < class T>
Nodo<T> *Arbol<T>::EncontrarSucesor(Nodo<T> *newnodo, T P){
    if (newnodo == NULL){
        return NULL;
    }

    if(newnodo -> dato == P.nombre || newnodo -> dato == P.papa){
        return newnodo;
    }else{
        Nodo<T> *resultado = EncontrarSucesor(newnodo -> izq, P);

        if (resultado == NULL){
            resultado = EncontrarSucesor(newnodo -> medio, P);
        }

        if (resultado == NULL){
            resultado = EncontrarSucesor(newnodo -> der, P);
        }

        return resultado;
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
    int resp = 0;
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

    do{
        cout << "|                    ***menu***                       |" << endl;
        cout << "|_____________________________________________________|" << endl;
        cout << "|1- Mostrar arbol acostado | 2- Eliminar Nodo         |" << endl;
        cout << "|3- PreOrden               | 4- InOrden               |" << endl;
        cout << "|5- PostOrden              | 6- Hijos solteros        |" << endl;
        cout << "|7- Parejas sin hijos      | 8- plantilla mujeres     |" << endl;
        cout << "|9- Plantilla hombres      | 10- Salir                |" << endl;
        cout << "|_____________________________________________________|" << endl;
        cin >>  resp;
        

        switch(resp){
            case 1:
                familia.mostrarArbol(raizArbol, 0);
            break;

            case 2:
                cout << " " << endl;
                cout << "Ingrese un nombre:" << endl;
                cin >> nombreEliminar;
                familia.eliminar(nombreEliminar, raizArbol);

                cout << endl;
                familia.mostrarArbol(raizArbol, 0);

            break;

            case 3:
                cout << endl;
                familia.pre_orden(raizArbol);

            break;

            case 4:
                cout << endl;
                familia.in_orden(raizArbol);
            break;

            case 5:
                cout << endl;
                familia.post_orden(raizArbol);
            break;

            case 6:
                valor = familia.hijoSoltero(raizArbol);
                cout << "La cantidad de hijos solteros es :" << valor - 3 <<endl;
            break;

            case 7:
                valor2 = familia.parejasSinHijos(raizArbol);
                cout << "La cantidad de parejas sin hijos es: " << valor2 - 5 << endl;

            break;

            case 8:
                familia.mostrarPlantilla(raizArbol, 0);

            break;

            case 9:

            break;
        }

        system("pause");
        system("cls");
    }while (resp != 10);
    
}