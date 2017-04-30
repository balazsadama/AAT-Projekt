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
	KLista();
	KLista(ifstream&);	// file-bol valo beovlasasnal hasznaljuk
	KLista(Csomopont*);	// billentyuzetrol valo beolvasasnal hasznaljuk
	~KLista();
	int cspontokSzama();
	bool ures();
	bool tele();
	void kiir();
	void torol(Csomopont *p);
	Csomopont* getFej() { return fej; }	// tesztelni, hogy a main-bol tudjunk
	void beszurEle(Csomopont *p, Csomopont *uj);
	void beszurUtan(Csomopont *p, Csomopont *uj);
	void olvasBillenytuzetrol(int);
};

KLista::KLista() {
// megfelel az Init() fuggvenynek, letrehoz egy ures Korkoros Listat

	fej = 0;
}

KLista::KLista(ifstream& f) {
// file-bol valo beolvasas
	int n;
	string foglalkozas;
	Csomopont *temp, *prev;

	prev = 0;
	fej = 0;
	f >> n;
	do {
		temp = new Csomopont;
		f >> temp->lakos_sz;
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
		else if (prev != 0){
			prev->next = temp;
		}
		prev = temp;
		temp->next = fej;
		n--;
	} while (n != 0);
	f.close();
}

void KLista::kiir() {
	Csomopont *p;

	p = fej;
	if (fej != 0) do {
		//cout << "Lakosok szama : " << p->lakos_sz << endl;
		cout << p->lakos_sz << " lakos: ";
		for (map<string, int>::iterator it = p->lakosok.begin(); it != p->lakosok.end(); it++)
			//cout << it->first << '\t' << it->second << endl;
			cout << it->first << ": " << it->second << '\t';
		cout << endl;
		p = p->next;
	} while (p != fej);
	cout << endl << endl;
}

int KLista::cspontokSzama() {
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

	if (cspontokSzama() == 0)
		return true;
	return false;
}

bool KLista::tele() {
// ha MAX_CSOMOPONT szamu csomopontbol all a lista, akkor igaz erteket terit vissza

	if (cspontokSzama() == MAX_CSOMOPONT)
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
	}
}

void KLista::torol(Csomopont *p) {
	Csomopont *q;

	if (ures())
		cout << "A lista ures!\n";
	else if (cspontokSzama() == 1) {
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

KLista::KLista(Csomopont* x) {
// billentyuzetrol valo beolvasaskor inicializaljuk a Korkoros Lista fej mutatojat az elso beolvasott adatra
	fej = x;
	x->next = fej;
}

void KLista::olvasBillenytuzetrol(int n) {
	// parameterkent kap egy helyes csomopontszamot, hibakezeles mas alprogramban
	int m;
	Csomopont *temp, *prev;
	string foglalkozas;
	
	//fej = 0;
	//prev = 0;
	prev = fej;
	for (int i = 0; i < n; i++) {
		temp = new Csomopont;
		cout << "Hany lakos?\n";
		cin >> m;
		temp->lakos_sz = m;
		cout << "Kerem adja meg mindeniknek a foglalkozasat:\n";
		for (int j = 0; j < m; j++) {
			cin >> foglalkozas;
			if (temp->lakosok.find(foglalkozas) == temp->lakosok.end())	//nincs meg ilyen foglalkozas
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
}