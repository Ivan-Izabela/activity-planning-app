
#include "activGUI.h"
#include "domain.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>

using std::string;

void ActivitateGUI::initGUICmps() {
	//QHBoxLayout* ly = new QHBoxLayout;
	QGridLayout* ly = new QGridLayout;
	setLayout(ly);
	
	//adauga lista si butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	lst = new QListWidget;
	vl->addWidget(lst);

	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);

	btnSortTitlu = new QPushButton("Sort titlu:");
	lyBtnsDr->addWidget(btnSortTitlu);

	btnSortDescriere = new QPushButton("Sort descriere:");
	lyBtnsDr->addWidget(btnSortDescriere);

	btnSortTipdurata = new QPushButton("Sort tip-durata:");
	lyBtnsDr->addWidget(btnSortTipdurata);

	btnFiltrDescriere = new QPushButton("Filtru descriere:");
	lyBtnsDr->addWidget(btnFiltrDescriere);

	btnFiltrTip = new QPushButton("Filtru tip:");
	lyBtnsDr->addWidget(btnFiltrTip);

	vl->addWidget(widBtnDreapta);
	ly->addWidget(widDreapta);

	//format pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);

	txtTitlu = new QLineEdit;
	formLDetalii->addRow(new QLabel("Titlu: "), txtTitlu);

	txtDescriere = new QLineEdit;
	formLDetalii->addRow(new QLabel("Descriere: "), txtDescriere);

	txtTip = new QLineEdit;
	formLDetalii->addRow(new QLabel("Tip: "), txtTip);


	txtDurata = new QLineEdit;
	formLDetalii->addRow(new QLabel("Durata: "), txtDurata);

	btnAdd = new QPushButton("Add actv.");
	formLDetalii->addWidget(btnAdd);

	btnDel = new QPushButton("Delete actv.");
	formLDetalii->addWidget(btnDel);

	btnChg = new QPushButton("Change actv.");
	formLDetalii->addWidget(btnChg);

	btnFnd = new QPushButton("Find actv.");
	formLDetalii->addWidget(btnFnd);

	btnPrt = new QPushButton("Print actv.");
	formLDetalii->addWidget(btnPrt);

	btnUnd = new QPushButton("Undo actv.");
	formLDetalii->addWidget(btnUnd);

	btnAddL = new QRadioButton("Add actv. lista");
	formLDetalii->addWidget(btnAddL);

	btnAddR = new QPushButton("Add actv. random");
	formLDetalii->addWidget(btnAddR);

	btnGol = new QPushButton("Goleste lista actv.");
	formLDetalii->addWidget(btnGol);

	btnUndL = new QPushButton("Undo lista");
	formLDetalii->addWidget(btnUndL);

	btnPrtL = new QPushButton("Print lista actv.");
	formLDetalii->addWidget(btnPrtL);

	ly->addWidget(widDetalii);
}

