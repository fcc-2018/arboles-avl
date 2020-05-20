#include <string>
#define GRAFO_H
#include <iostream>
#include "lista.hpp"
#include "cola.hpp"
#include <map>
#include <set>
#include <fstream>

using namespace std;

/*!
*\file grafo.hpp
*@brief Definición de la clase Grafo, Vertice, Arista, Etiqueta, y la implementación de sus métodos.
*/

class Vertice;

/*!
*@class Etiqueta
*@brief Clase de apoyo para conservar el Vértice Origen y su Peso
*/
class Etiqueta{
	public:
	//!&lt; Varible contenedora del Peso del Vértice Origen
	float peso;
	//!&lt; Apuntador al Vértice Origen
	Vertice * verticeOrigen;
	//!&lt; Marca para evitar que el Origen cambie
	bool permanente;

	/*!
	*@brief Constructor de Etiqueta
	*@param p Peso del Vértice Origen
	*@param origen Apuntador al Vértice que se tomará como Origen
	*@param permanente Marca utilizada para evitar el cambio de Origen
	*/
	Etiqueta(float p, Vertice * origen, bool permanente): 
		peso(p), verticeOrigen(origen), permanente(permanente){}

	/*!
	*@brief Atributos de un Vértice Origen creado por defecto
	*/
	Etiqueta(){
		peso = 0;
		verticeOrigen = NULL;
		permanente = false;
	}
};

/*!
*@class Vertice
*@brief Clase encargada de llenar los datos en los Nodos insertados al Grafo
*/
class Vertice{
	public:
	//!&lt; Se usa para recorrer la lista de vertices
	Vertice *sig;
	//!&lt; Lista de vértices adyacentes (Vertice *)
	Lista<Vertice*> *adyacente;
	//!&lt; Nombre que llevará el vértice
	string nombre;
	//!&lt; Información que almacena el vértice
	int dato;
	//!&lt; Creación de un Vértice Origen por defecto
	Etiqueta etiqueta;
	//!&lt; Marca para saber por cuáles vértices ya se ha pasado en los recorridos
	bool visitado;

	/*!
	*@brief Constructor de Vertice
	*@param nombre Forma en la que nos referiremos al vértice
	*@param dato Información que contendra el vértice
	*/
	Vertice(string nombre, int dato): sig(NULL), 
		nombre(nombre), dato(dato), adyacente(new Lista<Vertice*>){}
	friend class Grafo;

	/*!
	*@brief Atributos de un vértice creado por defecto
	*/
	Vertice(): sig(NULL), nombre(""), dato(0){}

	/*!
	*@brief Al momento de llamar a " out << V " donde V es una variable de tipo Vertice,
	*@return Se mostrará en la salida "out" el campo "nombre" de V
	*/
	friend ostream& operator<<(ostream& os, const Vertice& v) {
		return os << v.nombre;
	}

	/*!
	*@brief Al momento de llamar a " out << V " donde V es una variable de tipo Vertice* (apuntador a Vertice)
	* (Este es un caso especial para que el grafo muestre los vértices correctamente)
	*@return Se mostrará en la salida "out" el campo "nombre" de *V
	*/
	friend ostream& operator<<(ostream& os, const Vertice* v) {
		return os << v->nombre;
	}
};

/*!
*@class Arista
*@brief Clase que lleva el control del vertice de 'origen' y de 'destino' y el peso del camino entre estos
*/
class Arista{
	public:
	//!&lt; Apuntador del vértice de origen 
	Vertice *origen;
	//!&lt; Apuntador del vértice de destino
	Vertice *destino;
	//!&lt; Peso del camino entre los vértices
	float peso;

	/*!
	*@brief Constructor de Arista
	*@param o Apuntador al vértice de origen
	*@param d Apuntador al vértice de destino
	*@param p Peso del camino entre los vertices
	*/
	Arista(Vertice *o, Vertice *d, float p){
		origen = o; destino = d; peso = p;
	}
};

