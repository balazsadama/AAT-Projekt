#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>
using namespace std;

#define MAX_Modul 6

struct Modul {
	int lakos_sz;
	map<pair<string, string>, int> lakosok;	// foglalkozas, nev, kor
	Modul* next;
};

class KLista {
private:
	int modulok_sz;
	Modul *fej;
public:
	KLista();
	~KLista();
	int teritHossz();
	bool ures();
	bool tele();
	void kiir();
	void torol(Modul *p);
	void beszurEle(Modul *p, Modul *uj);
	void beszurUtan(Modul *p, Modul *uj);

	Modul* ujModulOlvasBillentyuzetrol();
	int ujModulBeszurBillentyuzetrol();

	Modul* teritAdottIndexnel(int);
	void kiirModul(int);
	
	int olvas(ifstream&, bool);
	Modul* ujModulOlvas(ifstream&, bool);
	
	void evEltelik();
	int ujSzemely();
	int torolSzemely(int);
};

KLista::KLista() {
	// megfelel az Init() fuggvenynek, letrehoz egy ures Korkoros Listat

	modulok_sz = 0;
	fej = 0;
}

// mukszik
void KLista::kiir() {
	Modul *p;
	int count = 1;

	p = fej;
	cout << endl << "Az urallomast a kovetkezo modul(ok) alkotja(k):\n";
	if (p != 0) do {
		cout << count << ".modul-> ";
		kiirModul(count++);
		p = p->next;
	} while (p != fej);
	cout << endl;
}

KLista::~KLista() {
	// a program vegen kitorli a Modulokat, felszabaditja a memoriat
	Modul *to_del, *it;

	if (fej != 0) {
		it = fej;
		do {
			to_del = it;
			it = it->next;
			delete to_del;
		} while (it != fej);
		fej = 0;
	}
}

bool isNumeric(string str) {

	if (str[0] < '0' || str[0] > '9')
		if (str[0] != '-')
			return false;
	for (unsigned int i = 1; i < str.length(); i++)
		if (str[i] < '0' || str[i] > '9')
			return false;
	return true;
}

// mukszik
void KLista::beszurUtan(Modul *p, Modul *uj) {
	uj->next = p->next;
	p->next = uj;
}

// mukszik
void KLista::beszurEle(Modul *p, Modul *uj) {
	Modul *q = new Modul;

	q->lakosok = p->lakosok;
	q->lakos_sz = p->lakos_sz;
	q->next = p->next;

	p->lakosok = uj->lakosok;
	p->lakos_sz = uj->lakos_sz;
	p->next = q;
	delete uj;

	// ha a fej ele kell beszurni, akkor a fej mutatot aktualizaljuk, mert folulirtuk az eredeti
	// poziciojan az adatokat
	if (p == fej)
		fej = q;
}

// mukszik
Modul* KLista::ujModulOlvasBillentyuzetrol() {
	Modul *temp;
	string foglalkozas, num, nev, kor;
	int m;

	temp = new Modul;
	cout << "Hany lakos?\n";
	cin >> num;
	if (isNumeric(num))
		m = stoi(num);
	else {
		delete temp;
		return (0);
	}

	if (m < 0) {
		delete temp;
		return 0;
	}

	temp->lakos_sz = m;
	cout << "Adja meg mindeniknek a foglalkozasat, nevet es eletkorat (fontos a sorrend):\n";
	for (int j = 0; j < m; j++) {
		cin >> foglalkozas >> nev >> kor;
		if (!isNumeric(kor)) {
			delete temp;
			return 0;
		}
		if (temp->lakosok.find(pair<string, string>(foglalkozas, nev)) == temp->lakosok.end())
			temp->lakosok.insert(pair<pair<string, string>, int>(pair<string, string>(foglalkozas, nev), stoi(kor)));
		else {
			delete temp;
			return 0;
		}
	}

	return temp;
}


// mukszik
int KLista::teritHossz() {
	return modulok_sz;
}

// mukszik
bool KLista::ures() {
	// ha egyetlen Modulot sem tartalmaz a lista, akkor igaz erteket terit vissza

	if (modulok_sz == 0)
		return true;
	return false;
}

// mukszik
bool KLista::tele() {
	// ha MAX_Modul szamu Modulbol all a lista, akkor igaz erteket terit vissza

	if (modulok_sz == MAX_Modul)
		return true;
	return false;
}

// mukszik
void KLista::torol(Modul *p) {
	Modul *q;

	if (ures())
		cout << "A lista ures!\n";
	else if (teritHossz() == 1) {
		delete fej;
		fej = 0;
		modulok_sz = 0;
	}
	else {
		if (p->next == fej)
			fej = p;
		q = p->next;
		p->lakos_sz = q->lakos_sz;
		p->lakosok = q->lakosok;
		p->next = q->next;
		delete q;
		modulok_sz--;
	}
}

// mukszik
Modul* KLista::teritAdottIndexnel(int i) {
	// terit egy mutatot az (1-tol indexelve) i-edik elemre
	Modul* it;

	it = fej;
	for (int k = 1; k < i; k++)
		it = it->next;
	return it;
}

