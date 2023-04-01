#pragma once
#include <qwidget.h>
#include <qtimer.h>
#include <QtWidgets/QHBoxLayout>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qstring.h>
#include <qlabel.h>

#include <vector>
#include "listaActiv.h"
#include "observer.h"
#include "service.h"

using std::vector;

class ListaActivGUIList : public QWidget, public Observer {
private:
	ServiceActiv& s;
	ListaActiv& list;
	QListWidget* lst;
	QPushButton* btn;
	QPushButton* btnRandom;
	void loadList(const vector<Activitate>& act) {
		lst->clear();
		for (auto& a : act) {
			lst->addItem(QString::fromStdString(a.getTitlu()));

		}
	}

	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout;
		lst = new QListWidget;
		ly->addWidget(lst);
		btn = new QPushButton("Clear lista");
		ly->addWidget(btn);

		btnRandom = new QPushButton("Add random 3");
		ly->addWidget(btnRandom);
		setLayout(ly);
	}

	void connectSignals() {
		//list.addObserver(this);
		QObject::connect(btn, &QPushButton::clicked, [&]() {
			list.goleste();
			
			loadList(list.getLista());
			});
		QObject::connect(btnRandom, &QPushButton::clicked, [&]() {
			list.adaugaAleator(3,s.getAll());
			loadList(list.getLista());
			});
	}
public:
	ListaActivGUIList(ServiceActiv& s, ListaActiv& list) : s{ s }, list{ list }{
		initGUI();
		connectSignals();
		loadList(list.getLista());

	}

	void update() override {
		loadList(list.getLista());
	}


};