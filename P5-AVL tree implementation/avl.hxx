#include "avl.h"

using namespace std;

template <typename T, class comparar>
typename AVL<T,comparar>::altura AVL<T,comparar>::h(const typename bintree<pair<T,AVL<T,comparar>::altura> >::node & n) {
	int alt;
	if(n.null())
		alt = -1;
	else 
		alt = (*n).second;

	return alt;
}

template <typename T, class comparar>
typename AVL<T,comparar>::altura AVL<T,comparar>::h(const typename bintree<pair<T,AVL<T,comparar>::altura> >::const_node & n) {
	int alt;
	if(n.null())
		alt = -1;
	else 
		alt = (*n).second;

	return alt;
}

template <typename T, class comparar>
void AVL<T,comparar>::RSD(typename bintree<pair<T,altura> >::node & n) {
	bintree<pair<T, altura> > alpha;
	bintree<pair<T, altura> > beta;
	bintree<pair<T, altura> > gamma;
	typename bintree<pair<T, altura> >::node el_padre;
	typename bintree<pair<T, altura> >::node izquierda = n.left();
	el_avl.prune_left(izquierda,alpha);
	el_avl.prune_right(izquierda,beta);
	el_avl.prune_right(n,gamma);
	bintree<pair<T, altura> > treeB;
	bintree<pair<T, altura> > treeA;

	if(!n.parent().null()) {
		el_padre = n.parent();
		el_avl.prune_left(n,treeB);
		if(el_padre.right() == n) {
			el_avl.prune_right(el_padre,treeA);
			el_avl.insert_right(el_padre,treeB);
			el_avl.insert_right(izquierda,treeA);

		} else {
			el_avl.prune_left(el_padre,treeA);
			el_avl.insert_left(el_padre,treeB);
			el_avl.insert_right(izquierda,treeA);
		}

		el_avl.insert_left(izquierda,alpha);
		el_avl.insert_right(n,gamma);
		el_avl.insert_left(n,beta);

	} else {
		bintree<pair<T, altura> > nuevo_arbol(*izquierda);
		nuevo_arbol.insert_right(nuevo_arbol.root(),(*n));
		el_avl = nuevo_arbol;
		el_avl.insert_left(el_avl.root(),alpha);
		el_avl.insert_right(el_avl.root().right(),gamma);
		el_avl.insert_left(el_avl.root().right(),beta);
	}

	if(h(n.left()) > h(n.right()))
		(*n).second = h(n.left()) +1;
	else 
		(*n).second = h(n.right()) +1;

	if(h(izquierda.left()) > h(izquierda.right()))
		(*(izquierda)).second = h(izquierda.left()) +1;
	else 
		(*(izquierda)).second = h(izquierda.right()) +1;

	n = izquierda;
}

template <typename T, class comparar>
void AVL<T,comparar>::RSI(typename bintree<pair<T,altura> >::node & n) {
	bintree<pair<T, altura> > alpha;
	bintree<pair<T, altura> > beta;
	bintree<pair<T, altura> > gamma;
	typename bintree<pair<T, altura> >::node el_padre;
	typename bintree<pair<T, altura> >::node derecha = n.right();
	el_avl.prune_left(n,alpha);
	el_avl.prune_left(derecha,beta);
	el_avl.prune_right(derecha,gamma);
	bintree<pair<T, altura> > treeB;
	bintree<pair<T, altura> > treeA;

	if(!n.parent().null()) {
		el_padre = n.parent();
		el_avl.prune_right(n,treeB);
		if(el_padre.right() == n) {
			el_avl.prune_right(el_padre,treeA);
			el_avl.insert_right(el_padre,treeB);
			el_avl.insert_left(derecha,treeA);

		} else {
			el_avl.prune_left(el_padre,treeA);
			el_avl.insert_left(el_padre,treeB);
			el_avl.insert_left(derecha,treeA);
		}

		el_avl.insert_right(derecha,gamma);
		el_avl.insert_left(n,alpha);
		el_avl.insert_right(n,beta);

	} else {
		bintree<pair<T, altura> > nuevo_arbol((*(n.right())));
		nuevo_arbol.insert_left(nuevo_arbol.root(),(*n));
		el_avl = nuevo_arbol;
		el_avl.insert_right(el_avl.root(),gamma);
		el_avl.insert_left(el_avl.root().left(),alpha);
		el_avl.insert_right(el_avl.root().left(),beta);
	}

	//Actualizamos las alturas
	if(h(n.left()) > h(n.right()))
		(*n).second = h(n.left()) +1;
	else 
		(*n).second = h(n.right()) +1;

	if(h(derecha.left()) > h(derecha.right())) {
		(*(derecha)).second = h(derecha.left()) +1;
	}
	else {
		(*(derecha)).second = h(derecha.right()) +1;
	}

	n = derecha;
}


