#include "arbol.h"
#include "testing.h"

/*!
 * \file arbolAVL.hpp
 * @brief Cabecera de la clase ArbolAVL e implementación de sus métodos
 * 
 * Archivo de cabecera que contiene la clase ArbolAVL. Esta clase es utilizada
 * para construir árboles binarios *balanceados* los cuales se dice que están
 * *balanceados* si su **factor de equilibrio** \f$F_e = \{-1,0,1\}\f$.
 * <br>
 * Si el árbol no cuenta con dicho factor de equilibrio, es decir, \f$F_e = \{
 * -2,2\}\f$, se dice que el árbol está *desbalanceado*.
 * <br>
 * Cuando el árbol está desbalanceado, según su **tipo de desbalance**, se aplica
 * alguna de las cuatro rotaciones que se darán a continuación. Sean \f$R\f$ un
 * vértice raíz del subárbol en estudio, \f$I\f$ el hijo izquierdo de la raíz y
 * \f$D\f$ el hijo derecho de la raíz. Tenemos las siguientes rotaciones según
 * sus factores de equilibrios definidos por \f$F_e\f$:
 * - Rotación simple izquierda. Esta rotación se aplica cuando \f$F_e(R) = -2\f$
 * y \f$F_e(I) = -1\f$
 * 
 * ![Ilustración de la rotación izquierda](./img/rot_izq.png)
 * 
 * - Rotación simple derecha. Esta rotación se aplica cuando \f$F_e(R) = 2\f$
 * y \f$F_e(D) = 1\f$
 * 
 * ![Ilustración de la rotación derecha](./img/rot_der.png)
 * 
 * - Rotación doble izquierda. Esta rotación se aplica cuando \f$F_e(R) = 2\f$
 * y \f$F_e(D) = -1\f$
 * 
 * ![Ilustración de la rotación doble izquierda](./img/rot_d_izq.png)
 * 
 * - Rotación doble derecha. Esta rotación se aplica cuando \f$F_e(R) = -2\f$
 * y \f$F_e(I) = 1\f$
 * 
 * ![Ilustración de la rotación doble derecha](./img/rot_d_der.png)
 * 
 * @see ArbolAVL
 * */

/*!
 * @class ArbolAVL
 * @brief Implementación de un arbol binario que por cada inserción se corrobore
 * el balance del mismo y se pueda auto-balancear
 * 
 * Un Árbol AVL consiste en un árbol binario de búsqueda pero que cuenta con la
 * cualidad de que siempre esta equilibrado. Esto último se debe a diferentes
 * condiciones que se establecen para que el árbol se balancee en un momento
 * determinado.
 * <br>
 * La condición principal para determinar si un árbol está balanceado es observar
 * si su **factor de equilibrio** \f$F_e = \{-1,0,1\}\f$ (para más detalle, véase
 * factor_de_equilibrio(Vertice*, Vertice*)). En caso de que no se cumpla con la
 * condición mencionada anteriormente, se dice que el árbol está *desbalanceado*.
 * <br>
 * Cuando se busca balancear el árbol, se utiliza alguna de las rotaciones
 * siguientes:
 * - Rotación simple izquierda (rotacion_izquierda(Vertice*, Vertice*))
 * - Rotación simple derecha (rotacion_derecha(Vertice*, Vertice*))
 * - Rotación doble izquierda (rotacion_doble_izquierda(Vertice*, Vertice*))
 * - Rotación doble derecha (rotacion_doble_derecha(Vertice*, Vertice*))
 * 
 * Véase equilibrar_subarbol(Vertice*) para saber el momento en el que se aplica
 * una de las 4 rotaciones dadas.
 * @see factor_de_equilibrio(Vertice*, Vertice*)
 * @see equilibrar_subarbol(Vertice*)
 * */
class ArbolAVL : public Arbol{
    public:
    /*!
     * @brief Consturctor de ArbolAVL
     * */
    ArbolAVL() : Arbol(){}

