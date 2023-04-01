#pragma once
#include "domain.h"
#include "repo.h"
#include "listaActiv.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;

	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Activitate actAdd;
	Repo& r;
public:
	UndoAdauga(Repo& r, const Activitate& a) : r{ r }, actAdd{ a } {}

	void doUndo() override {
		r.sterge(actAdd);
	}
};


class UndoSterge : public ActiuneUndo {
private:
	Activitate actDel;
	Repo& r;
public:
	UndoSterge(Repo& r, const Activitate& a) noexcept : r{ r }, actDel{ a } {}

	void doUndo() override {
		r.adauga(actDel);
	}
};


class UndoModifica : public ActiuneUndo {
private:
	Activitate actMdf;
	Activitate actN;
	Repo& r;
public:
	UndoModifica(Repo& r, const Activitate& a, const Activitate& b) noexcept : r{ r }, actMdf{ a }, actN{ b } {}

	void doUndo() override {
		r.sterge(actMdf);
		r.adauga(actN);
	}
};


class UndoAdaugaLista : public ActiuneUndo {
private:
	ListaActiv& l;
public:
	UndoAdaugaLista(ListaActiv& l) noexcept :l{ l } {}

	void doUndo() override {
		l.stergeL();
	}
};
