#include "fenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale() : QMainWindow() {
	// le widget dans lequel tout s'affiche
	widget_general = new QWidget;
	QHBoxLayout * qbl_general = new QHBoxLayout;
	widget_general->setLayout(qbl_general);
	this->setCentralWidget(widget_general);
	//exemple de creation d'une zone ou mettre boutons...
	qbl_general->addWidget(BuildGroupBoxControle());
}
// exemple de création d'un menu
menuFichier = menuBar()->addMenu(tr("&Fichier"));
FenetrePrincipale::~FenetrePrincipale() {
}
QGroupBox * FenetrePrincipale::BuildGroupBoxControle() {
	QGroupBox * qgb = new QGroupBox(tr("Contrôle"));
	return qgb;
}