#include "mainwindow.h"

#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QBuffer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    cerrar = false;
    puntos=0;

    resize(450,450);
    crearAccion();
    crearMenu();
    inicializaComidas();
    iniciarJuego();

    temporizador = new QTimer(this);
    temporizador->setSingleShot(false);

    connect(temporizador,SIGNAL(timeout()),
        this, SLOT(slotTemporizador()));

    tiempoFruta = rand() % 25 + 50;
    temporizador->setInterval(1000/nivel);
    temporizador->start();
}

//********* METODOS *********
void MainWindow::crearMenu(){
    menu = new QMenu(QString("Menu"));
    menu->addAction(accionMover);
    menu->addAction(accionNueva);
    menuBar()->addMenu(menu);
    //********** MENU 2 **********
    menuPartida = new QMenu(QString("Menu de Partida"));
    menuPartida->addAction(accionPuntuacion);
    menuPartida->addAction(accionGuardar);
    menuPartida->addAction(accionCargar);

    menuBar()->addMenu(menuPartida);
}

void MainWindow::crearAccion(){
    accionMover = new QAction(QString("Control con Ratón"));

    accionNueva = new QAction(QString("Nueva Partida"));
    accionNueva->setShortcut(QKeySequence::New);

    accionGuardar = new QAction(QString("Guardar Partida"));
    accionGuardar->setShortcut(QKeySequence::Save);

    accionCargar = new QAction(QString("Cargar Partida"));
    accionCargar->setShortcut(QKeySequence::Replace);

    accionPuntuacion = new QAction(QString("Ver Puntuaciones"));
    accionPuntuacion->setShortcut(QKeySequence::Find);

    connect(accionMover, SIGNAL(triggered()),
            this, SLOT(slotMostrarControlRaton()));

    connect(accionNueva, SIGNAL(triggered()),
            this, SLOT(slotNueva()));

    connect(accionGuardar, SIGNAL(triggered()),
            this, SLOT(slotGuardarPartida()));

    connect(accionCargar, SIGNAL(triggered()),
            this, SLOT(slotCargarPartida()));

    connect(accionPuntuacion, SIGNAL(triggered()),
            this, SLOT(slotMostrarPuntuaciones()));
}

void MainWindow::iniciarJuego(){
    inicio ini;
    ini.exec();

    if(ini.botonPulsado == "Nueva"){
        nuevoJuego();
    } else if(ini.botonPulsado == "Cargar"){
        slotCargarPartida();

    } else if (ini.botonPulsado == "Salir"){
        cerrar = true;
    }
}

void MainWindow::nuevoJuego(){
    dnuevojuego nuevo;
    nuevo.exec();

    nombre = nuevo.ui->nick->text();

    if(nuevo.skinElegido == "Verde"){
        spriteSnake = QImage("./imagenes/cuerpo/snake_verde.png");
    } else if(nuevo.skinElegido == "Lila"){
        spriteSnake = QImage("./imagenes/cuerpo/snake_lila.png");
    }else if(nuevo.skinElegido == "Azul"){
        spriteSnake = QImage("./imagenes/cuerpo/snake_azul.png");
    }else if(nuevo.skinElegido == "Negra"){
        spriteSnake = QImage("./imagenes/cuerpo/snake_negra.png");
    }

    if(nuevo.nivelElegido == "Facil"){
        nivel = 1;
    } else if(nuevo.nivelElegido == "Normal"){
        nivel = 2;
    }else if(nuevo.nivelElegido == "Dificil"){
        nivel = 3;
    }else if(nuevo.nivelElegido == "Experto"){
        nivel = 4;
    }

    jugador = new cuerpo(40,40,cuerpo::abajo,spriteSnake);
}

void MainWindow::inicializaComidas(){

    QStringList ficheroComidas;
    ficheroComidas <<"cerezas.png" << "fresa.png"
                  << "kiwi.png" << "melocoton.png";
    int alComida=0;
    for (int i = 0; i < ficheroComidas.length(); i++) {
        QString ruta = "./imagenes/fruta/";
        ruta = ruta + ficheroComidas.at(i);

        QImage imagen = QImage(ruta);
        imagen = imagen.scaled(cuerpo::TAM,cuerpo::TAM);
        alComida++;
        posiblesFrutas.append(new frutaPosible(imagen,alComida));
        if (posiblesFrutas.last()->imagen.isNull())
            qDebug() << "Algún error con la imagen";
    }

    frutaEnJuego primeraFruta;
    primeraFruta.miFruta = *(posiblesFrutas.at(0));
    primeraFruta.posFX = ((width() / 2)/jugador->TAM) *jugador->TAM;
    primeraFruta.posFY = ((height() / 2)/jugador->TAM) *jugador->TAM ;
    frutasEnJuego.append(primeraFruta);
}

