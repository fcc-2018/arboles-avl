#include <iostream>

#define TEST_NULL "TEST IS NULL"

/*!
 * \file testing.h
 * @brief Cabecera destinada a pruebas de funcionamiento
 * 
 * Archivo de cabecera que contiene un *namespace* con métodos utilizados para probar
 * y monitorear el funcionamiento de las funciones en estudio.
 * <br>
 * Todos los métodos contenidos en él archivo tienen la función de imprimir de
 * manera más práctica en consola mensajes [DEBUG] personalizados por el
 * desarrollador
 * */

// algunas funciones para evitar escribir mucho...
// cout << "mensaje chido para saber que algo funciona bien" << variable <<  " mas cosas etc etc";
// tambien sirve para ahorrar tiempo quitando mensajes de prueba
// si se pone a false la variable debug_mode no mostrara ningun mensaje

/*!
 * @brief Espacio de nombres destinado a funciones utilizadas en la depuración
 * de las funciones en estudio
 * 
 * Contiene funciones *test* que permiten imprimir de manera más práctica directo
 * a consola mensajes de depuración para monitorear de forma más limpia la
 * ejecución de las funciones de interés
 * */
namespace cu{

/*!
 * @brief Texto que indica que se hace referencia a un texto del depurador
 * */
std::string promt = "[DEBUG]";
/*!
 * @brief Booleano que indica si el modo depurador está activado o no, es decir,
 * si está en *true* o *false* respectivamente
 * */
bool debug_mode = true;
/*!
 * @brief Muestra en consola el texto pasado como parámetro
 * @param str texto a imprimir en consola
 * */
void test(std::string str){
    if(debug_mode)
        std::cout << "\n" << promt <<" " << str << std::endl;
}
/*!
 * @brief Muestra en consola los textos pasados como parámetro
 * @param str primer texto a imprimir en consola
 * @param str2 segundo texto a imprimir en consola
 * */
void test(std::string str, std::string str2){
    if(debug_mode)
        std::cout << "\n" << promt <<" " << str << " " << str2 << std::endl;
}
/*!
 * @brief Muestra en consola una descripción y un valor dados
 * @param str descripción del valor
 * @param dato valor numérico
 * */
void test(std::string str, int dato){
    if(debug_mode)
	    std::cout << "\n" << promt <<" " << str << " : " << dato << "\n";
}
/*!
 * @brief Muestra en consola una descripción junto con un valor inicial y un valor
 * como resultado
 * @param str descripción de la operación
 * @param dato valor numérico inicial
 * @param res valor numérico resultante
 * */
void test(std::string str, int dato, int res){
    if(debug_mode)
	    std::cout << "\n" << promt <<" " << str << " [" << dato << "] result ["<< res <<"]\n";
}
/*!
 * @brief Muestra en consola una descripción y, según un valor booleano, decide qué
 * texto mostrar después
 * @param str descripción de las condiciones
 * @param cond booleano determinante
 * @param msg1 texto que se mostrará si el valor booleano es *true*
 * @param msg2 texto que se mostrará si el valor booleano es *false*
 * */
void test(std::string str, bool cond, std::string msg1, std::string msg2){
    if(debug_mode)
	    std::cout << "\n" << promt <<" " << str << " : " << (cond? msg1: msg2) << "\n";
}
/*!
 * @brief Muestra en consola una descripción y, dependiendo del valor booleano dado,
 * mostrará un mensaje "YES" o un mensaje "NO"
 * @param str descripción de la condición
 * @param cond booleano determiante. En caso de ser *true*, se mostrará "YES". En
 * caso contrario (es decir, *false*) se mostrará "NO"
 * */
void test(std::string str, bool cond){
    if(debug_mode)
	    std::cout << "\n" << promt <<" " << str << " : " << (cond? "YES": "NO") << "\n";
}

};


/*

void test(int data, int expect){
    if(data != expect)
        std::cout << "\n[ERROR] Test: " << expect << " expected, " << data << " result\n";
    else 
        std::cout << "\n[CHECK] Test: " << expect << " expected, " << data << " result\n";
}

void test(bool data, bool expect){
    if(data != expect)
        std::cout << "\n[ERROR] Test: " << (expect? "true" : "false") << " expected, " << (data? "true" : "false") << " result\n";
    else 
        std::cout << "\n[CHECK] Test: " << (expect? "true" : "false") << " expected, " << (data? "true" : "false") << " result\n";
}

*/

