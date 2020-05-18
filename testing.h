#include <iostream>

#define TEST_NULL "TEST IS NULL"

// algunas funciones para evitar escribir mucho...
// cout << "mensaje chido para saber que algo funciona bien" << variable <<  " mas cosas etc etc";
// tambien sirve para ahorrar tiempo quitando mensajes de prueba
// si se pone a false la variable debug_mode no mostrara ningun mensaje
namespace cu{

std::string promt = "[DEBUG]";
bool debug_mode = true;
void test(std::string str){
    if(debug_mode)
        std::cout << "\n" << promt <<" " << str << std::endl;
}

void test(std::string str, std::string str2){
    if(debug_mode)
        std::cout << "\n" << promt <<" " << str << " " << str2 << std::endl;
}

void test(std::string str, int dato){
    if(debug_mode)
	    std::cout << "\n" << promt <<" " << str << " : " << dato << "\n";
}

void test(std::string str, int dato, int res){
    if(debug_mode)
	    std::cout << "\n" << promt <<" " << str << " [" << dato << "] result ["<< res <<"]\n";
}
void test(std::string str, bool cond, std::string msg1, std::string msg2){
    if(debug_mode)
	    std::cout << "\n" << promt <<" " << str << " : " << (cond? msg1: msg2) << "\n";
}

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

