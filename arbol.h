#include <iostream>
#include <cmath>
#include <string>
#include "grafo.h"
#include "pila.h"



/*!
 * \file arbol.h
 * \brief Definción de clase Arbol e implementación de sus métodos
 * */


/*! \mainpage Equipo 3 - Integrantes 
   *
   * \section intro_sec -  
   * \subsection rralex Batres Pedroza Alejandro          201836943
   * \subsection yorch Garcia Gonzalez Jorge             201847512
   * \subsection sebas Mendez Mendez Sebastian           201836190
   * \subsection yo Segura Cuanalo Ricardo Alejandro  201848777
   *
*/


/*!
 * @class Arbol
 * @brief Implementación de un árbol binario con listas de adyacencia.
 * <br>
 * 
 * Es una representación de un árbol binario basada en listas de 
 * adyacencia, usa la clase Vertice y la clase Lista para construir la siguiente estructura:
 *  <br>
 * Lista( <br>
 *  [Vertice A] -> Lista([B] -> [C]) -> <br>
 *  [Vertice B] -> Lista([D]) -> <br> 
 *  [Vertice C] -> Lista() -> <br> 
 *  [Vertice D] -> Lista() <br>
 * )
 * 
 * En todo el código de la clase se asume que el primer vértice en la lista de adyacencia
 * es la raíz del árbol.
 * 
 * Al insertar un nodo la clase Arbol, agrega un nuevo nodo a la lista de adyacencia
 * prinipal e inicializa el nuevo nodo con una lista de adyacencia propia.
 * 
 * Para acceder a los vértices/nodos del árbol exiten dos maneras:
 * - 1. Utilizar Lista::iterator para recorrer la lista de adyacencia de manera lineal (Esta forma es heredada de Grafo)
 * - 2. Utilizar el metodo obtener_hijos(Vertice* raiz) en un vértice raíz y acceder a sus hijos izquierdo y derecho (Forma de árbol binario)
 * 
 * Los métodos de la clase con nombre de la forma: \__nombre__ son metodos recursivos
 * que recorren el árbol respetando su estructura, (Forma 2).
 * Es decir se llama al metodo obtener_hijos(Vertice*raiz) y se utilizan sus hijos (izquierdo o derecho) para continuar 
 * con el recorrido del arbol.
 * 
 * Cada método recursivo cuenta con un método más seguro, (no recursivo) que acepta menos parámetros y cuenta con 
 * más validaciones, que hacen más fácil la correción de errores y las llamadas a los métodos más limpias.
 * 
 * A menos que se esté completamente seguro de como funciona el método recursivo, se recomienda utilizar los __métodos 
 * intermediarios__ (métodos sin __ en el principio de su nombre).
 * 
 * 
 * 
 * 
 * */
class Arbol: public Grafo{
    public:
        /*!
         * @brief Constructor
         * */
        Arbol(): Grafo() {}

		/*!
         * @brief Inserta un dato en el árbol
         * 
         * Busca un vertice con un espacio vacio y que cumpla con el orden en el arbol,
         * raiz < hijo derecho, raiz > hijo izquierdo
         *  
         * @param dato número a insertar 
         * @return Nivel en el que fué insertado el nodo
         * */
        int insertar(int dato);

        /*!
         * @brief Muestra el árbol de manera horizontal
         * @param out Referencia a un flujo de salida
         * */
        void mostrar(ostream & out);

        /*!
         * @brief Muestra el árbol verticalmente
         * */
        void recorrer();

        /*!
         * @brief Metodo recursivo auxiliar para recorrer()
         * @param raiz puntero a la raíz del arbol a mostrar
         * @param cont contador del nivel del nodo actual (cont = 0)
         * @see recorrer()
         * */
        void recorrer(Vertice *raiz,int cont);

        /*!
         * @brief Recorre el árbol en preorden e inserta los vertices obtenidos en una lista
         * @return Lista de punteros a vértices del árbol en preorden
         * */
        Lista<Vertice*> * preorden();

        /*!
         * @brief Recorre el árbol en inorden e inserta los vertices obtenidos en una lista
         * @return Lista de punteros a vértices del arbol en inorden
         * */
        Lista<Vertice*> * inorden();

        /*!
         * @brief Recorre el árbol en inorden e inserta los vertices obtenidos en una lista
         * @return Lista de punteros a vertices del arbol en postorden
         * */
        Lista<Vertice*> * postorden();

        /*!
         * @brief Calcula el número de nodos en el árbol
         * @return numero de nodos 
         * */
        int peso();

        /*!
         * @brief Calcula el grado del árbol, es decir el número máximo de hijos en cada nodo
         * @return grado del árbol
         * */
        int grado();

        /*!
         * @brief Obtiene el padre de un nodo a partir del valor de uno de sus hijos
         * @param hijo valor numérico de un vértice hijo
         * @return puntero a vértice padre o NULL si el hijo no existe
         * */
        Vertice * padre(int hijo);