template <typename T, class comparar>
void AVL<T,comparar>::RDDI(typename bintree<pair<T,altura> >::node & n) {
	typename bintree<pair<T, altura> >::node nodo = n.right();
	typename bintree<pair<T, altura> >::node copia = n;
	RSD(nodo);
	RSI(copia);
}

template <typename T, class comparar>
void AVL<T,comparar>::RDID(typename bintree<pair<T,altura> >::node & n) {
	typename bintree<pair<T, altura> >::node nodo = n.left();
	typename bintree<pair<T, altura> >::node copia = n;
	RSI(nodo);
	RSD(copia);
}


template<typename T, class comparar>
AVL<T,comparar>::AVL() {
	tama = 0;
}

template<typename T, class comparar>
AVL<T,comparar>::AVL(const AVL<T,comparar> & a_copiar) {
	el_avl = a_copiar.el_avl;
	tama = a_copiar.tama;
	//cmp = a_copiar.cmp;
}

template<typename T, class comparar>
AVL<T,comparar> & AVL<T,comparar>::AVL::operator=(const AVL<T,comparar> & a_copiar) {
	if(this != &a_copiar) {
		el_avl = a_copiar.el_avl;
		tama = a_copiar.tama;
	}
	//cmp = a_copiar.cmp;

	return *this;
}

///////////////////////////////////////
//METODOS RELACIONADOS CON ITERADORES//
///////////////////////////////////////

template<typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::begin() {
	typename bintree<pair<T,altura> >::inorder_iterator it_aux = el_avl.begin_inorder();
	AVL<T, comparar>::iterator iter;
	iter.it = it_aux;
	return iter;
}

template<typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::end() {
	typename bintree<pair<T,altura> >::inorder_iterator it_aux = el_avl.end_inorder();
	AVL<T, comparar>::iterator iter;
	iter.it = it_aux;
	return iter;
}

template<typename T, class comparar>
typename AVL<T,comparar>::reverse_iterator AVL<T,comparar>::rbegin() {
	typename bintree<pair<T,altura> >::node node_aux = el_avl.root();
	typename AVL<T, comparar>::reverse_iterator iter;

	while(!(node_aux.right().null()))
		node_aux = node_aux.right();
	
	typename bintree<pair<T,altura> >::inorder_iterator iter_aux(node_aux);
	iter.it = iter_aux;
	return iter;
}

template<typename T, class comparar>
typename AVL<T,comparar>::reverse_iterator AVL<T,comparar>::rend() {
	typename bintree<pair<T,altura> >::inorder_iterator it_aux = el_avl.end_inorder();
	AVL<T, comparar>::reverse_iterator iter;
	iter.it = it_aux;
	return iter;
}

template<typename T, class comparar>
typename AVL<T,comparar>::const_iterator AVL<T,comparar>::cbegin() const {
	typename bintree<pair<T,altura> >::const_inorder_iterator it_aux = el_avl.begin_inorder();
	AVL<T, comparar>::const_iterator iter;
	iter.it = it_aux;
	return iter;
}

template<typename T, class comparar>
typename AVL<T,comparar>::const_iterator AVL<T,comparar>::cend() const {
	typename bintree<pair<T,altura> >::const_inorder_iterator it_aux = el_avl.end_inorder();
	AVL<T, comparar>::const_iterator iter;
	iter.it = it_aux;
	return iter;
}

