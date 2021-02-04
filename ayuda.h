#ifndef AYUDA_H
#define AYUDA_H

#include <QDialog>

namespace Ui {
class ayuda;
}

class ayuda : public QDialog{
    Q_OBJECT

public:
    explicit ayuda(QWidget *parent = 0);
    ~ayuda();

private:
    Ui::ayuda *ui;
};

#endif // AYUDA_H