// mukszik
int KLista::ujModulBeszurBillentyuzetrol() {
	Modul *uj, *hova;
	string valaszt, num;
	int ind;

	uj = ujModulOlvasBillentyuzetrol();

	if (uj == 0)
		return 0;

	if (fej == 0) {
		fej = uj;
		uj->next = fej;
		modulok_sz++;
		return 1;
	}

	cout << "Modul ele, vagy Modul utan szurjuk? (ele / utan)\n";
	cin >> valaszt;

	if (valaszt != "ele" && valaszt != "utan")
		return 0;

	cout << "Hanyadik modul " << valaszt << " szeretne beszurni?\n";
	cin >> num;

	if (isNumeric(num)) {
		ind = stoi(num);
		if (ind <= 0)
			return 0;
	}
	else
		return 0;

	hova = teritAdottIndexnel(ind);
	if (valaszt == "ele") {
		beszurEle(hova, uj);
		modulok_sz++;
	}
	else if (valaszt == "utan") {
		beszurUtan(hova, uj);
		modulok_sz++;
	}
	else
		return 0;
	return 1;
}

// mukszik
void KLista::kiirModul(int ind) {
	Modul* p = teritAdottIndexnel(ind);

	cout << p->lakos_sz << " lakos: ";
	for (map<pair<string, string>, int >::iterator it = p->lakosok.begin(); it != p->lakosok.end(); it++)
		cout << it->first.first << ": " << it->first.second << ' ' << it->second << '\t';
	cout << endl;
}

Modul* KLista::ujModulOlvas(ifstream& f, bool billentyuzetrol) {
	Modul *temp;
	string foglalkozas, num, nev, kor;
	int m;

	temp = new Modul;
	if (billentyuzetrol)
		cout << "Hany lakos?\n";
	f >> num;
	if (isNumeric(num))
		m = stoi(num);
	else {
		delete temp;
		return (0);
	}

	if (m < 0) {
		delete temp;
		return 0;
	}

	temp->lakos_sz = m;
	if (billentyuzetrol)
		cout << "Adja meg mindeniknek a foglalkozasat, nevet es eletkorat (fontos a sorrend):\n";
	for (int j = 0; j < m; j++) {
		f >> foglalkozas >> nev >> kor;
		if (!isNumeric(kor)) {
			delete temp;
			return 0;
		}
		if (temp->lakosok.find(pair<string, string>(foglalkozas, nev)) == temp->lakosok.end())
			temp->lakosok.insert(pair<pair<string, string>, int>(pair<string, string>(foglalkozas, nev), stoi(kor)));
		else {
			delete temp;
			return 0;
		}
	}

	return temp;
}

int KLista::olvas(ifstream& f, bool billentyuzetrol) {
	int n;
	Modul *temp, *prev;
	string foglalkozas, num, nev, kor;

	if (f.eof())
		return 0;

	if (billentyuzetrol)
		cout << "Hany modulbol fog allni az urallomas?\n";
	f >> num;
	if (isNumeric(num))
		n = stoi(num);
	else
		return (0);

	if (n < 0 || n > MAX_Modul)
		return 0;

	modulok_sz = n;
	prev = fej;
	for (int i = 0; i < n; i++) {

		temp = ujModulOlvas(f, billentyuzetrol);
		if (temp == 0)
			return 0;

		if (fej == 0) {
			fej = temp;
			temp->next = fej;
		}
		else
			beszurUtan(prev, temp);
		prev = temp;
	}

	return 1;
}

void KLista::evEltelik(){
	Modul* p = fej;

	if (p != 0) do {
		for (map<pair<string, string>, int>::iterator it = p->lakosok.begin(); it != p->lakosok.end(); ++it)
			it->second++;
		p = p->next;
	} while (p != fej);
}

int KLista::ujSzemely() {
	Modul* p;
	string foglalkozas, nev, num;
	int m;

	cout << "Mi lesz a foglalkozasa?\n";
	cin >> foglalkozas;
	cout << "Mi lesz a neve?\n";
	cin >> nev;
	cout << "Hanyas modulban fog elni?\n";
	cin >> num;

	if (!isNumeric(num))
		return 0;
	m = stoi(num);
	if (m < 1 || m > modulok_sz)
		return 0;

	p = teritAdottIndexnel(m);
	while (p->lakosok.find(pair<string, string>(foglalkozas, nev)) != p->lakosok.end()) {
		cout << "Ilyen nevu es foglalkozasu szemely mar letezik ebben a modulban, kerem adjon meg mas nevet:\n";
		cin >> nev;
	}

	p->lakosok.insert(pair<pair<string, string>, int>(pair<string, string>(foglalkozas, nev), 0));
	p->lakos_sz++;
	return 1;
}

int KLista::torolSzemely(int ind) {
	Modul *p = teritAdottIndexnel(ind);
	string foglalkozas, nev;

	cout << "Mi a foglalkozasa?\n";
	cin >> foglalkozas;
	cout << "Mi a neve?\n";
	cin >> nev;

	if (p->lakosok.find(pair<string, string>(foglalkozas, nev)) != p->lakosok.end()) {
		p->lakosok.erase(pair<string, string>(foglalkozas, nev));
		p->lakos_sz--;
		return 1;
	}
	else
		return 0;
}