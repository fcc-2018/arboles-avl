#include <iostream>

/*!
*\file cola.hpp
*Definición de la clase nodo, cola, y la implementación de sus métodos, haciendo uso de templates
*/

template<class TIPO> class cola;
//AL USAR NUESTRA CLASE COMO UNA PLATILLA NOS PERMITE ANTEPONERNOS A UN FORMATO ESPECIFICO DE DATO, SU UTLIDAD SE VE EN LA CLASE Grafo
template<class TIPO>
/*!
*@class nodo
*@brief Clase que maneja los atributos escenciales de un nodo, haciendo uso de templates
*
*
*AL USAR NUESTRA CLASE COMO UNA PLATILLA NOS PERMITE ANTEPONERNOS A UN FORMATO ESPECIFICO DE DATO, SU UTLIDAD SE VE EN LA CLASE Grafo
*/
class nodo {
   public:
      /*!
      *@brief Constructor de nodo
      *@param v Infomación que almacena el nodo
      *@param sig Apuntador al nodo siguiente (NULL)
      */
      nodo(TIPO v, nodo<TIPO> *sig = NULL) {
         valor = v;
         siguiente = sig;
      }

   private:
      //!&lt; Contiene la información que almacena el nodo
      TIPO valor;
      //!&lt; Apuntador al siguiente nodo
      nodo<TIPO> *siguiente;
      //!&lt; El comando apuntador nos permite  acceder a los atributos y metodos desde la clase cola 
      friend class cola<TIPO>;
};


template<class TIPO>
/*!
*@class cola
*@brief Clase que contiene las operaciones de una cola, haciendo uso de templates
*
*
*AL USAR NUESTRA CLASE COMO UNA PLATILLA NOS PERMITE ANTEPONERNOS A UN FORMATO ESPECIFICO DE DATO, SU UTLIDAD SE VE EN LA CLASE Grafo
*/
class cola {
   public:
      /*!
      *@brief Constructor de cola
      *@param primero Primer elemento en la cola (Por defecto: NULL)
      *@param ultimo Último elemento en la cola (Por defecto: NULL)
      */
      cola() : primero(NULL), ultimo(NULL) {}
      /*!
      *@brief Nos indica si la cola está vacía
      */
      bool vacio();
      /*!
      *@brief Realiza la operación PUSH, agregando un nuevo elemento a la cola
      *@param v Elemento que se agregará a la cola
      */
      void encolar(TIPO v);
      /*!
      *@brief Realiza la operación POP, eliminando un elemento a la cola
      */
      TIPO desencolar();

   private:
      //!&lt; PUNTEROS PRIMERO, ULTIMO O ATRAS, FRENTE.
      nodo<TIPO> *primero, *ultimo;
};


template<class TIPO>
bool cola<TIPO>::vacio(){ 
	return primero == NULL;
}

template<class TIPO>
void cola<TIPO>::encolar(TIPO v) {
   nodo<TIPO> *nuevo;

   /* Crear un nodo nuevo */
   /* Este sería el último nodo, no debe tener siguiente */
   nuevo = new nodo<TIPO>(v);
   /* Si la cola no estaba vacía, añadimos el nuevo a continuación del último */
   if(ultimo) ultimo->siguiente = nuevo;
   /* Ahora, el último elemento de la cola es el nuevo nodo */
   ultimo = nuevo;
   /* Si primero es NULL, la cola estaba vacía, ahora primero apuntaría también al nuevo nodo */
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
