
#include "mainWindow.h"
#include "Voiture.h"
#include "VoitureDAO.h"
#include "Historique.h"
#include "HistoriqueDAO.h"
#include "Detail.h"
#include <iostream>
#include <vector>
#include <QtCore/qmath.h> 
#include <cmath>       
#include <QKeyEvent>
#include <iostream>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), drawShape(false), vitesse(0),tempsEcoule(0) {

   
    input = new QLineEdit(this);
    input->setPlaceholderText("Entrez le nom de la voiture");
    input->setFixedSize(300, 40);
    input->move(50, 50); 

    button = new QPushButton("Valider", this);
    button->setFocusPolicy(Qt::NoFocus);

    button->setFixedSize(300, 40);
    button->move(50, 100);  
    simulations = new QPushButton("simulation", this);
    simulations->setFocusPolicy(Qt::NoFocus);

    simulations->setFixedSize(300, 40);
    simulations->move(50, 150); 

    plein= new QPushButton("arret", this);
    plein->setFocusPolicy(Qt::NoFocus);

    plein->setFixedSize(80, 40);
    plein->move(50, 500);  
    plein->hide();

    replay = new QPushButton("Replay", this);
    replay->setFocusPolicy(Qt::NoFocus);
    replay->setFixedSize(50, 40);
    replay->move(500, 600); 
    replay->hide();

 
    connect(button, &QPushButton::clicked, this, &MainWindow::onValidate);
    connect(simulations, &QPushButton::clicked, this, &MainWindow::simul);
    connect(plein, &QPushButton::clicked, this, &MainWindow::faireLePlein);
    connect(replay, &QPushButton::clicked, this, &MainWindow::replaySimul);
  
    retourLabel = new QLabel("<a href='#'>Retour</a>", this);
    retourLabel->move(50, 150); 
    retourLabel->setVisible(false); 
    retourLabel->setTextFormat(Qt::RichText);
    retourLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    retourLabel->setCursor(Qt::PointingHandCursor);
    connect(retourLabel, &QLabel::linkActivated, this, &MainWindow::onRetour);

    timerSecondes = new QTimer(this);
    connect(timerSecondes, &QTimer::timeout, this, &MainWindow::updateTemps);
    timerSecondes->start(1000); 
    carburantTimer = new QTimer(this);
    connect(carburantTimer, &QTimer::timeout, this, &MainWindow::updateCarburant);

  
    resize(800, 800);  
}

void MainWindow::onValidate() {
    QString text = input->text();
    std::string str = text.toStdString();
    VoitureDAO voitureDAO;
    std::vector<Voiture> voitures = voitureDAO.getVoitureByName(str);
        if (voitures.size() == 0) {
            QMessageBox::warning(this, "Erreur", "La voiture entrée n'existe pas");
        } else {
            simulationActive = true;  
            distance=0.0;
            input->setEnabled(false);
            voiture=voitures[0];
            litre=voiture.getLitre();
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &MainWindow::updateVitesse);
            animationTimer->start(100); 
            carburantTimer->start(500);


            drawShape = true;  
            update();  
            input->hide();
            button->hide();
            
            
            retourLabel->show();
            plein->show();
            replay->hide();
            simulations->hide();
           
        }
    
}
void MainWindow::simul() {
    QString text = input->text();
    std::string str = text.toStdString();
    VoitureDAO voitureDAO;
    std::vector<Voiture> voitures = voitureDAO.getVoitureByName(str);
        if (voitures.size() == 0) {
            QMessageBox::warning(this, "Erreur", "La voiture entrée n'existe pas");
        } else {
            simulationActive = true;  
            distance=0.0;
            input->setEnabled(false);
            voiture=voitures[0];
            litre=voiture.getLitre();
            animationTimer = new QTimer(this);
            connect(animationTimer, &QTimer::timeout, this, &MainWindow::updateVitesse);
            animationTimer->start(100); 
            carburantTimer->start(500);


            drawShape = true;  
            update();  
            input->hide();
            button->hide();
            
            
            retourLabel->show();
            plein->show();
            replay->show();
            simulations->hide();
            
           
        }
    
}

void MainWindow::updateVitesse() {
    if (vitesse < voiture.getVitesse()) {
        vitesse += 1;

    } else if (vitesse > voiture.getVitesse()) {
        vitesse -= 1;
    }if(vitesse<=0){
        voiture.setVitesse(0);
    }
    
    // Calculer la distance parcourue en supposant une mise à jour toutes les 100ms
    distance += (vitesse / 36.0); // Convertir km/h en m/s (100ms = 1/10s donc / 36)
    
    update();
}



