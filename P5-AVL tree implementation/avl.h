#ifndef __AVL_H
#define __AVL_H

#include "bintree.h"
#include <string>
#include <vector>
#include <iostream>
#include <utility>

using namespace std;

template <typename T, class comparar = less<T> >

class AVL {
public:

	typedef int altura;
	typedef unsigned int size_type;
	class iterator;
	class reverse_iterator;
	class const_iterator;
	class const_reverse_iterator;

private:
	// Representacion
	bintree <pair<T,altura> > el_avl;
	size_type tama;
	comparar cmp;
  	// Metodos privados
   	altura h(const typename bintree<pair<T,altura> >::node & n);
   	altura h(const typename bintree<pair<T,altura> >::const_node & n);
   	void RSD(typename bintree<pair<T,altura> >::node & n); 	//Rotacion simple derecha
   	void RSI(typename bintree<pair<T,altura> >::node & n); 	//Rotacion simple izquierda
   	void RDDI(typename bintree<pair<T,altura> >::node & n); //Rotacion doble derecha-izquierda
   	void RDID(typename bintree<pair<T,altura> >::node & n); //Rotacion doble izquierda-derecha

public:
	AVL();
	AVL(const AVL<T,comparar> & a_copiar);
	AVL & operator=(const AVL<T,comparar> & a_copiar);

	//Metodos relacionados con iteradores
	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_iterator cbegin() const;
	const_iterator cend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	//Consulta de estado
	bool empty();
	size_type size();
	
	//Modificacion de estado
	pair<iterator, bool> insert (const T & val);
	int erase (const T & val);
	void swap (AVL<T,comparar> & x);
	void clear();

	//Consulta
	iterator find (const T & val) const;
	iterator lower_bound (const T & val) const;
	iterator upper_bound (const T & val) const;

	//Clase iterator
	class iterator {
	private:
		typename bintree<pair<T,altura> >::inorder_iterator it;
		friend class AVL <T,comparar>;
	public:
		iterator();
		iterator(const iterator & i);
		T & operator*();
		iterator & operator++();
		iterator & operator--();
		bool operator==(const iterator & i);
		bool operator!=(const iterator & i);
		iterator & operator=(const iterator & i);

	};


	//Clase reverse_iterator
	class reverse_iterator {
	private:
		typename bintree<pair<T,altura> >::inorder_iterator it;
		friend class AVL <T,comparar>;
	public:
		reverse_iterator();
		reverse_iterator(const reverse_iterator & i);
		T & operator*();
		reverse_iterator & operator++();
		reverse_iterator & operator--();
		bool operator==(const reverse_iterator & i);
		bool operator!=(const reverse_iterator & i);
		reverse_iterator & operator=(const reverse_iterator & i);
	};



	//Clase const_iterator
	class const_iterator {
	private:
		typename bintree<pair<T,altura> >::const_inorder_iterator it;
		friend class AVL <T,comparar>;
	public:
		const_iterator();
		const_iterator(const const_iterator & i);
		const T & operator*();
		const_iterator & operator++();
		const_iterator & operator--();
		bool operator==(const const_iterator & i);
		bool operator!=(const const_iterator & i);
		const_iterator & operator=(const const_iterator & i);
	};



	//Clase const_reverse_iterator
	class const_reverse_iterator {
	private:
		typename bintree<pair<T,altura> >::const_inorder_iterator it;
		friend class AVL <T,comparar>;
	public:
		const_reverse_iterator();
		const_reverse_iterator(const const_reverse_iterator & i);
		const T & operator*();
		const_reverse_iterator & operator++();
		const_reverse_iterator & operator--();
		bool operator==(const const_reverse_iterator & i);
		bool operator!=(const const_reverse_iterator & i);
		const_reverse_iterator & operator=(const const_reverse_iterator & i);
	};
};

#include "avl.hxx"


#endif

