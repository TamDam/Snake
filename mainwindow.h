#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inicio.h"
#include "ui_inicio.h"
#include "dnuevojuego.h"
#include "ui_dnuevojuego.h"
#include "cuerpo.h"
#include "dcontrolraton.h"
#include "ui_dcontrolraton.h"
#include "fruta.h"
#include "puntuacion.h"
#include "ui_puntuacion.h"

#include <QMainWindow>

#include <QTimer>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QLabel>
#include <QPaintEvent>
#include <QVector>

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    QTimer * temporizador;
    QMenu * menu, * menuPartida;
    QAction * accionMover, *accionNueva,* accionGuardar, * accionCargar,* accionPuntuacion;
    QString nombre;
    QLabel * puntuacionPartida;
    Qt::Key teclaPulsada;
    bool cerrar;
    int puntos, nivel;
    cuerpo * jugador;
    QImage spriteSnake;

    /*fruta*/
    QVector<frutaPosible *> posiblesFrutas;//las que pueden
    QVector<frutaEnJuego> frutasEnJuego;//las que se ven
    int tiempoFruta;

public:
    MainWindow(QWidget *parent = 0);

    void crearMenu();
    void crearAccion();
    void iniciarJuego();
    void nuevoJuego();
    void inicializaComidas();
    void guardarPuntuacion(QString nombre, int punt);
    void paintEvent(QPaintEvent * event);
    void keyPressEvent(QKeyEvent * event);

    ~MainWindow();

signals:
    void cambioDireccion(cuerpo::Direccion);

public slots:
    void slotTemporizador();
    void slotMostrarControlRaton();
    void slotCambioDireccionRaton(cuerpo::Direccion);
    void slotGuardarPartida();
    void slotCargarPartida();
    void slotMostrarPuntuaciones();
    void slotNueva();
};

#endif // MAINWINDOW_H
