#include <iostream>
#include "arbolAVL.hpp"
#include "menu.h"


int main(){
    ArbolAVL * a1 = new ArbolAVL;
    int dato;
	cout<<"Creando arbol, por favor digite el dato de la raiz: "<<endl;
	cin >> dato;
    a1->insertar(dato);
    	// crear menu automatico xD
	Menu menu(a1, "Arboles AVL");
		// pedir numero al usuario y agregue un vertice
	funcion_menu agregar = [](ArbolAVL* a) -> bool{
		int dato;
		cout<<"\nIngrese el dato del nodo: ";
		cin>>dato;
		a->insertar(dato);
		// indica que no debe salir aun del bucle del menu
		return false;
	};
	menu.agregar_opcion("Agregar nodo", &agregar);
	funcion_menu salir = [](ArbolAVL*a) -> bool{
		// retornar true para salir del bucle del menu
		return true;
	};
	menu.agregar_opcion("<<Salir>>", &salir);


	menu.ejecutar();
	
return 0;
}
