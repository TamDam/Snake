#include "cuerpo.h"
#include <QDebug>

cuerpo::cuerpo(int x, int y, Direccion dir, QImage imagen){

    spriteSnake = imagen;
    spriteSnake = spriteSnake.scaledToWidth(TAM*5);

    direccion = dir;
    direccion = abajo;

    crecer = 0;

    for (int i=0; i<4 ;i++ ){
        serpiente.prepend(QPoint(x, y+TAM*i));
    }
}

// ********* METODOS *********
void cuerpo::pintarCuerpo(QPainter & pintor){
    QPoint cabeza = serpiente.at(0);
    if (direccion == derecha)
        pintor.drawImage(cabeza,spriteSnake,QRect(4*TAM,0*TAM,TAM,TAM));
    if (direccion == izquierda)
        pintor.drawImage(cabeza,spriteSnake,QRect(3*TAM,1*TAM,TAM,TAM));
    if (direccion == arriba)
        pintor.drawImage(cabeza,spriteSnake,QRect(3*TAM,0*TAM,TAM,TAM));
    if (direccion == abajo)
        pintor.drawImage(cabeza,spriteSnake,QRect(4*TAM,1*TAM,TAM,TAM));

    //cuerpo
    int tx = 0,ty = 0 ;
    for (int i= 1; i< serpiente.size() - 1 ; i++) {
        QPoint previo =serpiente.at(i-1);
        QPoint actual =serpiente.at(i);
        QPoint siguiente = serpiente.at(i+1);

        if (previo.x() < actual.x() && siguiente.x() > actual.x() ||
                siguiente.x() < actual.x() && previo.x() > actual.x()) {
            // Horizontal Izquierda-Derecha
            tx = 1; ty = 0;
        } else if (previo.x() < actual.x() && siguiente.y() > actual.y() ||
                   siguiente.x() < actual.x() && previo.y() > actual.y()) {
            // Angle Izquierda-Abajo
            tx = 2; ty = 0;
        } else if (previo.y() < actual.y() && siguiente.y() > actual.y() ||
                   siguiente.y() < actual.y() && previo.y() > actual.y()) {
            // Vertical Arriba-Abajo
            tx = 2; ty = 1;
        } else if (previo.y() < actual.y() && siguiente.x() < actual.x() ||
                   siguiente.y() < actual.y() && previo.x() < actual.x()) {
            // Angle Top-Izquierda
            tx = 2; ty = 2;
        } else if (previo.x() > actual.x() && siguiente.y() < actual.y() ||
                   siguiente.x() > actual.x() && previo.y() < actual.y()) {
            // Angle Derecha-Arriba
            tx = 0; ty = 1;
        } else if (previo.y() > actual.y() && siguiente.x() > actual.x() ||
                   siguiente.y() > actual.y() && previo.x() > actual.x()) {
            // Angle Abajo-Derecha
            tx = 0; ty = 0;
        }
        pintor.drawImage(actual,spriteSnake,QRect(tx*TAM,ty*TAM,TAM,TAM));
    }

    //cola
    QPoint ultimo = serpiente.last();
    QPoint penultimo = serpiente.at(serpiente.length()-2);
    if (penultimo.y() < ultimo.y()) {
        // Arriba
        tx = 3; ty = 2;
    } else if (penultimo.x() > ultimo.x()) {
        // Derecha
        tx = 4; ty = 2;
    } else if (penultimo.y() > ultimo.y()) {
        // Abajo
        tx = 4; ty = 3;
    } else if (penultimo.x() < ultimo.x()) {
        // Izquierda
        tx = 3; ty = 3;
    }

    pintor.drawImage(ultimo,spriteSnake,QRect(tx*TAM,ty*TAM,TAM,TAM));
}

void cuerpo::mover(int nivel, int width,int height){

    xNueva = serpiente.first().x();
    yNueva = serpiente.first().y();

    if(direccion == derecha)
        xNueva = xNueva + TAM;
    if(direccion == izquierda)
        xNueva = xNueva - TAM;
    if(direccion == arriba)
        yNueva = yNueva - TAM;
    if(direccion == abajo)
        yNueva = yNueva + TAM;

    if(nivel<3){
        if(xNueva < 0)
            xNueva = (width/TAM) *TAM -TAM;
        if(xNueva > width-1)
            xNueva = 0;
        if(yNueva < 0)
            yNueva = (height/TAM) *TAM -TAM;
        if(yNueva > height-1)
            yNueva = 0;
    }

    QPoint p(xNueva,yNueva);
    serpiente.prepend(p);//prepend añade cabeza

    if(crecer>0) {
        crecer--;
    }else{
        serpiente.pop_back();//pop_back elimina el ultimo
    }
}

void cuerpo::girar(int dseleccion){

    switch (dseleccion) {
    case 0:
        direccion = derecha;
        break;
    case 1:
        direccion = izquierda;
        break;
    case 2:
        direccion = arriba;
        break;
    case 3:
        direccion = abajo;
        break;

    default:
        break;
    }
}
