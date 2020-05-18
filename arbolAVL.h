/*
    * Integrantes del equipo *
    * Batres Pedroza Alejandro          201836943
    * Garcia Gonzalez Jorge             201847512
    * Mendez Mendez Sebastian           201836190
    * Segura Cuanalo Ricardo Alejandro  201848777

	El objetivo de esta practica es ver y entender el comportamiento de un arbol AVL, aplicando
	los 4 tipos de rotaciones que aprendimos de la bibliografia, para poder balancearlo.

	En este archivo se define la clase ArbolAVL con algunos metodos como:
	void __insertar__(Vertice * raiz, Vertice * nuevo):: insertar nuevo nodo, al insertar se balancea
    void rotacion_derecha(Vertice * raiz):: Rotacion derecha (comprobacion)
    void rotacion_izquierda(Vertice * raiz);:: (comprobacion) 
    void rotacion_derecha(Vertice * raiz, Vertice * hijoDer) :: (ejecucion)
    void rotacion_izquierda(Vertice * raiz, Vertice * hijoIzq);(ejecucion)
    void rotacion_doble_izquierda(Vertice * raiz):: (comprobacion)
    void rotacion_doble_derecha(Vertice * raiz):: (comprobacion)
    void rotacion_doble_izquierda(Vertice * raiz, Vertice * hijoIzq)::  (ejecucion)
    void rotacion_doble_derecha(Vertice * raiz, Vertice * hijoDer):: (ejecucion)
    void equilibrar_subarbol(Vertice * raiz):: se llaman algunos metodos ya mencionados
    int factor_de_equilibrio(Vertice * hijoIzq, Vertice * hijoDer) :: se calcula el Fe dado un nodo raiz
*/


#include "arbol.h"
#include "testing.h"
class ArbolAVL : public Arbol{
    public:
    ArbolAVL() : Arbol(){}
    void insertar(int dato);
    
    void __insertar__(Vertice * raiz, Vertice * nuevo);
    
    void rotacion_derecha(Vertice * raiz);
    void rotacion_izquierda(Vertice * raiz);
    void rotacion_derecha(Vertice * raiz, Vertice * hijoDer);
    void rotacion_izquierda(Vertice * raiz, Vertice * hijoIzq);
    void rotacion_doble_izquierda(Vertice * raiz);
    void rotacion_doble_derecha(Vertice * raiz);
    void rotacion_doble_izquierda(Vertice * raiz, Vertice * hijoIzq);
    void rotacion_doble_derecha(Vertice * raiz, Vertice * hijoDer);
    
    bool eliminar(int dato);
    void __eliminar__(Vertice * padre, Vertice * nodo);
    // metodos para probar la clase
    void borrar();
    void test();
    void factores_de_equilibrio(Vertice * r);
    void test_hardcore(ArbolAVL * a, int * vector, int n, bool porPasos);


    protected:
    void equilibrar_subarbol(Vertice * raiz);
    int factor_de_equilibrio(Vertice * raiz);
    int factor_de_equilibrio(Vertice * hijoIzq, Vertice * hijoDer);
};

// elimina un elemento del arbol AVL
bool ArbolAVL::eliminar(int dato){
    Vertice * _padre = padre(dato);
    require(_padre != NULL, 
        "El padre de " + to_string(dato) + " no se encontro en el arbol");
    Vertice * nodo = dato > _padre->dato ? (obtener_hijos(_padre))[1] : (obtener_hijos(_padre))[0];
    if(nodo == NULL) return false;
    __eliminar__(_padre, nodo);
    return true;
}
// elimina un elemento de un arbol AVL
void ArbolAVL::__eliminar__(Vertice * padre, Vertice * nodo){
    // obtener el vertice mayor del subarbol izquierdo del nodo
    Vertice * remplazo = nodo;
    Vertice ** hijos = obtener_hijos(nodo);
    
    

}


// borra todo el arbol
void ArbolAVL::borrar(){
    while(!vertices.vacia())
        vertices.suprimir_final();
}

// imprime los factores de equilibrio
void ArbolAVL::factores_de_equilibrio(Vertice * raiz){
    if(raiz != NULL){
        cu::test("Fe("+raiz->nombre+") = " + to_string(factor_de_equilibrio(raiz)));
        Vertice ** hijos = obtener_hijos(raiz);
        factores_de_equilibrio(hijos[0]);
        factores_de_equilibrio(hijos[1]);
    }
}


void ArbolAVL::test_hardcore(ArbolAVL * a, int * vector, int n, bool porPasos){
    int i = 0;
    if(porPasos)
        do{
            cu::test("Insertar " + to_string(vector[i]));
            getchar();
            a->insertar(vector[i]);
            a->mostrar(cout);
            a->factores_de_equilibrio(a->vertices.primero());
            i++;
        } while(i < n);
    else{
        for(int i = 0; i < n; i++)
            a->insertar(vector[i]);
        a->mostrar(cout);
    }
}


