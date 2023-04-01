#pragma once

#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include "service.h"
#include "domain.h"
#include <vector>

#include <QtWidgets/qradiobutton.h>

using std::vector;

class ActivitateGUI : public QWidget {
private:
	ServiceActiv& s;
	QListWidget* lst;
	//QGridLayout* ly = new QGridLayout;

	QPushButton* btnSortTitlu;
	QPushButton* btnSortDescriere;
	QPushButton* btnSortTipdurata;
	QPushButton* btnFiltrDescriere;
	QPushButton* btnFiltrTip;
	QLineEdit* txtTitlu;
	QLineEdit* txtDescriere;
	QLineEdit* txtTip;
	QLineEdit* txtDurata;
	QPushButton* btnAdd;
	QPushButton* btnDel;
	QPushButton* btnChg;
	QPushButton* btnFnd;
	QPushButton* btnPrt;
	QPushButton* btnUnd;

	QRadioButton* btnAddL;
	QPushButton* btnGol;
	QPushButton* btnAddR;
	QPushButton* btnUndL;
	QPushButton* btnPrtL;

	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(vector<Activitate> act);
	void addNew();
	void dell();
	void change();
	void find();
	//void print();
	void undo();
	
	void addList();
	void goleste();
	void addRandom();
	void undoList();

public:
	ActivitateGUI(ServiceActiv& s) : s{ s } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(s.getAll());
	}


};