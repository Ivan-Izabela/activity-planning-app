#include "repo.h"
#include <assert.h>
#include<iostream>
#include<sstream>
#include<algorithm>
#include <utility>
#include <fstream>

using std::ostream;
using std::stringstream;

/*
fnctia adauga o activitate
input-a activitate
arunca o eroare in cazul in care activitatea exista deja*/
void RepoActiv::adauga(const Activitate& a) {
	/*if (exista(a)) {
		throw RepoActivEx("Aceasta activitate exista");
	}
	all.push_back(a);*/


	auto found = std::find_if(all.begin(), all.end(), [a](const std::pair<string, Activitate>& aa) {
		return (aa.second).getTitlu() == a.getTitlu() && (aa.second).getTip() == a.getTip() && (aa.second).getDescriere() == a.getDescriere() && (aa.second).getDurata() == a.getDurata();
		});

	if (found != all.end()) {
		throw RepoActivEx("Aceasta activitate exista");
	}
	all.insert(std::pair<string, Activitate>(a.getTitlu(), a));

}

/*
functia verifica daca o activitate exista
input-a activitate
functia returneaza true daca activitatea exista sau fals in caz contrar
bool RepoActiv::exista(const Activitate& a) const {
	try {
		cauta(a.getTitlu());
		return true;
	}
	catch (RepoActivEx&) {
		return false;}
}*/

/*
functia cauta o activitate dupa titlu
input-titlu
reurneaza activitatea daca aceasta exista sau arunca o exceptie daca nu*/
const Activitate& RepoActiv::cauta(string titlu) const {
	/*for (const auto& a : all) {
		if (a.getTitlu() == titlu) {
			return a;
		}
	}
	throw RepoActivEx("Nu exista aceasta activitate");*/
	auto found = std::find_if(all.begin(), all.end(), [&](const std::pair<string, Activitate>& aa) {
		return (aa.second).getTitlu() == titlu;
		});
	if (found == all.end()) {
		throw RepoActivEx("Nu exista aceasta activitate");
	}
	return (*found).second;
}

//functia returneaza toate activitatile
const vector<Activitate> RepoActiv::getAll() {
	vector<Activitate> v;
	std::transform(all.begin(), all.end(), back_inserter(v), [](std::pair<string, Activitate> const& aa) noexcept {return aa.second; });
	return v;
}



/*ostream& operator<<(ostream& out, const RepoActivEx& ex) {
	out << ex.msj;
	return out;
}*/

/*
functi sterge o activitate
input-activitate
arunca o exceptie daca aceasta nu exista*/
void  RepoActiv::sterge(const Activitate& a) {
	/*if (exista(a)==false) {
		throw RepoActivEx("Aceasta activitate nu exista");
	}
	//unsigned int it;
	vector<Activitate> all2;
	vector<Activitate>::iterator it;
	vector<Activitate>::iterator i;
	for ( it = all.begin(); it != all.end(); ++it) {

		if ((*it).getTitlu() == a.getTitlu()) {
			i = it;
		}

	}
	all.erase(i);*/

	auto found = std::find_if(all.begin(), all.end(), [a](const std::pair<string, Activitate>& aa) {
		return (aa.second).getTitlu() == a.getTitlu() && (aa.second).getTip() == a.getTip() && (aa.second).getDescriere() == a.getDescriere() && (aa.second).getDurata() == a.getDurata();
		});
	if (found == all.end()) {
		throw RepoActivEx("Nu exista aceasta activitate");
	}

	all.erase(found);


}

//REPOFILE!!!

void RepoActivFile::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) {//verificam daca s-a deschis
		throw RepoActivEx("Unable to open file:" + fName);
	}
	while (!in.eof()) {
		string titlu;
		in >> titlu;
		string descriere;
		in >> descriere;
		string tip;
		in >> tip;
		int durata;
		in >> durata;
		if (in.eof()) {
			break;
		}
		Activitate a{ titlu.c_str(),descriere.c_str(),tip.c_str(),durata };
		all.insert(std::pair<string, Activitate>(a.getTitlu(), a));
	}
	in.close();
}

void RepoActivFile::writeToFile() {
	std::ofstream out(fName);
	if (!out.is_open()) {
		throw RepoActivEx("Unable to open file");
	}
	for (auto& a : getAll()) {
		out << a.getTitlu() << std::endl;
		out << a.getDescriere() << std::endl;
		out << a.getTip() << std::endl;
		out << a.getDurata() << std::endl;
	}
	out.close();
}

void RepoActivFile::adauga(const Activitate& a) {
	loadFromFile();
	auto found = std::find_if(all.begin(), all.end(), [a](const std::pair<string, Activitate>& aa) {
		return (aa.second).getTitlu() == a.getTitlu() && (aa.second).getTip() == a.getTip() && (aa.second).getDescriere() == a.getDescriere() && (aa.second).getDurata() == a.getDurata();
		});

	if (found != all.end()) {
		throw RepoActivEx("Aceasta activitate exista");
	}
	all.insert(std::pair<string, Activitate>(a.getTitlu(), a));
	writeToFile();
}

const Activitate& RepoActivFile::cauta(string titlu) const {
	//loadFromFile();
	auto found = std::find_if(all.begin(), all.end(), [&](const std::pair<string, Activitate>& aa) {
		return (aa.second).getTitlu() == titlu;
		});
	if (found == all.end()) {
		throw RepoActivEx("Nu exista aceasta activitate");
	}
	return (*found).second;

}