void MainWindow::paintEvent(QPaintEvent *event) {
    if (drawShape) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        double pourcentage=(voiture.getLitre()/voiture.getCapacite())*100;
        painter.drawText(50, 250, "Carburant Restant: " +QString::number(pourcentage)+"%");
        painter.drawText(500, 310, "Temps écoulé: " + QString::number(tempsEcoule) + " secondes");
    int width = 50;
    int height = 150;  // Hauteur totale du réservoir
    int fuelHeight = (voiture.getLitre() / voiture.getCapacite()) * height;  // Calcul de la hauteur du carburant restant

    // Rectangle du réservoir (cadre)
    QRect rect(50, 300, width, height);
    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(rect);

    // Rectangle représentant le carburant (partie verte)
    if (fuelHeight > 0) {
        QRect fuelRect(50, 300 + (height - fuelHeight), width, fuelHeight);
        painter.setBrush(QBrush(Qt::green));
        painter.drawRect(fuelRect);
        
    }

    // Partie vide du réservoir (en rouge si vide)
    if (fuelHeight < height) {
        QRect emptyRect(50, 300, width, height - fuelHeight);
        painter.setBrush(QBrush(Qt::red));
        painter.drawRect(emptyRect);
    }


         // Ajouter une aiguille rouge
         QPoint center(100 + (170 * 4) / 2, 350 + (75 * 4) / 2);  // Centre du demi-cercle

         // Calculer l'angle pour la vitesse
         double angle = -(vitesse / 120.0) * 180.0;  // Convertir la vitesse en angle (0 à 120 km/h pour 0 à 180°)

         // Convertir l'angle en radians pour le calcul de la position
         double radians = qDegreesToRadians(angle);

         // Calculer la position de l'extrémité de l'aiguille
         int length = 100;  // Longueur de l'aiguille
         int endX = center.x() - length * cos(radians);  // Coordonnée x de l'extrémité de l'aiguille
         int endY = center.y() + length * sin(radians);  // Coordonnée y de l'extrémité de l'aiguille (inversé pour la coordonnée y)

         // Dessiner l'aiguille en rouge
         painter.setPen(QPen(Qt::red, 3));  // Couleur rouge et épaisseur de 3
         painter.drawLine(center, QPoint(endX, endY));  // Dessiner la ligne de l'aiguille

         // Dessiner les marques (0, 10, 20, ..., 120)
         int totalMarks = 13;  // Marqueurs de 0 à 120 (inclus)
         double startAngle = 0.0;  // L'angle de départ (0°)
         double angleStep = 180.0 / (totalMarks - 1);  // Espacement des marques

         for (int i = 0; i < totalMarks; ++i) {
            // Inverser les angles pour que 0 soit à gauche et 120 à droite
            double angle = 180.0 - (i * angleStep);
        
            double radians = qDegreesToRadians(angle);
        
            int length = 130;
            int markX = center.x() + length * cos(radians);
            int markY = center.y() - length * sin(radians);
        
            painter.setPen(QPen(Qt::black));
            painter.drawLine(center, QPoint(markX, markY));
        
            painter.setPen(QPen(Qt::black));
            painter.drawText(markX - 10, markY - 10, QString::number(i * 10));
        
            painter.drawText(500, 250, "Vitesse: " + QString::number(voiture.getVitesse()) + " m/s");
            painter.drawText(500, 280, "Distance: " + QString::number(distance, 'f', 2) + " m");
        }
    }        
    // Ajoutez cette méthode à votre classe MainWindow

}
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (simulationActive) {
        if (event->key() == Qt::Key_Control) {
            event->accept();
            shiftAppuye = true;
            std::cout << "Shift détecté et activé !" << std::endl;
            return;
           
        }
        if (event->key() == Qt::Key_Space) {
            event->accept();
            espaceAppuye = true;  // Espace est enfoncé, activer l'accélération possible
            return;
        }

        // Accélération seulement si Espace est maintenu
        if (espaceAppuye || shiftAppuye) {
            int pourcentage = 0;
            switch (event->key()) {
                case Qt::Key_1: pourcentage = 10; break;
                case Qt::Key_2: pourcentage = 20; break;
                case Qt::Key_3: pourcentage = 30; break;
                case Qt::Key_4: pourcentage = 40; break;
                case Qt::Key_5: pourcentage = 50; break;
                case Qt::Key_6: pourcentage = 60; break;
                case Qt::Key_7: pourcentage = 70; break;
                case Qt::Key_8: pourcentage = 80; break;
                case Qt::Key_9: pourcentage = 90; break;
                case Qt::Key_0: pourcentage = 100; break;
                default:
                    event->ignore();
                    return;
            }
            if (pourcentage > 0) {
                Historique historique=Historique(0,0,0,0,0);
                if(espaceAppuye){
                    voiture.accelerer(pourcentage);
                    double newacc=(pourcentage*voiture.getAcceleration())/100;
                    historique=Historique(1,voiture.getLitre(),voiture.getVitesse(),newacc,voiture.getId());
                    HistoriqueDAO historiqueDAO;
                    if(repereA==0 && newacc!=0){
                        historiqueDAO.ajouterHistorique(historique);
                    }
                    repereA=repereA+1;
                    repereF=newacc;
                    std::cout << "repere Final " << repereF << std::endl;
                }
                if(shiftAppuye){
                    voiture.deccelerer(pourcentage);
                    double newdec=(pourcentage*voiture.getDeceleration())/100;
                    historique=Historique(1,voiture.getLitre(),voiture.getVitesse(),-newdec,voiture.getId());
                    HistoriqueDAO historiqueDAO;
                    if(repereD==0 && newdec!=0){
                        historiqueDAO.ajouterHistorique(historique);
                    }
                    repereD=repereD+1;
                    repereF=-newdec;
                    std::cout << "repere Final " << repereF << std::endl;
                }
                updateVitesse();
                update();
            }
        } else {
            event->ignore();  // Ignorer les chiffres si Espace n'est pas enfoncé
        }
    } else {
        QWidget::keyPressEvent(event);
    }
}