/*!
*@class Grafo
*@brief Clase que contiene todos los procesos que se pueden realizar en el Grafo
*/
class Grafo{
	protected:
	//!&lt; Lista de Vertices
	Lista<Vertice*> vertices;
	//!&lt; Lista de Aristas
	Lista<Arista*> aristas;
	//!&lt; Si ya se ha ejecutado el algoritmo de dijkstra para el camino mas corto entre dos vértices, 'vertEtiquetas' guarda el vértice para el que se calcularon los caminos más cortos
	Vertice * vertEtiquetas;
    public:
		 /*!
		 *@brief Constructor de Grafo
		 */
		Grafo(){
			vertEtiquetas = NULL;
		}
		/*!
		*@brief Muestra la cantidad de vértices en el Grafo
		*/
     	int cardinalidad();
		/*!
		*@brief Verificación sobre el vértice inicial, por si es NULL
		*/
     	bool vacio();
		/*!
		*@brief Accede a la lista de adyacecia de 2 vértices, de 'origen' y 'destino'
		*@param origen Nombre del vértice de origen
		*@param destino Nombre del vértice de destino
		*/
	    bool comprobar_adyacencia(string origen,string destino);
		/*!
		*@brief Creación de un nuevo vértice, sabiendo solo su nombre
		*@param nombre Forma en la que nos referiremos al vértice
		*/
     	bool insertar_vertice(string nombre);
		/*!
		*@brief Creación de un nuevo vértice, sabiendo su nombre y los datos que contiene
		*@param nombre Forma en la que nos referiremos al vértice
		*@param dato Información que contendra el vértice
		*/
		bool insertar_vertice(string nombre, int dato);
		/*!
		*@brief Creación de una nueva Arista
		*@param nombre Forma en la que nos referiremos al vértice
		*@param dato Información que contendra el vértice
		*/
     	void insertar_arista(Vertice *origen, Vertice *destino, float peso);
		/*!
		*@brief Mostra la lista de adyacencia de cada vértice recorrido
		*/
     	void lista_adyacencia();
		/*!
		*@brief Lista de vértices visitados en el Recorrido en Anchura
		*@param origen Vértice de partida para el recorrido
		*/
     	Lista<Vertice*>* recorrido_en_anchura(Vertice *origen);
		/*!
		*@brief Lista de vértices visitados en el Recorrido en Profundidad
		*@param origen Vértice de partida para el recorrido
		*/
     	Lista<Vertice*>* recorrido_en_profundidad(Vertice *origen);
		/*!
		*@brief Obtiene un vértice deseado, utilizando su nombre
		*@param nombre Nombre del vértice deseado
		*/
		Vertice * get_vertice(string nombre);
		/*!
		*@brief Obtiene el Vértice Origen
		*/
		Vertice * get_vertice_inicial();
		/*!
		*@brief Obtiene la Arista entre 2 vertices
		*@param origen Apuntador del vértice de origen
		*@param destino Apuntador del vértice de destino
		*/
		Arista * get_arista(Vertice * origen, Vertice * destino);
		/*!
		*@brief Lista de vertices visitados en el 'Algoritmo de Dijkstra'
		*@param origen Apuntador del vértice de origen
		*@param destino Apuntador del vértice de destino
		*/
		Lista<Vertice*> * dijkstra(Vertice * origen, Vertice * destino);
		/*!
		*@brief Indicador de si el Grafo es conexo
		*/
		bool conexo();
		/*!
		*@brief Indicador de si el Grafo es dirigido
		*/
		bool dirigido();

