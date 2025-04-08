#include "Historique.h"

// Constructeur
Historique::Historique(int id,double litre,double vitesse, double acceleration, int voitureId)
    : id(id),litre(litre),vitesse(vitesse), acceleration(acceleration), voitureId(voitureId) {
        // Obtenir la date et l'heure actuelles
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
    
        // Formater la date et l'heure en format 'YYYY-MM-DD HH:MM:SS'
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
        dateTime = buf;
}

// Méthode pour obtenir la vitesse
double Historique::getVitesse() const {
    return vitesse;
}

double Historique::getLitre() const {
    return litre;
}

// Méthode pour définir la dateTime
void Historique::setDateTime(const std::string& dateTime) {
    this->dateTime = dateTime;
}

int Historique::getId() const {
    return id;
}

// Méthode pour obtenir l'heure de l'enregistrement
std::string Historique::getDateTime() const {
    return dateTime;
}

// Méthode pour obtenir l'accélération
double Historique::getAcceleration() const {
    return acceleration;
}

// Méthode pour obtenir l'identifiant de la voiture
int Historique::getVoitureId() const {
    return voitureId;
}

// Méthode pour afficher l'historique
void Historique::afficherHistorique() const {
    std::cout << "Vitesse: " << vitesse << " km/h" << std::endl;
    std::cout << "Accélération: " << acceleration << " m/s²" << std::endl;
    std::cout << "ID de la voiture: " << voitureId << std::endl;
    std::cout << "Date et Heure: " << dateTime;
}