    /*!
     * @brief Inserta un dato en el árbol
     * 
     * Determina si el árbol cuenta con cero o más vertices. En caso de no tener
     * vértices, simplemente inserta el vértice como si fuera la raiz, y termina
     * su ejecución. En caso contrario, llama a la función recursiva
     * "__insertar__(Vertice*, Vertice*)" para ser insertado entre los vértices
     * preexistentes.
     * @param dato valor numérico a insertar
     * @see "__insertar__(Vertice*, Vertice*)"
     * */
    void insertar(int dato);
    
    /*!
     * @brief Método recursivo para insertar un dato en el árbol
     * 
     * Inserta el vertice de la forma en que usualmente debería hacerse, buscando
     * si el valor de dicho vertice es menor o mayor o igual al vertice "subraíz"
     * en el que se encuentra. De ahí que se inserte en la izquierda/derecha, o
     * bien, se busque en el subárbol izquierdo/derecho hasta encontrar un lugar
     * vacío.
     * <br>
     * Al final de realizar la inserción del vértice, se ejecuta la función
     * equilibrar_subarbol(Vertice*). Esta realmente es la única diferencia con
     * el método de insertar entre los árboles normales y los árboles AVL.
     * 
     * Dentro de equilibrar_subarbol(Vertice*) se comparan factores de equilibrio
     * de los vértices del subárbol que solamente están contenidos en el *camino*
     * que empieza con el vértice raíz y termina con el nuevo vértice insertado.
     * Ejemplo. Supóngase el siguiente árbol
     * <br>
     * ![Árbol de ejemplo 1](./img/ex1.png)
     * <br>
     * Si suponemos que el vértice \f$d\f$ es el último se ha ingresado, entonces las
     * comparaciones se harían en el siguiente orden:
     * - Se equilibra el subárbol con raíz \f$b\f$
     * - Se equilibra el subárbol con raíz \f$a\f$
     * 
     * Nótese que, como tal, no existe un camino del vértice \f$b\f$ al vértice \f$a\f$,
     * ya que estamos hablando de que los árboles son *digrafos*. En este caso si
     * existe una relación {padre -> hijo} pero no una relación {hijo -> padre}.
     * Sin embargo, gracias a la recusrividad, es posible "seguir" este camino
     * desde el vértice hijo hasta el vértice raíz.
     * @param raiz puntero al vertice raiz del subárbol especificado
     * @param nuevo puntero al vertice nuevo que se busca insertar
     * @see equilibrar_subarbol(Vertice*)
     * */
    void __insertar__(Vertice * raiz, Vertice * nuevo);
    
    /*!
     * @brief Método preliminar para realizar la rotación derecha. Verifica que 
     * la raiz dada exista y que tenga un hijo derecho
     * 
     * Dirigirse a rotacion_derecha(Vertice *, Vertice *) para ver el
     * funcionamiento detallado
     * @param raiz puntero al vertice raiz del subárbol especificado
     * @see rotacion_derecha(Vertice *, Vertice *)
     * */
    void rotacion_derecha(Vertice * raiz);

    /*!
     * @brief Método preliminar para realizar la rotación izquierda. Verifica que 
     * la raiz dada exista y que tenga un hijo izquierdo
     * 
     * Dirigirse a rotacion_izquierda(Vertice *, Vertice *) para ver el
     * funcionamiento detallado
     * @param raiz puntero al vertice raiz del subárbol especificado
     * @see rotacion_izquierda(Vertice *, Vertice *)
     * */
    void rotacion_izquierda(Vertice * raiz);

    /*!
     * @brief Realiza la rotación derecha
     * 
     * Para la rotación derecha, se tienen que tomar los siguientes datos.
     * Dados un vertice \f$R\f$, raiz del subárbol en estudio y un vertice
     * \f$X\f$, hijo derecho de la raiz, tenemos
     * - El hijo izquierdo de \f$X\f$ ahora será el hijo derecho de \f$R\f$
     * - El vertice \f$X\f$ ahora será padre del vértice \f$R\f$, y \f$R\f$ será
     * su hijo izquierdo
     * <br>
     * ![Ilustración de la rotación derecha](./img/rot_der.png)
     * @param raiz puntero al vertice raiz del subárbol especificado
     * @param hijoDer puntero al vertice del hijo derecho de la raiz dada
     * */
    void rotacion_derecha(Vertice * raiz, Vertice * hijoDer);

