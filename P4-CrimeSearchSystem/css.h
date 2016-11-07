#ifndef __CSS_H
#define __CSS_H
#include "fecha.h"
#include "crimen.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <list>
#include <fstream>
#include <iostream>
#include <fstream>
#include <functional>
#include <queue>


class CSS {
public:
	//Redefinicion de tipos//
	typedef float Longitud;
	typedef float Latitud;
	typedef unsigned int ID;
	typedef string Termino;
	typedef string IUCR;
	typedef fecha Date;
	
	//Declaracion de clases anidadas
	class iterator;
	class IUCR_iterator;
	class Date_iterator;

	//Functor de comparacion
	class Comparador {
		public:
			bool operator()(pair<ID,float> & p1, pair<ID,float> & p2);
	};

private:
	map <ID,crimen> baseDatos;
	multimap<Date, map<ID,crimen>::iterator> DateAcces;
	map <IUCR, set<ID> > IUCRAcces;
	unordered_map <Termino, set<ID> > index;
	map <Longitud, multimap<Latitud, ID> > posicionGeo;
	friend class IUCR_iterator;
	friend class Date_iterator;
	friend class iterator;
	map<ID,float> unionPeso( const set<ID> & t1, const set<ID> & t2); 
	void unionPeso( map<ID,float> & m, set<ID> & t_i);

public:
	CSS();
	void load(string nombreBD);
	void insert(const crimen & x);
	
	void erase(const ID id);
	iterator find_ID(const ID id);
	void setArrest(const ID id, bool value);
	vector<pair<ID,float> > Query(list<string> & q, int k);    
	list<ID> inArea(Longitud x1, Latitud y1, Longitud x2, Latitud y2 );
	//Metodos relacionados con iteradores
	IUCR_iterator ibegin();
	IUCR_iterator iend();
	IUCR_iterator lower_bound(const IUCR & iucr);
	IUCR_iterator upper_bound(const IUCR & iucr);
	Date_iterator dbegin();
	Date_iterator dend();
	Date_iterator lower_bound(const Date & date);
	Date_iterator upper_bound(const Date & date);
	iterator begin();
	iterator end();

	//Clases de iteradores
	class iterator {
	private:
		map<ID, crimen>::iterator it;
		friend class CSS;

	public:
		iterator();
		iterator(const iterator & it_c);
		pair<const ID, crimen > & operator*();
		iterator operator++(int); 	//it++
		iterator & operator++(); 	//++it
		iterator operator--(int); 	//it--
		iterator & operator--();	//--it
		bool operator==(const iterator & it_c);
		bool operator!=(const iterator & it_c);
		iterator & operator=(const iterator & it_c);
	};

	class Date_iterator {
	private:
		multimap<Date, map<ID,crimen> ::iterator >::iterator it_mm;
		friend class CSS;

	public:
		Date_iterator();
		Date_iterator(const Date_iterator & it);
		pair<const ID, crimen > & operator*();
		Date_iterator operator++(int); 	//it++
		Date_iterator & operator++(); 	//++it
		Date_iterator operator--(int); 	//it--
		Date_iterator & operator--();	//--it
		bool operator==(const Date_iterator & it);
		bool operator!=(const Date_iterator & it);
		Date_iterator & operator=(const Date_iterator & it);
	};
	
	class IUCR_iterator {
	private:
		map<IUCR,set<ID> >::iterator it_m;
		map<ID,crimen> * ptr;
		set<ID>::iterator it_s;
		friend class CSS;

	public:
		IUCR_iterator();
		IUCR_iterator(const IUCR_iterator & it);
		pair<const ID, crimen > & operator*();
		IUCR_iterator operator++(int); 	//it++
		IUCR_iterator & operator++(); 	//++it
		IUCR_iterator operator--(int); 	//it--
		IUCR_iterator & operator--();	//--it
		bool operator==(const IUCR_iterator & it);
		bool operator!=(const IUCR_iterator & it);
		IUCR_iterator & operator=(const IUCR_iterator & it);
	};
};

bool to_bool(const string& str);

#include "css.hxx"

#endif