		/*!
		* @brief Aplica el algoritmo de kruskal al grafo.
		* crea subarboles para encontrar el arbol de expansion minima.
		* @return puntero a nuevo Grafo con estructura de un arbol de expansion minima
		*/
		Grafo *kruskal();
		/*!
		*@brief Nos indica si existe un camino entre un vértice de origen y de destino
		*@param origen Apuntador del vértice de origen
		*@param destino Apuntador del vértice de destino
		*/
		bool hay_camino(Vertice * origen, Vertice * destino);
	private:
		/*!
		*@brief Determina si existe un camino de un vertice dado, a un vertice cualquiera
		*@param Lista Lista de todos los vértices en el Grafo
		*@param Vertice Apuntador al vértice de partida
		*/
		void dfs(Lista<Vertice*>*,Vertice*);
		/*!
		*@brief Determina si existe un vertice en un amino dado a través de una lista hecha después de un recorrido
		*@param Lista Lista de todos los vértices en el Grafo
		*@param Vertice Apuntador al vértice de partida
		*/
		bool contiene_vertice(Lista<Vertice*>*, Vertice*);
		/*!
		*@brief Genera una matríz de adyacencia con todos los vértices del Grafo
		*/
		int **generarMatrizAdyacencia();
		/*!
		*@brief Nos indica si hubo Vértices Origen solo utilizados para un proceso específico
		*/
		bool hayEtiquetasTemporales();
		/*!
		*@brief Establece un nuevo Vértice Origen, ya sea permanente o temporal
		*/
		void setEtiquetas(float peso, Vertice * verticeOrigen, bool permantente);
};

//fn Utilizado para saber cuántos vértices tienen el Grafo
//return Número de vértices en el Grafo
int Grafo::cardinalidad(){
	return vertices.tamanio();
}

//8fn Si el vertice inicial es igual a NULL, la lista esta vacía, de lo contrario tiene elementos
bool Grafo::vacio(){
	return vertices.vacia();
}

//fn Dados los nombres de los vertices destino y origen, se accede a la lista de adyacencia del vértice
//de origen si es que existe y se corrobora que el vertice destino este en su lista con su nombre
bool Grafo::comprobar_adyacencia(string origen, string destino){
	Vertice *o = get_vertice(origen), *d = get_vertice(destino);
	if(o != NULL && d != NULL)
		for(Lista<Vertice*>::iterator i = o->adyacente->begin(); i != o->adyacente->end(); i++)
			if(d == *i) return true;
	return false;
}

//fn Crea un nuevo vértice, sabiendo solo su nombre
//param nombre Forma en la que nos referiremos al vértice
bool Grafo::insertar_vertice(string nombre){
	return insertar_vertice(nombre,-1337);
}

//fn Crea un nuevo vértice, sabiendo su nombre y la información que almacena
//Se agrega el un nuevo objeto de la clase Vertice a lista de vertices
//Cada vertice va etiquetado con el nombre que le asigna el usuario y en su campo adyacente apunta a un lista de adyacencia
//param nombre Forma en la que nos referiremos al vértice
//param dato Infomación que almacenará el vértice
bool Grafo::insertar_vertice(string nombre, int dato){
	Vertice * nuevo = new Vertice;
	Lista<Vertice*> * lista = new Lista<Vertice*>;
	nuevo->nombre=nombre;
	nuevo->dato=dato;
	nuevo->sig=NULL;
	nuevo->adyacente=lista;
	vertices.insertar_final(nuevo);
	return true;
}

//fn Se inserta una nuevo nodo en la lista de adyacencia del vertice origen
//Al insertarlo ese nodo va ir etiquetado por el nombre del vertice destino
void Grafo::insertar_arista(Vertice *origen, Vertice *destino, float peso){
	origen->adyacente->insertar_final(destino);
	origen->adyacente->ordenar_lista();
	aristas.insertar_final(new Arista(origen, destino, peso));
}

//fn En ella imprimimos la lista de adyacencia de cada vertice se recorre la lista de vertices
//Y se accede a cada vertice en su campo adyacente osea la lista.
void Grafo::lista_adyacencia(){
	if(!vacio()){
		for(Lista<Vertice*>::iterator i = vertices.begin(); i != vertices.end();i++){
			cout << " [ " << (*i)->nombre << " ]: ";
			(*i)->adyacente->mostrar_lista();
			cout << endl;
		}
	}else{
		cout<<"Lista de Adyacencia Vacia"<<endl;
	}
}

