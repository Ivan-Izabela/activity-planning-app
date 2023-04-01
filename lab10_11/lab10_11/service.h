#pragma once 
#include "export.h"
#include "domain.h"
#include "repo.h"
#include "validator.h"
#include "undo.h"
//#include "Lista.h"
#include "listaActiv.h"
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <algorithm>

using std::unique_ptr;

using std::map;
using std::vector;
using std::string;
using std::function;


//RAPORT
/*class ActivDto {
private:
	string titlu;
	string tip;
	int count;
public:
	ActivDto() : titlu{ "" }, tip{ "" }, count{ 0 }{}
	string getTitlu() const;
	string getTip() const;
	int getCount() const  noexcept;
	void add();
	void setTip(string tp);
	void setTitlu(string tit);
};*/

class ServiceActiv {
private:
	Repo& r;
	ValidatorActiv& v;
	//tinem pointeri la ActiuneUndo pentru ca vrem apel polimorfic
	//punem unique_ptr pentru ca avem responsabilitatea de a elibera memoria pentru 
	vector<unique_ptr<ActiuneUndo>> undoActions;
	//vector<ActiuneUndo*> undoActions;
	vector<unique_ptr<ActiuneUndo>> undoActionsLista;

	ListaActiv list;

	//const vector<Activitate> sortF(bool(*maiMicF)(const Activitate&, const Activitate&)) const;

	//const vector<Activitate> filtreaza(function<bool(const Activitate&)> fct) const;

public:
	ServiceActiv(Repo& r, ValidatorActiv& v) noexcept : r{ r }, v{ v } {}

	~ServiceActiv();

	ServiceActiv(const ServiceActiv& ot) = delete;

	void operator=(const ServiceActiv& ot) = delete;

	void adaugaActiv(const string& titlu, const string& descriere, const string& tip, int durata);

	void modifActiv(const string& titlu, const string& descriere, const string& tip, int durata);

	void stergeActiv(const string& titlu);

	const Activitate& cautaActiv(const string& titlu) const;

	const vector<Activitate> getAll() const noexcept {
		return r.getAll();
	}

	const vector<Activitate> sortTitlu() const;

	const vector<Activitate> sortDescriere() const;

	const vector<Activitate> sortTipDurata() const;

	const vector<Activitate> filtrDescriere(const string& descriere) const;

	const vector<Activitate> filtrTip(const string& tip) const;

	//vector<ActivDto> raport() const;

	const void adaugaLista(const string& titlu);
	const void addRandom(int cate);
	const void golesteL();
	const vector<Activitate>& getAllList();
	void exportListaCVS(string fName) const;

	void undo();
	void undoLista();

	int total();

};


void testService();