void MainWindow::guardarPuntuacion(QString nombre, int punt){

    QFile fichero("./puntuaciones");
    fichero.open(QIODevice::Append);

    QTextStream stream(&fichero);
    stream << nombre <<" "<< QString::number(punt)<<endl;

    fichero.close();
}

void MainWindow::paintEvent(QPaintEvent * event){
    if(cerrar){
        return;
    }

    QPainter pintor(this);
    jugador->pintarCuerpo(pintor);

    for (int i=0 ; i<frutasEnJuego.size(); i++){
        frutaEnJuego unaFruta = frutasEnJuego[i];
        pintor.drawImage(QRect(unaFruta.posFX-3, unaFruta.posFY-3,
                               jugador->TAM+4,jugador->TAM+4),
                         unaFruta.miFruta.imagen);
    }
}

void MainWindow::keyPressEvent(QKeyEvent * event){
    cuerpo::Direccion dirsel = jugador->direccion;

    switch (event->key()) {
    case Qt::Key_Right:
        if( jugador->direccion != jugador->izquierda)
            dirsel = cuerpo::derecha;
        break;
    case Qt::Key_Left:
        if( jugador->direccion != jugador->derecha)
            dirsel = cuerpo::izquierda;
        break;
    case Qt::Key_Up:
        if( jugador->direccion != jugador->abajo)
            dirsel = cuerpo::arriba;
        break;
    case Qt::Key_Down:
        if( jugador->direccion != jugador->arriba)
            dirsel = cuerpo::abajo;
        break;
    default:
        break;
    }
    jugador->girar(dirsel);
}

//********* SLOTS *********
void MainWindow::slotTemporizador(){
    if(cerrar){
        this->close();
        QApplication::exit(0);
        return;
    }
    for (int i=0 ; i<frutasEnJuego.size(); i++){
        frutaEnJuego unaFruta = frutasEnJuego[i];
        if((jugador->serpiente.at(0).x()==unaFruta.posFX)&&(jugador->serpiente.at(0).y()==unaFruta.posFY)){

            jugador->crecer=unaFruta.miFruta.alimento;
            puntos++;

            frutaEnJuego nueva;
            nueva.posFX=((rand() % width()) /jugador->TAM) *jugador->TAM;
            nueva.posFY=((rand() % height()) /jugador->TAM) *jugador->TAM;
            int nuevoIndice = rand() % posiblesFrutas.size();
            nueva.miFruta=*(posiblesFrutas.at(nuevoIndice));
            frutasEnJuego.remove(i);
            frutasEnJuego.append(nueva);
            break;
        }
    }

    jugador->mover(nivel,this->width(),this->height());

    for(int i=1;i<jugador->serpiente.size();i++){
        if(jugador->serpiente[i]==(QPoint(jugador->xNueva, jugador->yNueva))){
            temporizador->stop();
            guardarPuntuacion(nombre, puntos);
            puntuacion dialogoPuntuaciones;
            dialogoPuntuaciones.exec();
        }
    }
    if(nivel==4){
        if(tiempoFruta==0){
            tiempoFruta = rand() % 25 + 50;
            puntos--;
            if(puntos<0) puntos=0;
            for (int i=0 ; i<frutasEnJuego.size(); i++){
                frutaEnJuego nueva;
                nueva.posFX=((rand() % width()) /jugador->TAM) *jugador->TAM;
                nueva.posFY=((rand() % height()) /jugador->TAM) *jugador->TAM;
                int nuevoIndice = rand() % posiblesFrutas.size();
                nueva.miFruta=*(posiblesFrutas.at(nuevoIndice));
                frutasEnJuego.remove(i);
                frutasEnJuego.append(nueva);
            }
        }else{
            tiempoFruta--;
        }
    }

    if(nivel>2){
        if((jugador->serpiente.at(0).x() == 0)||
                (abs(jugador->serpiente.at(0).x() - this->width()) <= cuerpo::TAM) ||
                (jugador->serpiente.at(0).y() == 0)||
                (abs(jugador->serpiente.at(0).y() - this->height()) <= cuerpo::TAM)){
            temporizador->stop();
            guardarPuntuacion(nombre, puntos);
            puntuacion dialogoPuntuaciones;
            dialogoPuntuaciones.exec();
        }
    }

    this->update();
}