template<typename T, class comparar>
typename AVL<T,comparar>::const_reverse_iterator AVL<T,comparar>::crbegin() const {
	typename bintree<pair<T,altura> >::node node_aux = el_avl.root();
	typename AVL<T, comparar>::const_reverse_iterator iter;

	while(!(node_aux.right().null()))
		node_aux = node_aux.right();
	
	typename bintree<pair<T,altura> >::const_inorder_iterator iter_aux(node_aux);
	iter.it = iter_aux;
	return iter;
}

template<typename T, class comparar>
typename AVL<T,comparar>::const_reverse_iterator AVL<T,comparar>::crend() const {
	typename bintree<pair<T,altura> >::const_inorder_iterator it_aux = el_avl.end_inorder();
	AVL<T, comparar>::const_reverse_iterator iter;
	iter.it = it_aux;
	return iter;
}

///////////////////////////////////////
//METODOS PARA MODIFICACION DE ESTADO//
///////////////////////////////////////

template<typename T, class comparar>
pair<typename AVL<T,comparar>::iterator, bool> AVL<T,comparar>::insert (const T & val) {
	typename bintree< pair<T,AVL<T,comparar>::altura> >::node nodo = el_avl.root();
	typename bintree< pair<T,AVL<T,comparar>::altura> >::node padre;
	typename AVL<T,comparar>::iterator iter;
	bool encontrado = false, cambio_altura = true;
	pair<typename AVL<T,comparar>::iterator,bool> a_devolver;
	pair<int,altura> par;

	if(el_avl.empty()) { //el arbol esta vacio
		par.first = val;
		par.second = 0;
		bintree< pair<T,altura> > nuevo(par);
		el_avl = nuevo;
		typename bintree< pair<T,AVL<T,comparar>::altura> >::inorder_iterator iter_aux(el_avl.end_inorder());
		iter.it = iter_aux;
		a_devolver.first = iter;
		a_devolver.second = true;
	} else {
		while(!encontrado && !nodo.null()) {
			if(cmp((*nodo).first,val)) {
				padre = nodo;
				nodo = nodo.right();
			} else if (cmp(val,(*nodo).first)) {
				padre = nodo;
				nodo = nodo.left();
			} else
				encontrado = true;
		}

		typename bintree< pair<T,AVL<T,comparar>::altura> >::inorder_iterator iter_aux(nodo);
		iter.it = iter_aux;
		a_devolver.first = iter;
		a_devolver.second = !encontrado;	

		pair<char,char> registro; //declaro un par para almacenar el registro de los dos ultimos pasos
		pair<T,AVL<T,comparar>::altura> label(val,0);
		if(!encontrado) {
			if(cmp(val,(*padre).first)) {
				el_avl.insert_left(padre,label);
				nodo = padre.left();
				registro.first = 'i';
				registro.second = 'i';
			}
			else if(cmp((*padre).first,val)) {
				el_avl.insert_right(padre,label);
				nodo = padre.right();
				registro.first = 'd';
				registro.second = 'd';
			}
			int diferencia;
			while(cambio_altura && !nodo.null()) {
				if( (h(nodo) < (h(nodo.left())+1)) || (h(nodo) < (h(nodo.right())+1)) ) {
					if((h(nodo.left()) > h(nodo.right())))
						diferencia = (h(nodo.left()) - h(nodo.right()));
					else 
						diferencia = h(nodo.right()) - h(nodo.left());
					if( diferencia > 1 || diferencia < -1) { //hay que hacer rotacion
						if(registro.first == 'd' && registro.second =='d') {
							RSI(nodo);
						} else if(registro.first == 'i' && registro.second =='i') {
							RSD(nodo);
						} else if(registro.first == 'd' && registro.second =='i') {
							RDDI(nodo);
						} else if(registro.first == 'i' && registro.second =='d') {
							RDID(nodo);
						}

						cambio_altura = false;

					} else {
						(*nodo).second += 1; //la altura aumenta como mucho en una unidad en cada insercion
					}

				} else {
					if((!nodo.left().null()) && !(nodo.right().null()))
						cambio_altura = false;
				}

				//Actualizar el registro
				if(!nodo.parent().null()) {
					registro.second = registro.first;
					if(cmp( (*(nodo.parent())).first,(*nodo).first))
						registro.first = 'd';
					else
						registro.first = 'i';
				}	

				//avanzar el nodo
				nodo = nodo.parent();
			}
			tama ++;
		}
	}
	return a_devolver;
	
}

