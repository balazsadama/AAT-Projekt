#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

#define MAX_CSOMOPONT 6

struct Csomopont {
	int lakos_sz;
	map<string, int> lakosok;
	Csomopont* next;
};

class KLista {
private:
	Csomopont *fej;
public:
	KLista();		// itt hagyom h ha elfelejt a felhasznalo init-elni, megis mukodjon a program
	void init();
	~KLista();
	int teritHossz();
	bool ures();
	bool tele();
	void kiir();
	void torol(Csomopont *p);
	Csomopont* teritFej() { return fej; }	// tesztelni, hogy a main-bol tudjunk
	void beszurEle(Csomopont *p, Csomopont *uj);
	void beszurUtan(Csomopont *p, Csomopont *uj);
	int olvasBillenytuzetrol();
	int olvasFilebol(ifstream&);
	Csomopont* ujCspontOlvasBillentyuzetrol();
	int ujCspontBeszurBillentyuzetrol();
	Csomopont* teritAdottIndexnel(int);
	void kiirCsomopont(int);
	Csomopont* ujCspontOlvasFilebol(ifstream&);
	int ujCspontBeszurFilebol(ifstream&);
	bool isNumeric(string str);
};

KLista::KLista() {
	// megfelel az Init() fuggvenynek, letrehoz egy ures Korkoros Listat

	fej = 0;
}

void KLista::init() {
	// kezdoertekkent
	fej = 0;
}

void KLista::kiir() {
	Csomopont *p;
	int count = 1;

	p = fej;
	if (fej != 0) {
		cout << endl << "Az urallomast a kovetkezo modul(ok) alkotja(k):\n";
		do {
			cout << count++ << ".modul-> ";
			cout << p->lakos_sz << " lakos: ";
			for (map<string, int>::iterator it = p->lakosok.begin(); it != p->lakosok.end(); it++)
				cout << it->first << ": " << it->second << '\t';
			cout << endl;
			p = p->next;
		} while (p != fej);
		cout << endl;
	}
}

int KLista::teritHossz() {
	// visszateriti, hogy hany csomopontot tartalmaz a lista

	int count = 0;
	Csomopont *it;

	if (fej != 0) {
		count++;
		it = fej->next;
		while (it != fej) {
			count++;
			it = it->next;
		}
	}

	return count;
}

bool KLista::ures() {
	// ha egyetlen csomopontot sem tartalmaz a lista, akkor igaz erteket terit vissza

	if (teritHossz() == 0)
		return true;
	return false;
}

bool KLista::tele() {
	// ha MAX_CSOMOPONT szamu csomopontbol all a lista, akkor igaz erteket terit vissza

	if (teritHossz() == MAX_CSOMOPONT)
		return true;
	return false;
}

