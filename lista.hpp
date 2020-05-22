/*Objetivo: Hacer la implementacion del tipo de dato abstracto lista de forma dinamica que construye apartir de nodos
los metodos de esta practica 
*/

#ifndef LISTA_HPP
#define LISTA_HPP

/**!
  * \file lista.hpp
  * @brief Definicion de la clase Lista 
  * @version 1.0
  * @date 22/05/2020
  * @title Clase Lista 
  * @author Team JAVASTANTICO
  */
#include <iostream>
#include <string.h>
#define INVALID -1337



/**
  * @brief funcion para salir del programa cuando sucede algo indebido
  * @param mensaje string de salida
  * @return fin de la ejecucion
  */
  
// funcion para salir del programa cuando haces cosas malas xD
void require(bool condicion, std::string mensaje){
	if(!condicion){
		std::cout << "\n" << mensaje;
		exit(1);
	}
}


/**
  * @class Lista
  * @brief Clase TDA Lista con diversas operaciones
  */
  
template <typename tipo>
class Lista{
public:
	/* Metodos de la lista */
	
/**
  * @brief Funcion para retornar el dato de un nodo dado su posicion
  * @param La posicion
  * @return El dato de ese nodo
  */
	tipo* get(int pos);
/**
  * @brief Funcion para insertar al inicio de la lista
  * @param TDA o elemento a insertar.
  * @return Valor boleano que nos dice si fue exitoso o no el procedimiento
  */
    bool insertar_inicio(tipo el);
/**
  * @brief Funcion para insertar al final de la lista
  * @param TDA o elemento a insertar.
  * @return Valor boleano que nos dice si fue exitoso o no el procedimiento
  */
    bool insertar_final(tipo destino);
/**
  * @brief Funcion para suprimir al inicio de la lista
  * @return Dato del elemento suprimido
  */
    tipo suprimir_inicio();
/**
  * @brief Funcion para suprimir al final de la lista
  * @return Dato del elemento suprimido
  */
    tipo suprimir_final();
/**
  * @brief Funcion para suprimir un elemento en cualquier posicion de la lista
  * @param El dato del elemento a suprimir
  * @return Valor boleano que nos dice si fue exitoso o no el procedimiento 
  */
	bool suprimir(tipo);
/**
  * @brief Funcion para saber si esta vacia la lista
  * @return Valor boleano que nos dice si esta vacia o tiene elementos
  */
    bool vacia();
/**
  * @brief Funcion para obtener el primer elemento de la lista
  * @return Elemento al inicio de la lista
  */
    tipo primero();
/**
  * @brief Funcion para obtener el ultimo elemento de la lista
  * @return Elemento al final de la lista
  */
    tipo ultimo();
/**
  * @brief Funcion para eliminar los elementos duplicados en la lista
  */
    void eliminar_duplicados();
/**
  * @brief Funcion para buscar un elemento de la lista
  * @param Dato del elemento a buscar
  * @return Posicion que ocupa dentro la lista
  */
    int buscar_elemento(std::string nombre);
/**
  * @brief Funcion para obtener el nombre de un elemento de la lista
  * @param Indice del elemento en la lista
  * @return Dato del elemento buscado en la lista
  */
	std::string obtener_nombre(int indice);
/**
  * @brief Funcion para obtener el elemento de una lista
  * @param Indice del elemento en la lista
  * @return Elemento buscado en la lista
  */
	tipo obtener(int indice);
/**
  * @brief Funcion para saber si existe un elemento en la lista
  * @param Dato de elemento a buscar
  * @return Valor boleano que nos dice si existe o no ese elemento
  */
	bool existe(tipo dato);
/**
  * @brief Funcion para mostrar la lista
  */
    void mostrar_lista();
/**
  * @brief Funcion para ordenar la lista
  */
	void ordenar_lista();
/**
  * @brief Constructor de la clase Lista
  */
    Lista():lista(NULL), tam(0){}
    //!&lt; Tama�o de la lista
    int tamanio();
    /**
     * @brief iterador adicional.
     * @relates iterator
     */
	friend class iterator;
	/* Subclases */
	
/**
  * @class Nodo
  * @brief Clase que funciona como unidad basica en el TDA Lista.
  */
  