void ArbolAVL::test(){
    ArbolAVL * a = new ArbolAVL;

    int datos[] = {1,2,3,4,5,6,7};
    int n = 7;
    
    int d[] = {1,99,80,70,71,72,3};
    test_hardcore(a, d, 7, true);
    
    a->borrar();
    // test hardcore
    int muchos[] = {3,4,6,1,32,5,9,0,1,56,31,76,45,16,39,67,90};
    test_hardcore(a, muchos, 18, true);
    
}


// Rota a la derecha * raiz
void ArbolAVL::rotacion_derecha(Vertice * raiz){
    require(raiz != NULL, 
        "No se puede efectuar una rotacion en un vertice NULL");
    Vertice ** hijos = obtener_hijos(raiz);
    Vertice * izq = hijos[0], * der = hijos[1];
    require(der != NULL,
        "No se puede efectuar una rotacion a la derecha en un vertice sin hijo derecho");
    rotacion_derecha(raiz, der);
}

// Rota a la derecha * raiz
// hijoDer debe ser el hjo derecho de raiz 
void ArbolAVL::rotacion_derecha(Vertice * raiz, Vertice * hijoDer){
    require(raiz != NULL,"La raiz no puede ser NULL, ArbolAVL::rotacion_derecha(Vertice * raiz, Vertice * hijoDer)");
    require(raiz->adyacente->existe(hijoDer),"hijoDer (" + hijoDer->nombre +") no es un hijo de raiz (" + raiz->nombre +"), ArbolAVL::rotacion_derecha(Vertice * raiz, Vertice * hijoDer)");
    // si el vertice raiz es la raiz del arbol
    if(vertices.primero() == raiz){
        // mover al inicio de la lista de vertices el hijo derecho de la raiz
        // eliminar de la lista al hijo derecho temporalmente
        vertices.suprimir(hijoDer);
        // insertar al inicio
        vertices.insertar_inicio(hijoDer);
    } else {
        // si no es la raiz del arbol entonces se debera buscar
        // su padre para eliminar * raiz y colocar el hijo derecho de 
        // la raiz en su lugar
        Vertice * _padre = padre(raiz);
        require(_padre != NULL,"El vertice raiz no existe en el arbol, ArbolAVL::rotacion_derecha");
        _padre->adyacente->suprimir(raiz);
        _padre->adyacente->insertar_final(hijoDer);
        
    }

    //       raiz 
    //          \
    //           B
    //          /
    //         A
    // A = hijo izquierdo del hijo derecho la la raiz
    // B = hijo derecho de la raiz
    // borrar B de los hijos de la raiz
    raiz->adyacente->suprimir(hijoDer);
    // obtener los hijos de B
    Vertice ** hijosDer = obtener_hijos(hijoDer);
    Vertice * A = hijosDer[0], * B = hijoDer;
    // si B tiene un hijo izquierdo A
    if(A != NULL){
        // eliminar A de los hijos de B
        B->adyacente->suprimir(A);
        // hacer A el hijo derecho de la raiz
        raiz->adyacente->insertar_final(A);
    }
        
    // hacer la raiz el hijo izquierdo de B
    B->adyacente->insertar_final(raiz);
}

// Rota a la izquierda * raiz
void ArbolAVL::rotacion_izquierda(Vertice * raiz){
    require(raiz != NULL, 
            "No se puede efectuar una rotacion en un vertice NULL");
    Vertice ** hijos = obtener_hijos(raiz);
    Vertice * izq = hijos[0], * der = hijos[1];
    require(izq != NULL,
        "No se puede efectuar una rotacion a la izquierda en un vertice sin hijo izq");
    rotacion_izquierda(raiz, izq);
}

// Rota a la izquierda * raiz
// izq debe ser el hijo izquierdo de raiz 
void ArbolAVL::rotacion_izquierda(Vertice * raiz, Vertice * izq){
    // si el vertice raiz es la raiz del arbol
    if(vertices.primero() == raiz){
        // mover al inicio de la lista de vertices el hijo izquierdo de la raiz
        // eliminar de la lista al hijo izquierdo temporalmente
        vertices.suprimir(izq);
        // insertar al inicio
        vertices.insertar_inicio(izq);
        
    } else {
        // si no es la raiz del arbol entonces se debera buscar
        // su padre para eliminar * raiz y colocar el hijo izquierdo de 
        // la raiz en su lugar
        Vertice * _padre = padre(raiz);
        require(_padre != NULL,
            "El vertice raiz no existe en el arbol, ArbolAVL::rotacion_derecha");
        _padre->adyacente->suprimir(raiz);
        _padre->adyacente->insertar_inicio(izq);
    }

    //       raiz 
    //       /  
    //      B
    //     / \
    //    C   A
    // A = hijo derecho del hijo izquierdo la la raiz
    // B = hijo izquierdo de la raiz
    // borrar B de los hijos de la raiz
    raiz->adyacente->suprimir(izq);
    // obtener los hijos de B
    Vertice ** hijosIzq = obtener_hijos(izq);
    Vertice * A = hijosIzq[1], * B = izq;
    // si B tiene un hijo derecho A
    if(A != NULL){
        // eliminar A de los hijos de B
        B->adyacente->suprimir(A);
        // hacer A el hijo izquierdo de la raiz
        raiz->adyacente->insertar_final(A);
    }
    
    // hacer la raiz el hijo derecho de B
    B->adyacente->insertar_final(raiz);

}

