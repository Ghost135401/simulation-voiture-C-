#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QTimer>  // Inclure pour QTimer
#include "Voiture.h"
#include "VoitureDAO.h"
#include "Historique.h"
#include "HistoriqueDAO.h"
#include "Detail.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Voiture voiture=Voiture(0,0,0,0," ",0,0,0);
    int repereA=0;
    int repereD=0;
    double repereF=0;
    double litre=0;

private slots:
    void onValidate();
    void updateVitesse();  // Slot pour mettre à jour la vitesse
    void onRetour();
    void faireLePlein();
    void updateTemps();
    void replaySimul();
    void updateCarburant();
    void simul();
 


protected:
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;  // Déclaration de la méthode keyPressEvent
    void keyReleaseEvent(QKeyEvent *event) override; 


private:
    QLineEdit *input;
    bool drawShape = false;  // Contrôle si la forme doit être dessinée
    int vitesse = 0;  // La vitesse actuelle de la voiture
    QTimer *animationTimer;  // Le timer pour animer la vitesse
    double distance = 0.0;
    bool espaceAppuye = false;  // Ajoute ceci pour suivre l'état de l'appui sur Espace
    bool espaceRelache = false;
    QLabel *retourLabel; 
    QPushButton *button;
    QPushButton *contre;
    QPushButton *plein;
    QPushButton *replay;
    QPushButton *simulations;
    bool simulationActive=false; 
    bool shiftAppuye = false;
    private:
    int tempsEcoule;  // Temps écoulé en secondes
    QTimer* timerSecondes;  // Timer pour les secondes
    QTimer* carburantTimer;



};

#endif // MAINWINDOW_H
