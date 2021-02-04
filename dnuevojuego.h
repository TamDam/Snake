#ifndef DNUEVOJUEGO_H
#define DNUEVOJUEGO_H

#include "ayuda.h"

#include <QDialog>
#include <QString>

namespace Ui {
class dnuevojuego;
}

class dnuevojuego : public QDialog{
    Q_OBJECT

public:
    QString skinElegido, nivelElegido;

    explicit dnuevojuego(QWidget *parent = 0);
    ~dnuevojuego();

public slots:
    void slotSkin(const QString skin);
    void slotNivel(const QString level);
    void slotAyuda();

public:
    Ui::dnuevojuego *ui;
};

#endif // DNUEVOJUEGO_H
