#ifndef PUNTUACION_H
#define PUNTUACION_H

#include <QDialog>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

namespace Ui {
class puntuacion;
}

class puntuacion : public QDialog{
    Q_OBJECT

public:
    explicit puntuacion(QWidget *parent = 0);
    ~puntuacion();

public slots:
    void slotBorrar();

public:
    Ui::puntuacion *ui;
};

class ModeloPuntuaciones : public QAbstractTableModel{

public:

    QVector<QString> puntuaciones;
    ModeloPuntuaciones (QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const;

    void actualizaPuntuaciones();

};

#endif // PUNTUACION_H
