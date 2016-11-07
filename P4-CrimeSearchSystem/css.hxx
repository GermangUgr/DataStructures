#include "css.h"

bool to_bool(const string& str){
	return ( str=="true");
}

void CSS::load(string nombreBD) {
	ifstream fe;
 	string cadena;
	int principio,fin;
	crimen crim;
	fe.open(nombreBD.c_str(), ifstream::in);
if (fe.fail()) {
   cerr << "Error al abrir el fichero " << nombreBD << endl;
} else {
   getline(fe,cadena,'\n'); //leo la cabecera del fichero
    while (!fe.eof()){ 

		getline(fe,cadena,'\n');
       	if (!fe.eof()) {
      	principio=0;
			//set    ID
		fin=cadena.find_first_of(',',principio);
		long int aux=stol(cadena.substr(principio,fin-principio));
		crim.setID(aux);
		principio=fin;
			//set    CASE_NUMBER
		fin=cadena.find_first_of(',',principio+1);
		crim.setCaseNumber(cadena.substr(principio+1,fin-principio-1));
		principio=fin;
			//set    DATE
		fin=cadena.find_first_of(',',principio+1);
		fecha date(cadena.substr(principio+1,fin-principio-1));
		crim.setDate(date);
		principio=fin;
			//ignora BLOCK
		fin=cadena.find_first_of(',',principio+1);
		principio=fin;
			//set    IUCR
		fin=cadena.find_first_of(',',principio+1);
		crim.setIUCR(cadena.substr(principio+1,fin-principio-1));
		principio=fin;
			//set    PRIMARY_TYPE
		string cadenaAux;
		fin=cadena.find_first_of(',',principio+1);
		crim.setPrimaryType(cadena.substr(principio+1,fin-principio-1));
		cadenaAux = cadena.substr(principio+1,fin-principio-1);
		principio=fin;
			//set    DESCRIPTION 
		fin=cadena.find_first_of(',',principio+1);
		cadenaAux.append(" ");
		cadenaAux.append(cadena.substr(principio+1,fin-principio-1));
		principio=fin;
			//set    LOCATION_DESCRIPTION
		fin=cadena.find_first_of(',',principio+1);
		crim.setLocationDescription(cadena.substr(principio+1,fin-principio-1));
		cadenaAux.append(" ");
		cadenaAux.append(cadena.substr(principio+1,fin-principio-1));
		crim.setDescription(cadenaAux);
		principio=fin;
			//set    ARREST
		fin=cadena.find_first_of(',',principio+1);
		crim.setArrest(to_bool(cadena.substr(principio+1,fin-principio-1)));
		principio=fin;
			//set   DOMESTIC
		fin=cadena.find_first_of(',',principio+1);
		crim.setDomestic(to_bool(cadena.substr(principio+1,fin-principio-1)));
		principio=fin;
			//ignora BEAT
		fin=cadena.find_first_of(',',principio+1);
		principio=fin;
			//ignora DISTRIC	
		fin=cadena.find_first_of(',',principio+1);
		principio=fin;
			//ignora WARD
		fin=cadena.find_first_of(',',principio+1);
		principio=fin;
			//ignora COMMUNITY_AREA
		fin=cadena.find_first_of(',',principio+1);
		principio=fin;
			//ignora FBI_CODE
		fin=cadena.find_first_of(',',principio+1);
		principio=fin;
			//ignora X_COORDINATE
		fin=cadena.find_first_of(',',principio+1);
		principio=fin;
			//ignora Y_COORDINATE
		fin=cadena.find_first_of(',',principio+1);
		principio=fin;
			//ignora YEAR
		fin=cadena.find_first_of(',',principio+1);
		principio=fin;
			//ignora UPDATED_ON
		fin=cadena.find_first_of(',',principio+1);
		principio=fin;
			//set    LATITUDE
		fin=cadena.find_first_of(',',principio+1);
		if(fin-principio-1 != 0)
			crim.setLatitude(stod(cadena.substr(principio+1,fin-principio-1)));
		principio=fin;
			//set    LONGITUDE
		fin=cadena.find_first_of(',',principio+1);
		if(fin-principio-1 != 0)
			crim.setLongitude(stod(cadena.substr(principio+1,fin-principio-1)));
		principio=fin;
			//ignora LOCATION
		fin=cadena.find_first_of(',',principio+1);
				
	    insert(crim) ;
	    //cout << "\nSIGUIENTE CRIMEN\n";
     	}
	}
    fe.close();
	}
}

