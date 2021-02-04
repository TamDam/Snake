#ifndef CUERPO_H
#define CUERPO_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QImage>

class cuerpo{
   // Q_OBJECT ??

public:
    typedef enum {derecha, izquierda, arriba, abajo} Direccion;
    Direccion direccion;
    static const int TAM=20;
    int posX, posY, xNueva, yNueva, crecer;
    QImage spriteSnake;
    QVector<QPoint> serpiente;
    Qt::Key teclaPulsada;

public:
    void pintarCuerpo(QPainter &);
    void mover(int nivel,int width,int height);
    void girar(int dseleccionada);

    cuerpo(int x, int y, Direccion dir, QImage imagen);
};

#endif // CUERPO_H