void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    Historique historique=Historique(1,voiture.getLitre(),voiture.getVitesse(),0,voiture.getId());
    HistoriqueDAO historiqueDAO;
    if (event->key() == Qt::Key_Space) {
        if(simulationActive && espaceAppuye && repereF!=0){
        historiqueDAO.ajouterHistorique(historique);
        }
        espaceAppuye = false;  // Désactiver l'accélération si Espace est relâché
        repereA=0;
        event->accept();
    }
    if (event->key() == Qt::Key_Control) {
        if(simulationActive && shiftAppuye && repereF!=0){
        historiqueDAO.ajouterHistorique(historique);

        }
        shiftAppuye = false;
        repereD=0;
        event->accept();
    }
    QWidget::keyReleaseEvent(event);
}

void MainWindow::onRetour() {
    input->show();
    button->show();
    retourLabel->hide(); // Cacher le lien retour
    plein->hide(); // Afficher le lien retour
    simulations->show();
      // Lorsque la simulation se termine, réactiver le focus sur le champ de texte
      simulationActive = false;
      input->setEnabled(true);  // Réactiver le champ de texte
      input->setFocus();  // Mettre le focus sur le champ de texte

   
}
void MainWindow::faireLePlein() {
    HistoriqueDAO historiqueDAO;
    Historique historique =Historique(1,voiture.getLitre(),voiture.getVitesse(),repereF,voiture.getId());
    historiqueDAO.ajouterHistorique(historique);
    QMessageBox::information(this, "jeux", "jeux arreter !");
}

void MainWindow::updateTemps() {
    if (simulationActive) {
        tempsEcoule++;  // Augmenter le temps écoulé
        update();  // Redessiner l'interface
    }
}



void MainWindow::replaySimul() {
    HistoriqueDAO historiqueDAO;
    std::vector<Historique> historiques = historiqueDAO.getHistorique(voiture.getId());
    double distanceeff=historiqueDAO.calculerDistanceParcourue(voiture.getId(),voiture.getLitre());

    if (historiques.empty()) {
        QMessageBox::information(this, "Simulation Terminée", "Aucune simulation trouver");
        return;
    }

    int interval = 10; // Temps entre chaque incrémentation de vitesse
    int delay = 0; // Délai pour chaque QTimer
    distance = 0.0;

    for (size_t i = 0; i < historiques.size() - 1; ++i) {
        double vitesseActuelle = historiques[i].getVitesse();
        double vitesseCible = historiques[i + 1].getVitesse();
        double acceleration = historiques[i].getAcceleration();
        double litreActuel = historiques[i].getLitre();
        double litreCible = historiques[i + 1].getLitre();
        
        int steps = std::max(1, (int)std::round(std::abs((vitesseCible - vitesseActuelle) / (acceleration != 0 ? acceleration : 1)))); // Éviter division par 0
        double consommationParStep = (litreActuel - litreCible) / steps;
    
        if (acceleration == 0) {
            // Phase de vitesse constante
            int dureeConstante = 10; // Durée de maintien en ms (modifiable)
            std::cout << "steps." << steps << std::endl;
            QTimer::singleShot(delay, this, [this]() {
                updateVitesse();
                update();
            });
            delay += dureeConstante;
        } else {
            // Phase de variation de vitesse
            double vitesseStep = acceleration;
            for (int z = 0; z < steps; z++) {
                QTimer::singleShot(delay, this, [this, vitesseStep, consommationParStep]() {
                    voiture.setVitesse(voiture.getVitesse() + vitesseStep);
                    voiture.setLitre(voiture.getLitre() - consommationParStep);
                    updateVitesse();
                    update();
                });
                delay += interval;
            }
        }
    }
    
    // Afficher le message de fin de simulation
    QTimer::singleShot(delay, this, [this,distanceeff]() {
        QMessageBox::information(this, "Simulation Terminée", "Consommation moyenne: " + QString::number(distanceeff) + " L");

        // Redémarrer les timers après la simulation
        animationTimer->start(100);
        carburantTimer->start(500);
        timerSecondes->start(1000);
    });
}









void MainWindow::updateCarburant() {
    if (voiture.getCapacite() > litre) {
        voiture.setLitre(voiture.getLitre() - 0.1);  // Réduction progressive
        update();
    } else {
        carburantTimer->stop();  // Arrêter l'animation quand le réservoir est vide
    }
}





