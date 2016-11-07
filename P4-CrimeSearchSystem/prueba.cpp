#include <functional>
#include "crimen.h"
#include "css.h"
#include "fecha.h"
#include <iostream>
#include <fstream>
#include <string>

//Orden para compilar: g++ -std=c++0x prueba.cpp -o prueba
//Coordenadas de prueba para inArea: x1 = -87.9, y1=41.6, x2 = -87, y2 = 42
int main(){

	CSS css;

	cout << "Cargando...\n";
	css.load("crimenes.csv");

	//css.erase(10166591);
	//96174

	int opcion, num_coincidencias, cont = 1, cont2 = 0;
	double x1, y1, x2, y2;
	string cadena, aux;
	list<string> consulta;
	vector<pair<CSS::ID, float> > consulta_resuelta;
	vector<pair<CSS::ID, float> > :: iterator itVec;
	list<CSS::ID> inAreaResult;
	list<CSS::ID> :: iterator itList;


	do {
		cout << "---------------------------------------------------------------------\n";
		cout << "Seleccione una opcion: " << endl;
		cout << "1: Consulta libre (Query)" << endl;
		cout << "2: Crimenes en area (inArea)" << endl;
		cout << "0: Salir" << endl;
		cout << "Esperando opcion: ";
		cin >> opcion;

		if(opcion == 1) {
			cont = 1;
			cout << "---------------------------------------------------------------------\n";
			cout << "Introduzca la cadena a buscar " << endl;
			cout << "Formato: palabras en mayuscula y separadas por espacios: " << endl;
			cout << "Introduzca el caracter . para finalizar" << endl;
			cout << "Introduzca la palabra Nº " << cont << ": ";
			cin >> cadena;
			while (cadena != ".") {
				consulta.push_back(cadena);
				cont++;
				cout << "Introduzca la palabra Nº " << cont << ": ";
				cin >> cadena;
			}
			cout << "Introduzca el numero de coincidencias a buscar: ";
			cin >> num_coincidencias;

			if(consulta.size() > 0) {
				consulta_resuelta = css.Query(consulta, num_coincidencias);
				itVec = consulta_resuelta.begin();
				cout << "\nResultado de la busquerda (Formato: ID --- Peso): " << endl;	

				while (itVec != consulta_resuelta.end()) {
					cout << itVec->first << " --- " << itVec->second << endl;
					itVec++;
				}
			} else 
				cout << "Error: Cadena vacia\n" << endl;

		} else if(opcion == 2) {
			cout << "---------------------------------------------------------------------\n";
			cout << "Introduzca la coordenada x1: ";
			cin>> x1;
			cout << "Introduzca la coordenada y1: ";
			cin>> y1;
			cout << "Introduzca la coordenada x2: ";
			cin>> x2;
			cout << "Introduzca la coordenada y2: ";
			cin>> y2;

			inAreaResult = css.inArea(x1, y1, x2, y2);
			itList = inAreaResult.begin();

			cout << "\nResultado de la busqueda: " << endl;

			while(itList != inAreaResult.end()) {
				cout << *itList << " -- ";
				itList++;
				if(cont2 == 3) {
					cout << endl;
					cont2 = 0;
				}
				cont2++;
			}

			cout << "Numero total de coincidencias: " << inAreaResult.size() << endl;

		}
	} while (opcion != 0);

	/*
	Para probar los distintos iteradores por separado se pueden utilizar los separadores dispuestos
	entre cada fragmento de codigo ejecutable de forma que añadiendo o eliminando el espacio entre 
	los caracteres "*" y "/" a la erecha del separador podemos descomentar o comentar respectivamente 
	el fragmento de codigo bajo el separado hasta el seiguiente separador.

	Para probarlo solo debemos recompilar y volver a ejecutar
	*/

	////////////////////////////////////
	//Codigo para probar CSS::iterator//
	////////////////////////////////////
	/* ----------------------------------------------------- * /
	CSS::iterator it1 = css.begin();

	cont2 = 0;
	cout << "Recorriendo hacia delante: \n";
	while(it1 != css.end()) {
		cout << (*it1).first << " --- ";
		if(cont2 == 3) {
			cout << endl;
			cont2 = 0;
		}
		cont2++;
		it1++;
	}
	/* ----------------------------------------------------- * /
	CSS::iterator it2 = css.end();
	it2--;

	cont2 = 0;
	cout << "Recorriendo hacia atras: \n";
	while(it2 != css.begin()) {
		cout << (*it2).first << " --- ";
		if(cont2 == 3) {
			cout << endl;
			cont2 = 0;
		}
		cont2++;
		it2--;
	}

	////////////////////////////////////
	//Codigo para probar Date_iterator//
	////////////////////////////////////
	/* ----------------------------------------------------- * /
	CSS::Date_iterator Dit1 = css.dbegin();

	cont2 = 0;
	cout << "Recorriendo hacia delante: \n";
	while(Dit1 != css.dend()) {
		cout << (*Dit1).first << " --- ";
		if(cont2 == 3) {
			cout << endl;
			cont2 = 0;
		}
		cont2++;
		Dit1++;
	}

	/* ----------------------------------------------------- * /

	CSS::Date_iterator Dit2 = css.dend();
	Dit2--;

	cont2 = 0;
	cout << "Recorriendo hacia atras: \n";
	while(Dit2 != css.dbegin()) {
		cout << (*Dit2).first << " --- ";
		if(cont2 == 3) {
			cout << endl;
			cont2 = 0;
		}
		cont2++;
		Dit2--;
	}

	////////////////////////////////////
	//Codigo para probar IUCR_iterator//
	////////////////////////////////////
	/* ----------------------------------------------------- * /
	CSS::IUCR_iterator IUit1 = css.ibegin();

	cont2 = 0;
	cout << "Recorriendo hacia delante: \n";
	while(IUit1 != css.iend()) {
		cout << (*IUit1).first << " --- ";
		if(cont2 == 3) {
			cout << endl;
			cont2 = 0;
		}
		cont2++;
		IUit1++;
	}
	/* ----------------------------------------------------- * /

	CSS::IUCR_iterator IUit2 = css.iend();

	cont2 = 0;
	cout << "Recorriendo hacia delante: \n";
	while(IUit2 != css.ibegin()) {
		cout << (*IUit2).first << " --- ";
		if(cont2 == 3) {
			cout << endl;
			cont2 = 0;
		}
		cont2++;
		IUit2--;
	}

	/* ----------------------------------------------------- */
	
	cout << endl << endl;
	return 0;

}
