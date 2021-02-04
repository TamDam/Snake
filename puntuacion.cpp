#include "puntuacion.h"
#include "ui_puntuacion.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <algorithm>

puntuacion::puntuacion(QWidget *parent) :
    QDialog(parent), ui(new Ui::puntuacion){
    ui->setupUi(this);

    connect(ui->btn_borrar,SIGNAL(clicked()),
            this,SLOT(slotBorrar()));
    ModeloPuntuaciones * modelo = new ModeloPuntuaciones;
    ui->vistaPuntuaciones->setModel(modelo);
}

ModeloPuntuaciones::ModeloPuntuaciones(QObject * parent){

    QFile fichero ("./puntuaciones");
    if (!fichero.open(QIODevice::ReadOnly)){
        QMessageBox::warning(nullptr, tr("Editor"),
                             tr("No puedes abrir el fichero %1:\n%2.")
                             .arg(fichero.fileName())
                             .arg(fichero.errorString()),
                             QMessageBox::Cancel,QMessageBox::Cancel);
        return;
    }
    QTextStream stream(&fichero);
    while (!stream.atEnd()) {
       puntuaciones.append(stream.readLine());
    }
}

int ModeloPuntuaciones::rowCount( const QModelIndex & parent ) const{
    return puntuaciones.size();
}

int ModeloPuntuaciones::columnCount( const QModelIndex & parent ) const{
    return 2;
}

QVariant ModeloPuntuaciones::headerData( int section, Qt::Orientation orientacion, int role) const{

  if  ( (orientacion == Qt::Horizontal) && (section == 0) && role == Qt::DisplayRole)
    return QVariant(QString("Nombre"));


  if  ( (orientacion == Qt::Horizontal) && (section == 1) && role == Qt::DisplayRole )
    return QVariant(QString("Puntuación"));

  if ( role == Qt::DisplayRole )
      return QVariant(QString::number(section));
  return QVariant();


}

QVariant ModeloPuntuaciones::data( const QModelIndex & index, int role ) const{

    if(role != Qt::DisplayRole)
        return QVariant();

    int linea = index.row();
    int num_palabra = index.column();

    return QVariant (puntuaciones.at(linea).split(" ").at(num_palabra));
}

//********** METODOS **********
void ModeloPuntuaciones::actualizaPuntuaciones(){
    QModelIndex topLeft = index(0,0);
    QModelIndex bottomRight = index(puntuaciones.size(), 2);

    beginResetModel();
    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);

    QFile fichero("./puntuaciones");
    fichero.Truncate;
    fichero.open(QIODevice::WriteOnly);

    QTextStream stream(&fichero);
    for (int i = 0; i < puntuaciones.size(); i++) {
        stream << puntuaciones.at(i) <<endl;
    }
    fichero.close();
}

//********** SLOTS **********
void puntuacion::slotBorrar(){

    QModelIndexList seleccionado;
    seleccionado = ui->vistaPuntuaciones->selectionModel()->selectedRows();

    std::sort(seleccionado.begin(),seleccionado.end());

    ModeloPuntuaciones * modelo;

    modelo = dynamic_cast<ModeloPuntuaciones *>
            (ui->vistaPuntuaciones->model());

    for( int i= seleccionado.count()-1; i>=0; i--){
        modelo->puntuaciones.remove(seleccionado.at(i).row());
        modelo->actualizaPuntuaciones();
        ui->vistaPuntuaciones->clearSelection();
    }
}
puntuacion::~puntuacion(){
    delete ui;
}
