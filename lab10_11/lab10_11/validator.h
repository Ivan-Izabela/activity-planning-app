#pragma once
#include <string>
#include <vector>
#include "domain.h"

using std::vector;
using std::string;
using std::ostream;

class ValidatorEx {
private:
	vector<string> mesaj;
public:
	ValidatorEx(const vector<string>& erori) :mesaj{ erori } {}
	friend ostream& operator<<(ostream& out, const ValidatorEx& ex);

};
ostream& operator<<(ostream& out, const ValidatorEx& ex);

class ValidatorActiv {
public:
	void valid(const Activitate& a);
};

void testValid();

