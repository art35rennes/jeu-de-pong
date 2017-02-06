#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H
#include <QtWidgets>
	class FenetrePrincipale : public QMainWindow {
		Q_OBJECT
		public:
			FenetrePrincipale();
			~FenetrePrincipale();
			QGroupBox * BuildGroupBoxControle();
	
		public slots:
	
		private:
			QWidget * widget_general;
			QMenu * menuFichier;
	};
#endif