template<typename T, class comparar>
int AVL<T,comparar>::erase(const T & val) {
	typename bintree< pair<T,AVL<T,comparar>::altura> >::node nodo = el_avl.root();
	typename bintree< pair<T,AVL<T,comparar>::altura> >::node padre, nodo2, padre2;
	bintree<pair<T,altura> > aux, eliminar;
	bool encontrado = false, salir = false;
	int a_devolver, diferencia, mayor_altura;
	string rotacion;

	if(el_avl.empty()) {
		a_devolver = 0;
	} else  {

		while(!encontrado && !nodo.null()) {
			if(cmp((*nodo).first,val)) {
				padre = nodo;
				nodo = nodo.right();
			} else if (cmp(val,(*nodo).first)) {
				padre = nodo;
				nodo = nodo.left();
			} else
				encontrado = true;
		}

		if(encontrado) {
			a_devolver = 1;
			if (!nodo.right().null() && !nodo.left().null()){ //No es hoja y tiene hijo izquierda y derecha
				nodo2 = nodo.left();
				while(!nodo2.null()) {
					padre2 = nodo2;
					nodo2 = nodo2.right();
				}
				(*nodo).first = (*padre2).first;
				nodo = padre2;
				padre = nodo.parent();
			}

			if(!nodo.right().null() && nodo.left().null()) { //No es hoja y solo tiene hijo derecha
				(*nodo).first = (*(nodo.right())).first;
				padre = nodo;
				nodo = nodo.right();
			} else if(nodo.right().null() && !nodo.left().null()) { //No es hoja y solo tiene hijo izquierda
				(*nodo).first = (*(nodo.left())).first;
				padre = nodo;
				nodo = nodo.left();
			}

			if(nodo.right().null() && nodo.left().null()) { //Es un nodo hoja
				if(nodo == padre.left()) 
					el_avl.prune_left(padre,eliminar);
				else 
					el_avl.prune_right(padre,eliminar);

				salir = false;
				nodo = padre;
				while(!nodo.null() && !salir) {
					diferencia = h(nodo.right()) - h(nodo.left());
					if(diferencia > 1) { //la derecha es mayor
						if(h(nodo.right().right()) > h(nodo.right().left())) {
							RSI(nodo);
						}
						else{
							RDDI(nodo);
						}
					} else if (diferencia < -1) { //la izquierda es mayor
						if(h(nodo.left().left()) > h(nodo.left().right())){
							RSD(nodo);
						}
						else {
							RDID(nodo);
						}
					}
					mayor_altura = h(nodo.left()) > h(nodo.right())?h(nodo.left()):h(nodo.right());
					if(mayor_altura != h(nodo))
						(*nodo).second = mayor_altura+1;
					else
						salir = true;

					nodo = nodo.parent();
				}


			}  

		} else 
			a_devolver = 0;
	}
	tama--;
	return a_devolver;
}

template<typename T, class comparar>
void AVL<T,comparar>::clear() {
	el_avl.clear();
}

template<typename T, class comparar>
void AVL<T,comparar>::swap(AVL<T,comparar> & x) {
	el_avl.swap(x.el_avl);
}

///////////////////////////////////
//METODOS PARA CONSULTA DE ESTADO//
///////////////////////////////////

template<typename T, class comparar>
bool AVL<T,comparar>::empty() {
	return el_avl.root().null();
}

template<typename T, class comparar>
typename AVL<T,comparar>::size_type AVL<T,comparar>::size() {
	return tama;
}

//////////////////////////////////////
//METODOS PARA CONSULTA DE ELEMENTOS//
//////////////////////////////////////

template<typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::find(const T & val) const {
	typename bintree< pair<T,AVL<T,comparar>::altura> >::node nodo = el_avl.root();
	bool encontrado = false;

	while(!encontrado && !nodo.null()) {
		if(cmp((*nodo).first,val))
			nodo = nodo.right();
		else if(cmp(val,(*nodo).first))
			nodo = nodo.left();
		else 
			encontrado = true;
	}

	typename bintree<pair <T, altura> >::inorder_iterator it_aux(nodo);
	typename AVL<T,comparar>::iterator iter;
	iter.it = it_aux;

	return iter;
}

