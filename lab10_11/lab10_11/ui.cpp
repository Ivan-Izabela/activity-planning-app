#include "ui.h"
#include "domain.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

template<typename T>

T myread(const char* msg) {
	T cmd{};
	while (true) {
		cout << endl << msg;
		cin >> cmd;
		const bool fail = cin.fail();
		cin.clear();
		const auto& aux = cin.ignore(1000, '\n');
		if (!fail && aux.gcount() <= 1) {
			break; //nu am reusit sa citesc numar
		}
	}
	return cmd;
}

int UI::readCommand() {
	cout << "Meniu:\n";
	cout << " 0-exit\n 1-adauga\n 2-afisare activ\n 3-cauta\n 4-sterge\n 5-modifica\n 6-sortare titlu\n 7-sortare descriere\n ";
	cout << "8-sortare tip/durata\n 9-filtrare descriere\n 10-filtrare tip\n 11-raport\n ";
	cout << "12 - adauga activ.in lista\n 13 - goleste lista de activ.\n 14 - adauga random in lista\n ";
	cout << "15 - afisare lista activ\n 16 - total\n 17 - exportCVS\n 18 - undo\n 19 - undoLista";

	return myread<int>("Dati comanda:");
}


/*void printTableHeader() {
	cout.width(20);
	cout << "Titlu";
	cout.width(20);
	cout << "Descriere";
	cout.width(20);
	cout << "Tip";
	cout.width(10);
	cout << "Durata";

}

void UI::afisare(const vector<Activitate>& act) {
	cout << "Activitati:\n";
	printTableHeader();
	for (const auto& a : act) {
		cout.width(20);
		cout << a.getTitlu();
		cout.width(20);
		cout << a.getDescriere();
		cout.width(20);
		cout << a.getTip();
		cout.width(10);
		cout << a.getDurata();
	}
	cout << endl;
}*/

void UI::afisare(const vector<Activitate>& act) {
	cout << "Activitati:\n";
	for (const auto& a : act) {
		cout << "Titlu: " << a.getTitlu() << " Descriere: " << a.getDescriere() << " Tip: " << a.getTip() << " Durata: " << a.getDurata() << "\n";

	}
}

/*void UI::raport() {
	auto l = s.raport();
	for (const auto& a : l) {
		cout << "Titlu: " << a.getTitlu() << " Tip: " << a.getTip() << " Type Count: " << a.getCount()<<"\n";
	}
}*/

void UI::add() {
	const string tit = myread<string>("Titlu:");
	const string desc = myread<string>("Destinatie:");
	const string tip = myread<string>("Tip:");
	const int drt = myread<int>("Durata:");
	s.adaugaActiv(tit, desc, tip, drt);
	cout << "Activitatea a fost adaugata!\n";
}

void UI::run() {
	while (true) {
		const int cmd = readCommand();
		if (cmd == 0) {
			break;
		}
		try {
			if (cmd == 1) {
				add();
			}
			if (cmd == 2) {
				afisare(s.getAll());
			}
			if (cmd == 3) {
				cautaA();
			}
			if (cmd == 4) {
				del();

			}
			if (cmd == 5) {
				modif();
			}
			if (cmd == 6) {
				afisare(s.sortTitlu());
			}
			if (cmd == 7) {
				afisare(s.sortDescriere());
			}
			if (cmd == 8) {
				afisare(s.sortTipDurata());
			}
			if (cmd == 9) {
				cout << "Dati descrierea: ";
				string d;
				cin >> d;
				afisare(s.filtrDescriere(d));
			}
			if (cmd == 10) {
				cout << "Dati tipul: ";
				string t;
				cin >> t;
				afisare(s.filtrTip(t));
			}
			/*if (cmd == 11) {
				raport();
			}*/
			if (cmd == 12) {
				addList();
			}
			if (cmd == 13) {
				delList();
			}
			if (cmd == 14) {
				randList();
			}
			if (cmd == 15) {
				afisare(s.getAllList());
			}
			if (cmd == 16) {
				cout << s.total() << "\n";
			}
			if (cmd == 17) {
				s.exportListaCVS(myread<string>("CVS file:"));
			}
			if (cmd == 18) {
				s.undo();
			}
			if (cmd == 19) {
				s.undoLista();
			}


		}
		catch (const RepoActivEx & ex) {
			cout << ex.getMesaj() << "\n";
		}
		catch (const ValidatorEx & ex) {
			cout << ex << "\n";
		}
	}
}

