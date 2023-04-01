#include "export.h"
#include "domain.h"
#include <fstream>
#include <string>
#include <vector>

#include "repo.h"

/*
Scrie in fisierul fName lista de animale
in format Comma Separated Values
arunca PetException daca nu poate crea fisierul
*/
void exportToCVS(const std::string& fName, const std::vector<Activitate>& act) {
	std::ofstream out(fName, std::ios::trunc);
	if (!out.is_open()) {
		throw RepoActivEx("Unable to open file:" + fName);
	}
	for (const auto& a : act) {
		out << a.getTitlu() << ",";
		out << a.getDescriere() << ",";
		out << a.getTip() << ",";
		out << a.getDurata() << std::endl;
	}
	out.close();
}