	class Nodo{
    public:
    	 //!&lt; Capo siguiente de nodo
        Nodo * sig; 
         //!&lt; Dato cualquiera
        tipo dato; // dato cualquiera
         //!&lt; Nombre del nodo
        std::string nombre; // nombre del nodo
/**
  * @brief Constructor de la clase Nodo
  */
        Nodo(): sig(NULL){}
/**
  * @brief Constructor de la clase Nodo
  * @param Dato
  */
        Nodo(tipo d): sig(NULL), dato(d){}
/**
  * @brief Constructor de la clase Nodo
  * @param Nombre del nodo
  * @param Dato
  */
        Nodo(std::string nombre, tipo d):sig(NULL),nombre(nombre),dato(d){}
    };
 //!&lt; Puntero a nodo
    typedef Nodo * pNodo;
    
/**
  * @class iterator
  * @brief Clase que ayuda a acceder a los elementos del TDA Lista
  */

	class iterator{
		 //!&lt; Referencia a lista
		Lista<tipo>& l;
		//!&lt; Puntero al nodo actual
		Nodo * actual;
		//!&lt; Indice de referencia
		int index;
		public:
/**
  * @brief Constructor de la clase iterator para definir el inicio
  * @param Referencia a lista
  */
		iterator(Lista<tipo>& il) : l(il), index(0), actual(il.lista) {}
/**
  * @brief Constructor de la clase iterator para definir el final
  * @param Referencia a lista
  * @param Valor boleano
  */
		iterator(Lista<tipo>& il, bool) : l(il), index(il.tam), actual(il.lista) {}
		// ++++ juasjuas
/**
  * @brief Funcion para aumentar el indice iterador
  * @return Dato del nodo actual
  */
		tipo operator++() { // ++i
			require(index < l.tam, 
			"iterador movido fuera de rango");
			actual = actual->sig;
			index ++;
			return actual->dato;
		}
		// juasjuas ++++
/**
  * @brief Funcion para aumentar el indice iterador
  * @param Indice
  * @return Dato del nodo actual
  */
		tipo operator++(int) { // i++
			require(index < l.tam, 
			"iterador movido fuera de rango");
			tipo dat = actual->dato;
			actual = actual->sig;
			index ++;
			return dat;
		}

/**
  * @brief Funcion para aumentar la cantidad predeterminada de elementos
  * @param Cantidad de elementos
  * @return Referencia de iterator
  */
		iterator& operator+=(int amount) {
			require(index + amount < l.tam,
				"Lista<tipo>::iterator::operator+=() \n intento de moverse fuera de rango");
			int i = 0;
			// no se va a pasar a null porque se comprueba arriba si
			// existen los elementos necesarios para avanzar
			while(i < amount) { actual = actual->sig; i++; }
			index += amount;
			return *this;
		}
/**
  * @brief Funcion para ver si estas en el final de la lista / o comparar iteradores
  * @param Referenca de iterator
  * @return Referencia de iterator
  */
		iterator & operator=(const iterator& aa) {
			if(this != &aa){
				index = aa.index;
				actual = aa.actual;
				l = aa.l;
			}
			return *this;
		}
/**
  * @brief Funcion para obtener el valor del actual 
  * @return Valor del nodo actual
  */
		tipo& operator*() {
			require(index < l.tam, 
			"iterador movido fuera de rango");
			return actual->dato;
		}
/**
  * @brief Funcion para ver si estas en el final de la lista / o comparar iteradores 
  * @param Referencia a iterator
  * @return Valor boleano que nos indica si estamos al final de la lista o son iguales los iteradores
  */
		bool operator==(const iterator& rv) const {
			return index == rv.index;
		}
/**
  * @brief Funcion para saber si el iterador es distinto de otro iterador ? 
  * @param Referencia a iterator
  * @return Valor boleano que nos indica si el iterador es distinto de otro iterador
  */
		bool operator!=(const iterator& rv) const {
			return index != rv.index;
		}
/**
  * @brief Funcion para obtener el elemento actual
  * @return valor del nodo actual
  */
		tipo current() const { return actual->dato; }
		
/**
  * @brief Funcion para imprimir en pantalla
  * @param os ostream& 
  * @param Referencia constante de un iterator
  * @return Operator ostream&
  */
		friend std::ostream& operator<<(std::ostream& os, const iterator& it) {
			return os << it.current();
		}
	};
	
	iterator begin() { return iterator(*this); }
	// crear el iterador de a mentis para end:
	iterator end() { return iterator(*this, true); }

	// operadores
	Lista<tipo> & operator=(Lista<tipo> & aa){
		if(this != &aa){
			while(!vacia())
				suprimir_inicio();
			Nodo * aux = aa.lista;
			while(aux != NULL){
				insertar_final(aux->dato);
				aux = aux->sig;
			}
		}
		return *this;
	}
	// lista[n]
	tipo * operator[](int i) {
		if(i < 0 || i > tam) return NULL;
		pNodo aux = lista;
		int j = 0;
		while(aux != NULL && j < i) {
			aux = aux->sig;
			j++;
		}
		return &(aux->dato);
	}

private:
	/* Atributos */
    pNodo lista;
    int tam;
};

