/*
    * Integrantes del equipo *
    * Batres Pedroza Alejandro          201836943
    * Garcia Gonzalez Jorge             201847512
    * Mendez Mendez Sebastian           201836190
    * Segura Cuanalo Ricardo Alejandro  201848777
*/
/*Objetivo: Hacer la implementacion del tipo de dato abstracto pila de forma dinamica que se construye apartir de nodos
HACIENDO USO DE TEMPLATES
los metodos de esta practica son los unicos que se utlizan dentro de la clase grafo
*/


#include <iostream>

template<class TIPO> class pila;

template<class TIPO>//AL USAR NUESTRA CLASE COMO UNA PLATILLA NOS PERMITE ANTEPONERNOS A UN FORMATO ESPECIFICO DE DATO
//SU UTLIDAD SE VE EN LA CLASE GRAFO
class nodos {//Se le puso 'nodos' y no 'nodo' para evitar problemas de sobreescritura con cola.cpp
   public:
      nodos(TIPO v, nodos<TIPO> *sig = NULL) {//constructor de la clase
         valor = v;
         siguiente = sig;//atributos de la clase
      }

   private:
      TIPO valor;
      nodos<TIPO> *siguiente;//puntero

      friend class pila<TIPO>;//el comando friend class nos permite acceder a los atributos y metodos desde la clase pila
};

template<class TIPO>
class pila {
   public:
      pila() : ultimo(NULL) {}//constructor de la clase
      //METODOS DE LA CLASE PILA//
	  bool vacia();
      void apilar(TIPO v);
      TIPO desapilar();

   private:
      nodos<TIPO> *ultimo;//apuntador al ultimo elemento de la pila
};

template<class TIPO>
bool pila<TIPO>::vacia(){//Comprobar si la pila esta vacia
	return ultimo == NULL;
}

template<class TIPO>
void pila<TIPO>::apilar(TIPO v) {
   nodos<TIPO> *nuevo;

   /* Crear un nodo nuevo */
   nuevo = new nodos<TIPO>(v, ultimo);
   /* Ahora, el comienzo de nuestra pila es en nuevo nodo */
   ultimo = nuevo;
}

template<class TIPO>
TIPO pila<TIPO>::desapilar(){
    nodos<TIPO> *Nodo; /* variable auxiliar para manipular nodo */
    TIPO v;      /* variable auxiliar para retorno */

    if(!ultimo) return 0; /* Si no hay nodos en la pila retornamos 0 */
    /* Nodo apunta al primer elemento de la pila */
    Nodo = ultimo;
    /* Asignamos a pila toda la pila menos el primer elemento */
    ultimo = Nodo->siguiente;
    /* Guardamos el valor de retorno */
    v = Nodo->valor;
    /* Borrar el nodo */
    delete Nodo;
    return v;
}