        /*!
         * @brief Obtiene el padre de un nodo a partir del nombre de uno de sus hijos
         * @param hijo nombre de un vértice hijo
         * @return puntero a vértice padre o NULL si el hijo no existe
         * */
        Vertice * padre(string hijo);

        /*!
         * @brief Obtiene el padre de un nodo a partir de un puntero a uno de sus hijos
         * @param hijo puntero a vértice hijo
         * @return puntero a vértice padre
         * */
        Vertice * padre(Vertice * hijo);
        
        /*!
         * @brief Obtiene los hijos de un vértice a partir del valor de su nodo padre
         * @param padre valor numérico del vértice padre
         * @return lista de punteros a vértices hijos
         * */
        Lista<Vertice*> * hijos(int padre);

        /*!
         * @brief Obtiene los hijos de un vértice a partir del nombre de su nodo padre
         * @param padre nombre del vértice padre
         * @return lista de punteros a vértices hijos
         * */

        Lista<Vertice*> * hijos(string padre);

        /*!
         * @brief Obtiene las hojas del árbol (nodos con 0 hijos)
         * @return lista de punteros a vértices hojas
         * */

        Lista<Vertice*> * hojas();

        /*!
         * @brief Calcula el número de hojas en el árbol
         * @param raiz puntero a vértice raíz del árbol
         * @return lista de punteros a vértices hijos
         * */

        int cont_hojas(Vertice *raiz);
 
        /*!
         * @brief Obtiene el hermano de un vértice (nodo con el mismo padre)
         * @param buscar valor numérico del hermano del vértice buscar
         * @return puntero a vértice hermano
         * */
       
        Vertice * hermano(int buscar);

        /*!
         * @brief Verifica si el árbol cumple las condiciones de un árbol lleno,
         * es decir cada nodo debe tener 0 o 2 hijos.
         * @return *true* si el árbol es lleno, *false* en caso contrario.
         * */

        bool es_lleno();

        /*!
         * @brief Verifica si el árbol cumple las condiciones de un árbol perfecto/lleno 
         * ( árbol lleno con todas sus hojas en el mismo nivel )
         * @return *true* si es perfecto, *false* en caso contrario
         * */
        bool es_completo_o_perfecto();

        /*!
         * @brief Calcula la altura de un nodo (longitud del camino mas largo desde el nodo y un nodo hoja)
         * @param dato valor numérico del nodo
         * @return altura del nodo
         * */
        int altura(int dato);
 
        /*!
         * @brief Calcula la altura de un nodo (longitud del camino mas largo desde el nodo y un nodo hoja)
         * @param nombre nombre del vértice
         * @return altura del nodo
         * */
        int altura(string nombre);

        /*!
         * @brief Calcula la altura de un nodo (longitud del camino mas largo desde el nodo y un nodo hoja)
         * @param nodo puntero al nodo
         * @return altura del nodo
         * */
        int altura(Vertice * nodo);

        /*!
         * @brief Calcula el nivel donde se encuentra un nodo (la raíz tiene un nivel 0 y sus hijos tienen un nivel 1)
         * @param dato valor numérico del nodo
         * @return nivel del nodo
         * */
        int nivel(int dato);

        /*!
         * @brief Calcula el nivel donde se encuentra un nodo (la raíz tiene un nivel 0 y sus hijos tienen un nivel 1)
         * @param nombre nombre del nodo
         * @return nivel del nodo
         * */
        int nivel(string nombre);

        /*!
         * @brief Obtiene los antecesores de un nodo
         * @param dato valor numérico del nodo
         * @return lista de punteros a vértices previos al nodo
         * */
        Lista<Vertice*> * antecesores(int dato);

        /*!
         * @brief Obtiene los antecesores de un nodo
         * @param nombre nombre del nodo raíz
         * @return lista de punteros a vértices antecesores al nodo
         * */
        Lista<Vertice*> * antecesores(string nombre);

        /*!
         * @brief Obtiene los descendientes de un nodo
         * @param dato valor numérico del nodo raíz
         * @return lista de punteros a vértices descendientes al nodo
         * */
        Lista<Vertice*> * descendientes(int dato);

        /*!
         * @brief Obtiene los descendientes de un nodo
         * @param nombre nombre del nodo raíz
         * @return lista de punteros a vértices descendientes al nodo
         * */
        Lista<Vertice*> * descendientes(string nombre);

        /*!
         * @brief Obtiene el un camino entre dos vértices en el árbol
         * @param o valor numérico del vértice origen
         * @param d valor numérico del vértice destino
         * @return lista de punteros a vértices en el camnino de o a d
         * */
        Lista<Vertice*> * camino_entre(int o, int d);