void ArbolAVL::rotacion_doble_derecha(Vertice * raiz){
    Vertice ** hijos = obtener_hijos(raiz);
    rotacion_doble_derecha(raiz, hijos[0]);
}

void ArbolAVL::rotacion_doble_izquierda(Vertice * raiz){
    Vertice ** hijos = obtener_hijos(raiz);
    rotacion_doble_izquierda(raiz, hijos[1]);
}

// cuidado!
// *hijoIzq debe ser el hijo izquierdo de la raiz
// es mejor usar el metodo void ArbolAVL::rotacion_doble_izquierda();
// si no se esta seguro de un posible error
void ArbolAVL::rotacion_doble_derecha(Vertice * raiz, Vertice * hijoIzq){
    require(raiz != NULL && hijoIzq != NULL, 
        "*raiz y *hijoIzq deben ser distintos de NULL, ArbolAVL::rotacion_doble_izquierda");
    // Se aplica cuando el arbol apuntado por raiz esta cargado a la izquierda
    // y ademas el hijo izquierdo esta cargado a la derecha
    //         raiz
    //        /    
    //       A
    //        \
    //         B
    //          \   
    //           C
    // rotacion a la izquierda sobre A(hijoIzq):
    rotacion_derecha(hijoIzq);
    // rotacion a la derecha sobre raiz
    rotacion_izquierda(raiz);
}

// cuidado!
// *hijoDer debe ser el hijo derecho de la raiz
// es mejor usar el metodo void ArbolAVL::rotacion_doble_derecha();
// si no se esta seguro de un posible error
void ArbolAVL::rotacion_doble_izquierda(Vertice * raiz, Vertice * hijoDer){
    require(raiz != NULL && hijoDer != NULL, 
        "*raiz y *hijoDer deben ser distintos de NULL, ArbolAVL::rotacion_doble_izquierda");
    // Se aplica cuando el arbol apuntado por raiz esta cargado a la derecha
    // y ademas el hijo derecho esta cargado a la izquierda
    //         raiz
    //             \   
    //              A
    //             /
    //            B
    //           / 
    //          C
    // rotacion a la derecha sobre A(hijoDer):
    rotacion_izquierda(hijoDer);
    // rotacion a la izquierda sobre raiz
    rotacion_derecha(raiz);
}

void ArbolAVL::insertar(int dato){
    Vertice * nuevo = new Vertice(to_string(dato), dato);
    vertices.insertar_final(nuevo);
    if(vertices.tamanio() == 1) return;
    __insertar__(vertices.primero(), nuevo);
}

void ArbolAVL::__insertar__(Vertice * raiz, Vertice * nuevo){
    Vertice ** hijos = obtener_hijos(raiz);
    
    if(raiz->dato <= nuevo->dato){
        if(hijos[1] == NULL)
            raiz->adyacente->insertar_final(nuevo);
        else 
            __insertar__(hijos[1], nuevo);
    } else {
        if(hijos[0] == NULL)
            raiz->adyacente->insertar_final(nuevo);
        else
            __insertar__(hijos[0], nuevo);
    }
    equilibrar_subarbol(raiz);
}

void ArbolAVL::equilibrar_subarbol(Vertice * raiz){
    Vertice ** hijos = obtener_hijos(raiz);

    int fe = factor_de_equilibrio(hijos[0], hijos[1]);
    if(fe > -2 && fe < 2) return;
    
    // si esta cargado a la derecha
    if(fe == 2){
        // si el subarbol derecho esta cargado a la izquierda
        if(factor_de_equilibrio(hijos[1]) < 0){
            rotacion_doble_izquierda(raiz);
        }
        else{
            rotacion_derecha(raiz);
        }
    } // si esta cargado a la izquierda
    else if(fe == -2){
        // si el subarbol izquierdo esta cargado a la derecha
        if(factor_de_equilibrio(hijos[0]) > 0)
            rotacion_doble_derecha(raiz);
        else
            rotacion_izquierda(raiz);
    }
    
}

// retorna el factor de equilibrio de un arbol pasando su
// raiz como argumento
int ArbolAVL::factor_de_equilibrio(Vertice * raiz){
    if(raiz == NULL) return 0;
    Vertice ** hijos = obtener_hijos(raiz);
    return factor_de_equilibrio(hijos[0], hijos[1]);
}

// retorna el factor de equilibrio de un arbol, pasando sus hijos como
// argumentos 
int ArbolAVL::factor_de_equilibrio(Vertice * hijoIzq, Vertice * hijoDer){
    return altura(hijoDer) - altura(hijoIzq);
}

