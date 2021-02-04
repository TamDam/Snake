#include "inicio.h"
#include "ui_inicio.h"

inicio::inicio(QWidget *parent) :
    QDialog(parent), ui(new Ui::inicio){
    ui->setupUi(this);

    connect(ui->btn_nuevo, SIGNAL(clicked()),
            this,SLOT(slotNuevo()));

    connect(ui->btn_cargar, SIGNAL(clicked()),
            this, SLOT(slotCargar()));

    connect(ui->btn_salir, SIGNAL(clicked()),
            this, SLOT(slotSalir()));

}

// ********* SLOTS *********
void inicio::slotNuevo(){
    botonPulsado = "Nueva";
    this->close();
}

void inicio::slotCargar(){
    botonPulsado = "Cargar";
    this->close();
}

void inicio::slotSalir(){
    botonPulsado = "Salir";
    this->close();
}

inicio::~inicio(){
    delete ui;
}
