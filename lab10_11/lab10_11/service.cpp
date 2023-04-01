#include "service.h"
#include <functional>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <iterator>
#include <memory>
#include <fstream>



ServiceActiv::~ServiceActiv() {
	//for (auto act: undoActions) {
		//delete act;
	//}
}

/*
functia adauga o activitate
input-titlu,descriere,tipsi durata activitate
arunca o exceptie in cazul in care datele nu sunt corecte*/
void ServiceActiv::adaugaActiv(const string& titlu, const string& descriere, const string& tip, int durata) {
	Activitate a{ titlu,descriere,tip,durata };
	v.valid(a);
	r.adauga(a);
	undoActions.push_back(std::make_unique<UndoAdauga>(r, a));
	//undoActions.push_back(new UndoAdauga{ r,a });
}

//functia cauta o activitate
const Activitate& ServiceActiv::cautaActiv(const string& titlu) const {
	return r.cauta(titlu);

}

//functia sterge activitate
//input-titlu activitatii de sters
void ServiceActiv::stergeActiv(const string& titlu) {
	const auto& a = cautaActiv(titlu);
	undoActions.push_back(std::make_unique<UndoSterge>(r, a));
	r.sterge(a);

	//undoActions.push_back(new UndoSterge{ r,a });
}

/*
funtia modifica o activitate
input-titlu,descriere,tip,durata*/
void ServiceActiv::modifActiv(const string& titlu, const string& descriere, const string& tip, int durata) {
	auto a = cautaActiv(titlu);
	r.sterge(a);
	adaugaActiv(titlu, descriere, tip, durata);
	const auto& b = cautaActiv(titlu);
	undoActions.push_back(std::make_unique<UndoModifica>(r, b, a));
}


/*const vector<Activitate> ServiceActiv::sortF(bool(*maiMicF)(const Activitate&, const Activitate&)) const{
   vector<Activitate> a{ r.getAll() };
   for (size_t i = 0; i < a.size(); i++) {
	   for (size_t j = i + 1; j < a.size(); j++) {
		   if (!maiMicF(a.at(i), a.at(j))) {
			   Activitate aux = a.at(i);
			   a.at(i) = a.at(j);
			   a.at(j) = aux;
		   }
	   }
   }

   return a;

}*/

//sortare dupa titlu
const vector<Activitate> ServiceActiv::sortTitlu() const {
	auto a = r.getAll();
	std::sort(a.begin(), a.end(), [](const Activitate& a1, const Activitate& a2) {
		return a1.getTitlu() < a2.getTitlu(); });
	return a;
}

//sortare dupa descriere
const vector<Activitate> ServiceActiv::sortDescriere() const {
	auto a = r.getAll();
	std::sort(a.begin(), a.end(), [](const Activitate& a1, const Activitate& a2) {
		return a1.getDescriere() < a2.getDescriere(); });

	return a;
}

//sortare dupa tip si durata
const vector<Activitate> ServiceActiv::sortTipDurata() const {
	/*return sortF([](const Activitate& a1, const Activitate& a2) {
		if (a1.getTip() == a2.getTip()) {
			return a1.getDurata() < a2.getDurata();
		}
		return  a1.getTip() < a2.getTip();
		});*/
	auto a = r.getAll();
	std::sort(a.begin(), a.end(), [](const Activitate& a1, const Activitate& a2) {
		if (a1.getTip() == a2.getTip())
			return a1.getDurata() < a2.getDurata();

		return a1.getTip() < a2.getTip(); });

	return a;
}

/*functie generala de filtrae
fct-functie/lambda
returneaza activitatile care trec de fct
const vector<Activitate> ServiceActiv::filtreaza(function<bool(const Activitate&)> fct) const {
	vector<Activitate> rez;
	for (const auto& a : r.getAll()) {
		if (fct(a)) {
			rez.push_back(a);
		}
	}
	return rez;
}*/

/*filtru dupa descriere
input-descriere
returneaza activitatile care au descrierea data*/
const vector<Activitate> ServiceActiv::filtrDescriere(const string& descriere) const {
	vector<Activitate> rez;
	auto all = r.getAll();
	std::copy_if(all.begin(), all.end(), back_inserter(rez), [=](const Activitate& a) {
		return a.getDescriere() == descriere; });
	return rez;
}

/*filtru dupa tip
input-tip
returneaza activitatile care au tipul dat*/
const vector<Activitate> ServiceActiv::filtrTip(const string& tip) const {

	vector<Activitate> rez;
	auto all = r.getAll();
	std::copy_if(all.begin(), all.end(), back_inserter(rez), [=](const Activitate& a) {
		return a.getTip() == tip; });
	return rez;
}

