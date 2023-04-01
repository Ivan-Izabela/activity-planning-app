#pragma once
#include <string>
#include <vector>
#include "domain.h"

/*
Scrie in fisierul fName lista de animale
in format Comma Separated Values
arunca PetException daca nu poate crea fisierul
*/
void exportToCVS(const std::string& fName, const std::vector<Activitate>& act);
/*
Scrie in fisierul fName lista de animale
in format HTML
arunca PetException daca nu poate crea fisierul
*/
//void exportToHTML(const std::string& fName, const std::vector<Activitate>& pets);