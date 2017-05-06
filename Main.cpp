#include "KorkorosLista.h"

ifstream f("input2.txt");
ifstream g(stdin);
KLista kl;

void menuKiir() {
	cout << "\n->Menu<-\n";
	cout << "1. Feltolt\n";
	cout << "2. Egy modul kiiratasa\n";
	cout << "3. Osszes modul kiiratasa\n";
	cout << "4. Modulok darabszamanak kiiratasa\n";
	cout << "5. Uj modul hozzaadasa\n";
	cout << "6. Modul torlese\n";
	cout << "7. Uj szemely adatainak beolvasasa\n";
	cout << "8. Szemely torlese a nyilvantartasbol\n";
	cout << "9. Ev eltelese\n";
	cout << "0. Kilepes\n";
	cout << "Kerem valasszon egy muveletet: ";
}

void valaszt(int v) {
	switch (v) {
	case 0: break;
	case 1: {
		char c;

		cout << "Allomanybol vagy billentyuzetrol szeretne beolvasni? (a/b)\n";
		cin >> c;
		if (c == 'a')
			if (kl.olvas(f, 0))
				cout << "Beolvasas sikeres\n";
			else {
				cout << "Beolvasas sikertelen, hibas bemeneti adatok.\n";
				kl.~KLista();
			}
		else if (c == 'b')
			if (kl.olvas(g, 1))
				cout << "Beolvasas sikeres.\n";
			else {
				cout << "Beolvasas sikertelen, hibas bemeneti adatok.\n";
				kl.~KLista();
			}
		else
			cout << "Nincs ilyen valasztasi lehetoseg.\n";
		break;
	}

	case 2: {
		string ind;
		int n;

		if (kl.ures())
			cout << "Az urhajo nem tartalmaz modulokat.\n";
		else {
			cout << "Hanyadik modul adatait szeretne megtekinteni?\n";
			cin >> ind;
			if (isNumeric(ind)) {
				n = stoi(ind);
				if (n < 1 || n > kl.teritHossz())
					cout << "Kiiras sikertelen, hibas bemeneti adat.\n";
				else
					kl.kiirCsomopont(n);
			}
			else
				cout << "Kiiras sikertelen, hibas bemeneti adat.\n";
		}
		break;
	}

	case 3: {
		if (kl.ures())
			cout << "Az urhajo nem tartalmaz modulokat.\n";
		else
			kl.kiir();
		break;
	}

	case 4: {
		cout << "Az urallomas jelenleg " << kl.teritHossz() << " modulbol all.\n";
		break;
	}

	case 5: {
		if (kl.tele())
			cout << "Nem lehetseges beszurni, az urhajo mar maximalis szamu modult tartalmaz.\n";
		else {
			if (kl.ujCspontBeszurBillentyuzetrol())
				cout << "Sikeresen hozzaadtuk az uj modult az urallomashoz.\n";
			else
				cout << "Beszuras sikertelen, hibas bemeneti adatok.\n";
		}
		break;
	}

	case 6: {
		if (kl.ures())
			cout << "Nem lehetseges torolni, az urallomas nem tartalmaz modulokat.\n";
		else {
			string ind;
			int n;

			cout << "Hanyadik modult szeretne eltavolitani az urallomasbol?\n";
			cin >> ind;

			if (isNumeric(ind)) {
				n = stoi(ind);
				if (n > 0 && n <= kl.teritHossz()) {
					kl.torol(kl.teritAdottIndexnel(n));
					cout << "Modul sikeresen eltavolitva.\n";
				}
				else
					cout << "A megadott index helytelen.\n";
			}
			else
				cout << "A megadott index helytelen.\n";
		}
		break;
	}

	case 7: {
		if (kl.ujSzemely())
			cout << "Beolvasas sikeres.\n";
		else
			cout << "Beolvasas sikertelen, hibas bemeneti adatok.\n";
		break;
	}

	case 8: {
		if (kl.ures())
			cout << "Nem lehetseges torolni, az urallomas nem tartalmaz modulokat.\n";
		else {
			string ind;
			int n;

			cout << "Hanyadik modulban talalhato a szemely?\n";
			cin >> ind;

			if (isNumeric(ind)) {
				n = stoi(ind);
				if (n > 0 && n <= kl.teritHossz()) {
					if (kl.torolSzemely(n))
						cout << "Torles sikeres.\n";
					else
						cout << "A megadott szemely nem szerepel a modul nyilvantartasaban.\n";
				}
				else
					cout << "A megadott index helytelen.\n";
			}
			else
				cout << "A megadott index helytelen.\n";
		}
		break;
	}

	case 9: {
		kl.evEltelik();
		cout << "Mindenkinek az eletkora sikeresen frissitve\n";
		break;
	}

	default: {
		cout << "Nincs ilyen sorszamu muvelet, kerem valasszon a felsoroltak kozul.\n";
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

	f.close();
	g.close();
	return 0;
}