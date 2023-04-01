#include "listaActiv.h"

void ListaActiv::adaugaL(const Activitate& a) {
	lista.push_back(a);
}

void ListaActiv::goleste() {
	lista.clear();
}

void ListaActiv::stergeL() {
	lista.pop_back();
}


void ListaActiv::adaugaAleator(size_t cate, vector<Activitate> all) {
	std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (lista.size() < cate && all.size() > 0) {
		lista.push_back(all.back());
		all.pop_back();
	}
}

const vector<Activitate>& ListaActiv::getLista() const noexcept {
	return lista;
}