        /*!
         * @brief Obtiene el un camino entre dos vértices en el árbol
         * @param origen nombre del vértice origen
         * @param destino nombre del vértice destino
         * @return lista de punteros a vértices en el camnino de origen a destino
         * */
        Lista<Vertice*> * camino_entre(string origen, string destino);
   protected:

        // los metodos que de la forma: __metodo__ son recursivos
        
        /*!
         * @brief Recorre un árbol en preorden (Visitar, Izquierda, Derecha) recursivamente, 
         * método auxiliar de preorden()
         * @param raiz puntero a la raíz del árbol a recorrer
         * @param lista puntero a lista de vértices (donde se guardarán los vértices visitados en orden)
         * @see preorden()
         **/
        void __preorden__(Vertice * raiz, Lista<Vertice*> * lista);

        /*!
         * @brief Recorre un árbol en inorden (Izquierda, Visitar, Derecha) recursivamente,
         * método auxiliar de inorden()
         *
         * @param raiz puntero a la raíz del árbol a recorrer
         * @param lista puntero a lista de vertices (donde se guardarán los vértices visitados en orden)
         * @see inorden()
         * */
        void __inorden__(Vertice * raiz, Lista<Vertice*> * lista);

        /*!
         * @brief Recorre un árbol en postorden (Izquierda, Derecha, Visitar) recursivamente,
         * método auxiliar de postorden()
         * @param raiz puntero a vértice raíz del árbol
         * @param lista puntero a lista de vértices (donde se guardarán los vértices visitados en orden)
         * @see postorden()
         * */
        void __postorden__(Vertice * raiz, Lista<Vertice*> * lista);
        
        /*!
         * @brief Obtiene el camino entre 2 vértices en el árbol, método auxiliar de camino_entre()
         * @param origen puntero a vértice de inicial del camino
         * @param destino puntero a vértice final del camino
         * @param camino doble puntero a lista de vértices donde se guardarán los nodos en orden
         * @see camino_entre()
         * */
        void __camino__(Vertice* origen, Vertice* destino, Lista<Vertice*> **camino);

        /*!
         * @brief Obtiene el grado de un árbol, método auxiliar de grado()
         * @param raiz puntero a vértice raíz del árbol
         * @return número más grande de hijos en nodos del árbol
         * @see grado()
         * */
        int __grado__(Vertice* raiz);
       
        /*!
         * @brief Obtiene la altura de un árbol recursivamente, auxiliar de altura()
         * @param v puntero a vértice raíz del árbol
         * @return altura del árbol 0 si es hoja 
         * @see altura()
         * */
        int __altura__(Vertice * v);
        
        /*!
         * @brief Obtiene el nivel de un nodo en el árbol, auxiliar de nivel()
         * @param raiz puntero a raíz del árbol donde se buscará el nodo
         * @param vert puntero a vértice que se encontrará su nivel
         * @param lvl nivel actual en el subárbol
         * @return nivel del nodo apuntado por vert
         * @see nivel()
         * */
        int __nivel__(Vertice * raiz, Vertice * vert, int lvl);

        /*!
         * @brief Obtiene las hojas de un árbol, auxiliar de hojas()
         * @param raiz puntero a raíz del subárbol 
         * @param lista puntero a lista de vértices donde se guardarán los vértices hojas
         * @see hojas()
         * */
        void __hojas__(Vertice * raiz, Lista<Vertice*> * lista);

        /*!
         * @brief Obtiene los hijos de un nodo dado, auxiliar de hijos()
         * @param raiz del árbol donde se buscará el nodo
         * @param padre puntero al nodo que se quieren obtener los nodos hijos
         * @param lista puntero a lista de vértices donde se guardarán los hijos del nodo
         * @see hijos()
         * */
        void __hijos__(Vertice * raiz, Vertice * padre, Lista<Vertice*> * lista);

        /*!
         * @brief Obtiene el padre de un nodo dado, auxiliar de padre()
         * @param raiz puntero a la raíz del subárbol
         * @param padre doble puntero a un vértice donde se pondrá la direccion de memoria del padre
         * @see padre()
         * */
        void __padre__(Vertice * raiz, Vertice * hijo, Vertice ** padre);
        
        /*!
         * @brief Ordena una lista de vértices en orden ascendente
         * @param lista puntero a lista de vertices a ordenar
         * @see Vertice
         * */    
        void ordenar_lista_de_adyacentes(Lista<Vertice*> * lista);

        /*!
         * @brief Obtiene los hijos de un vértice en orden ascendente
         * @param padre vértice padre
         * @return Arreglo de vértices de longitud 2, hijos[0] hijo izquierdo de padre, hijos[1] hijo derecho de padre
         * */
        Vertice ** obtener_hijos(Vertice * padre);

