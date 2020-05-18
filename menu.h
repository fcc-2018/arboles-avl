#include <iostream>
#include <functional>

// utilizamos std::function para almacenar en variables
// funciones normales, y funciones lambda
// para hacer mas faciles las cosas usamos typedef
typedef std::function<bool(ArbolAVL*a)> funcion_menu;

// Opcion del menu
class Opcion{
	public:
	// titulo que se muestra en el menu
	std::string titulo;
	// funcion que ejecuta el codigo de la opcion
	// del menu, cuando se selecciona
	std::function<bool (ArbolAVL * a)> * funcion;
	// constructor
	Opcion(std::string titulo, std::function<bool (ArbolAVL* a)> * funcion): 
		titulo(titulo), funcion(funcion){}
};

// Muestra un menu de opciones automaticamente
// y ejecuta el codigo que se le indica mediante
// funciones lambda en cada opcion
class Menu{
	public:
	// arbol sobre el que se va a operar
	ArbolAVL * arbol;
	std::string titulo;

	Menu(ArbolAVL* a) :arbol(a), titulo("Sin titulo"), 
				indice(1), ancho_menu(50) {}
	Menu(ArbolAVL* a, std::string titulo) :arbol(a), titulo(titulo), 
				indice(1), ancho_menu(50) {}
	// agrega una opcion al menu 
	// recibe un titulo y una funcion a ejecutar cuando se
	// selecciona dicha opcion
	void agregar_opcion(std::string titulo, std::function<bool(ArbolAVL*a)>* funcion)
	{ 
		// insertar en la lista de opciones
		opciones.insertar_final(new Opcion(titulo, funcion));
		// incrementar el indice de opcions
		indice ++; 
	}

	// imprime un titulo o un mensaje de adios
	void imprimir_opcion(string texto){
		texto = "| " + texto;
		int longitud = texto.length();
		string esp = generar_n_espacios(ancho_menu - longitud);
		std::cout << texto << esp << "|" <<endl;
	}

	std::string generar_n_espacios(int n){
		string esp = "";
		for(int i = 0; i < n; i++) esp += " ";
		return esp;
	}

	// imprime una opcion con estilo
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

	// muestra el menu de manera elegante 
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
	
	// ejecuta la accion actual ingresada por el usuario
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
		imprimir_opcion("Vuelve pronto prro jsjsjs xD");
	}

	private: 
		int indice, eleccion, ancho_menu;
		Lista<struct Opcion *> opciones;
		
};
