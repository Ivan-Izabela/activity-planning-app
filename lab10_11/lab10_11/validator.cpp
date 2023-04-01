#include "validator.h"
#include "domain.h"
#include <assert.h>
#include <sstream>


void ValidatorActiv::valid(const Activitate& a) {
	vector<string> mesaj;
	if (a.getTitlu().size() == 0) mesaj.push_back("Titlul nu trebuie sa fie vid!");
	if (a.getDescriere().size() == 0) mesaj.push_back("Descrierea nu trebuie sa fie vid!");
	if (a.getTip().size() == 0) mesaj.push_back("Tipul nu trebuie sa fie vid!");
	if (a.getDurata() < 0) mesaj.push_back("Durata trebuie sa fie un nr natural!");
	if (mesaj.size() > 0) {
		throw ValidatorEx(mesaj);
	}
}

ostream& operator<<(ostream& out, const ValidatorEx& ex) {
	for (const auto& msj : ex.mesaj) {
		out << msj << " ";
	}
	return out;
}

void testValid() {
	ValidatorActiv v;
	Activitate a{ "","","",-5 };
	try {
		v.valid(a);
	}
	catch (const ValidatorEx & ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("vid") >= 0);
		assert(mesaj.find("natural") >= 0);

	}

}