template<typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::lower_bound(const T & val) const { //no estricto
	typename bintree< pair<T,AVL<T,comparar>::altura> >::node nodo = el_avl.root();
	typename bintree< pair<T,AVL<T,comparar>::altura> >::node nodo_aux;
	typename bintree< pair<T,AVL<T,comparar>::altura> >::node padre;
	typename AVL<T,comparar>::iterator iter;
	bool encontrado = false;

	while(!encontrado && !nodo.null()) {
		if(cmp((*nodo).first,val)) {
			padre = nodo;
			nodo = nodo.right();
		} else if (cmp(val,(*nodo).first)) {
			padre = nodo;
			nodo = nodo.left();
		} else
			encontrado = true;
	}

	if(!encontrado)
		nodo_aux = padre;
	else
		nodo_aux = nodo;

	typename bintree< pair<T,AVL<T,comparar>::altura> >::inorder_iterator iter_aux(nodo_aux);
	iter.it = iter_aux;

	if(!encontrado && !cmp(val,*iter)) //si no se ha encontrado y val es mayor que el padre;
		++iter;

	return iter;
} 

template<typename T, class comparar>
typename AVL<T,comparar>::iterator AVL<T,comparar>::upper_bound(const T & val) const { //estricto
	typename bintree< pair<T,AVL<T,comparar>::altura> >::node nodo = el_avl.root();
	typename bintree< pair<T,AVL<T,comparar>::altura> >::node padre;
	typename AVL<T,comparar>::iterator iter;
	bool encontrado = false;

	while(!encontrado && !nodo.null()) {
		if(cmp((*nodo).first,val)) {
			padre = nodo;
			nodo = nodo.right();
		} else if (cmp(val,(*nodo).first)) {
			padre = nodo;
			nodo = nodo.left();
		} else
			encontrado = true;
	}

	typename bintree< pair<T,AVL<T,comparar>::altura> >::inorder_iterator iter_aux(padre);
	typename bintree< pair<T,AVL<T,comparar>::altura> >::inorder_iterator iter_aux2(nodo);

	if(!encontrado) {
		iter.it = iter_aux;
		if(!cmp(val,(*padre).first))
			++iter;
	} else {
		iter.it = iter_aux2;
		++iter;
	}
		
	return iter;
}


///////////////////
//Clase iterator //
///////////////////

template<typename T, class comparar>
AVL<T,comparar>::iterator::iterator() {}

template<typename T, class comparar>
AVL<T,comparar>::iterator::iterator (const AVL<T,comparar>::iterator & i) { //tengo que poner el typename?
	if (this != &i) {
		it = i.it;
	}
}

template<typename T, class comparar>
typename AVL<T,comparar>::iterator & AVL<T,comparar>::iterator::operator=(const AVL<T,comparar>::iterator & i) {
	it = i.it;
	return *this;
}

template<typename T, class comparar>
T & AVL<T,comparar>::iterator::operator*() {
	return (*it).first;
}

template<typename T, class comparar>
typename AVL<T,comparar>::iterator & AVL<T,comparar>::iterator::operator++() {
	++it;
}

template<typename T, class comparar>
typename AVL<T,comparar>::iterator & AVL<T,comparar>::iterator::operator--() {
	--it;
}

template<typename T, class comparar>
bool AVL<T,comparar>::iterator::operator==(const AVL<T,comparar>::iterator & i) {
	return it == i.it;
}

template<typename T, class comparar>
bool AVL<T,comparar>::iterator::operator!=(const AVL<T,comparar>::iterator & i) {
	return it != i.it;
}

//////////////////////////
//Clase reverse_iterator//
//////////////////////////

template<typename T, class comparar>
AVL<T,comparar>::reverse_iterator::reverse_iterator() {}

template<typename T, class comparar>
AVL<T,comparar>::reverse_iterator::reverse_iterator (const AVL<T,comparar>::reverse_iterator & i) { //tengo que poner el typename?
	if(this != &i){
		it = i.it;
	}
}