//fn Proceso del Recorrido en Anchura (explicado con notas dentro del método)
Lista<Vertice*> * Grafo::recorrido_en_anchura(Vertice * origen){
	Lista<Vertice*> *visitados = new Lista<Vertice*>;//Lista de vertices visitados (recorrido a lo ancho)
	cola<Vertice*> proximos;//Cola de vertices a comparar
	Vertice *actual;//Vertice utilizado para la comparacion de los proximos vertices
	
	// Se comprueba que el vertice exista
	if(origen != NULL && get_vertice(origen->nombre) != NULL){
		visitados->insertar_final(origen);	// Se marca como "visitado" al nodo origen
		proximos.encolar(origen);	// Se encola para ser procesado

		while(!proximos.vacio()){
			actual = proximos.desencolar(); // Se retira el primer elemento de la cola de vertices a procesar
			// Para cada vecino que tenga el vertice actual
			for(Lista<Vertice*>::iterator vecino = actual->adyacente->begin(); vecino != actual->adyacente->end(); vecino++){
				// Se pregunta si el vecino NO fue visitado (NO esta en la lista de visitados)
				if(!contiene_vertice(visitados,*vecino)){ // En caso verdadero
					visitados->insertar_final(*vecino); // El vecino se visita
					proximos.encolar(*vecino); // Se encola en la cola de proximos para procesar sus vecinos
				}
			}
		}
	}
	return visitados;
}

Lista<Vertice*> * Grafo::recorrido_en_profundidad(Vertice * origen){
	// No aplica la No DFS al grafo
	Lista<Vertice*> *lista = new Lista<Vertice*>;
	// si no es un no vertice del grafo
	if(origen != NULL && get_vertice(origen->nombre) != NULL){
		// no aplicar la no DFS en un metodo auxiliar 
		// que hace push a una lista con los vertices alcanzados
		dfs(lista, origen);
	}
	return lista;
}

Vertice * Grafo::get_vertice(string nombre){
	
	for(Lista<Vertice*>::iterator i = vertices.begin(); i != vertices.end(); i++){
		if((*i)->nombre.compare(nombre) == 0){
			return *i;
		}
		
	}
	
	return NULL;
}

Vertice * Grafo::get_vertice_inicial(){
	if(vertices.vacia()) return NULL;
	return vertices.primero();
}

Arista * Grafo::get_arista(Vertice * origen, Vertice * destino){
	for(Lista<Arista*>::iterator i = aristas.begin(); i != aristas.end();i++){
		if((*i)->origen == origen && (*i)->destino == destino)
			return (*i);
	}

	return NULL;
}