        /*!
         * @brief Verifica que todos los vértices en el árbol cumplen. 
         * una condición dada por una función de callback
         * @param funcion_callback función que verifica una condición en un solo vértice
         * @return true si todos los vértices pasan la prueba false si no.
         * */
        bool todos_cumplen_con(bool (*funcion_callback)(Vertice*));

        /*!
         * @brief Método auxiliar para todos_cumplen_con() verifica la condición en
         * cada nodo del árbol recursivamente
         * @param funcion_callback función que verifica una condición en un solo vértice
         * @param vert puntero a vértice raíz del subárbol
         * @return true si los nodos en el subárbol cumplen la condicion, false en caso contrario.
         * @see todos_cumplen_con()
         * */

        bool __todos_cumplen_con__(bool (*funcion_callback)(Vertice*),Vertice* vert);
};

// Obtiene el hermano de un nodo
Vertice * Arbol::hermano(int buscar){
    // encontrar el padre del nodo, y obtener la direccion
	Vertice * _padre = padre(buscar),
			* vert = get_vertice(to_string(buscar));

	//Verificamos que el vertice ingresado exista
	if(_padre == NULL){
		return NULL;
	} else {

		Vertice ** hijos = obtener_hijos(_padre);
		Vertice * izq = hijos[0], * der = hijos[1];
		if(izq == vert)
			return der;
		else
			return izq;
	}
}

Lista<Vertice*> * Arbol::hijos(int padre){
	return hijos(to_string(padre));
}
// Funcion que retorna los hijos del vertice padre dado
Lista<Vertice*> * Arbol::hijos(string padre){
	Lista<Vertice*> * lista = new Lista<Vertice*>;
	Vertice * vert = get_vertice(padre);
	if(vert == NULL) return lista;
	__hijos__(vertices.primero() ,vert, lista);
	return lista;
}

void Arbol::__hijos__(Vertice * raiz, Vertice * padre, Lista<Vertice*> * lista){
	if(raiz != NULL){
		Vertice ** hijos = obtener_hijos(raiz);
		if(raiz == padre){
			if(hijos[0])
				lista->insertar_final(hijos[0]);
			if(hijos[1])
				lista->insertar_final(hijos[1]);
		} else {
			__hijos__(hijos[0], padre, lista);
			__hijos__(hijos[1], padre, lista);
		}
	}
}

Vertice * Arbol::padre(int hijo){
	return padre(to_string(hijo));
}

// Funcion que retorna el padre del vertice hijo dado
Vertice * Arbol::padre(string hijo){
	Vertice * _padre = NULL,
			* _hijo = get_vertice(hijo);

	if(_hijo == NULL) return _padre;

	__padre__(vertices.primero(), _hijo, &_padre);
	return _padre;
}

Vertice * Arbol::padre(Vertice * hijo){
	Vertice * _padre = NULL;

	if(hijo == NULL) return _padre;

	__padre__(vertices.primero(), hijo, &_padre);
	return _padre;
}

void Arbol::__padre__(Vertice * raiz, Vertice* hijo, Vertice ** padre){
	if(raiz != NULL) {
		Vertice ** hijos = obtener_hijos(raiz);
		if(hijos[0] == hijo || hijos[1] == hijo)
			*padre = raiz;
		else{
			__padre__(hijos[0], hijo, padre);
			__padre__(hijos[1], hijo, padre);
		}
	}
}

// cuenta las hojas del arbol de manera elegante
int Arbol::cont_hojas(Vertice *raiz){
	//metodo recursivo
	Vertice ** hijos = obtener_hijos(raiz);
	int total = 0;
    // si el nodo raiz es null retornar vacio
    if (!raiz)
        return 0;
    // si el nodo es una hoja retorna 1
    if (!hijos[1] && !hijos[0])
        return 1;

    // la variable total va sumando cada uno de los casos en los hijos son hojas
    if (hijos[0])
       total += cont_hojas(hijos[0]);

    if (hijos[1])
      total += cont_hojas(hijos[1]);
      return total;
}


Lista<Vertice*> * Arbol::hojas(){
	Lista<Vertice*> * lista = new Lista<Vertice*>;
	//__hojas__ metodo recursivo imprime las hojas desde el metodo
	__hojas__(vertices.primero(), lista);
	return lista;
}

// metodo recursivo para obtener las hojas del arbol
void Arbol::__hojas__(Vertice * raiz, Lista<Vertice*> * lista){
	Vertice ** hijos = obtener_hijos(raiz);
    // si el nodo raiz es null retornar vacio
    if (!raiz)
        return;
    // si el nodo es una hoja imprime sus datos
    if (!hijos[0] && !hijos[1])
    {
		lista->insertar_final(raiz);
        return;
    }

    if (hijos[0])//por cada hijo se vuelve a llamar el metodo de nuevo xD
       __hojas__(hijos[0], lista);

    if (hijos[1])
      __hojas__(hijos[1], lista);
}