template <typename tipo>
tipo * Lista<tipo>::get(int index){
	if(index < 0 || index >= tam) return NULL;
	pNodo aux = lista;
	int j = 0;
	while(aux != NULL && j < index) {
		aux = aux->sig;
		j++;
	}
	return &(aux->dato);
}

/* 
	Inserta un nuevo elemento al final de la lista 
	retorna: true si fue correcta la insercion
			 false si no hay memoria suficiente para crear un nodo
*/
template <typename tipo>
bool Lista<tipo>::insertar_inicio(tipo elem){
	// (nothrow) en lugar de parar el programa 
	// si no hay espacio en memoria devuelve NULL
    pNodo nuevo = new (std::nothrow)Nodo(elem);
    if(nuevo == 0) return false;
	// formar nuevo elemento adelante de *lista
    nuevo->sig = lista;
    lista = nuevo;
	tam++;
    return true;
}
/* 
	Inserta un nuevo elemento al final de la lista 
	retorna: true si fue correcta la insercion
			 false si no hay memoria suficiente para crear un nodo
*/
template <typename tipo>
bool Lista<tipo>::insertar_final(tipo destino){
	// (nothrow) en lugar de parar el programa 
	// si no hay espacio en memoria devuelve NULL
    pNodo nuevo = new (std::nothrow)Nodo(destino);
	require(nuevo != 0, "Error al solicitar memoria en tiempo de ejecucion");
    if(lista==NULL){
        lista = nuevo;
    } else {
		
		// caso lista no vacia
        pNodo aux = lista;
		// encontrar el ultimo elemento
		
        while(aux->sig != NULL)
            aux = aux->sig;
		// apuntar al nuevo elemento
        aux->sig = nuevo;
    }
	
    tam++;
    return true;
}

/*
	Elimina el elemento que se encuentra al inicio 
	de la lista.
	retorna: int elemento si la lista tiene elementos
			 INVALID si la lista esta vacia
*/
template <typename tipo>
tipo Lista<tipo>::suprimir_inicio(){
	// valor por defecto
	tipo dato;
	require(!vacia(), "La lista esta vacia!, tipo Lista<tipo>::suprimir_inicio()");
	pNodo aux = lista;
	lista = lista->sig;
	dato = aux->dato;
	tam--;
	delete aux;
	return dato;
}

/*
	Elimina el elemento que se encuentra al final 
	de la lista.
	retorna: int elemento si la lista tiene elementos
			 INVALID si la lista esta vacia
*/
template <typename tipo>
tipo Lista<tipo>::suprimir_final(){
	tipo dato;
	require(!vacia(), "La lista esta vacia!, tipo Lista<tipo>::suprimir_final()");
	// si solo tiene un elemento
	if(lista->sig == NULL){
		dato = lista->dato;
		delete lista;
		lista = NULL;
	}else{
	// si tiene mas de un elemento
		pNodo aux = lista;
		while(aux->sig->sig != NULL)
			aux = aux->sig;
		dato = aux->sig->dato;
		delete aux->sig;
		aux->sig = NULL;
	}
	tam--;
	return dato;
}


/*
	Suprime el elemento de la lista coincidiente con
	el dato pasado por parametro
*/
template <typename tipo>
bool Lista<tipo>::suprimir(tipo dato){
	require(!vacia(), "La lista esta vacia!, tipo Lista<tipo>::suprimir()");
	pNodo aux, prev;
	aux = prev = lista;
	while(aux != NULL){
		if(aux->dato != dato){
			prev = aux;
			aux = aux->sig;
			continue;
		}
		break;
	}
	if(aux != NULL){
		if(aux == lista)
			lista = lista->sig;
		else
			prev->sig = prev->sig->sig;
		delete aux;
		tam--;
		return true;
	}
	return false;
}

/*
	Comprueba si el apuntador raiz (lista)
	es nulo, es decir si la lista no tiene elementos
*/
template <typename tipo>
bool Lista<tipo>::vacia(){
    return (lista == NULL);
}

template <typename tipo>
int Lista<tipo>::tamanio(){
    return tam;
}

/*
	Busca un elemento en la lista
	retorna int posicion si valor esta en la lista
			INVALID si el elemento no se encontro
*/
template <typename tipo>
int Lista<tipo>::buscar_elemento(std::string destino)
{
	int i = 1;
	// no perder la referencia al inicio de la lista
	pNodo aux = lista;

	// buscar
    while(aux!=NULL)
    {
        if(aux->nombre==destino)
        {
           	return i;
        }
        aux = aux->sig;
        i++;
    }
	return INVALID;
}

