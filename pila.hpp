#include <iostream>
#include "lista.hpp"

/*!
*\file pila.hpp
*\brief Definición de la clase pila y la implementación de sus métodos, haciendo uso de templates
*/

template<class TIPO> class pila;

/*!
* @class pila
* @brief Clase que contiene las operaciones de una pila, haciendo uso de templates
* para evitar limitaciones con los tipos de datos.
*/
template<class TIPO>
class pila : public Lista<TIPO>{
   public:
   /*!
      *@brief Constructor de pila
      */
      pila() : Lista<TIPO>(){}
      /*!
      *@brief Nos indica si la pila está vacía
      *@return Valor booleano que nos indica si esta vacia la pila
      */
	   bool vacio();
      /*!
      *@brief Realiza la operación PUSH, agregando un elemento al final de la pila
      *@param v Elemento que se agregará a la pila
      */
      void apilar(TIPO v);
      /*!
      *@brief Realiza la operación POP, eliminando el último elemento de la pila
      */
      TIPO desapilar();
};

template<class TIPO>
bool pila<TIPO>::vacio(){//Comprobar si la pila esta vacia
	return Lista<TIPO>::vacia();
}

template<class TIPO>
void pila<TIPO>::apilar(TIPO v) {//Insertamos un elemento al final de la pila
   Lista<TIPO>::insertar_final(v);
}

template<class TIPO>
TIPO pila<TIPO>::desapilar(){//Eliminamos un elemento al final de la pila
   return Lista<TIPO>::suprimir_final();
}