// hace el recorrido en preorden del arbol
// regresa una lista de vertices con los vertices
// obtenidos del recorrido
Lista<Vertice*> * Arbol::preorden(){
	// lista para almacenar recorrido
	Lista<Vertice*> * recorrido = new Lista<Vertice*>;
	// si no hay vertices
	if(vertices.vacia()) return recorrido;
	// llamar a la funcion recursiva de preorden
	__preorden__(vertices.primero(), recorrido);
	return recorrido;
}

// funcion recursiva que hace el recorrido en preorden del arbol
// metodo privado de la clase Arbol
void Arbol::__preorden__(Vertice * raiz, Lista<Vertice*> * lista){

	if(raiz == NULL) return;
	Vertice ** hijos = obtener_hijos(raiz);

	lista->insertar_final(raiz);
	__preorden__(hijos[0], lista);
	__preorden__(hijos[1], lista);
}

// hace el recorrido en inorden del arbol
// regresa una lista de vertices con los vertices
// obtenidos del recorrido
Lista<Vertice*> * Arbol::inorden(){
	// lista para almacenar recorrido
	Lista<Vertice*> * recorrido = new Lista<Vertice*>;
	// si no hay vertices
	if(vertices.vacia()) return recorrido;
	// llamar a la funcion recursiva de preorden
	__inorden__(vertices.primero(), recorrido);
}

// funcion recursiva que hace el recorrido en inorden del arbol
void Arbol::__inorden__(Vertice * raiz, Lista<Vertice*> * lista){

	if(raiz == NULL) return;
	Vertice ** hijos = obtener_hijos(raiz);

	__inorden__(hijos[0], lista);
	lista->insertar_final(raiz);
	__inorden__(hijos[1], lista);
  
}



// verifica que todos los vertices cumplen
// con una funcion condicion pasada por parametro
// si algun vertice no cumple... retorna false
// si todos cumplen retorna true
bool Arbol::todos_cumplen_con(bool (*func_condicion)(Vertice * v)){
	return __todos_cumplen_con__(func_condicion,vertices.primero());
}

bool Arbol::__todos_cumplen_con__(bool (*func_condicion)(Vertice * v), Vertice* vert){
	if(vert == NULL)
		return true;
	if(func_condicion(vert)){
		Vertice ** hijos = obtener_hijos(vert);
		bool flag = __todos_cumplen_con__(func_condicion, hijos[0]) && __todos_cumplen_con__(func_condicion, hijos[1]);
		delete [] hijos;
		return flag;
	}
	return false;
}

// hace el recorrido en postorden del arbol
// regresa una lista de vertices con los vertices
// obtenidos del recorrido
Lista<Vertice*> * Arbol::postorden(){
	// lista para almacenar recorrido
	Lista<Vertice*> * recorrido = new Lista<Vertice*>;
	// si no hay vertices
	if(vertices.vacia()) return recorrido;
	// llamar a la funcion recursiva de preorden
	__postorden__(vertices.primero(), recorrido);
	return recorrido;
}

// funcion recursiva que hace el recorrido en postorden del arbol
// metodo privado de la clase Arbol
void Arbol::__postorden__(Vertice * raiz, Lista<Vertice*> * lista){
	if(raiz == NULL) return;
	Vertice ** hijos = obtener_hijos(raiz);

	__postorden__(hijos[0], lista);
	__postorden__(hijos[1], lista);
	lista->insertar_final(raiz);
}

int Arbol::peso(){
	Lista<Vertice*> *relleno = new Lista<Vertice*>;
	return vertices.tamanio();
}

int Arbol::grado(){
	return __grado__(vertices.primero());
}

int Arbol::__grado__(Vertice *raiz){//metodo recursivo
	int mayor = 0, retorno;
	if(raiz == NULL)
		return 0; //si la raiz es nula retorna 0 ya que no tiene hijos
	else{
		Vertice ** hijos = obtener_hijos(raiz);
		Vertice * izq = hijos[0], * der = hijos[1]; //obtenemos los hijos de la raiz

		// Por cada hijo distinto de null, el grado del nodo aumenta por uno
		if(izq != NULL) mayor++;
		if(der != NULL) mayor++;

		if((retorno = __grado__(der)) > mayor) mayor = retorno; //se llama al metodo recursivamente por cada hijo desde la raiz
		if((retorno = __grado__(izq)) > mayor) mayor = retorno;
	}
	return mayor; //se retorna la variable mayor que es la que guarda la mayor cantidad de de hijos de los Vertices.
}