template<typename T, class comparar>
typename AVL<T,comparar>::reverse_iterator & 
AVL<T,comparar>::reverse_iterator::operator=(const AVL<T,comparar>::reverse_iterator & i) {
	it = i.it;
	return *this;
}

template<typename T, class comparar>
T & AVL<T,comparar>::reverse_iterator::operator*() {
	return (*it).first;
}

template<typename T, class comparar>
typename AVL<T,comparar>::reverse_iterator & AVL<T,comparar>::reverse_iterator::operator++() {
	--it;
}

template<typename T, class comparar>
typename AVL<T,comparar>::reverse_iterator & AVL<T,comparar>::reverse_iterator::operator--() {
	++it;
}

template<typename T, class comparar>
bool AVL<T,comparar>::reverse_iterator::operator==(const AVL<T,comparar>::reverse_iterator & i) {
	return it == i.it;
}

template<typename T, class comparar>
bool AVL<T,comparar>::reverse_iterator::operator!=(const AVL<T,comparar>::reverse_iterator & i) {
	return it != i.it;
}

////////////////////////
//Clase const_iterator//
////////////////////////

template<typename T, class comparar>
AVL<T,comparar>::const_iterator::const_iterator() {}

template<typename T, class comparar>
AVL<T,comparar>::const_iterator::const_iterator (const AVL<T,comparar>::const_iterator & i) { //tengo que poner el typename?
	if(this != &i) {
		it = i.it;
	}
}

template<typename T, class comparar> 
typename AVL<T,comparar>::const_iterator & 
AVL<T,comparar>::const_iterator::operator=(const AVL<T,comparar>::const_iterator & i) {
	it = i.it;
	return *this;
}

template<typename T, class comparar>
const T & AVL<T,comparar>::const_iterator::operator*() {
	return (*it).first;
}

template<typename T, class comparar>
typename AVL<T,comparar>::const_iterator & AVL<T,comparar>::const_iterator::operator++() {
	++it;
}

template<typename T, class comparar>
typename AVL<T,comparar>::const_iterator & AVL<T,comparar>::const_iterator::operator--() {
	--it;
}

template<typename T, class comparar>
bool AVL<T,comparar>::const_iterator::operator==(const AVL<T,comparar>::const_iterator & i) {
	return it == i.it;
}

template<typename T, class comparar>
bool AVL<T,comparar>::const_iterator::operator!=(const AVL<T,comparar>::const_iterator & i) {
	return it != i.it;
}

////////////////////////////////
//Clase const_reverse_iterator//
////////////////////////////////

template<typename T, class comparar>
AVL<T,comparar>::const_reverse_iterator::const_reverse_iterator() {}

template<typename T, class comparar>
AVL<T,comparar>::const_reverse_iterator::const_reverse_iterator (const AVL<T,comparar>::const_reverse_iterator & i) { //tengo que poner el typename?
	if(this != &i) {
		it = i.it;	
	}
}

template<typename T, class comparar>
typename AVL<T,comparar>::const_reverse_iterator & 
AVL<T,comparar>::const_reverse_iterator::operator=(const AVL<T,comparar>::const_reverse_iterator & i) {
	it = i.it;
	return *this;
}

template<typename T, class comparar>
const T & AVL<T,comparar>::const_reverse_iterator::operator*() {
	return (*it).first;
}

template<typename T, class comparar>
typename AVL<T,comparar>::const_reverse_iterator & AVL<T,comparar>::const_reverse_iterator::operator++() {
	--it;
}

template<typename T, class comparar>
typename AVL<T,comparar>::const_reverse_iterator & AVL<T,comparar>::const_reverse_iterator::operator--() {
	++it;
}

template<typename T, class comparar>
bool AVL<T,comparar>::const_reverse_iterator::operator==(const AVL<T,comparar>::const_reverse_iterator & i) {
	return it == i.it;
}

template<typename T, class comparar>
bool AVL<T,comparar>::const_reverse_iterator::operator!=(const AVL<T,comparar>::const_reverse_iterator & i) {
	return it != i.it;
}