//RAPORT
/*
string ActivDto::getTitlu() const {
	return titlu;
}

string ActivDto::getTip() const {
	return tip;
}

int ActivDto::getCount() const noexcept {
	return count;
}

void ActivDto::setTitlu(string tit) {
	titlu = tit;
}

void ActivDto::setTip(string tp) {
	tip = tp;
}

void ActivDto::add() {
	count++;
}

vector<ActivDto> ServiceActiv::raport() const{
	map<string, ActivDto> m;
	vector<ActivDto> l;
	for (const auto& a : r.getAll()) {
		ActivDto d;
		d.setTitlu(a.getTitlu());
		d.setTip(a.getTip());
		for (const auto& ac : r.getAll()) {
			if (d.getTip() == ac.getTip()) {
				d.add();
			}
		}
		m.insert(std::pair<string, ActivDto>(a.getTip(), d));
	}

	vector<Activitate> v;
	std::transform(all.begin(), all.end(), back_inserter(v), [](std::pair<string, Activitate> const& aa) noexcept{return aa.second; });
	return v;
	for (const auto& a : r.getAll()) {
		ActivDto d = m.find(a.getTip())->second;
		d.setTitlu(a.getTitlu());
		l.push_back(d);
	}
	return l;
}*/



const void ServiceActiv::adaugaLista(const string& titlu) {
	const Activitate& a = r.cauta(titlu);
	list.adaugaL(a);
	undoActionsLista.push_back(std::make_unique<UndoAdaugaLista>(list));

}

const void ServiceActiv::addRandom(int cate) {
	list.adaugaAleator(cate, r.getAll());
	//return list.getLista();
}

const void ServiceActiv::golesteL() {
	list.goleste();
	//return list.getLista();
}

const vector<Activitate>& ServiceActiv::getAllList() {
	return list.getLista();
}

int ServiceActiv::total() {
	vector<int> rez;
	auto t = r.getAll();
	for (auto a : t) {
		rez.push_back(a.getDurata());
	}
	auto s = std::accumulate(rez.begin(), rez.end(), 0);
	return s;
}

void ServiceActiv::exportListaCVS(string fName) const {
	exportToCVS(fName, list.getLista());
}

