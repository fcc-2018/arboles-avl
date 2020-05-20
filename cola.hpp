/*
    * Integrantes del equipo 
    * Batres Pedroza Alejandro          201836943
    * Garcia Gonzalez Jorge             201847512
    * Mendez Mendez Sebastian           201836190
    * Segura Cuanalo Ricardo Alejandro  201848777
*/


/**
  * @file cola.hpp
  * @brief Definicion de la clase cola 
  * @version 1.0
  * @date 22/05/2020
  * @title Clase Cola 
  * @author Team JAVASTANTICO
  */

#include <iostream>
#include "lista.hpp"

/**
  * @class cola
  * @brief Clase para formar el TDA cola
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
  * @return Valor boleano que nos indica si esta vacia la cola
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
