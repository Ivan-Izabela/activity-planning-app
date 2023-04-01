#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "domain.h"
using std::vector;

class ListaActiv {
private:
	vector<Activitate> lista;
public:
	ListaActiv() = default;

	void adaugaL(const Activitate& a);
	//void stergeL(const Activitate& a);

	void adaugaAleator(size_t cate, vector<Activitate> all);

	const vector<Activitate>& getLista() const noexcept;

	void goleste();

	void stergeL();
};
