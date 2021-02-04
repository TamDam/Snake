#include "dcontrolraton.h"
#include "ui_dcontrolraton.h"

dcontrolraton::dcontrolraton(QWidget *parent) :
    QDialog(parent), ui(new Ui::dcontrolraton){
    ui->setupUi(this);

    connect(ui->btn_arriba, SIGNAL(clicked()),
            this, SLOT(slotCambiaDirRaton()));
    connect(ui->btn_abajo, SIGNAL(clicked()),
            this, SLOT(slotCambiaDirRaton()));
    connect(ui->btn_derecha, SIGNAL(clicked()),
            this, SLOT(slotCambiaDirRaton()));
    connect(ui->btn_izquierda, SIGNAL(clicked()),
            this, SLOT(slotCambiaDirRaton()));
}
//********** SLOTS **********
void dcontrolraton::slotCambiaDirRaton(){
    QToolButton * nDireccion = qobject_cast<QToolButton*>(QObject::sender());

    if(nDireccion->objectName()=="btn_izquierda")
        emit cambioDireccionRaton(cuerpo::izquierda);

    if(nDireccion->objectName()=="btn_derecha")
        emit cambioDireccionRaton(cuerpo::derecha);

    if(nDireccion->objectName()=="btn_arriba")
        emit cambioDireccionRaton(cuerpo::arriba);

    if(nDireccion->objectName()=="btn_abajo")
        emit cambioDireccionRaton(cuerpo::abajo);
}

dcontrolraton::~dcontrolraton(){
    delete ui;
}
