#ifndef FRUTA_H
#define FRUTA_H

#include <QImage>

class frutaPosible{

public:
    frutaPosible(QImage, int);
    frutaPosible();

    QImage imagen;
    int alimento;
};

//***********************

class frutaEnJuego{
public:
    frutaPosible miFruta;
    int posFX, posFY;

    frutaEnJuego();
};

#endif // FRUTA_H
