#pragma once
#include "domain.h"
#include<string>
#include<vector>
#include<ostream>
#include<algorithm>
#include<map>


//#include "Lista.h"
using std::map;
using std::vector;
using std::string;
using std::ostream;

class Repo {
private:
	vector<Activitate> act;
public:
	Repo() = default;
	Repo(const Repo& ot) = delete;
	virtual ~Repo() = default;
	virtual void adauga(const Activitate& a) = 0;

	virtual const Activitate& cauta(string titlu) const = 0;

	virtual const vector<Activitate> getAll() = 0;

	virtual void sterge(const Activitate& a) = 0;

};


class RepoActiv : public Repo {
private:
	map<string, Activitate> all;

	//bool exista(const Activitate& a) const;
public:
	RepoActiv()noexcept :Repo() {};
	//RepoActiv(const RepoActiv& ot) = delete;

	//virtual ~RepoActiv() = default;

	void adauga(const Activitate& a) override;

	const Activitate& cauta(string titlu) const override;

	const vector<Activitate> getAll() override;

	void sterge(const Activitate& a) override;
};

class RepoActivEx {
private:
	string msj;
public:
	RepoActivEx(string m) : msj{ m } {}

	string getMesaj()const {
		return msj;
	}
};


class RepoActivFile :public Repo {
private:
	string fName;
	map<string, Activitate> all;
	void loadFromFile();
	void writeToFile();
public:
	RepoActivFile(string fName) :Repo(), fName{ fName }{
		loadFromFile();//incarcam datele din fisier
	}

	void adauga(const Activitate& a) override;

	void sterge(const Activitate& a) override;

	const Activitate& cauta(string titlu) const override;


	const vector<Activitate> getAll() override;


};

class RepoLab : public Repo {
private:
	int p;
	map<string, Activitate> all;
public:
	RepoLab(int p) noexcept :Repo(), p{ p } {}

	void adauga(const Activitate& a) override;

	const Activitate& cauta(string titlu) const override;

	const vector<Activitate> getAll() override;

	void sterge(const Activitate& a) override;

};

void testRepo();