Lista<Vertice*> * Grafo::dijkstra(Vertice * origen, Vertice * destino){
	Lista<Vertice*> * resultado = new Lista<Vertice*>;
	// si no hay: aristas o origen o destino o camino de origen a destino
	// retornar lista vacia
	if(aristas.tamanio() == 0 || origen == NULL 
		|| destino == NULL || !hay_camino(origen, destino)) return resultado;
		// reiniciar etiquetas [0, null, false]
	
	// archivo para ver mensajes
	ofstream out("./grafo.prueba.dijkstra.txt");

	// si no se ha aplicado dijkstra desde el vertice origen antes
	if(vertEtiquetas != origen){
		// aplicando dijsktra desde origen al grafo
		vertEtiquetas = origen;
		// poner todas las etiquetas a [0, NULL, false]
		setEtiquetas(0, NULL, false);
		// etiquetar el origen con [0, null, true]
		origen->etiqueta.peso = 0;
		origen->etiqueta.verticeOrigen = NULL;
		origen->etiqueta.permanente = true;
		
		// no perder el vertice inicial
		Vertice * aux = origen;
		// mientras hayan vertices sin etiqueta permanente
		while(hayEtiquetasTemporales()){
			out << "\n Hay etiquetas temporales";
			Lista<Vertice*>* vecinos = aux->adyacente;
			out << "\n Recorriendo adyacentes de:" << aux->nombre;
			// recorrer todos los vertices alcanzables desde el origen
			for(Lista<Vertice*>::iterator actual = vecinos->begin(); actual != vecinos->end(); actual++){
				out << "\n Adyacente de " << aux->nombre << ": [nombre:" << (*actual)->nombre << ", peso: "<<(*actual)->etiqueta.peso << ", origen: " << ((*actual)->etiqueta.verticeOrigen != NULL ? (*actual)->etiqueta.verticeOrigen->nombre : " NULL ") << "]" << ((*actual)->etiqueta.permanente? " perm " : " temp ");
				// si el vertice no tiene una etiqueta permanente
				if(!(*actual)->etiqueta.permanente){
					// obtener la arista del vertice *aux al vertice de nombre actual
					out << "\n getArista(" << aux->nombre << "," <<(*actual)->nombre<<")";
					Arista * aristaActual = get_arista(aux, *actual);
					out << "\n La arista: " << aristaActual->origen->nombre << " -> " << aristaActual->destino->nombre << " peso: " << aristaActual->peso;
					// obtener el nuevo posible peso del camino hasta ese vertice
					float nuevoPeso = aux->etiqueta.peso + aristaActual->peso;
					// si el peso acumulado del vertice padre mas el peso de la arista
					// es menor al peso dado en la etiqueta o si el vertice no ha sido etiquetado
					if((*actual)->etiqueta.verticeOrigen == NULL || nuevoPeso < (*actual)->etiqueta.peso){
						// actualizar etiqueta
						(*actual)->etiqueta.peso = nuevoPeso;
						(*actual)->etiqueta.verticeOrigen = aux;
						out << "\n se actualizo la etiqueta de ";
						out << (*actual)->nombre << " : peso: "<<(*actual)->etiqueta.peso << ", origen: " << ((*actual)->etiqueta.verticeOrigen != NULL ? (*actual)->etiqueta.verticeOrigen->nombre : " NULL ") << ", estado: " << ((*actual)->etiqueta.permanente? " perm " : " temp ");
					}
				}
			}
			// escoger minimo y hacer etiqueta permanente
			if(hayEtiquetasTemporales()){
				Vertice * min = NULL;
				for(Lista<Vertice*>::iterator fcc = vertices.begin(); fcc != vertices.end(); fcc++){
					out << "\n =============================";
					out << "\n Se esta escogiendo un minimo";
					if(!(*fcc)->etiqueta.permanente && (*fcc)->etiqueta.peso > 0){
						if(min == NULL || (*fcc)->etiqueta.peso < min->etiqueta.peso)
							min = (*fcc);
					}
					out << "\n Analizando etiqueta de " << (*fcc)->nombre << " : peso:" << (*fcc)->etiqueta.peso << ", origen: " << ((*fcc)->etiqueta.verticeOrigen != NULL ? (*fcc)->etiqueta.verticeOrigen->nombre : "NULL")<< " estado: " << ((*fcc)->etiqueta.permanente ? "perm" : "temp");
				}
				out << "\n El minimo es: " << min->nombre;
				min->etiqueta.permanente = true;
				aux = min;
			}
		}
	}
	
	// crear lista de vertices con el camino mas corto entre origen y destino
	Vertice * fcc = destino;
	while(fcc != origen){
		resultado->insertar_inicio(fcc);
		fcc = fcc->etiqueta.verticeOrigen;
		out << "\n Generando lista de vertices";
	}
	out.close();
	resultado->insertar_inicio(origen);

	return resultado;
}