    /*!
     * @brief Realiza la rotación izquierda
     * 
     * Para la rotación izquierda, se tienen que tomar los siguientes datos.
     * Dados un vertice \f$R\f$, raiz del subárbol en estudio y un vertice
     * \f$X\f$, hijo izquierdo de la raiz, tenemos
     * - El hijo derecho de \f$X\f$ ahora será el hijo izquierdo de \f$R\f$
     * - El vertice \f$X\f$ ahora será padre del vértice \f$R\f$, y \f$R\f$ será
     * su hijo derecho
     * <br>
     * ![Ilustración de la rotación izquierda](./img/rot_izq.png)
     * @param raiz puntero al vertice raiz del subárbol especificado
     * @param hijoIzq puntero al vertice del hijo izquierdo de la raiz dada
     * */
    void rotacion_izquierda(Vertice * raiz, Vertice * hijoIzq);

    /*!
     * @brief Método preliminar para realizar la rotación doble izquierda
     * 
     * Dirigirse a rotacion_doble_izquierda(Vertice *, Vertice *) para ver el
     * funcionamiento detallado
     * @param raiz puntero al vertice raiz del subárbol especificado
     * @see rotacion_doble_izquierda(Vertice *, Vertice *)
     * */
    void rotacion_doble_izquierda(Vertice * raiz);

    /*!
     * @brief Método preliminar para realizar la rotación doble derecha
     * 
     * Dirigirse a rotacion_doble_derecha(Vertice *, Vertice *) para ver el
     * funcionamiento detallado
     * @param raiz puntero al vertice raiz del subárbol especificado
     * @see rotacion_doble_derecha(Vertice *, Vertice *)
     * */
    void rotacion_doble_derecha(Vertice * raiz);

    /*!
     * @brief Realiza la rotación doble izquierda, que es una composición de dos
     * rotaciones
     * 
     * Este método realiza la rotación doble izquierda la cual consiste en:
     *  - realizar una rotación izquierda en el hijo derecho de la raiz
     *  - realizar una rotación derecha en la raiz del subárbol
     * 
     * Dados un vértice R raíz de todo el subárbol y un vértice X hijo derecho
     * de la raíz. Se tiene la siguiente ilustración
     * <br>
     * ![Ilustración de la rotación doble izquierda](./img/rot_d_izq.png)
     * @param raiz puntero al vertice raiz del subárbol especificado
     * @param hijoDer puntero al vertice del hijo derecho de la raiz dada
     * */
    void rotacion_doble_izquierda(Vertice * raiz, Vertice * hijoDer);

    /*!
     * @brief Realiza la rotación doble derecha, que es una composición de dos
     * rotaciones
     * 
     * Este método realiza la rotación doble derecha la cual consiste en: 
     * - realizar una rotación derecha en el hijo izquierdo de la raiz
     * - realizar una rotación izquierda en la raiz del subárbol
     * 
     * Dados un vértice R raíz de todo el subárbol y un vértice X hijo izquierdo
     * de la raíz. Se tiene la siguiente ilustración
     * <br>
     * ![Ilustración de la rotación doble derecha](./img/rot_d_der.png)
     * @param raiz puntero al vertice raiz del subárbol especificado
     * @param hijoIzq puntero al vertice del hijo izquierdo de la raiz dada
     * */
    void rotacion_doble_derecha(Vertice * raiz, Vertice * hijoIzq);
    
    // Métodos para probar la clase
    /**
     * @brief Borra todos los vertices del árbol. **Se recomienda su uso
     * SOLO en caso de necesitar probar el funcionamiento de la clase**
     * */
    void borrar();

    /**
     * @brief Método que contiene ciertos valores ya definidos para probar el
     * funcionamiento. **Se recomienda su uso SOLO en caso de necesitar probar el
     * funcionamiento de la clase**
     * @see test_hardcore(ArbolAVL*, int*, int, bool)
     * */
    void test();

