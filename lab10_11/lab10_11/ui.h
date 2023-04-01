#pragma once
#include "service.h"
#include "domain.h"
#include <vector>
//#include "Lista.h"

class UI {
private:
	ServiceActiv& s;
	void add();

	int readCommand();

	void cautaA();

	void afisare(const vector<Activitate>& act);

	void del();

	void modif();

	void raport();

	void addList();

	void delList();

	void randList();

	//void exportL();

public:
	UI(ServiceActiv& s) noexcept : s{ s } {}
	//UI(const ServiceActiv& ot) = delete;

	void run();

};