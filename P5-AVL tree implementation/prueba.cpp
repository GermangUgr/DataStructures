#include "bintree.h"
#include "avl.h"
#include <iostream>
#include <iomanip>
#include <vector>

//Orden para compilar: g++ -std=c++0x prueba.cpp -o prueba

void iterar_sobre(const AVL<int> & t) {
	AVL<int>::const_iterator it = t.cbegin();
	for(it = t.cbegin(); it != t.cend(); ++it)
		cout << *it << " ";
}

int main(){
	bintree<int> t;
	AVL<int> tree;
	int opcion, aux, aux2;
	AVL<int>::iterator it;
	pair<AVL<int>::iterator,bool> parAux;
	char iterar;
	
	cout << "Se insertan en el arbol los numeros del 0 al 60 contando de tres en tres" << endl;
	for(int i=0; i<60; i+=3) {
		tree.insert(i);
	}

	while (opcion != 0) {
		iterar = 'n';
		cout << "-------------------//-------------------" << endl;
		cout << "Elija una opcion: " << endl;
		cout << "| Eliminar un elemento del arbol: 1" << endl;
		cout << "| Insertar un elemento en el arbol: 2" << endl;
		cout << "| Lower bound de un elemento: 3" << endl;
		cout << "| Upper bound de un elemento: 4" << endl;
		cout << "| Encontrar un elemento: 5" << endl;
		cout << "| Salir de menu: 0" << endl;
		cout << "<-- ";
		cin >> opcion;
		if(opcion != 0) {
			cout << "¿Iterar en postorder tras la accion seleccionada? [S/N]: " << endl;
			cin >> iterar;
		}
		if(opcion == 1) {
			cout << "Introduzca el elemento a eliminar: ";
			cin >> aux;
			aux2 = tree.erase(aux);
			if(aux2 == 1)
				cout << "Elemento eliminado con exito" << endl;
			else
				cout << "El elemento no se encontraba en el arbol" << endl;
		} else if(opcion == 2) {
			cout << "Introduzca el elemento a insertar: ";
			cin >> aux;
			parAux = tree.insert(aux);
			if(parAux.second)
				cout << "Elemento insertado con exito" << endl;
			else
				cout << "El elemento ya se encontraba en el arbol" << endl;
		} else if (opcion == 3) {
			cout << "Accion: lower_bound(valor). Introduzca valor: ";
			cin >> aux;
			it = tree.lower_bound(aux);
			if(it != tree.end()) 
				cout << "Lower bound de " << aux << ": " << *it << endl;
			else
				cout << "Error: " << aux << " es mayor que el mayor elemento del arbol" << endl;

		} else if(opcion == 4) {
			cout << "Accion: upper_bound(valor). Introduzca valor: ";
			cin >> aux;
			it = tree.upper_bound(aux);
			if(it != tree.end()) 
				cout << "Upper bound de " << aux << ": " << *it << endl;
			else
				cout << "Error: no se encontro ningun elemento mayor que " << aux << " en el arbol" << endl; 

		} else if(opcion == 5) {
			cout << "Introduzca el elemento a encontrar: ";
			cin >> aux;
			it = tree.find(aux);
			if(it != tree.end())
				cout << "El elemento se encontro en el arbol" << endl;
			else
				cout << "El elemento no se contro en el arbol" << endl;
		}

		if(iterar == 'S' || iterar == 's') {
			cout << "------Iterando sobre el arbol------" << endl;
			iterar_sobre(tree);
			cout << endl;
		}

	}

	
}