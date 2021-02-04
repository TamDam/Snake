#include "dnuevojuego.h"
#include "ui_dnuevojuego.h"

#include "QDebug"
dnuevojuego::dnuevojuego(QWidget *parent) :
    QDialog(parent), ui(new Ui::dnuevojuego){
    ui->setupUi(this);

    connect(ui->btn_ayuda, SIGNAL(clicked()),
            this, SLOT(slotAyuda()));
    connect(ui->cb_skin, SIGNAL(currentIndexChanged(const QString)),
            this,SLOT(slotSkin(const QString)));
    connect(ui->cb_nivel, SIGNAL(currentIndexChanged(const QString)),
            this, SLOT(slotNivel(const QString)));
}

// ********* SLOTS *********
void dnuevojuego::slotAyuda(){
    ayuda * widgetayuda = new ayuda();
    widgetayuda->show();
}

void dnuevojuego::slotSkin(const QString color){

    if(color == "Serpiente Verde")
        skinElegido ="Verde";

    if(color == "Serpiente Lila")
        skinElegido ="Lila";

    if(color == "Serpiente Azul")
        skinElegido ="Azul";

    if(color == "Serpiente Negra")
        skinElegido ="Negra";
}

void dnuevojuego::slotNivel(const QString nivel){

    if(nivel == "Fácil")
        nivelElegido ="Facil";

    if(nivel == "Normal")
        nivelElegido ="Normal";

    if(nivel == "Difícil")
        nivelElegido ="Dificil";

    if(nivel == "Experto")
        nivelElegido ="Experto";
}

dnuevojuego::~dnuevojuego(){
    delete ui;
}