// obtiene los hijos de un vertice dado
Vertice ** Arbol::obtener_hijos(Vertice * padre){
	int tam = padre->adyacente->tamanio();
	require(padre != NULL,
			"El vertice no puede ser NULL -> Arbol::obtener_hijos");
	require(tam <= 2,
			"Tamanio de lista de vertices adyacentes excede 2 Arbol::obtener_hijos");
	// obtiene los hijos de un vertice
	// extrae de la lista de adyacencia todos los vertices y los devuelve
	// en un arreglo ordenados, hijo_izquierdo = arr[0], hijo_der = arr[[1]
	// para averiguar cual es el izquierdo y derecho ... compara con el valor
	// del vertice padre
	Vertice ** hijos = new Vertice*[2];
	// poner a null los dos hijos
	hijos[0] = NULL;
	hijos[1] = NULL;
	// si solo tiene un vertice
	if(tam == 1){
		// obtener el vertice
		Vertice * vert = padre->adyacente->primero();
		// si el dato del vertice es menor al dato de su padre
		if(vert->dato < padre->dato){
			hijos[0] = vert;
		} else {
			hijos[1] = vert;
		}
	} else if(tam == 2){
		int j = 0;
		// guardar los hijos en el arreglo
		for(Lista<Vertice*>::iterator i = padre->adyacente->begin(); i != padre->adyacente->end(); i++){
				hijos[j] = *i;
				j++;
		}
		// si los hijos estan en el orden inverso...
		if(hijos[0]->dato >= padre->dato){
			// intecambiar
			Vertice * ERT = hijos[0];
			hijos[0] = hijos[1];
			hijos[1] = ERT;
		}
	}
	return hijos;
}

// ordena una lista de vertices adyacentes de a lo mas 2 elementos
// solo para arboles binarios
void Arbol::ordenar_lista_de_adyacentes(Lista<Vertice*> * lista){
    // guardar el tamanio de la lista de vertices a ordenar
    int tam = lista->tamanio();
	// se necesita ordenar ?
	if(tam == 0 || tam == 1) return;
	// verificar que sea un arbol binario
	require(tam == 2,
			"Tamanio excedido en lista de adyacencia de arbol binario");

    Vertice ** aux = new Vertice*[2];
    // contador
    int i = 0;
	// obtener todos los elementos de la lista y
    // colocarlos en un arreglo
    while(!lista->vacia() && i < tam){
        aux[i] = lista->suprimir_final();
        i++;
    }
	if(aux[0]->dato > aux[1]->dato){
		// swap
		Vertice * ERT = aux[0];
		aux[0] = aux[1];
		aux[1] = ERT;
	}

    // y ahora insertas en orden todos los vertices
    for(i = 0; i < tam; i++){
        lista->insertar_final(aux[i]);
    }
}


void Arbol::mostrar(ostream & out)
{
    // pila global de vertices
	pila<Vertice*> p_global;
    // apilar la raiz del arbol
	p_global.apilar(vertices.primero());
    // a los n espacios se imprime la raiz
	int espacios = 32;
    // la fila a imprimir esta vacia?
	bool fila_vacia = false;
    // mientras la fila a imprimir no este vacia
	while(!fila_vacia)
	{
        // pila local para guardar los hijos de los vertices impresos
		pila<Vertice*> p_local;
        // suponemos que la fila esta vacia por defecto
		fila_vacia = true;
		// imprimir n espacios antes del primer vertice de la fila
		for(int j = 0; j < espacios; j++)
			out<< " ";
		// mientras la pila global no este vacia
        // en la pila global se guardan los vertices de la fila (nivel) anterior
		while(!p_global.vacia()){
            // vertice a imprimir
            Vertice * temp = p_global.desapilar();
			if(temp != NULL){
				out <<  temp->nombre;
                // obtener los hijos del vertice
                // si no existe el hijo retorna un NULL en la posicion del hijo
                Vertice ** hijos = obtener_hijos(temp);
                // apilar los dos hijos (aunque sean NULL)
                // necesario para que en la siguiente iteracion los espacios
                // se impriman correctamente
				p_local.apilar(hijos[0]);
				p_local.apilar(hijos[1]);
				// si el vertice tiene hijos... entonces la siguiente fila
                // tiene vertices a imprimirse
				if(hijos[0] != NULL || hijos[1] != NULL)
					fila_vacia = false;
			} else {
                // imprimir nodo vacio
				out << "--";
                // apilar dos hijos nulos para respetar los
                // espacios en el siguiente nivel
				p_local.apilar(NULL);
                p_local.apilar(NULL);
			}
            // imprimir espacios entre dos nodos
			for(int j = 0; j<espacios*2-2;j++)
			   out << " ";
		}
		out << "\n";
        // los espacios del siguiente nivel son de la mitad del nivel actual
		espacios /= 2;
        // mientras la pila local tenga vertices
		while(!p_local.vacia())
			p_global.apilar(p_local.desapilar());

	}
}