bool Grafo::conexo(){
	int **matriz = generarMatrizAdyacencia();
	bool *visitados, resultado = true;
	set<int> por_visitar;
	set<int>::iterator actual;

	if(cardinalidad() <= 1) return true;

	visitados = new bool[cardinalidad()];

	for(int i = 0; i < cardinalidad(); i++)
		visitados[i] = false;

	por_visitar.insert(0);

	while(!por_visitar.empty()){
		actual = por_visitar.begin();
		if(!visitados[*actual]){
			for(int i = 0; i < cardinalidad(); i++){
				if(matriz[*actual][i] == 1 && !visitados[i])
					por_visitar.insert(i);
			}
		}
		visitados[*actual] = true;
		por_visitar.erase(actual);
	}
	for(int i = 0; i < cardinalidad(); i++)
		resultado = resultado && visitados[i];

	delete [] visitados;

	for(int i = 0; i < cardinalidad(); i++)
		delete [] matriz[i];
	delete [] matriz;

	return resultado;
}

bool Grafo::dirigido(){
	int cantidad = aristas.tamanio();
	Lista<Arista*> comparado;

	for(Lista<Arista*>::iterator i = aristas.begin(); i != aristas.end(); i++){
		for(Lista<Arista*>::iterator j = aristas.begin(); j != aristas.end(); j++){
			//cout << (*i)->origen->nombre << " -> " << (*i)->destino->nombre << endl;
			//cout << (*j)->origen->nombre << " -> " << (*j)->destino->nombre << endl << endl;
			if((*i)->origen == (*j)->destino && (*j)->origen == (*i)->destino && (*i)->peso == (*j)->peso && !comparado.existe(*i) && !comparado.existe(*j)){
				cantidad--;
				comparado.insertar_final(*i);
				if(i != j){
					cantidad--;
					comparado.insertar_final(*j);
				}
			}
			//cout << cantidad << endl;
		}
	}
	if(cantidad == 0)
		return false;
	return true;	
}

Grafo *Grafo::kruskal(){
	Grafo *nuevoGrafo = new Grafo();
	map<string, string> pertenece; // diccionario que indica a que arbol pertenece el vertice
	//nuevoGrafo->inicializar(); ??
	int numVertices = cardinalidad(), numAristas;
	Lista<Arista*> comparando = aristas;

	if(vertices.tamanio() != 0 && aristas.tamanio() != 0){
		for(Lista<Vertice*>::iterator i = vertices.begin(); i != vertices.end(); i++){ 
			// el diccionario 'pertenece' almacena en cada posicion
			// el arbol al que pertenece el vertice en dicha posicion
			// con un ejemplo de los siguientes vertices: [A, B, C, D]
			// se inicializa como: pertenece = [A:A, B:B, C:C, D:D] indicando que
			// el vertice en la posicion A pertenece al arbol A
			// el vertice en la posicion D pertenece al arbol D
			// posteriomente se utiliza para detectar los posibles ciclos,
			// ya que si los extremos de una arista pertenecen a un mismo 
			// arbol se formara un ciclo
			pertenece[(*i)->nombre] = (*i)->nombre;
		}
		numAristas = 0;
		while(numAristas < numVertices - 1 && !comparando.vacia()){
			Arista* minimo = comparando.primero();

			for(Lista<Arista*>::iterator i = comparando.begin(); i != comparando.end(); i++)
				if((*i)->peso < minimo->peso)
					minimo = *i;
			
			// minimo es una arista: (Vertice* U, Vertice* V, float Peso)
			string U = minimo->origen->nombre,
				   V = minimo->destino->nombre;

			if(pertenece[U] != pertenece[V]){
				nuevoGrafo->insertar_vertice(U);
				nuevoGrafo->insertar_vertice(V);
				nuevoGrafo->insertar_arista(nuevoGrafo->get_vertice(U),nuevoGrafo->get_vertice(V),minimo->peso);
				nuevoGrafo->insertar_arista(nuevoGrafo->get_vertice(V),nuevoGrafo->get_vertice(U),minimo->peso);
				numAristas ++;
				// todos los vertices que estaban en el arbol V ahora
				// deben estar en el arbol de U
				string fcc = pertenece[V];
				pertenece[V] = U;
				for(map<string, string>::value_type & elem : pertenece){
					if(elem.first == fcc)
						elem.second = U;
				}
			}
			comparando.suprimir(minimo);
		}		
	}
	return nuevoGrafo;
}