    /**
     * @brief Mestra los factores de equilibrio de todos los vertices existentes
     * actualmente en el subárbol dado. **Se recomienda su uso SOLO en caso de
     * necesitar probar el funcionamiento de la clase**
     * @param r puntero al vertice raíz de dicho subárbol
     * @see factor_de_equilibrio(Vertice*, Vertice*)
     * */
    void factores_de_equilibrio(Vertice * r);

    /**
     * @brief Método que permite realizar las debidas pruebas del funcionamiento
     * segun los valores dados a través del método test(). **Se recomienda su uso
     * SOLO en caso de necesitar probar el funcionamiento de la clase**
     * @param a puntero a un ArbolAVL
     * @param vector arreglo de valores numericos de cada vertice
     * @param n cantidad de elementos en el arreglo
     * @param porPasos booleano que determina si mostrarán individualmente las
     * inserciones o no.
     * @see test()
     * */
    void test_hardcore(ArbolAVL * a, int * vector, int n, bool porPasos);

    protected:
    /**
     * @brief Realiza las debidas comparaciones para determinar si el
     * árbol requiere ser balanceado
     * 
     * Este método, según los siguientes criterios, ejecutará las rotaciones
     * especificadas en ArbolesAVL.
     * Sean R un vértice raíz de un subárbol, I el hijo izquierdo de la raíz
     * y D el hijo derecho de la raíz. Tenemos:
     * - Si \f$F_e(R) = -2\f$ y \f$F_e(I) = -1\f$, entonces se realizará la
     * rotación izquierda (Véase rotacion_izquierda(Vertice*, Vertice*))
     * - Si \f$F_e(R) = 2\f$ y \f$F_e(D) = 1\f$, entonces se realizará la
     * rotación derecha (Véase rotacion_derecha(Vertice*, Vertice*))
     * - Si \f$F_e(R) = 2\f$ y \f$F_e(D) = -1\f$, entonces se realizará la
     * rotación doble izquierda (Véase rotacion_doble_izquierda(Vertice*, Vertice*))
     * - Si \f$F_e(R) = -2\f$ y \f$F_e(I) = 1\f$, entonces se realizará la
     * rotación doble derecha (Véase rotacion_doble_derecha(Vertice*, Vertice*))
     * @param raiz puntero al vertice raíz del subárbol especificado
     * */
    void equilibrar_subarbol(Vertice * raiz);

    /**
     * @brief Obtiene el factor de equilibrio de la raíz dada
     * 
     * Comprueba que la raiz dada exista y que luego compara
     * la altura de su hijo derecho y de su hijo izquierdo para determinar
     * cual es factor de equilibrio de la raiz.
     * Véase la función factor_de_equilibrio(Vertice*, Vertice*) para entender
     * el funcionamiento detallado
     * @param raiz puntero al vertice raíz del subárbol especificado
     * @return valor numérico referente al factor de equilibrio de la raiz
     * @see factor_de_equilibrio(Vertice*, Vertice*)
     * */
    int factor_de_equilibrio(Vertice * raiz);

    /**
     * @brief Obtiene el factor de equilibrio de la raíz en base a sus vértices
     * hijo
     * 
     * Calcula el factor de equilibrio de la raiz en base a lo
     * siguiente. Dados los vértices \f$R\f$, \f$D\f$ e \f$I\f$ el vértice raíz,
     * el hijo derecho de la raiz y el hijo izquierdo de la raiz respectivamente,
     * tenemos que
     * \f[
     *  F_e(R) = altura(D) - altura(I) 
     * \f]
     * Donde \f$F_e\f$ es el *factor de equilibrio* de la raiz
     * @param hijoIzq puntero al hijo izquierdo de la raiz dada
     * @param hijoDer puntero al hijo derecho de la raiz dada
     * @return valor numérico referente al factor de equilibrio de la raiz
     * */
    int factor_de_equilibrio(Vertice * hijoIzq, Vertice * hijoDer);
};

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