// Inserta un nuevo nodo al arbol
// retorna el nivel donde el arbol fue insertado
int Arbol::insertar(int dato){
	// guardar el nivel en el que se inserto el vertice
	int nivel = 0;
    // insertar el vertice con el metodo de Grafo
    insertar_vertice(std::to_string(dato), dato);

    if(vertices.tamanio() == 1) return nivel;
    bool encontrado = false;
    // si el nodo insertado fue la raiz
    // posible vertice padre del nuevo vertice a insertar
    // la raiz del arbol se supone como el primer elemento de la lista
    Vertice * posible_vert = vertices.primero();
    // obtener la direccion del nuevo vertice
    Vertice * nuevo = vertices.ultimo();

    // mientras no se encuentre un vertice con un espacio libre
    while(!encontrado){
        // si el dato del nuevo es menor al dato de posible_lugar
		Vertice ** hijos = obtener_hijos(posible_vert);
		Vertice * izq = hijos[0], * der = hijos[1];
        if(nuevo->dato < posible_vert->dato){
            // si la lista de adyacentes esta vacia o la posible posicion del nuevo vertice esta vacia
            if(posible_vert->adyacente->vacia() || izq == NULL)
                encontrado = true;
            else{
                posible_vert = izq;
				nivel ++;
			}
        } else {
			// si no tiene hijos o el hijo derecho es NULL
            if(posible_vert->adyacente->vacia() || der == NULL)
                encontrado = true;
            else{
                posible_vert = der;
				nivel++;
			}
        }
    }

	// insertamos sin importarnos el orden ...
    posible_vert->adyacente->insertar_final(nuevo);

	// ordenamos la lista con un nuevo metodo super chidoooo
	ordenar_lista_de_adyacentes(posible_vert->adyacente);

    return nivel;
}

// muestra el arbol de una manera mas chida
void Arbol::recorrer(Vertice *raiz,int cont){
	if(raiz == NULL){
		return;
	}else{
		Vertice ** hijos = obtener_hijos(raiz);
		Vertice * izq = hijos[0], * der = hijos[1];
		recorrer(der, cont+1);
		for(int i=0;i<cont;i++){
			std::cout<<"  ";
		}
		std::cout << raiz->nombre << endl;
		recorrer(izq, cont+1);
	}
}

// muestra el arbol de una manera mas chida
void Arbol::recorrer(){
	recorrer(vertices.primero(), 0);
}

// FUNCIONES CALLBACK

// verifica si un vertice tiene 2 o 0 hijos
bool dos_o_cero_hijos(Vertice * vert){
	int tam = vert->adyacente->tamanio();
	return (tam == 0 || tam == 2);
}

// FUNCIONES DE LA PRACTICA DEL 16 de abril

// verifica si el arbol actual es un arbol
// binario lleno
bool Arbol::es_lleno(){
	// un arbol binario es un arbol binario lleno
	// si todos sus nodos tienen 0 o 2 hijos
	// con excepcion de la raiz
	if(vertices.tamanio() == 1) return true;
	// verifica que todos los vertices tienen 2 o 0 hijos
	// usa la funcion de condicion: bool dos_o_cero_hijos(Vertice * vert);
	// y la funcion todos_cumplen_con(bool (*func_condicion)(Vertice *));
	// que aplica la funcion condicion a todos los vertices
	return todos_cumplen_con(dos_o_cero_hijos);
}

bool Arbol::es_completo_o_perfecto(){
	// Dado que la altura se mide desde la hoja mas profunda hasta un vertice dado,
	// la raiz contendria la mayor altura.
	// Por lo anterior, se deduce que la mayor de las profundidades entre las hojas
	// (o sea, el nivel mas alto) es equivalente a la altura de la raiz
	//
	// i.e.		Altura de la raiz = Nivel del vertice mas profundo
	//
	int nivel = altura(vertices.primero()->dato); // aplicando la logica anterior se tiene esto
	int hojas = cont_hojas(vertices.primero());// cont_hojas devuelve el numero de hojas del arbol.
	int perfectoEstimado = pow(2,nivel);

	// La cantidad de hojas en un arbol binario perfecto es igual a 2^n
	// donde n es el nivel de la hoja mas profunda
	return hojas == perfectoEstimado;
}

Lista<Vertice*> * Arbol::camino_entre(int o, int d){
	return camino_entre(to_string(o),to_string(d));
}

Lista<Vertice*> * Arbol::camino_entre(string origen, string destino){
	Lista<Vertice*> * camino = new Lista<Vertice*>;
	Vertice * o = get_vertice(origen);
	Vertice * d = get_vertice(destino);

	if(o == NULL || d == NULL) return camino; // Si los vertices no existen, regresan un camino vacio

	__camino__(o,d,&camino);
	return camino;
}

