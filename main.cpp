#include <iostream>
#include "arbolAVL.hpp"
#include "menu.hpp"

/*! \mainpage Presentación del trabajo
 * 
 * <center>
 * <table style="max-width: 650px;">
 * <tr><td style="padding: 15px;"><center><img src="./img/fcc_logo.png"></center><td style="padding: 15px;"><center><img src="./img/BUAP_logo.png"></center>
 * <tr><td align="center" style="padding: 5px; font-size: 15px;"><i><b>Facultad de Ciencias de la Computación</b></i><td align="center" style="padding: 5px; font-size: 15px;"><i><b>Benemértia Universidad Autónoma de Puebla</b></i>
 * <tr><td colspan="2" align="center" style="padding: 5px;"><b>Profesora</b> María del Carmen Santiago Díaz
 * <tr><td colspan="2" align="center" style="padding: 5px;">Estructuras de Datos
 * <tr><td colspan="2" align="center" style="padding: 5px; font-size: 20px;"><i><b>Manual técnico de TDAs y Árboles AVL</b></i>
 * </table>
 * <br>
 * <table class="team" style="max-width: 650px; border: 2px black solid;">
 * <tr><th colspan="2" style="background: black; color: white;">Integrantes del equipo 3
 * <tr><td style="border: 1px black solid; padding: 2px;">Batres Pedroza Alejandro<td style="border: 1px black solid; padding: 2px;">201836943
 * <tr><td style="border: 1px black solid; padding: 2px;">García González Jorge<td style="border: 1px black solid; padding: 2px;">201847512
 * <tr><td style="border: 1px black solid; padding: 2px;">Méndez Méndez Sebastián<td style="border: 1px black solid; padding: 2px;">201836190
 * <tr><td style="border: 1px black solid; padding: 2px;">Segura Cuanalo Ricardo Alejandro<td style="border: 1px black solid; padding: 2px;">201848777
 * </table>
 * <br>
 * <h2>Introducción
 * <div style="max-width: 650px;">
 * Este manual técnico fue realizado con el propósito de brindar una mejor comprensión para cualquiera que busque utilizar nuestros TDAs, ya que esto
 * podría ayudar al usuario a emplear nuestros algoritmos para diferentes tareas. Esto se pretende lograr, utilizando descripciones concisas para los
 * métodos empleados, los parámetros de estos y las variables que contiene cada clase utilizada en el código.
 * </div>
 * </center>
 *
*/
/*!
 * \file main.cpp
 * \brief Aplicación de los métodos de las clases Menu y ArbolAVL para la
 * demostración de su funcionamiento
 * */

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
