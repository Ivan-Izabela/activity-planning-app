//#include "lab10_11.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qlist.h>
#include <fstream>

#include "repo.h"
#include "service.h"
#include "ui.h"
#include "activGUI.h"

#include <string>
#include <list>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
   // lab10_11 w;
   // w.show();

    testRepo();
    testService();
    testValid();
    //std::ofstream out("activ.txt", std::ios::trunc);
    //out.close();
    RepoActivFile rep{ "activ.txt" };
    ValidatorActiv v;
    ServiceActiv srv{rep,v};
    //UI u{ srv };
   // u.run();

    QApplication a(argc, argv);
    ActivitateGUI gui{ srv };
    ActivitateGUI gui1{ srv };
    gui.show();
    gui1.show();



    return a.exec();
    
}
