/*
    * Integrantes del equipo *
    * Batres Pedroza Alejandro          201836943
    * Garcia Gonzalez Jorge             201847512
    * Mendez Mendez Sebastian           201836190
    * Segura Cuanalo Ricardo Alejandro  201848777
*/
/*Objetivo: Hacer la implementacion del tipo de dato abstracto lista de forma dinamica que construye apartir de nodos
los metodos de esta practica 
*/
#include <iostream>
#include <string.h>
#define INVALID -1337


// funcion para salir del programa cuando haces cosas malas xD
void require(bool condicion, std::string mensaje){
	if(!condicion){
		std::cout << "\n" << mensaje;
		exit(1);
	}
}

template <typename tipo>
class Lista{
public:
	/* Metodos de la lista */
	tipo* get(int pos);
    bool insertar_inicio(tipo el);
    bool insertar_final(tipo destino);
    tipo suprimir_inicio();
    tipo suprimir_final();
	bool suprimir(tipo);
    bool vacia();
    tipo primero();
    tipo ultimo();
    void eliminar_duplicados();
    int buscar_elemento(std::string nombre);
	std::string obtener_nombre(int indice);
	tipo obtener(int indice);
	bool existe(tipo dato);
    void mostrar_lista();
	void ordenar_lista();
    Lista():lista(NULL), tam(0){}
    int tamanio();
	friend class iterator;
	/* Subclases */
	class Nodo{
    public:
        Nodo * sig; 
        tipo dato; // dato cualquiera
        std::string nombre; // nombre del nodo
        Nodo(): sig(NULL){}
        Nodo(tipo d): sig(NULL), dato(d){}
        Nodo(std::string nombre, tipo d):sig(NULL),nombre(nombre),dato(d){}
    };
	/* Definir un puntero a Nodo */
    typedef Nodo * pNodo;

	class iterator{
		Lista<tipo>& l;
		Nodo * actual;
		int index;
		public:
		// para definir begin()
		iterator(Lista<tipo>& il) : l(il), index(0), actual(il.lista) {}
		// para definir end()
		iterator(Lista<tipo>& il, bool) : l(il), index(il.tam), actual(il.lista) {}
		// ++++ juasjuas
		tipo operator++() { // ++i
			require(index < l.tam, 
			"iterador movido fuera de rango");
			actual = actual->sig;
			index ++;
			return actual->dato;
		}
		// juasjuas ++++

		tipo operator++(int) { // i++
			require(index < l.tam, 
			"iterador movido fuera de rango");
			tipo dat = actual->dato;
			actual = actual->sig;
			index ++;
			return dat;
		}

		// aumentar una cantidad determinada de elementos
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

		// para wachar si estas en el final de la lista / o comparar iteradores
		iterator & operator=(const iterator& aa) {
			if(this != &aa){
				index = aa.index;
				actual = aa.actual;
				l = aa.l;
			}
			return *this;
		}

		// para obtener el valor del actual xD
		tipo& operator*() {
			require(index < l.tam, 
			"iterador movido fuera de rango");
			return actual->dato;
		}

		// para wachar si estas en el final de la lista / o comparar iteradores
		bool operator==(const iterator& rv) const {
			return index == rv.index;
		}
		// el iterador es distinto de otro iterador ? 
		bool operator!=(const iterator& rv) const {
			return index != rv.index;
		}
		// obtener el elemento actual
		tipo current() const { return actual->dato; }
		// para imprimir en pantalla 
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
