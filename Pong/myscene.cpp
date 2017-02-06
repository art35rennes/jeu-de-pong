#include "myscene.h"

void MyScene::initVar(){
    sensX = VITESSEX;
    sensY = VITESSEY;

    vitesseRaquette = 1;

    randYR = rand()%120;
    randYT = 120 + rand()%480;

    posYR1 = 100;
    posYR2 = 200;

    scoreJ1 = 0;
    scoreJ2 = 0;

    keyUp1 = false;
    keyUp2 = false;
    keyDown1 = false;
    keyDown2 = false;
    keyIA = false;
}

void MyScene::keyPressEvent(QKeyEvent * event){
    //qDebug() << "Touche pres" << event->key();
    switch (event->key()){
        case Qt::Key_A:
            keyUp1 = true;
            break;
        case Qt::Key_Q:
            keyDown1 = true;
            break;
        case Qt::Key_P:
            if(!keyIA)
                keyUp2 = true;
            break;
        case Qt::Key_M:
            if(!keyIA)
                keyDown2 = true;
            break;
        case Qt::Key_I:
            if(keyIA){
                keyIA = false;
                tIA->setVisible(false);
            }
            else{
                keyIA = true;
                tIA->setVisible(true);
                keyDown2 = false;
                keyUp2 = false;
            }
            break;
        case Qt::Key_Space:
            if(timer->isActive()){
                timer->stop();
                tPause->setVisible(true);
            }
            else{
                timer->start();
                tPause->setVisible(false);
            }
        break;
    }
}

void MyScene::keyReleaseEvent(QKeyEvent * event){
    //qDebug() << "Touche release" << event->key();
    switch (event->key()){
        case Qt::Key_A:
            keyUp1 = false;
            break;
        case Qt::Key_Q:
            keyDown1 = false;
            break;
        case Qt::Key_P:
            keyUp2 = false;
            break;
        case Qt::Key_M:
            keyDown2 = false;
            break;
    }
}

void MyScene::CheckBord(){

    //gestion rebont bord et score
    if(imgBalle->x()+sensX > 866){
        sensX = -VITESSEX;
        scoreJ1++;
        if(sensY > 0){
            sensY = VITESSEY;
        }
        else{
            sensY = -VITESSEY;
        }
    }
    if(imgBalle->x()+sensX < 5){
        sensX = VITESSEX;
        scoreJ2++;
        if(sensY > 0){
            sensY = VITESSEY;
        }
        else{
            sensY = -VITESSEY;
        }
    }

    if(imgBalle->y()+sensY > 566)
        sensY = -VITESSEY;
    if(imgBalle->y()+sensY < 10)
        sensY = VITESSEY;

    //rebond raquette
    if(imgBalle->collidesWithItem(raquette1) && sensX < 0){
        sensX *= -1.12;
        if(keyIA){
            randYR = rand()%120;
            randYT = 10 + rand()%480;
        }
        sensY = (posYR1+60)-(imgBalle->y()+16);
        if(imgBalle->y() < posYR2+60)
            sensY *= -1.12;
    }

    if(imgBalle->collidesWithItem(raquette2) && sensX > 0){
        sensX *= -1.12;
        if(keyIA){
            randYR = rand()%120;
            randYT = 10 + rand()%480;
        }
        sensY = ((( posYR2 - (imgBalle->y()+17) ) / 120));
        if(imgBalle->y() < posYR2+60)
            sensY *= -1.12;
    }
}

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent){

    initVar();

    //rectangle
    QGraphicsRectItem * qgri = new QGraphicsRectItem(10, 10, 900, 600);
    qgri->setBrush(QBrush(Qt::black));
    this->addItem(qgri) ;

    //ligne mediane
    this->ligneMid = new QGraphicsRectItem(0, 0, 6, 600);
    ligneMid->setPos(447, 10);
    ligneMid->setBrush(QBrush(Qt::yellow));
    this->addItem(ligneMid) ;

    //raquette1
    this->raquette1 = new QGraphicsRectItem(0, 0, 15, 120);
    raquette1->setPos(40, posYR1);
    raquette1->setBrush(QBrush(Qt::yellow));
    this->addItem(raquette1) ;
    //raquette2
    this->raquette2 = new QGraphicsRectItem(0, 0, 15, 120);
    raquette2->setPos(855, posYR2);
    raquette2->setBrush(QBrush(Qt::yellow));
    this->addItem(raquette2) ;

    //objet imgBalle
    this->imgBalle = new QGraphicsPixmapItem(QPixmap("/home/arthur/Cpp/Pong/Pong/dico.png"));
    imgBalle->setPos(160, 250);
    imgBalle->setScale(0.1);
    imgBalle->setRotation(0);
    this->addItem(imgBalle);

    //texte pause
    this->tPause  = new QGraphicsTextItem( "PAUSE");
    tPause->setPos(170, 125);
    tPause->setScale(10);
    this->addItem(this->tPause);
    tPause->setVisible(false);

    //texte IA
    this->tIA  = new QGraphicsTextItem( "IA");
    tIA->setPos(800, 500);
    tIA->setScale(5);
    this->addItem(this->tIA);
    tIA->setVisible(false);

    /*
    //debug
    this->rectDebug = new QGraphicsRectItem(0, 0, 5, 5);
    rectDebug->setPos(imgBalle->x(), imgBalle->y());
    rectDebug->setBrush(QBrush(Qt::blue));
    this->addItem(rectDebug) ;
    */

    //objet texte
    this->score  = new QGraphicsTextItem(QString::number(scoreJ1)+":"+QString::number(scoreJ2));
    score->setPos(310, 5);
    score->setScale(10);
    this->addItem(this->score);

    //timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    qDebug() << "coucou";
}