void MainWindow::slotMostrarControlRaton(){
    dcontrolraton * dcontrol = new dcontrolraton();
    dcontrol->show();

    connect(dcontrol, SIGNAL(cambioDireccionRaton(cuerpo::Direccion)),
            this, SLOT(slotCambioDireccionRaton(cuerpo::Direccion)));
}

void MainWindow::slotCambioDireccionRaton(cuerpo::Direccion dir){
    jugador->girar(dir);
}

void MainWindow::slotMostrarPuntuaciones(){
    temporizador->stop();
    puntuacion dialogoPuntuaciones;
    dialogoPuntuaciones.exec();
    temporizador->start();
}

void MainWindow::slotGuardarPartida(){

    QJsonObject jsonPrincipal;
    QJsonArray jsonFrutas, jsonSerpiente;
    QJsonObject posicionComida, puntuacion,nombreJugador, colorSerpiente,
            direccionSerpiente, nivelPartida;

    //Frutas
    for (int i = 0; i < frutasEnJuego.size(); ++i) {
       QJsonObject jsonUnaFruta;
       jsonUnaFruta["alimento"] = frutasEnJuego.at(i).miFruta.alimento;

       QImage img = frutasEnJuego.at(i).miFruta.imagen;
       QByteArray byteArray;
       QBuffer buffer(&byteArray);
       img.save(&buffer, "PNG");
       QString imgBase64 = QString::fromLatin1(byteArray.toBase64().data());

       jsonUnaFruta["image"] = imgBase64;
       jsonUnaFruta["x"] =  frutasEnJuego.at(i).posFX;
       jsonUnaFruta["y"] =  frutasEnJuego.at(i).posFY;
       jsonFrutas.append(jsonUnaFruta);
    }

    puntuacion["puntuacion"] = puntos;
    nombreJugador["nombreJugador"] = nombre;
    nivelPartida["nivel"] = nivel;

    QImage imagenSerpiente = spriteSnake;
    QByteArray byteSerpiente;
    QBuffer bufferSerpiente(&byteSerpiente);
    imagenSerpiente.save(&bufferSerpiente, "PNG");
    QString imgBaseSerpiente = QString::fromLatin1(byteSerpiente.toBase64().data());
    colorSerpiente["color"] = imgBaseSerpiente;

    for (int i = 0; i < jugador->serpiente.size(); i++) {
        QJsonObject posicion;
        posicion["x"] = jugador->serpiente.at(i).x();
        posicion["y"] = jugador->serpiente.at(i).y();
        jsonSerpiente.append(posicion);
    }
    direccionSerpiente["direccion"] = (int) jugador->direccion;

    //añadir al principal
    if(frutasEnJuego.size()>0) jsonPrincipal["frutas"] = jsonFrutas;

    jsonPrincipal["posicionComida"] = posicionComida;
    jsonPrincipal["puntuacion"] = puntuacion;
    jsonPrincipal["nombreJugador"] = nombreJugador;
    jsonPrincipal["color"] = colorSerpiente;
    jsonPrincipal["serpiente"] = jsonSerpiente;
    jsonPrincipal["direccion"] = direccionSerpiente;
    jsonPrincipal["nivel"] = nivelPartida;
    jsonPrincipal["crecer"]= jugador->crecer;

    //Guardar
    QFile saveFile(QStringLiteral("./save.json"));
    saveFile.open(QIODevice::WriteOnly);
    QJsonDocument saveDoc(jsonPrincipal);
    saveFile.write(saveDoc.toJson());

    saveFile.close();
}

