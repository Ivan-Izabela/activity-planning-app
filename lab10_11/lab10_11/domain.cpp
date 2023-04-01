#include "domain.h"

//functia returneaza titlul unei activitati
string Activitate::getTitlu() const {
	return titlu;
}

//functia returneaza descrierea unei activitati
string Activitate::getDescriere() const {
	return descriere;
}

//functia returneaza tipul unei activitai
string Activitate::getTip() const {
	return tip;
}

//functia returneaza durata unei activitati
int Activitate::getDurata() const noexcept {
	return durata;
}

/*functia compara doua activitati dupa titlu
returneaza true daca a1.titlu este mai mic decat a2.titlu
*/
/*bool cmpTitlu(const Activitate& a1, const Activitate& a2) {
	return a1.getTitlu() < a2.getTitlu();
}
*/
/*functia compara doua activitati dupa descriere
returneaza true daca a1.descriere este mai mic decat a2.descriere
*/
/*
bool cmpDescriere(const Activitate& a1, const Activitate& a2) {
	return a1.getDescriere() < a2.getDescriere();
}*/

/*bool cmpTip(const Activitate& a1, const Activitate& a2) {
	return a1.getTip() < a2.getTip();
}

bool cmpDurata(const Activitate& a1, const Activitate& a2) {
	return a1.getDurata() < a2.getDurata();
}*/