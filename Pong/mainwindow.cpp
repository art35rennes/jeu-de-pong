#include "mainwindow.h"
#include "myscene.h"



FenetrePrincipale::FenetrePrincipale() : QMainWindow() {

    // le widget dans lequel tout s'affiche
    widget_general = new QWidget;
    QHBoxLayout * qbl_general = new QHBoxLayout;
    widget_general->setLayout(qbl_general);
    this->setCentralWidget(widget_general);

    //exemple de creation d'une zone ou mettre boutons...
    qbl_general->addWidget(BuildGroupBoxControle());

    // exemple de création d'un menu
    menuFichier = menuBar()->addMenu(tr("&Fichier"));

    QGraphicsView * myview;
    myscene = new MyScene(this);
    myview = new QGraphicsView(myscene, this);
    //myview->setBackgroundBrush(Qt::blue);
    qbl_general->addWidget(myview);
}
FenetrePrincipale::~FenetrePrincipale() {
}

QGroupBox * FenetrePrincipale::BuildGroupBoxControle() {
    QGroupBox * qgb = new QGroupBox(tr("Contrôle"));
    return qgb;
}