void Arbol::__camino__(Vertice* actual, Vertice* destino, Lista<Vertice*> ** camino){
	// Si el vertice actual es NULL (no hay camino actual->destino), se borra todo el
	// progreso en la lista
	if(actual == NULL){
		while(!(*camino)->vacia())
			(*camino)->suprimir_final();
		return;
	}

	// Si el vertice actual es el vertice destino, significa que si hubo camino y
	// termina la ejecucion (ingresando el ultimo nodo al camino)
	if(actual == destino){
		(*camino)->insertar_final(actual);
		return;
	}

	// se obtienen hijos del vertice actual
	Vertice** hijos = obtener_hijos(actual);

	// se deduce temporalmente que dicho vertice es parte del camino
	(*camino)->insertar_final(actual);
	// el vertice actual se dirige a la rama con la mayor posibilidad de encontrar al destino
	if(destino->dato < actual->dato)
		__camino__(hijos[0],destino,camino);
	else
		__camino__(hijos[1],destino,camino);

	delete [] hijos;

	return;
}

int Arbol::altura(int dato){
	return altura(to_string(dato));
}

// Obtiene la altura de un nodo dado
// retorna -1 si el nodo no fue encontrado
int Arbol::altura(string nombre){
	Vertice * nodo = get_vertice(nombre);
	// se requiere que el nodo no sea NULL
	if(nodo == NULL) return -1;
	// si el nodo es una hoja

	// funcion resursiva que obtenga la altura de un arbol
	return __altura__(nodo);
}

// Obtiene la altura de un nodo dado
// retorna -1 si el nodo no fue encontrado
int Arbol::altura(Vertice * nodo){
	// se requiere que el nodo no sea NULL
	if(nodo == NULL) return -1;
	// si el nodo es una hoja
	// funcion resursiva que obtenga la altura de un arbol
	return __altura__(nodo);
}

// Funcion recursiva que obtiene la altura
// de un nodo dado
int Arbol::__altura__(Vertice * nodo){
	// si el nodo es una hoja su altura es 0
	if(nodo == NULL || nodo->adyacente->tamanio() == 0) return 0;
	Vertice ** hijos = obtener_hijos(nodo);
	// altura del subarbol izquierdo
	int a_izq = __altura__(hijos[0]);
	// altura del subarbol derecho
	int a_der = __altura__(hijos[1]);
	// retornar la altura mayor mas 1
	return a_izq >= a_der ? a_izq + 1: a_der + 1;
}

int Arbol::nivel(int dato){
	return nivel(to_string(dato));
}

int Arbol::nivel(string nombre){
	Vertice * nodo = get_vertice(nombre);
	if(nodo == NULL) return -1;

	// Dado que se empieza el recorrido desde la raiz, el nivel es 0
	return __nivel__(vertices.primero(), nodo, 0);
}

int Arbol::__nivel__(Vertice * raiz, Vertice * busc, int lvl){
	if (raiz == NULL) return -1; // árbol vacío o llegamos a una hoja y no encontramos el vertice

	Vertice ** hijos = obtener_hijos(raiz);
	Vertice * izq = hijos[0], * der = hijos[1];

	if(raiz == busc) return lvl; // Caso en el que el buscado sea la raiz, es decir, el nivel 0

	//Si no esta en izq o der, recorremos para seguir buscando y aumentamos lvl en 1
	if(busc->dato < raiz->dato)
		return __nivel__(izq,busc, ++lvl);
	else
		return __nivel__(der,busc, ++lvl);
}

// Obtiene los antecesores de un nodo
// Los nodos desde la raiz al nodo
Lista<Vertice*> * Arbol::antecesores(int dato){
	return antecesores(to_string(dato));
}

Lista<Vertice*> * Arbol::antecesores(string nombre){
	// Se obtiene el camino desde la raiz hasta el vertice dado
	Lista<Vertice*> * camino = camino_entre(vertices.primero()->nombre, nombre);
	// Se suprimer el ultimo elemento que es el vertice destino
	camino->suprimir_final();
	return camino;
}


// Funcion que retorna la lista con los descendientes
// del vertice dado
Lista<Vertice*> * Arbol::descendientes(int dato){
	return descendientes(to_string(dato));
}

// Funcion que retorna la lista con los descendientes
// del vertice dado
Lista<Vertice*> * Arbol::descendientes(string nombre){

	Lista<Vertice*> * desc = new Lista<Vertice*>;
	Vertice * vertice = get_vertice(nombre);

	// En caso de que no exista el vertice con dicho dato,
	// se procede a retornar una lista vacia
	if(vertice == NULL) return desc;

	// Se genera una lista de vertices en preorden desde
	// el vertice dado (fungiendo como la raiz de un subarbol)
	__preorden__(vertice,desc);

	// Todos los vertices resultantes obligatoriamente
	// deben ser descendientes del vertice dado (excepto
	// el primero que es la raiz del subarbol), por esto
	// se surpime el primer elemento de la lista
	desc->suprimir_inicio();
	return desc;
}