map<CSS::ID,float> CSS::unionPeso( const set<CSS::ID> & t1, const set<CSS::ID> & t2) {
	map<CSS::ID, float> unionPeso;
	set<CSS::ID> :: iterator it1 = t1.begin(), it2 = t2.begin();

	while(it1 != t1.end()) {
		unionPeso[*it1] = 1;
		it1++;
	}

	while(it2 != t2.end()) {
		if(unionPeso.find(*it2) != unionPeso.end())
			unionPeso[*it2]++;
		else
			unionPeso[*it2] = 1;
		it2++;
	}

	return unionPeso;
}

void CSS::unionPeso( map<CSS::ID,float> & m, set<CSS::ID> & t_i) {
	set<CSS::ID>::iterator itSet = t_i.begin();

	while (itSet != t_i.end()) {
		if(m.find(*itSet) != m.end())
			m[*itSet]++;
		else
			m[*itSet] = 1;

		itSet++;
	}
}

bool CSS::Comparador::operator()(pair<CSS::ID,float> & p1, pair<CSS::ID,float> & p2){
	return p1.second > p2.second;
}
	
vector< pair<CSS::ID,float> > CSS::Query(list<string> & q, int k) {
	//Declaracion del objeto a devolver (vector)
	vector< pair<CSS::ID,float> > a_devolver;
	//Declaracion de los set auxiliares
	set<CSS::ID>::iterator itSet;
	set<CSS::ID> setId1, setId2;
	//Declaracion del map auxiliar
	map<CSS::ID,float> Union;
	map<CSS::ID,float> :: iterator itUnion;
	//Declaracion de la cola con prioridad
	priority_queue< pair<CSS::ID,float>, vector<pair<CSS::ID,float> >, CSS::Comparador> cola;
	//Declaracion de iteradores y contadores auxiliares
	list<string>::iterator itList; 
	pair<CSS::ID, float> par;
	int cont;

	a_devolver.resize(k);

	if(q.size() == 1) {
		if(index.find(q.front()) != index.end()) {
			setId1 = index.at(q.front());
			itSet = setId1.begin();
			cont = k;
			while(itSet != setId1.end() && cont > 0) {
				par.first = *itSet;
				par.second = 1.0;
				a_devolver[cont-1] = par;
				itSet++;
				cont--;
			}
		}
	} else {
		itList = q.begin();
		setId1 = index.at(*itList);
		itList++;
		setId2 = index.at(*itList);
		Union = unionPeso(setId1, setId2);
		itList++;

		while(itList != q.end()) {
			unionPeso(Union,index.at(*itList));
			itList++;
		}

		itUnion = Union.begin();
		cont = 0;
		while(itUnion != Union.end()) {
			if(cont < k) {
				cola.push(*itUnion);
				cont++;
			} else {
				if ((itUnion->second) > (cola.top()).second) {
					cola.pop();
					cola.push(*itUnion);
				}
			}
			itUnion++;
		}

		cont = k;
		while( cont > 0) {
			a_devolver[cont-1] = cola.top();
			cola.pop();
			cont--;
		}
	}

	return a_devolver;

}


//Constructor por defecto
CSS::CSS(){}

void CSS::insert(const crimen & x) {
	//insertamos en baseDatos
	baseDatos[x.getID()] = x;
	//insertamos en DataAcces 
	map<ID,crimen>::iterator it;
	pair<Date,map<ID,crimen>::iterator> Par1;
	it = baseDatos.find(x.getID());
	Par1.first = x.getDate();
	Par1.second = it;
	DateAcces.insert(Par1);
	//insertamos en IUCRAcces
	IUCRAcces[x.getIUCR()].insert(x.getID());
	//insertamos en index
	string descripcion = x.getDescription(), aux;
	int fin = 0;
	int principio = 0;
	fin = descripcion.find_first_of(" ",0);
	aux = descripcion.substr(0,fin);
	
	while(fin != descripcion.npos) {
		index[aux].insert(x.getID());
		principio = fin;
		fin = descripcion.find_first_of(" ", principio+1);
		aux = descripcion.substr(principio+1,fin-principio-1);
	}

	index[aux].insert(x.getID());
	//insertamos en posicionGeo
	pair<Latitud,ID> Par2;
	Par2.first = x.getLatitude();
	Par2.second = x.getID();
	posicionGeo[x.getLongitude()].insert(Par2);
}

