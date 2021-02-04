#include "ayuda.h"
#include "ui_ayuda.h"

ayuda::ayuda(QWidget *parent) :
    QDialog(parent), ui(new Ui::ayuda){
    ui->setupUi(this);
}

ayuda::~ayuda(){
    delete ui;
}
