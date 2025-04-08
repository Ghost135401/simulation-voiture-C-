#include "HistoriqueDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <vector>


// Constructeur
HistoriqueDAO::HistoriqueDAO() {
    db.connecter();  // Se connecter à la base de données
}

// Destructeur
HistoriqueDAO::~HistoriqueDAO() {
    db.fermerConnexion();  // Fermer la connexion à la base de données
}

// Ajouter un historique
bool HistoriqueDAO::ajouterHistorique(const Historique& historique) {
    try {
        sql::PreparedStatement *stmt = db.getConnection()->prepareStatement(
            "INSERT INTO historique (vitesse, acceleration, voitureId, dateTime,litre) VALUES (?, ?, ?, NOW(),?)");
        stmt->setDouble(1, historique.getVitesse());
        stmt->setDouble(2, historique.getAcceleration());
        stmt->setInt(3, historique.getVoitureId());
        stmt->setDouble(4, historique.getLitre());
        
        stmt->executeUpdate();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de l'ajout de l'historique : " << e.what() << std::endl;
        return false;
    }
}

// Récupérer l'historique par ID de voiture
std::vector<Historique> HistoriqueDAO::getHistorique(int id) {
    std::vector<Historique> historiques;
    try {
        sql::PreparedStatement *stmt = db.getConnection()->prepareStatement(
            "SELECT id,vitesse, acceleration, dateTime,voitureId,litre FROM historique WHERE voitureId = ?");
        stmt->setInt(1, id);
        
        sql::ResultSet *res = stmt->executeQuery();
        
        while (res->next()) {
            Historique historique(
                res->getDouble("id"),
                res->getDouble("litre"),
                res->getDouble("vitesse"),
                res->getDouble("acceleration"),
                id
               
            );
            std::string dateTime = res->getString("dateTime"); 
            historique.setDateTime(dateTime);
            historiques.push_back(historique);

        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de la récupération des historiques : " << e.what() << std::endl;
    }
    
    return historiques;
}

// Récupérer tous les historiques
std::vector<Historique> HistoriqueDAO::getAllHistoriques() {
    std::vector<Historique> historiques;
    try {
        sql::Statement *stmt = db.getConnection()->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT id,vitesse, acceleration, dateTime, voitureId,litre FROM historique");
        
        while (res->next()) {
            Historique historique(
                res->getInt("id"),
                res->getDouble("litre"),
                res->getDouble("vitesse"),
                res->getDouble("acceleration"),
                res->getInt("voitureId")
            );
            std::string dateTime = res->getString("dateTime"); 
            historique.setDateTime(dateTime);
            historiques.push_back(historique);
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de la récupération des historiques : " << e.what() << std::endl;
    }
    
    return historiques;
}

double HistoriqueDAO::calculerDistanceParcourue1(int id,double litre) {
    std::vector<Historique> historiques = getHistorique(id);
    double distanceTotale = 0.0;

    if (historiques.size() < 2) {
        return 0.0;  // Si pas assez de données pour calculer
    }

    for (size_t i = 0; i < historiques.size() - 1; ++i) {
        // Récupérer les dates
        QDateTime dt0 = QDateTime::fromString(QString::fromStdString(historiques[i].getDateTime()), "yyyy-MM-dd HH:mm:ss");
        QDateTime dt1 = QDateTime::fromString(QString::fromStdString(historiques[i + 1].getDateTime()), "yyyy-MM-dd HH:mm:ss");

        // Calculer le temps écoulé en secondes entre les deux enregistrements
        int interval = dt0.msecsTo(dt1) / 1000;  // Convertir de millisecondes en secondes

        // Vérifier que l'intervalle est positif
        if (interval <= 0) continue;

        // Récupérer la vitesse de l'historique courant
        double vitesse = historiques[i].getVitesse();  // en km/h

        // Convertir la vitesse en m/s
        double vitesseMS = vitesse / 3.6;

        // Calculer la distance parcourue entre les deux enregistrements
        double distance = vitesseMS * interval;  // d = v * t

        // Ajouter à la distance totale
        distanceTotale += distance;
    }
    double finLitre=historiques[historiques.size()-1].getLitre();
    double newLitre=litre-finLitre;
    double distancef=distanceTotale*0.001;
    double resultat= (100*newLitre)/distancef;
    std::cout << "distance parcourue." << distancef << std::endl;
    std::cout << "litre/100km." << resultat << std::endl;
    return resultat ;  // Distance totale en mètres
}
double HistoriqueDAO::calculerDistanceParcourue(int id, double litreInitial) {
    std::vector<Historique> historiques = getHistorique(id);
    double distanceTotaleMetres = 0.0;

    for (size_t i = 0; i < historiques.size() - 1; ++i) {
        QDateTime dt0 = QDateTime::fromString(QString::fromStdString(historiques[i].getDateTime()), "yyyy-MM-dd HH:mm:ss");
        QDateTime dt1 = QDateTime::fromString(QString::fromStdString(historiques[i + 1].getDateTime()), "yyyy-MM-dd HH:mm:ss");

        int intervalSec = dt0.msecsTo(dt1) / 1000;
        if (intervalSec <= 0) continue;

        double vitesseKmh = historiques[i].getVitesse();
        double vitesseMs = vitesseKmh;

        double distance = vitesseMs * intervalSec;  // v * t
        distanceTotaleMetres += distance;
    }

    // Distance totale en km
    double distanceKm = distanceTotaleMetres / 1000.0;

    // Consommation
    double litreFinal = historiques.back().getLitre();
    double litreConsomme = litreInitial - litreFinal;

    double consoL_100km = distanceKm > 0 ? (litreConsomme / distanceKm) * 100.0 : 0.0;

    std::cout << "Distance parcourue : " << distanceKm << " km" << std::endl;
    std::cout << "Consommation : " << consoL_100km << " L/100km" << std::endl;

    return consoL_100km;
}



