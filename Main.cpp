#include "KorkorosLista.h"

KLista* kl;
ifstream f("input1.txt");

void menuKiir() {
	cout << "->Menu<-\n";
	cout << "1. Letrehoz\n";
	cout << "2. Feltolt\n";
	cout << "3. Lekerdez egy modul tartalmat\n";
	cout << "4. Urallomas kiiratasa\n";
	cout << "5. Ures-e\n";
	cout << "6. Tele van-e\n";
	cout << "7. Modulok darabszamanak kiiratasa\n";
	cout << "8. Uj modul beszurasa\n";
	cout << "9. Modul torlese\n";
	cout << "0. Kilepes\n";
}


void valaszt(int v) {
	switch (v) {
	case 1: {
		if (kl == 0) {
			kl = new KLista;	// meghivodik a konstruktor, ami a fej mutatot nullra allitja
			cout << "Letrehozas sikeres.\n";
		}
		else
			cout << "Az urallomas mar letre volt hozva!\n";
		break;
	}

	case 2: {
		string s;
		cout << "Allomanybol vagy billentyuzetrol szeretne beolvasni? (allomany/billentyuzet)\n";
		cin >> s;
		if (s == "allomany")
			kl->olvasFilebol(f);
		else if (s == "billentyuzet")
			kl->olvasBillenytuzetrol();
		else
			cout << "Nincs ilyen valasztasi lehetoseg.\n";
		break;
	}

	case 3: {
		int ind;
		cout << "Hanyadik modul adatait szeretne megtekinteni?\n";
		cin >> ind;
		kl->kiirCsomopont(ind);
		break;
	}

	case 4: {
		if (kl->ures())
			cout << "Az urallomas nem tartalmaz modulokat.\n";
		else
			kl->kiir();
		break;
	}

	case 5: {
		if (kl->ures())
			cout << "Az urallomas nem tartalmaz modulokat.\n";
		else
			cout << "Az urallomas tartalmaz modulokat.\n";
		break;
	}

	case 6: {
		if (kl->tele())
			cout << "Az urallomas maximalis szamu modult tartalmaz.\n";
		else
			cout << "Az urallomashoz meg lehet hozzaadni modult.\n";
		break;
	}

	case 7: {
		cout << "Az urallomas jelenleg " << kl->teritHossz() << " darab modulbol all.\n";
		break;
	}

	case 8: {
		if (kl->tele())
			cout << "Nem lehetseges beszurni, az urallomas mar maximalis szamu modult tartalmaz.\n";
		else {
			string s;
			cout << "Allomanybol vagy billentyuzetrol szeretne beszurni? (allomany/billentyuzet)\n";
			cin >> s;
			if (s == "allomany")
				if (!f.eof()) {
					kl->ujCspontBeszurFilebol(f);
					cout << "Sikeresen hozzaadtuk az uj modult az urallomashoz.\n";
				}
				else
					cout << "Beszuras sikertelen, az allomanyban nincs tobb adat.\n";
			else if (s == "billentyuzet") {
				kl->ujCspontBeszurBillentyuzetrol();
				cout << "Sikeresen hozzaadtuk az uj modult az urallomashoz.\n";
			}
			else
				cout << "Nincs ilyen valasztasi lehetoseg.\n";
		}
		break;
	}

	case 9: {
		if (kl->ures())
			cout << "Nem lehetseges torolni, az urallomas nem tartalmaz modulokat.\n";
		else {
			int ind;

			cout << "Hanyadik modult szeretne eltavolitani az urallomasbol?\n";
			cin >> ind;
			if (ind < 1)
				cout << "A megadott sorszam helytelen.\n";
			else {
				kl->torol(kl->teritAdottIndexnel(ind));
				cout << "Modul sikeresen eltavolitva.\n";
			}
		}
		break;
	}
	}
}


int main() {
	int v;

	do {
		menuKiir();
		cin >> v;
		valaszt(v);
	} while (v != 0);

	if (kl != 0)
		delete kl;

	f.close();
	return 0;
}