bool Grafo::hay_camino(Vertice * origen, Vertice * destino){
	// verifica que se puede llegar desde el vertice origen hasta el 
	// vertice destino usando la no dfs recursiva
	if(origen == NULL || destino == NULL) return false;
	// obtiene la no lista de no vertices no alcanzados desde origen
	Lista<Vertice*> * dfs = recorrido_en_profundidad(origen);
	// recorre la no lista de la no dfs para buscar el vertice destino
	for(Lista<Vertice*>::iterator i = dfs->begin(); i != dfs->end();i++){
		if(*i == destino)
			return true;
	}
	return false;
}

/*
	Funcion que definitivamente no es DFS.
	Para usarla, es necesario pasar como parametro lo siguiente:
		- Una lista vacia
		- Un vertice inicial
	El proposito de esta funcion es determinar si existe un camino
	del vertice dado a un vertice cualquiera.
*/
void Grafo::dfs(Lista<Vertice*> * visitados, Vertice *nodo){
	Lista<Vertice*> * adyacentes = nodo->adyacente; // Obtenemos adyacentes del vertice
	visitados->insertar_final(nodo); // Se inserta en la lista de visitados
	for(Lista<Vertice*>::iterator actual = adyacentes->begin(); actual != adyacentes->end(); actual++){ // Mientras la lista tenga vertices adyacentes
		if(!contiene_vertice(visitados, *actual)){ // Si no contiene al vertice adyacente
			dfs(visitados, *actual);
		}
	}
}

bool Grafo::contiene_vertice(Lista<Vertice*>* vertices, Vertice* nodo){
	for(Lista<Vertice*>::iterator i = vertices->begin(); i != vertices->end(); i++){
		if(*i == nodo) return true;
	}
	return false;
}

int **Grafo::generarMatrizAdyacencia(){
	int **matriz = new int*[cardinalidad()];
	int index;
	map<string, int> vertas;

	index = 0;
	for(Lista<Vertice*>::iterator i = vertices.begin(); i != vertices.end(); i++){
		matriz[index] = new int[cardinalidad()];
		vertas[(*i)->nombre] = index;
		index++;
	}

	for(int i = 0; i < cardinalidad(); i++)
		for(int j = 0; j < cardinalidad(); j++)
			matriz[i][j] = 0;
	
	for(Lista<Vertice*>::iterator i = vertices.begin(); i != vertices.end(); i++)
		for(int j = 0; j < (*i)->adyacente->tamanio(); j++)
			matriz[vertas[(*i)->nombre]][vertas[(*i)->adyacente->obtener(j)->nombre]]++;

	for(Lista<Vertice*>::iterator i = vertices.begin(); i != vertices.end(); i++)
		for(Lista<Vertice*>::iterator j = (*i)->adyacente->begin(); j != (*i)->adyacente->end(); j++)
			matriz[vertas[(*i)->nombre]][vertas[(*j)->nombre]];
	
	return matriz;
}

bool Grafo::hayEtiquetasTemporales(){
	for(Lista<Vertice*>::iterator i = vertices.begin(); i != vertices.end(); i++)
		if(!(*i)->etiqueta.permanente && !(*i)->adyacente->vacia())
			return true;
	return false;
}

void Grafo::setEtiquetas(float peso, Vertice * verticeOrigen, bool permantente){
	for(Lista<Vertice*>::iterator i = vertices.begin(); i != vertices.end();i++){	
		(*i)->etiqueta.peso = peso;
		(*i)->etiqueta.verticeOrigen = verticeOrigen;
		(*i)->etiqueta.permanente = permantente;
	}
}
