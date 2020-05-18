/*
    * Integrantes del equipo 
    * Batres Pedroza Alejandro          201836943
    * Garcia Gonzalez Jorge             201847512
    * Mendez Mendez Sebastian           201836190
    * Segura Cuanalo Ricardo Alejandro  201848777
*/
/*Objetivo: Hacer la implementacion del tipo de dato abstracto cola de forma dinamica que se construye apartir de nodos
HACIENDO USO DE TEMPLATES
los metodos de esta practica son los unicos que se utlizan dentro de la clase grafo
*/
#include <iostream>

template<class TIPO> class cola;

template<class TIPO>//AL USAR NUESTRA CLASE COMO UNA PLATILLA NOS PERMITE ANTEPONERNOS A UN FORMATO ESPECIFICO DE DATO
//SU UTLIDAD SE VE EN LA CLASE GRAFO
class nodo {//definicion de la clase nodo
   public:
      nodo(TIPO v, nodo<TIPO> *sig = NULL) {//constructor de la clase nodo
         valor = v;
         siguiente = sig;//atributos
      }

   private:
      TIPO valor;
      nodo<TIPO> *siguiente;//apuntador
      friend class cola<TIPO>;//el comando apuntador nos permite  acceder a los atributos y metodos desde la clase cola 
};


template<class TIPO>
class cola {//definicion de la clase cola
   public:
      cola() : primero(NULL), ultimo(NULL) {}//constructor
      //METODOS DE LA CLASE//
      bool vacio();
      void encolar(TIPO v);
      TIPO desencolar();

   private:
      nodo<TIPO> *primero, *ultimo;//PUNTEROS PRIMERO, ULTIMO O ATRAS, FRENTE... COMO LO VIMOS EN CLASE =)
};


template<class TIPO>
bool cola<TIPO>::vacio(){ 
	return primero == NULL;
}

template<class TIPO>
void cola<TIPO>::encolar(TIPO v) {
   nodo<TIPO> *nuevo;

   /* Crear un nodo nuevo */
   /* Este ser� el �ltimo nodo, no debe tener siguiente */
   nuevo = new nodo<TIPO>(v);
   /* Si la cola no estaba vac�a, a�adimos el nuevo a continuaci�n de ultimo */
   if(ultimo) ultimo->siguiente = nuevo;
   /* Ahora, el �ltimo elemento de la cola es el nuevo nodo */
   ultimo = nuevo;
   /* Si primero es NULL, la cola estaba vac�a, ahora primero apuntar� tambi�n al nuevo nodo */
   if(!primero) primero = nuevo;
}

template<class TIPO>
TIPO cola<TIPO>::desencolar() {
    nodo<TIPO> *Nodo; /* variable auxiliar para manipular nodo */
    TIPO v;      /* variable auxiliar para retorno */

   /* Nodo apunta al primer elemento de la pila */
   Nodo = primero;
   if(!Nodo) return 0; /* Si no hay nodos en la pila retornamos 0 */
   /* Asignamos a primero la direcci�n del segundo nodo */
   primero = Nodo->siguiente;
   /* Guardamos el valor de retorno */
   v = Nodo->valor;
   /* Borrar el nodo */
   delete Nodo;
   /* Si la cola qued� vac�a, ultimo debe ser NULL tambi�n*/
   if(!primero) ultimo = NULL;
   return v;
}
