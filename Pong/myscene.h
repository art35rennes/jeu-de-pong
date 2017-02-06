#ifndef MYSCENE_H
#define MYSCENE_H

#include <QPainter>
#include <QtWidgets>
#include <QString>
#include <QKeyEvent>
#include <time.h>

#define VITESSEX 2;
#define VITESSEY 1;;

#define TAILLEX 700;
#define TAILLEY 400;

int RandCoordY();

class MyScene : public QGraphicsScene {
        Q_OBJECT
    public :
        void initVar();
        MyScene(QObject *parent = 0);
        void CheckBord();

    public slots:
        void update();
    protected:
        void keyPressEvent(QKeyEvent * event);
        void keyReleaseEvent(QKeyEvent * event);

    private:
        QTimer *timer;
        QGraphicsPixmapItem *imgBalle;
        QGraphicsTextItem* score;
        QGraphicsTextItem* tPause;
        QGraphicsTextItem* tIA;
        QGraphicsRectItem* rectDebug;
        QGraphicsRectItem* raquette1;
        QGraphicsRectItem* raquette2;
        QGraphicsRectItem* ligneMid;

        QString* tScore;

        int randYR, randYT;

        int angle;
        float sensX, sensY;
        int posYR1, posYR2;
        int scoreJ1, scoreJ2;

        int vitesseRaquette;

        bool keyUp1;
        bool keyUp2;
        bool keyDown1;
        bool keyDown2;
        bool keyIA;
};


#endif
