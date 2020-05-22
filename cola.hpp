#include <iostream>
#include "lista.hpp"

/**
  * \file cola.hpp
  * @brief Definicion de la clase cola y la implementación de sus métodos, haciendo uso de templates
  * @version 1.0
  * @date 22/05/2020
  * @title Clase Cola 
  * @author Team JAVASTANTICO
  */

/**
  * @class cola
  * @brief Clase para formar el TDA cola, haciendo uso de templates
  * para evitar limitaciones con los tipos de datos.
  */
template<class TIPO>
class cola: public Lista<TIPO>{//definicion de la clase cola
   public:
/**
  * @brief Constructor de la clase cola por defecto
  */
      cola() : Lista<TIPO>() {}//constructor
      //METODOS DE LA CLASE//
/**
  * @brief Funcion para determinar si la cola esta vacia
  * @return Valor booleano que nos indica si esta vacia la cola
  */
      bool vacio();
/**
  * @brief Funcion para encolar un elemento
  * @param Elemento a encolar
  */
      void encolar(TIPO v);
/**
  * @brief Funcion para desencolar un elemento
  * @return Elemento desencolado
  */
      TIPO desencolar();

};


template<class TIPO>
bool cola<TIPO>::vacio(){ 
	return Lista<TIPO>::vacia();
}

template<class TIPO>
void cola<TIPO>::encolar(TIPO v) {
   Lista<TIPO>::insertar_final(v);
}

template<class TIPO>
TIPO cola<TIPO>::desencolar() {
   return Lista<TIPO>::suprimir_inicio();
}