void CSS::erase(const CSS::ID id){
	//almacenamos el crimen en una variable
	crimen crim;
	crim = (baseDatos.find(id))->second;

	//borramos el crimen de DateAcces
	multimap<Date, map<ID,crimen>::iterator> :: iterator itDate = DateAcces.find(crim.getDate());
	while (((*((*itDate).second)).second).getID() != crim.getID())
		itDate++;

	DateAcces.erase(itDate);

	//borramos de IUCRAcces
	map <IUCR, set<ID> > :: iterator IUCRit = IUCRAcces.find(crim.getIUCR());
	((*IUCRit).second).erase(crim.getID());
	if(((*IUCRit).second).empty())
		IUCRAcces.erase(IUCRit);

	//borramos de index
	string descripcion = crim.getDescription(), aux;
	int principio = 0;
	int fin = 0;

	fin = descripcion.find_first_of(" ",0);
	aux = descripcion.substr(0,fin);
	
	while(fin != descripcion.npos) {
		(index.at(aux)).erase(crim.getID());
		principio = fin;
		fin = descripcion.find_first_of(" ", principio+1);
		aux = descripcion.substr(principio+1,fin-principio-1);
	}

	//borramos de posicionGeo
	map <Longitud, multimap<Latitud, CSS::ID> > :: iterator itGeo = posicionGeo.find(crim.getLongitude());
	multimap<Latitud, ID> :: iterator itLatitude = ((*itGeo).second).find(crim.getLatitude());

	while((itLatitude)->second != crim.getID())
		itLatitude++;

	((*itGeo).second).erase(itLatitude);

	if(((*itGeo).second).empty())
		posicionGeo.erase(itGeo);

	//borramos el crimen de baseDatos
	baseDatos.erase(id);
}

list<CSS::ID> CSS::inArea(CSS::Longitud x1, CSS::Latitud y1, CSS::Longitud x2, CSS::Latitud y2 ) {
	list<CSS::ID> listaID;
	map <CSS::Longitud, multimap< CSS::Latitud, CSS::ID> > :: iterator itGeoIni = posicionGeo.upper_bound(x1);
	map <CSS::Longitud, multimap< CSS::Latitud, CSS::ID> > :: iterator itGeoFin = posicionGeo.lower_bound(x2);
	multimap<CSS::Latitud, CSS::ID> :: iterator itLatitudIni = (itGeoIni->second).upper_bound(y1);
	multimap<CSS::Latitud, CSS::ID> :: iterator itLatitudFin = (itGeoIni->second).lower_bound(y2);

	while(itGeoIni != itGeoFin) {
			while(itLatitudIni != itLatitudFin) {
					listaID.push_back(itLatitudIni->second);
					itLatitudIni++;
				}
		itGeoIni++;
		itLatitudIni = (itGeoIni->second).upper_bound(y1);
		itLatitudFin = (itGeoIni->second).lower_bound(y2);
	}

	return listaID;
}

CSS::iterator CSS::find_ID(const CSS::ID id) {
	CSS::iterator itID;
	itID.it = baseDatos.find(id);
	return itID;
}

void CSS::setArrest(const CSS::ID id, bool value) {
	CSS::iterator it;
	it = find_ID(id);
	((*it).second).setArrest(value);
}

CSS::IUCR_iterator CSS::lower_bound(const CSS::IUCR & iucr) {
	CSS::IUCR_iterator IUCRit;
	IUCRit.it_m = IUCRAcces.lower_bound(iucr);
	IUCRit.it_s = ((IUCRit.it_m)->second).begin();
	IUCRit.ptr = & baseDatos;

	return IUCRit;
}

CSS::IUCR_iterator CSS::upper_bound(const CSS::IUCR & iucr) {
	CSS::IUCR_iterator IUCRit;
	IUCRit.it_m = IUCRAcces.upper_bound(iucr);
	IUCRit.it_s = ((IUCRit.it_m)->second).begin();
	IUCRit.ptr = & baseDatos;

	return IUCRit;
}

CSS::Date_iterator CSS::lower_bound(const CSS::Date & date) {
	CSS::Date_iterator DateIt;
	DateIt.it_mm = DateAcces.lower_bound(date);

	return DateIt;
}

CSS::Date_iterator CSS::upper_bound(const Date & date) {
	CSS::Date_iterator DateIt;
	DateIt.it_mm = DateAcces.upper_bound(date);

	return DateIt;
}

CSS::iterator CSS::begin() {
	CSS::iterator itv;
	itv.it = baseDatos.begin();

	return itv;
}

CSS::iterator CSS::end() {
	CSS::iterator itv;
	itv.it = baseDatos.end();

	return itv;
}

CSS::Date_iterator CSS::dbegin() {
	CSS::Date_iterator itv;
	itv.it_mm = DateAcces.begin();

	return itv;
}

CSS::Date_iterator CSS::dend() {
	CSS::Date_iterator itv;
	itv.it_mm = DateAcces.end();

	return itv;
}

CSS::IUCR_iterator CSS::ibegin() {
	CSS::IUCR_iterator itv;
	itv.ptr = & baseDatos;
	itv.it_m = IUCRAcces.begin();
	itv.it_s = ((IUCRAcces.begin())->second).begin();

	return itv;
}