void UI::cautaA() {
	const string tit = myread<string>("Titlu:");
	auto a = s.cautaActiv(tit);
	cout << "Titlu: " << a.getTitlu() << " Descriere: " << a.getDescriere() << " Tip: " << a.getTip() << " Durata: " << a.getDurata() << "\n";

}

void UI::del() {
	const string tit = myread<string>("Titlu:");
	s.stergeActiv(tit);
	cout << "Activitatea a fost stearsa!\n";
}

void UI::modif() {
	const string tit = myread<string>("Titlu:");
	const string desc = myread<string>("Descriere:");
	const string tip = myread<string>("Tip:");
	const int drt = myread<int>("Durata:");
	s.modifActiv(tit, desc, tip, drt);
	cout << "Activitatea a fost modificata!\n";
}

void UI::addList() {
	const string tit = myread<string>("Titlu:");
	s.adaugaLista(tit);
	cout << "Activitatea a fost adaugata in lista!\n";
	cout << "In lista sunt: " << s.getAllList().size() << " activitati.\n";

}

void UI::delList() {
	s.golesteL();
	cout << "Lista a fost golita!\n";
	cout << "In lista sunt: " << s.getAllList().size() << " activitati.\n";
}

void UI::randList() {
	const int cate = myread<int>("Cate:");
	s.addRandom(cate);
	cout << "In lista sunt: " << s.getAllList().size() << " activitati.\n";
}

/*void UI::exportL() {
	cout << "CVS FILE: ";
	string fName;
	cin >> fName;
	s.exportListaCVS(fName);

}*/

/*
void UI::run() {
	int ok = 0;
	while (ok == 0) {
		cout << "Meniu:\n";
		cout << " 0-exit\n 1-adauga\n 2-afisare activ\n 3-cauta\n 4-sterge\n 5-modifica\n 6-sortare titlu\n 7-sortare descriere\n 8-sortare tip/durata\n 9-filtrare descriere\n 10-filtrare tip\n 11-raport\n 12-adauga activ. in lista\n 13-goleste lista de activ.\n 14-adauga random in lista\n 15-afisare lista activ\n 16-total\n ";
		int cmd;
		cout << "Dati comanda: ";
		cin >> cmd;
		try {
			if (cmd == 0) {
				cout << "Bye";
				ok = 1;
			}
			if (cmd == 1) {
				add();
			}
			if (cmd == 2) {
				afisare(s.getAll());
			}
			if (cmd == 3) {
				cautaA();
			}
			if (cmd == 4) {
				del();
			}
			if (cmd == 5) {
				modif();
			}
			if (cmd == 6) {
				afisare(s.sortTitlu());
			}
			if (cmd == 7) {
				afisare(s.sortDescriere());
			}
			if (cmd == 8) {
				afisare(s.sortTipDurata());
			}
			if (cmd == 9) {
				cout << "Dati descrierea: ";
				string d;
				cin >> d;
				afisare(s.filtrDescriere(d));
			}
			if (cmd == 10) {
				cout << "Dati tipul: ";
				string t;
				cin >> t;
				afisare(s.filtrTip(t));
			}
			//if (cmd == 11) {
				//raport();
			//}
			if (cmd == 12) {
				addList();
			}
			if (cmd == 13) {
				delList();
			}
			if (cmd == 14) {
				randList();
			}
			if (cmd == 15) {
				afisare(s.getAllList());
			}
			if (cmd == 16) {
				cout << s.total() << "\n";
			}

		}
		catch (const RepoActivEx & ex) {
			cout << ex << "\n";
		}
		catch (const ValidatorEx & ex) {
			cout << ex << "\n";
		}

	}

}*/