void  RepoActivFile::sterge(const Activitate& a) {

	loadFromFile();
	auto found = std::find_if(all.begin(), all.end(), [a](const std::pair<string, Activitate>& aa) {
		return (aa.second).getTitlu() == a.getTitlu() && (aa.second).getTip() == a.getTip() && (aa.second).getDescriere() == a.getDescriere() && (aa.second).getDurata() == a.getDurata();
		});
	if (found == all.end()) {
		throw RepoActivEx("Nu exista aceasta activitate");
	}

	all.erase(found);
	writeToFile();


}

const vector<Activitate> RepoActivFile::getAll() {
	//loadFromFile();
	vector<Activitate> v;
	std::transform(all.begin(), all.end(), back_inserter(v), [](std::pair<string, Activitate> const& aa) noexcept {return aa.second; });
	return v;
}

//REPOLAB!!!

void RepoLab::adauga(const Activitate& a) {
	int const x = rand() % 100;
	if (x > p)
		throw RepoActivEx("!!!");
	auto found = std::find_if(all.begin(), all.end(), [a](const std::pair<string, Activitate>& aa) {
		return (aa.second).getTitlu() == a.getTitlu() && (aa.second).getTip() == a.getTip() && (aa.second).getDescriere() == a.getDescriere() && (aa.second).getDurata() == a.getDurata();
		});

	if (found != all.end()) {
		throw RepoActivEx("Aceasta activitate exista");
	}
	all.insert(std::pair<string, Activitate>(a.getTitlu(), a));

}

const Activitate& RepoLab::cauta(string titlu) const {
	int const x = rand() % 100;
	if (x > p)
		throw RepoActivEx("!!!");
	auto found = std::find_if(all.begin(), all.end(), [&](const std::pair<string, Activitate>& aa) {
		return (aa.second).getTitlu() == titlu;
		});
	if (found == all.end()) {
		throw RepoActivEx("Nu exista aceasta activitate");
	}
	return (*found).second;
}

void  RepoLab::sterge(const Activitate& a) {
	int const x = rand() % 100;
	if (x > p)
		throw RepoActivEx("!!!");

	auto found = std::find_if(all.begin(), all.end(), [a](const std::pair<string, Activitate>& aa) {
		return (aa.second).getTitlu() == a.getTitlu() && (aa.second).getTip() == a.getTip() && (aa.second).getDescriere() == a.getDescriere() && (aa.second).getDurata() == a.getDurata();
		});
	if (found == all.end()) {
		throw RepoActivEx("Nu exista aceasta activitate");
	}

	all.erase(found);


}

const vector<Activitate> RepoLab::getAll() {
	int const x = rand() % 100;
	if (x > p)
		throw RepoActivEx("!!!");
	vector<Activitate> v;
	std::transform(all.begin(), all.end(), back_inserter(v), [](std::pair<string, Activitate> const& aa) noexcept {return aa.second; });
	return v;
}

void testAdauga() {
	RepoActiv r;
	r.adauga(Activitate{ "a","a","a",5 });
	assert(r.getAll().size() == 1);

	r.adauga(Activitate{ "b","b","b",5 });
	assert(r.getAll().size() == 2);

	try {
		r.adauga(Activitate{ "a","a","a",5 });
		assert(false);
	}
	catch (const RepoActivEx&) {
		assert(true);
	}

	/*try {
		r.cauta("c");
		assert(false);}
	catch (const RepoActivEx & e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}*/
}

void testCauta() {
	RepoActiv r;
	r.adauga(Activitate{ "a","a","a",5 });
	r.adauga(Activitate{ "b","b","b",5 });

	const auto& a = r.cauta("a");
	assert(a.getDescriere() == "a");
	assert(a.getTip() == "a");

	try {
		r.cauta("c");
		assert(false);
	}
	catch (RepoActivEx&) {
		assert(true);
	}

}

void testSterge() {
	RepoActiv r;
	r.adauga(Activitate{ "a","a","a",5 });
	r.adauga(Activitate{ "b","b","b",5 });
	assert(r.getAll().size() == 2);

	r.sterge(Activitate{ "a","a","a",5 });
	assert(r.getAll().size() == 1);
	try {
		r.sterge(Activitate{ "a","a","a",5 });
		assert(false);
	}
	catch (const RepoActivEx & ex) {
		assert(ex.getMesaj() == "Nu exista aceasta activitate");
	}

}

void testFileRepo() {
	std::ofstream out("testActiv.txt", std::ios::trunc);
	out.close();//creaza un fisier gol
	RepoActivFile r{ "testActiv.txt" };
	r.adauga(Activitate{ "a","a","a",5 });

	RepoActivFile r2{ "testActiv.txt" };
	auto a = r2.cauta("a");
	assert(a.getDurata() == 5);

	try {
		r.adauga(Activitate{ "a","a","a",5 });
		assert(false);
	}
	catch (RepoActivEx&) {
		assert(true);
	}

	try {
		r2.cauta("b");
		assert(false);
	}
	catch (RepoActivEx&) {
		assert(true);
	}
	r2.sterge(Activitate{ "a","a","a",5 });
	assert(r2.getAll().size() == 0);
	try {
		r2.sterge(Activitate{ "b","b","b",4 });
		assert(false);
	}
	catch (RepoActivEx&) {
		assert(true);
	}

	RepoActivFile r3{ "testActiv.txt" };
	assert(r3.getAll().size() == 0);

	//deschide fisier inexistent
	//arunca eroare
	try {
		RepoActivFile r4{ "test/Ac.txt" };
		assert(false);
	}
	catch (RepoActivEx&) {
		assert(true);
	}
}

void testRepo() {
	testAdauga();
	testCauta();
	testSterge();
	testFileRepo();
}