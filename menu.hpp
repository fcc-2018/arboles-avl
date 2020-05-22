#include <iostream>
#include <functional>


/*!
 * @file menu.hpp
 * @brief Implementacion de la clase Menu y Opcion
*/

// utilizamos std::function para almacenar en variables
// funciones normales, y funciones lambda
// para hacer mas faciles las cosas usamos typedef
typedef std::function<bool(ArbolAVL*a)> funcion_menu;



/*!
 * @class Opcion 
 * @brief Representa a una opcion en el menu del programa
 * */
class Opcion{
	public:
	/*!
	 *  @brief titulo que se muestra en el menu
	 */
	std::string titulo;

	/*!
	 *  @brief funcion que ejecuta el codigo de la opcion
	 *  del menu, cuando se selecciona
	 */
	std::function<bool (ArbolAVL * a)> * funcion;
	/*!
	 * @brief Constructor de la clase
	 * @param titulo titulo de la opcion, sin numero ni saltos de linea
	 * @param funcion funcion que se ejecuta al elegir esta opcion en el menu
	*/
	Opcion(std::string titulo, std::function<bool (ArbolAVL* a)> * funcion): 
		titulo(titulo), funcion(funcion){}
};

/*!
 * @class Menu
 * @brief Muestra un menu de opciones automaticamente
 * y ejecuta el codigo que se le indica mediante
 * funciones lambda en cada opcion.
 */
class Menu{
	public:
	/*!
	 *  @brief puntero a arbol sobre el que se va a operar
	 */
	ArbolAVL * arbol;
	/*!
	 * @brief titulo del menu en el programa
	 */
	std::string titulo;
	/*!
	 * @brief Constructor
	 * @param a puntero a ArbolAVL 
	 * */
	Menu(ArbolAVL* a) :arbol(a), titulo("Sin titulo"), 
				indice(1), ancho_menu(50) {}
	/*!
	 * @brief Constructor
	 * @param a puntero a arbolAVL
	 * @param titulo titulo del menu en el programa
	*/
	Menu(ArbolAVL* a, std::string titulo) :arbol(a), titulo(titulo), 
				indice(1), ancho_menu(50) {}

	/*!
	 * @brief agrega una opcion al menu 
	 * @param titulo titulo de la opcion en el menu
	 * @param funcion funcion que se ejecuta al seleccionar esta opcion
	*/
	void agregar_opcion(std::string titulo, std::function<bool(ArbolAVL*a)>* funcion)
	{ 
		// insertar en la lista de opciones
		opciones.insertar_final(new Opcion(titulo, funcion));
		// incrementar el indice de opcions
		indice ++; 
	}

	/*!
	 *  @brief Imprime una opcion/texto en el menu con formato
	 *  @param texto texto a imprimir
	 */
	void imprimir_opcion(string texto){
		texto = "| " + texto;
		int longitud = texto.length();
		string esp = generar_n_espacios(ancho_menu - longitud);
		std::cout << texto << esp << "|" <<endl;
	}

	/*!
	 * @brief genera n espacios en blanco
	 * @param n numero de espacios
	 * @return string con n espacios en blanco
	*/
	std::string generar_n_espacios(int n){
		string esp = "";
		for(int i = 0; i < n; i++) esp += " ";
		return esp;
	}

	/*!
	 * @brief imprime una opcion con indice
	*/
	void imprimir_opcion(Opcion* op, int ind){
		int longitud;
		std::string item, espacios;
		// crea esto: | ind)
		item = "| " + to_string(ind) + ") " + op->titulo;
		// longitud de la cadena que se imprimira
		longitud = item.length();
		// espacios faltantes para completar el cuadro
		espacios = generar_n_espacios(ancho_menu - longitud);
		// ahora si imprime todo
		std::cout << item << espacios << "|" << endl;
	}

	/*!
	 *  @brief Muestra el menu de manera elegante 
	 *  @return opcion elegida por el usuario
	 * */
	int mostrar(){
		// jaja para no reescribir cout xD
		ostream & out = std::cout;
		out<<"\n";
		out<<"|=================================================|"<<endl;
		imprimir_opcion(titulo);
		out<<"|=================================================|"<<endl;
		out<<"";arbol->recorrer();
		out<<"|=================================================|"<<endl;
		out<<"| Elija la operacion a realizar:                  |"<<endl;
		out<<"|                                                 |"<<endl;

		int longitud, j = 1; std::string item, espacios;
		for(Lista<struct Opcion*>::iterator i = opciones.begin(); i != opciones.end(); i++){
			imprimir_opcion(*i, j);
			j++;
		}
		
		out<<"|=================================================|"<<endl;
		out<<">>Elige una opcion: ";
		std::cin >> eleccion;
		return eleccion;
	}
	
	/*! 
	 * @brief Ejecuta la accion actual ingresada por el usuario
	 * @return *true* si la opcion fue ejecutada *false* si no se encontro la opcion
	 */
	bool accion(){
		// obtener la accion
		Opcion * act = opciones.obtener(eleccion -1);
		if(act != NULL)
			// ejecutar la funcion almacenada en la opcion 
			// funcion lambda
			return (*(act->funcion))(arbol);
		else 
			std::cout<<"\n Opcion no valida, prueba de nuevo";
		// retornar false le indica al programa que debe seguir
		// pintando el menu de opciones
		return false;
	}

	/*!
	 * @brief Ejecuta el menu mientras el usuario siga realizando operaciones
	 * */
	void ejecutar(){
		// coronavirus ? no_salir : salir;
		bool salir = false;
		do{
			// limpiar pantalla
			system("clear");
			// mostrar el menu de opciones
			mostrar();
			// ejecutar accion obtenida del menu de opciones
			salir = accion();
			std::cout<< "\n\nPresione de nuevo ... Ya sabe como es esto\n\n";
			getchar(); getchar();
		}while(!salir);
		imprimir_opcion("Gracias por su preferencia ;*");
	}

	private:
		/*!
		 * @brief indice numero de acciones en el menu
		 * @brief eleccion numero de accion seleccionada por el usuario
		 * @brief ancho_menu numero de caracteres por linea en el menu
		*/
		int indice, eleccion, ancho_menu;
		/*!
		 * @brief opciones lista de opciones en el menu
		*/
		Lista<struct Opcion *> opciones;		
};