template <typename tipo>
std::string Lista<tipo>::obtener_nombre(int indice){
	int i = 0;
	pNodo temporal = lista;
	while(temporal != NULL){
		if(indice == i)
			return temporal->nombre;
		temporal = temporal->sig;
		i++;
	}

	return "NULL";
}

template <typename tipo>
tipo Lista<tipo>::obtener(int indice){
	if(indice < 0 || indice > tam) return NULL;
	pNodo aux = lista;
	int i = 0;
	while(aux != NULL && i < indice) {
		aux = aux->sig;
		i++;
	}
	return aux->dato;
}

template <typename tipo>
bool Lista<tipo>::existe(tipo dato){
	pNodo aux = lista;
	while(aux != NULL){
		if(aux->dato == dato)
			break;
		aux = aux->sig;
	}
	return aux != NULL;
}

/*
	Muestra la lista con estilo FCC
*/
template <typename tipo>
void Lista<tipo>::mostrar_lista(){
	if(!vacia()){
		int i = 0;
		// no destruir la referencia al inicio de la lista
		pNodo aux = lista;
		// recorrer la lista
		while(aux != NULL){
			// mostrar con estilo
			std::cout<< " [ " << aux->dato << " ] -> ";
		    aux = aux->sig;
		    i++;
		}
		std::cout<< "NULL";
	} else
		std::cout<<"Todavia no hay elementos que mostrar";
}

/*
	Retorna el primer elemento de la lista
*/
template <typename tipo>
tipo Lista<tipo>::primero(){
	require(!vacia(), "La lista esta vacia!, tipo Lista<tipo>::primero()");
	return lista->dato;
}

/*
	Retorna el ultimo elemento de la lista
*/
template <typename tipo>
tipo Lista<tipo>::ultimo(){
	require(!vacia(), "La lista esta vacia!, tipo Lista<tipo>::ultimo()");
	// no destruir la referencia al inicio de la lista
	pNodo busqueda = lista;
	// recorrer la lista para llegar al ultimo
	while(busqueda->sig != NULL){
		busqueda = busqueda->sig;
	}
	return busqueda->dato;
}


/*
	Elimina los elementos duplicados de la lista
*/
template <typename tipo>
void Lista<tipo>::eliminar_duplicados(){
	// guardar referencia al inicio de la lista
	pNodo actual = lista;
	// contador de duplicados
	int duplicadosTotales=-1;
	
	if(!vacia()){
		duplicadosTotales=0;
		// recorrer la lista en busca de duplicados
		while(actual!=NULL){
			// guardar nodo anterior
			pNodo anterior = actual;
			// guardar nodo siguiente
			pNodo siguiente = actual->sig;
			// buscar en la lista el elemento "actual" a 
			// partir de "siguiente"
			while(siguiente != NULL){
				// si el dato actual es igual al siguiente
				if(actual->dato == siguiente->dato){
					// conectar el anterior al sucesor del siguiente
					anterior->sig = siguiente->sig;
					duplicadosTotales++;
					tam--;
					// guardar referencia al nodo a eliminar
					pNodo borrado = siguiente;
					// avanzar al siguiente
					siguiente = siguiente->sig;
					// borrar el nodo
					delete(borrado);
				}else{
					// avanzar al siguiente
					anterior = siguiente;
					siguiente = siguiente->sig;
				}
			}
			// avanzar al siguiente a comparar con el
			// resto de la lista
			actual = actual->sig;
		}
	}else{
		std::cout<<"\n La lista esta vacia";
	}

	if(duplicadosTotales==0)
		std::cout<<" La lista no tiene duplicados";
	if(duplicadosTotales>0)
		std::cout<<"\n Duplicados encontrados: "<<duplicadosTotales;
}

template <typename tipo>
void Lista<tipo>::ordenar_lista()
{
     pNodo actual , siguiente;
     std::string t;
     
     actual = lista;
     while(actual->sig != NULL)
     {
          siguiente = actual->sig;
          
          while(siguiente!=NULL)
          {
               if(actual->nombre > siguiente->nombre)
               {
                    t = siguiente->nombre;
                    siguiente->nombre = actual->nombre;
                    actual->nombre = t;          
               }
               siguiente = siguiente->sig;                    
          }    
          actual = actual->sig;
          siguiente = actual->sig;
           
     }
     
    //cout<<"\n\n\tLista ordenada..."<<endl;
}

#endif