KLista::~KLista() {
	// a program vegen kitorli a csomopontokat, felszabaditja a memoriat
	Csomopont *to_del, *it;

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

void KLista::torol(Csomopont *p) {
	Csomopont *q;

	if (ures())
		cout << "A lista ures!\n";
	else if (teritHossz() == 1) {
		delete fej;
		fej = 0;
	}
	else {
		if (p->next == fej)
			fej = p;
		q = p->next;
		p->lakos_sz = q->lakos_sz;
		p->lakosok = q->lakosok;
		p->next = q->next;
		delete q;
	}
}

void KLista::beszurEle(Csomopont *p, Csomopont *uj) {
	Csomopont *q = new Csomopont;

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

void KLista::beszurUtan(Csomopont *p, Csomopont *uj) {
	uj->next = p->next;
	p->next = uj;
}

int KLista::olvasBillenytuzetrol() {
	// parameterkent kap egy helyes csomopontszamot, hibakezeles mas alprogramban
	int m, n;
	Csomopont *temp, *prev;
	string foglalkozas, num;

	cout << "Hany modulbol fog allni az urallomas?\n";
	cin >> num;
	if (isNumeric(num))
		n = stoi(num);
	else
		return (0);

	if (n < 0 || n > MAX_CSOMOPONT)
		return 0;

	prev = fej;
	for (int i = 0; i < n; i++) {
		temp = new Csomopont;
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
		cout << "Kerem adja meg mindeniknek a foglalkozasat:\n";
		for (int j = 0; j < m; j++) {
			cin >> foglalkozas;
			if (temp->lakosok.find(foglalkozas) == temp->lakosok.end())	// ha nincs meg ilyen foglalkozas
				temp->lakosok.insert(pair<string, int>(foglalkozas, 1));
			else
				temp->lakosok[foglalkozas]++;
		}

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

int KLista::olvasFilebol(ifstream& f) {
	int n;
	string foglalkozas, num;
	Csomopont *temp, *prev;

	prev = 0;
	f >> num;
	if (isNumeric(num))
		n = stoi(num);
	else
		return (0);

	if (n < 0 || n > MAX_CSOMOPONT)
		return 0;

	do {
		temp = new Csomopont;
		f >> num;
		if (isNumeric(num))
			temp->lakos_sz = stoi(num);
		else {
			delete[] temp;
			return 0;
		}

		if (temp->lakos_sz < 0) {
			delete temp;
			return 0;
		}

		for (int i = 0; i < temp->lakos_sz; i++) {
			f >> foglalkozas;
			if (temp->lakosok.find(foglalkozas) == temp->lakosok.end())	//nincs meg ilyen foglalkozas
				temp->lakosok.insert(pair<string, int>(foglalkozas, 1));
			else
				temp->lakosok[foglalkozas]++;
		}

		if (fej == 0) {
			fej = temp;
		}
		else if (prev != 0) {
			prev->next = temp;
		}
		prev = temp;
		temp->next = fej;
		n--;
	} while (n != 0);

	return 1;
}

Csomopont* KLista::ujCspontOlvasBillentyuzetrol() {
	Csomopont *temp;
	string foglalkozas, num;
	int m;

	temp = new Csomopont;
	cout << "Hany lakos?\n";
	cin >> num;

	if (isNumeric(num)) {
		m = stoi(num);
		if (m < 0) {
			delete temp;
			return 0;
		}
	}
	else {
		delete temp;
		return 0;
	}

	temp->lakos_sz = m;
	cout << "Kerem adja meg mindeniknek a foglalkozasat:\n";
	for (int j = 0; j < m; j++) {
		cin >> foglalkozas;
		if (temp->lakosok.find(foglalkozas) == temp->lakosok.end())	//nincs meg ilyen foglalkozas
			temp->lakosok.insert(pair<string, int>(foglalkozas, 1));
		else
			temp->lakosok[foglalkozas]++;
	}

	return temp;
}

int KLista::ujCspontBeszurBillentyuzetrol() {
	Csomopont *uj, *hova;
	string valaszt, num;
	int ind;

	uj = ujCspontOlvasBillentyuzetrol();

	if (uj == 0)
		return 0;

	cout << "Csomopont ele, vagy csomopont utan szurjuk? (ele / utan)\n";
	cin >> valaszt;

	if (valaszt != "ele" && valaszt != "utan")
		return 0;

	cout << "Hanyadik elem " << valaszt << " szeretne beszurni?\n";
	cin >> num;

	if (isNumeric(num)) {
		ind = stoi(num);
		if (ind <= 0)
			return 0;
	}
	else
		return 0;

	hova = teritAdottIndexnel(ind);
	if (valaszt == "ele")
		beszurEle(hova, uj);
	else if (valaszt == "utan")
		beszurUtan(hova, uj);
	else
		return 0;
}

Csomopont* KLista::teritAdottIndexnel(int i) {
	// terit egy mutatot az (1-tol indexelve) i-edik elemre
	Csomopont* it;
	int n;

	n = teritHossz();
	it = fej;
	for (int k = 0; k < (i - 1) % n; k++)
		it = it->next;
	return it;
}

void KLista::kiirCsomopont(int ind) {
	Csomopont* cs = teritAdottIndexnel(ind);

	cout << cs->lakos_sz << " lakos: ";
	for (map<string, int>::iterator it = cs->lakosok.begin(); it != cs->lakosok.end(); it++)
		cout << it->first << ": " << it->second << '\t';
	cout << endl;
}

Csomopont* KLista::ujCspontOlvasFilebol(ifstream& f) {
	Csomopont *temp;
	string foglalkozas, num;

	temp = new Csomopont;
	f >> num;
	if (isNumeric(num))
		temp->lakos_sz = stoi(num);
	else {
		delete temp;
		return 0;
	}

	if (temp->lakos_sz < 0) {
		delete temp;
		return 0;
	}
	
	for (int j = 0; j < temp->lakos_sz; j++) {
		f >> foglalkozas;
		if (temp->lakosok.find(foglalkozas) == temp->lakosok.end())	//nincs meg ilyen foglalkozas
			temp->lakosok.insert(pair<string, int>(foglalkozas, 1));
		else
			temp->lakosok[foglalkozas]++;
	}

	return temp;
}

int KLista::ujCspontBeszurFilebol(ifstream& f) {
	Csomopont *uj, *hova;
	string valaszt, ind;
	int m;

	uj = ujCspontOlvasFilebol(f);

	if (uj == 0)		// ha sikertelen volt a beolvasas, sikertelen lesz a beszuras is
		return 0;

	f >> valaszt;

	if (valaszt != "ele" && valaszt != "utan")	/* this is new */
		return 0;

	f >> ind;

	if (isNumeric(ind)) {
		m = stoi(ind);
		if (m <= 0)
			return 0;
	}
	else
		return 0;

	hova = teritAdottIndexnel(m);
	if (valaszt == "ele")
		beszurEle(hova, uj);
	else if (valaszt == "utan")
		beszurUtan(hova, uj);
	else
		return 0;
	return 1;
}

bool KLista::isNumeric(string str) {
	
	if (str[0] < '0' || str[0] > '9')
		if (str[0] != '-')
			return false;
	for (unsigned int i = 1; i < str.length(); i++)
		if (str[i] < '0' || str[i] > '9')
			return false;
	return true;
}