void ActivitateGUI::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortTitlu, &QPushButton::clicked, [&]() {
		reloadList(s.sortTitlu());
		});

	QObject::connect(btnSortDescriere, &QPushButton::clicked, [&]() {
		reloadList(s.sortDescriere());
		});

	QObject::connect(btnSortTipdurata, &QPushButton::clicked, [&]() {
		reloadList(s.sortTipDurata());
		});

	//cand se selecteaza elementul din lista incarc detaliile

	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		if (lst->selectedItems().isEmpty()) {
			//nu este nimic in lista;
			txtTitlu->setText("");
			txtDescriere->setText("");
			txtTip->setText("");
			txtDurata->setText("");
			return;
		}

		QListWidgetItem* selItem = lst->selectedItems().at(0);
		QString titlu = selItem->text();
		txtTitlu->setText(titlu);

		QString descriere = selItem->data(Qt::UserRole).toString();
		txtDescriere->setText(descriere);

		//QString tip = selItem->data(Qt::UserRole).toString();
		//txtTip->setText(tip);


		try {
			//cautam activitate
			Activitate aa = s.cautaActiv(titlu.toStdString());
			txtTip->setText(QString::fromStdString(aa.getTip()));
		}
		catch (RepoActivEx & ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
		}

		try {
			//cautam activitate
			Activitate a = s.cautaActiv(titlu.toStdString());
			txtDurata->setText(QString::number(a.getDurata()));
		}
		catch (RepoActivEx & ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
		}

	});

	QObject::connect(btnFiltrDescriere, &QPushButton::clicked, [&]() {
		reloadList(s.filtrDescriere(txtDescriere->text().toStdString()));
		});

	QObject::connect(btnFiltrTip, &QPushButton::clicked, [&]() {
		reloadList(s.filtrTip(txtTip->text().toStdString()));
		});

	QObject::connect(btnPrt, &QPushButton::clicked, [&]() {
		reloadList(s.getAll());
		});
	QObject::connect(btnPrtL, &QPushButton::clicked, [&]() {
		reloadList(s.getAllList());
		});

	QObject::connect(btnAdd, &QPushButton::clicked, this, &ActivitateGUI::addNew);
	QObject::connect(btnDel, &QPushButton::clicked, this, &ActivitateGUI::dell);
	QObject::connect(btnChg, &QPushButton::clicked, this, &ActivitateGUI::change);
	QObject::connect(btnFnd, &QPushButton::clicked, this, &ActivitateGUI::find);
	QObject::connect(btnUnd, &QPushButton::clicked, this, &ActivitateGUI::undo);

	QObject::connect(btnAddL, &QPushButton::clicked, this, &ActivitateGUI::addList);
	QObject::connect(btnGol, &QPushButton::clicked, this, &ActivitateGUI::goleste);
	QObject::connect(btnAddR, &QPushButton::clicked, this, &ActivitateGUI::addRandom);
	QObject::connect(btnUndL, &QPushButton::clicked, this, &ActivitateGUI::undoList);


}

void ActivitateGUI::addNew() {
	try {
		s.adaugaActiv(txtTitlu->text().toStdString(), txtDescriere->text().toStdString(), txtTip->text().toStdString(), txtDurata->text().toDouble());
		reloadList(s.getAll());
	}
	catch(RepoActivEx& ex){
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}

void ActivitateGUI::dell() {
	try {
		s.stergeActiv(txtTitlu->text().toStdString());
		reloadList(s.getAll());
	}
	catch (RepoActivEx & ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}

void ActivitateGUI::change() {
	try {
		s.modifActiv(txtTitlu->text().toStdString(), txtDescriere->text().toStdString(), txtTip->text().toStdString(), txtDurata->text().toDouble());
		reloadList(s.getAll());
	}
	catch (RepoActivEx & ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}

void ActivitateGUI::reloadList(vector<Activitate> act) {
	lst->clear();
	for (auto& a : act) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.getTitlu()), lst);
		item->setData(Qt::UserRole, QString::fromStdString(a.getDescriere()));
		


	}


}

void ActivitateGUI::find() {
	try {
		vector<Activitate> v;
		auto a = s.cautaActiv(txtTitlu->text().toStdString());
		v.push_back(a);
		reloadList(v);
	}
	catch (RepoActivEx & ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}

void ActivitateGUI::undo() {
	try {
		s.undo();
		reloadList(s.getAll());
	}
	catch (RepoActivEx & ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}


void ActivitateGUI::addList() {
	try {
		s.adaugaLista(txtTitlu->text().toStdString());
		reloadList(s.getAllList());
	}
	catch (RepoActivEx & ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}

void ActivitateGUI::addRandom(){
	try {
		s.addRandom(3);
		reloadList(s.getAllList());
	}
	catch (RepoActivEx & ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}

void ActivitateGUI::goleste() {
	try {
		s.golesteL();
		reloadList(s.getAllList());
	}
	catch (RepoActivEx & ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}

void ActivitateGUI::undoList() {
	try {
		s.undoLista();
		reloadList(s.getAllList());
	}
	catch (RepoActivEx & ex) {
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMesaj()));
	}
}