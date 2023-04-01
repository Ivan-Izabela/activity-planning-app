#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;


class Activitate {
private:
	string titlu;
	string descriere;
	string tip;
	int durata;
public:
	Activitate() = default;

	Activitate(const string tit, const string des, const string tip, const int drt) :titlu{ tit }, descriere{ des }, tip{ tip }, durata{ drt }{}

	/*Activitate(const Activitate& ot) :titlu{ ot.titlu }, descriere{ ot.descriere }, tip{ ot.tip }, durata{ ot.durata }{
		cout << "!!!!!\n";
	}*/

	Activitate(const Activitate& a) = default;

	Activitate& operator=(const Activitate& ot) = default;

	string getTitlu() const;
	string getDescriere() const;
	string getTip() const;
	int getDurata() const noexcept;
};

bool cmpTitlu(const Activitate& a1, const Activitate& a2);

bool cmpDescriere(const Activitate& a1, const Activitate& a2);

//bool cmpTip(const Activitate& a1, const Activitate& a2);

//bool cmpDurata(const Activitate& a1, const Activitate& a2);