void MainWindow::slotCargarPartida(){

    QFile loadFile(QStringLiteral("./save.json"));
    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("No puedes abrirlo para lectura");
        return;
    }

    QByteArray savedData = loadFile.readAll();
    QJsonDocument readDoc(QJsonDocument::fromJson(savedData));
    QJsonObject jsonPrincipal = readDoc.object();

    if(jsonPrincipal.contains("frutas") && jsonPrincipal["frutas"].isArray()){

        frutasEnJuego.clear();

        QJsonArray arrayFrutas = jsonPrincipal["frutas"].toArray();

        for (int i = 0; i < arrayFrutas.size(); i++) {
            frutaEnJuego nuevaFruta;
            frutaPosible nuevaFrutaPosible ;
            QJsonObject objetoFruta = arrayFrutas[i].toObject();

            QString imgBase64 = objetoFruta["image"].toString();
            QByteArray byteArray = imgBase64.toLatin1();
            byteArray = QByteArray::fromBase64(byteArray, QByteArray::Base64Encoding);
            QBuffer buffer(&byteArray);
            QImage imagen;
            imagen.loadFromData(byteArray,"PNG");

            int cuadraditos = objetoFruta["alimento"].toInt();

            nuevaFrutaPosible.imagen = imagen;
            nuevaFrutaPosible.alimento = cuadraditos;
            nuevaFruta.miFruta = nuevaFrutaPosible;
            int x = objetoFruta["x"].toInt();
            int y = objetoFruta["y"].toInt();

            nuevaFruta.posFX = x ;
            nuevaFruta.posFY = y;

            frutasEnJuego.append(nuevaFruta);
        }
    }

    if(jsonPrincipal.contains("puntuacion")){
        QJsonObject puntuacionG = jsonPrincipal["puntuacion"].toObject();
        puntos = puntuacionG["puntuacion"].toInt();
    }

    if(jsonPrincipal.contains("nombreJugador")){
        QJsonObject nombreJugador = jsonPrincipal["nombreJugador"].toObject();
        nombre = nombreJugador["nombreJugador"].toString();
    }

    if(jsonPrincipal.contains("color")){
        QJsonObject colorSer = jsonPrincipal["color"].toObject();
        QString imgBaseSerpiente = colorSer["color"].toString();
        QByteArray byteSerpiente = imgBaseSerpiente.toLatin1();
        byteSerpiente = QByteArray::fromBase64(byteSerpiente, QByteArray::Base64Encoding);
        QBuffer bufferSerpiente(&byteSerpiente);
        QImage imagen;
        imagen.loadFromData(byteSerpiente,"PNG");
        spriteSnake = imagen;
    }

    jugador = new cuerpo(40,40,cuerpo::abajo,spriteSnake);
    jugador->serpiente.clear();

    if(jsonPrincipal.contains("serpiente") && jsonPrincipal["serpiente"].isArray()){
        QJsonArray arraySerpiente = jsonPrincipal["serpiente"].toArray();
        for (int i = 0; i < arraySerpiente.size(); i++) {
            QJsonObject objetoSerpiente = arraySerpiente[i].toObject();
            int x = objetoSerpiente["x"].toInt();
            int y = objetoSerpiente["y"].toInt();

            jugador->serpiente.append(QPoint(x, y));
        }
    }

    if(jsonPrincipal.contains("crecer")){
            QJsonObject jsonCrecer = jsonPrincipal["crecer"].toObject();
            jugador->crecer = jsonCrecer["crecer"].toInt();
        }

    if(jsonPrincipal.contains("direccion")){
        cuerpo::Direccion dirsel;
        QJsonObject direccionSerpiente = jsonPrincipal["direccion"].toObject();
        dirsel = (cuerpo::Direccion)(direccionSerpiente["direccion"].toInt());
        jugador->direccion = dirsel;
    }

    if(jsonPrincipal.contains("nivel")){
        QJsonObject nivelpartida = jsonPrincipal["nivel"].toObject();
        nivel = nivelpartida["nivel"].toInt();
    }

}

void MainWindow::slotNueva(){
    temporizador->stop();
    puntos=0;

    resize(450,450);
    iniciarJuego();
    for (int i=0 ; i<frutasEnJuego.size(); i++){
        frutasEnJuego.remove(i);
    }
    inicializaComidas();
    temporizador = new QTimer(this);
    temporizador->setSingleShot(false);

    connect(temporizador,SIGNAL(timeout()),
        this, SLOT(slotTemporizador()));

    tiempoFruta = rand() % 25 + 50;
    temporizador->setInterval(1000/nivel);
    temporizador->start();
}
MainWindow::~MainWindow(){
}