void ServiceActiv::undo() {
	if (undoActions.empty()) {
		throw RepoActivEx("Nu mai exista operatii");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();

	/*ActiuneUndo* act = undoActions.back();
	act->doUndo();
	undoActions.pop_back();
	delete act;*/
}

void ServiceActiv::undoLista() {
	if (undoActionsLista.empty()) {
		throw RepoActivEx("Nu mai exista operatii");
	}
	undoActionsLista.back()->doUndo();
	undoActionsLista.pop_back();

	/*ActiuneUndo* act = undoActions.back();
	act->doUndo();
	undoActions.pop_back();
	delete act;*/
}

void testAdaugaS() {
	RepoActiv r;
	ValidatorActiv v;
	ServiceActiv s{ r,v };
	s.adaugaActiv("a", "a", "a", 4);
	assert(s.getAll().size() == 1);
	assert(s.total() == 4);
	try {
		s.adaugaActiv("", "", "", -4);
		assert(false);
	}
	catch (ValidatorEx&) {
		assert(true);
	}

	try {
		s.adaugaActiv("a", "a", "a", -4);
		assert(false);
	}
	catch (ValidatorEx&) {
		assert(true);
	}
}

void testCautaS() {
	RepoActiv r;
	ValidatorActiv v;
	ServiceActiv s{ r,v };
	s.adaugaActiv("a", "a", "a", 4);
	s.adaugaActiv("b", "b", "b", 1);
	assert(s.getAll().size() == 2);

	const auto& a = s.cautaActiv("a");
	assert(a.getDescriere() == "a");
	assert(a.getTip() == "a");

	try {
		s.cautaActiv("c");
		assert(false);
	}
	catch (RepoActivEx&) {
		assert(true);
	}
}

void testStergeS() {
	RepoActiv r;
	ValidatorActiv v;
	ServiceActiv s{ r,v };
	s.adaugaActiv("a", "a", "a", 4);
	s.adaugaActiv("b", "b", "b", 1);
	assert(s.getAll().size() == 2);

	s.stergeActiv("a");
	assert(s.getAll().size() == 1);


}

void testModif() {
	RepoActiv r;
	ValidatorActiv v;
	ServiceActiv s{ r,v };

	s.adaugaActiv("a", "a", "a", 4);
	s.adaugaActiv("b", "b", "b", 1);
	assert(s.getAll().size() == 2);

	s.modifActiv("a", "c", "d", 5);
	const auto& a = s.cautaActiv("a");
	assert(a.getDescriere() == "c");
	assert(a.getTip() == "d");

}

void testFiltrare() {
	RepoActiv r;
	ValidatorActiv v;
	ServiceActiv s{ r,v };
	s.adaugaActiv("a", "a", "a", 4);
	s.adaugaActiv("b", "a", "b", 1);
	s.adaugaActiv("c", "c", "c", 3);

	assert(s.getAll().size() == 3);
	assert(s.filtrDescriere("a").size() == 2);
	assert(s.filtrTip("a").size() == 1);
	assert(s.filtrDescriere("b").size() == 0);
}

void testSortare() {
	RepoActiv r;
	ValidatorActiv v;
	ServiceActiv s{ r,v };

	s.adaugaActiv("b", "c", "b", 4);
	s.adaugaActiv("a", "a", "a", 1);
	s.adaugaActiv("c", "c", "c", 3);
	s.adaugaActiv("d", "c", "b", 3);
	assert(s.getAll().size() == 4);

	auto a = s.sortTitlu();
	assert(a.at(0).getTitlu() == "a");

	a = s.sortDescriere();
	assert(a.at(0).getDescriere() == "a");

	a = s.sortTipDurata();
	assert(a.at(0).getDurata() == 1);

	a = s.sortTipDurata();
	assert(a.at(1).getDurata() == 3);


}

void testLista() {
	RepoActiv r;
	ValidatorActiv v;
	ServiceActiv s{ r,v };

	s.adaugaActiv("a", "a", "a", 5);
	s.adaugaActiv("b", "b", "b", 5);
	s.adaugaActiv("c", "c", "c", 5);

	assert(s.getAllList().size() == 0);
	s.adaugaLista("a");
	assert(s.getAllList().size() == 1);
	try {
		s.adaugaLista("dd");
		assert(false);
	}
	catch (RepoActivEx&) {
		assert(true);
	}
	s.golesteL();
	assert(s.getAllList().size() == 0);
	s.addRandom(5);
	assert(s.getAllList().size() == 3);

}

void testExporta() {
	RepoActiv r;
	ValidatorActiv v;
	ServiceActiv s{ r,v };
	s.adaugaActiv("a", "a", "a", 5);
	s.adaugaActiv("b", "b", "b", 5);
	s.adaugaActiv("c", "c", "c", 5);
	s.addRandom(3);
	s.exportListaCVS("testExport1.cvs");
	std::ifstream in("testExport1.cvs");
	assert(in.is_open());
	int countLines = 0;
	while (!in.eof()) {
		string line;
		in >> line;
		countLines++;
	}
	in.close();
	assert(countLines == 4);
	in.open("testExport1.cvs");
	assert(in.is_open());

	try {
		s.exportListaCVS("test/export.cvs");
		assert(false);
	}
	catch (RepoActivEx&) {
		assert(true);
	}
}


void testUndo() {
	RepoActiv r;
	ValidatorActiv v;
	ServiceActiv s{ r,v };
	s.adaugaActiv("a", "a", "a", 5);
	s.adaugaActiv("b", "b", "b", 5);
	s.adaugaActiv("c", "c", "c", 5);
	s.undo();
	assert(s.getAll().size() == 2);
	s.undo();
	s.undo();
	assert(s.getAll().size() == 0);
	try {
		s.undo();
		assert(false);
	}
	catch (RepoActivEx&) {
		assert(true);
	}

	s.adaugaActiv("a", "a", "a", 5);
	s.adaugaActiv("b", "b", "b", 5);
	s.adaugaActiv("c", "c", "c", 5);
	assert(s.getAll().size() == 3);

	assert(s.getAllList().size() == 0);
	s.adaugaLista("a");
	assert(s.getAllList().size() == 1);
	s.undoLista();
	assert(s.getAllList().size() == 0);

	try {
		s.undoLista();
		assert(false);
	}
	catch (RepoActivEx&) {
		assert(true);
	}



	s.stergeActiv("a");
	assert(s.getAll().size() == 2);
	s.undo();
	assert(s.getAll().size() == 3);



	s.modifActiv("a", "d", "d", 7);
	auto ac = s.cautaActiv("a");
	assert(ac.getDescriere() == "d");
	assert(ac.getDurata() == 7);
	s.undo();
	ac = s.cautaActiv("a");
	assert(ac.getDescriere() == "a");
	assert(ac.getDurata() == 5);
}

void testService() {
	testAdaugaS();
	testCautaS();
	testStergeS();
	testModif();
	testFiltrare();
	testSortare();
	testLista();
	testExporta();
	testUndo();
}