void MyScene::update(){

    CheckBord();
    //deplacement balle
    imgBalle->setX(imgBalle->x()+sensX);
    imgBalle->setY(imgBalle->y()+sensY);

    /*
    //deplacement rectangle debug
    rectDebug->setX(imgBalle->x());
    rectDebug->setY(imgBalle->y());
    */

    score->setPlainText(QString::number(scoreJ1)+" "+QString::number(scoreJ2));
    if(scoreJ1 > 9)
        score->setPos(225, 5);

    //deplacement raquette
    if(keyUp1)
        if(posYR1 - vitesseRaquette > 10){
            //for(int i; i < absolue(sensX);i++)
            raquette1->setPos(40, posYR1 -=vitesseRaquette);
        }
    if(keyDown1)
        if(posYR1 + vitesseRaquette < 490){
            raquette1->setPos(40, posYR1 +=vitesseRaquette);
        }

    if(keyUp2)
        if(posYR2 - vitesseRaquette > 10){
            raquette2->setPos(855, posYR2 -=vitesseRaquette);
        }
    if(keyDown2)
        if(posYR2 + vitesseRaquette < 490){
            raquette2->setPos(855, posYR2 +=vitesseRaquette);
        }

    //deplacement raquette IA
    if(keyIA && sensX > 0){
        if(imgBalle->y() > posYR2+randYR && posYR2+120+vitesseRaquette < 600)
            raquette2->setPos(855, posYR2+=vitesseRaquette);
        else{
            if(imgBalle->y() < posYR2+randYR && posYR2-vitesseRaquette > 10)
                raquette2->setPos(855, posYR2-=vitesseRaquette);
        }
    }
    else{
        if(keyIA && sensX < 0 && (posYR2+randYR <= randYT-3 || posYR2+randYR >= randYT+3)){
            if(posYR2+randYR >= randYT)
                raquette2->setPos(855, posYR2-=vitesseRaquette);
            else
                raquette2->setPos(855, posYR2+=vitesseRaquette);
        }
    }

}