CSS::IUCR_iterator CSS::iend() {
	CSS::IUCR_iterator itv;
	map <IUCR, set<ID> >::iterator itAux = IUCRAcces.end();
	itv.ptr = & baseDatos;
	itv.it_m = itAux;
	itAux--;
	itv.it_s = (itAux->second).end();

	return itv;
} 
///////////////////////////////////////
//IMPLEMENTACION DE LA CLASE ITERATOR//
///////////////////////////////////////

CSS::iterator::iterator(){}

CSS::iterator::iterator(const CSS::iterator & it_c){
	it = it_c.it;
}

pair<const CSS::ID, crimen> & CSS::iterator::operator*() {
	return *it;
}

CSS::iterator CSS::iterator::operator++(int) {
	CSS::iterator original;
	original = *this;
	++it;
	return original;
}

CSS::iterator & CSS::iterator::operator++() {
	it++;
	return *this;
}

CSS::iterator CSS::iterator::operator--(int) {
	CSS::iterator original;
	original = *this;
	--it;
	return original;
}

CSS::iterator & CSS::iterator::operator--() {
	it--;
	return *this;
}

bool CSS::iterator::operator==(const CSS::iterator & it_c) {
	return it == it_c.it;
}

bool CSS::iterator::operator!=(const CSS::iterator & it_c) {
	return it != it_c.it;
}

CSS::iterator & CSS::iterator::operator=(const CSS::iterator & it_c) {
	if(this != &it_c)
		it = it_c.it;
	return *this;
}

///////////////////////////////////////////
//IMPLEMETACION DE LA CLASE DATE_ITERATOR//
///////////////////////////////////////////

CSS::Date_iterator::Date_iterator(){}

CSS::Date_iterator::Date_iterator(const CSS::Date_iterator & it){
	it_mm = it.it_mm;
}

pair<const CSS::ID, crimen > & CSS::Date_iterator::operator*() {
	map<CSS::ID,crimen>::iterator itv;
	itv = (*it_mm).second;
	return *itv;
}

CSS::Date_iterator CSS::Date_iterator::operator++(int) {
	CSS::Date_iterator original;
	original = *this;
	++it_mm;
	return original;
}

CSS::Date_iterator & CSS::Date_iterator::operator++() {
	it_mm++;
	return *this;
}

CSS::Date_iterator CSS::Date_iterator::operator--(int) {
	CSS::Date_iterator original;
	original = *this;
	--it_mm;
	return original;
}

CSS::Date_iterator & CSS::Date_iterator::operator--() {
	it_mm--;
	return *this;
}

bool CSS::Date_iterator::operator==(const CSS::Date_iterator & it) {
	return it_mm == it.it_mm;
}

bool CSS::Date_iterator::operator!=(const CSS::Date_iterator & it) {
	return it_mm != it.it_mm;
}

CSS::Date_iterator & CSS::Date_iterator::operator=(const CSS::Date_iterator & it) {
	if(this != &it)
		it_mm = it.it_mm;
	return *this;
}

////////////////////////////////////////////
//IMPLEMENTACION DE LA CLASE IUCR_ITERATOR//
////////////////////////////////////////////

CSS::IUCR_iterator::IUCR_iterator(){}

CSS::IUCR_iterator::IUCR_iterator(const CSS::IUCR_iterator & it) {
	it_m = it.it_m;
	ptr = it.ptr;
	it_s = it.it_s;
}

pair<const CSS::ID, crimen > & CSS::IUCR_iterator::operator*() {
	return  *((*ptr).find(*it_s));
}

CSS::IUCR_iterator CSS::IUCR_iterator::operator++(int) {
	CSS::IUCR_iterator original;
	++(*this);
	return original;
}

CSS::IUCR_iterator & CSS::IUCR_iterator::operator++() {
	if(it_s == (--((it_m->second).end()))) {
		it_m++;
		it_s = (it_m->second).begin();
	} else {
		it_s++;
	}
	return *this;
}

CSS::IUCR_iterator CSS::IUCR_iterator::operator--(int) {
	CSS::IUCR_iterator original;
	--(*this);
	return original;
}

CSS::IUCR_iterator & CSS::IUCR_iterator::operator--() {
	if(it_s == (((it_m->second).begin()))) {
		it_m--;
		it_s = --((it_m->second).end());
	} else {
		it_s--;
	}
	return *this;
}

bool CSS::IUCR_iterator::operator==(const CSS::IUCR_iterator & it) {
	return (it_m == it.it_m) && (it_s == it.it_s);
}

bool CSS::IUCR_iterator::operator!=(const CSS::IUCR_iterator & it) {
	return (it_m != it.it_m) && (it_s != it.it_s);
}

CSS::IUCR_iterator & CSS::IUCR_iterator::operator=(const CSS::IUCR_iterator & it) {
	if(this != &it) {
		it_m = it.it_m;
		ptr = it.ptr;
		it_s = it.it_s;
	}
	return *this;
}
