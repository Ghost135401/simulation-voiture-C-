#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <iostream>
#include <string>
#include <ctime>

class Historique {
private:
    int id;
    double litre;
    double vitesse;        // Vitesse enregistrée
    std::string dateTime;  // Date et heure de l'enregistrement
    double acceleration;   // Accélération enregistrée
    int voitureId;         // Identifiant de la voiture

public:
    // Constructeur
    Historique(int id,double litre,double vitesse, double acceleration, int voitureId);
    double getLitre() const;
    int getId() const;

    // Méthode pour obtenir la vitesse
    double getVitesse() const;

    // Méthode pour obtenir l'heure de l'enregistrement
    std::string getDateTime() const;
    // Méthodes pour définir et récupérer la dateTime
    void setDateTime(const std::string& dateTime);

    // Méthode pour obtenir l'accélération
    double getAcceleration() const;

    // Méthode pour obtenir l'identifiant de la voiture
    int getVoitureId() const;

    // Méthode pour afficher l'historique
    void afficherHistorique() const;
};

#endif