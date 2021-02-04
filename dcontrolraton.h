#ifndef DCONTROLRATON_H
#define DCONTROLRATON_H

#include "cuerpo.h"

#include <QDialog>

namespace Ui {
class dcontrolraton;
}

class dcontrolraton : public QDialog{
    Q_OBJECT

public:
    explicit dcontrolraton(QWidget *parent = 0);
    ~dcontrolraton();

signals:
    void cambioDireccionRaton(cuerpo::Direccion);

public slots:
    void slotCambiaDirRaton();

private:
    Ui::dcontrolraton *ui;
};

#endif // DCONTROLRATON_H
