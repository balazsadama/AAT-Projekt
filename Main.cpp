#include "KorkorosLista.h"

KLista* kl;
ifstream f("input1.txt");

void menuKiir() {
	cout << "1. Letrehoz\n";
	cout << "2. Feltolt\n";
	cout << "3. Lekerdez egy modul tartalmat\n";
	cout << "4. Urallomas kiirasa\n";
	cout << "5. Ures-e\n";			// ez a ketto 
	cout << "6. Tele van-e\n";		// lehet nem kell ide
	cout << "7. Uj modul beszurasa\n";
	cout << "8. Modul torlese\n";
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
		if (kl->tele())
			cout << "Nem lehetseges beszurni, az urallomas mar maximalis szamu modult tartalmaz.\n";
		else {
			string s;
			cout << "Allomanybol vagy billentyuzetrol szeretne beszurni? (allomany/billentyuzet)\n";
			cin >> s;
			if (s == "allomany")
				kl->ujCspontBeszurFilebol(f);
			else if (s == "billentyuzet")
				kl->ujCspontBeszurBillentyuzetrol();
			else
				cout << "Nincs ilyen valasztasi lehetoseg.\n";
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
