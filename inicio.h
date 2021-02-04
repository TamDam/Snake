#ifndef INICIO_H
#define INICIO_H

#include <QDialog>

namespace Ui {
class inicio;
}

class inicio : public QDialog{
    Q_OBJECT

public:
    QString botonPulsado;

public:
    explicit inicio(QWidget *parent = 0);
    ~inicio();

public slots:
    void slotNuevo();
    void slotCargar();
    void slotSalir();

private:
    Ui::inicio *ui;
};

#endif // INICIO_H
