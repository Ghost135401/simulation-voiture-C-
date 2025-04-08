#include "VoitureDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <vector>

// Constructeur
VoitureDAO::VoitureDAO() {
    db.connecter();  // Se connecter à la base de données
}

// Destructeur
VoitureDAO::~VoitureDAO() {
    db.fermerConnexion();  // Fermer la connexion à la base de données
}

// Ajouter une voiture
bool VoitureDAO::ajouterVoiture(const Voiture& voiture) {
    try {
        sql::PreparedStatement *stmt = db.getConnection()->prepareStatement(
            "INSERT INTO voitures (capacite, consommation, acceleration, litre, nomVoiture,vitesse,deceleration) VALUES (?, ?, ?, ?, ?,?,?)");
        stmt->setDouble(1, voiture.getCapacite());
        stmt->setDouble(2, voiture.getConsommation());
        stmt->setDouble(3, voiture.getAcceleration());
        stmt->setDouble(4, voiture.getLitre());
        stmt->setString(5, voiture.getNom());  // Ajouter le nom de la voiture
        stmt->setDouble(6, voiture.getVitesse());
        stmt->setDouble(7, voiture.getDeceleration());
        
        stmt->executeUpdate();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de l'ajout de la voiture : " << e.what() << std::endl;
        return false;
    }
}

// Récupérer une voiture par ID
std::vector<Voiture> VoitureDAO::getVoiture(int id) {
    std::vector<Voiture> voitures;
    try {
        sql::PreparedStatement *stmt = db.getConnection()->prepareStatement(
            "SELECT capacite, consommation, acceleration, litre, nomVoiture,vitesse,deceleration FROM voitures WHERE id = ?");
        stmt->setInt(1, id);
        
        sql::ResultSet *res = stmt->executeQuery();
        
        if (res->next()) {
            // Modification ici : passer le nom en plus du constructeur
            Voiture voiture(
                res->getDouble("capacite"),
                res->getDouble("litre"),
                res->getDouble("consommation"), 
                res->getDouble("acceleration"),
                res->getString("nomVoiture"), 
                id,
                res->getDouble("vitesse"),
                res->getDouble("deceleration")
            );
            voitures.push_back(voiture);
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de la récupération des voitures : " << e.what() << std::endl;
    }
    
    return voitures;
}
// Récupérer une voiture par ID
std::vector<Voiture> VoitureDAO::getVoitureByName(std::string nom) {
    std::vector<Voiture> voitures;
    try {
        sql::PreparedStatement *stmt = db.getConnection()->prepareStatement(
            "SELECT capacite, consommation, acceleration, litre, nomVoiture,vitesse,id,deceleration FROM voitures WHERE nomVoiture = ?");
        stmt->setString(1, nom);
        
        sql::ResultSet *res = stmt->executeQuery();
        
        if (res->next()) {
            // Modification ici : passer le nom en plus du constructeur
            Voiture voiture(
                res->getDouble("capacite"),
                res->getDouble("litre"),
                res->getDouble("consommation"), 
                res->getDouble("acceleration"),
                nom, 
                res->getInt("id"),
                res->getDouble("vitesse"),
                res->getDouble("deceleration")
            );

    
            voitures.push_back(voiture);
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de la récupération des voitures : " << e.what() << std::endl;
    }
    
    return voitures;
}

// Récupérer toutes les voitures
std::vector<Voiture> VoitureDAO::getAllVoitures() {
    std::vector<Voiture> voitures;
    try {
        sql::Statement *stmt = db.getConnection()->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT capacite, consommation, acceleration, litre, nomVoiture,vitesse,id,deceleration FROM voitures");
        
        while (res->next()) {
            // Modification ici : passer le nom en plus du constructeur
            Voiture voiture(
                res->getDouble("capacite"),
                res->getDouble("litre"),
                res->getDouble("consommation"), 
                res->getDouble("acceleration"),
                res->getString("nomVoiture"), 
                res->getInt("id"),
                res->getDouble("vitesse"),
                res->getDouble("deceleration")
             
            );
            voiture.fairePlein();  // Remplir le réservoir
            voitures.push_back(voiture);
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de la récupération des voitures : " << e.what() << std::endl;
    }
    
    return voitures;
}

// Mettre à jour les informations d'une voiture
bool VoitureDAO::mettreAJourVoiture(const Voiture& voiture) {
    try {
        sql::PreparedStatement *stmt = db.getConnection()->prepareStatement(
            "UPDATE voitures SET capacite = ?, consommation = ?, acceleration = ?, litre = ?,vitesse=? WHERE id = ?");
        stmt->setDouble(1, voiture.getCapacite());
        stmt->setDouble(2, voiture.getConsommation());
        stmt->setDouble(3, voiture.getAcceleration());
        stmt->setDouble(4, voiture.getLitre());
        stmt->setInt(5, voiture.getId());
        stmt->setDouble(5, voiture.getVitesse());
        
        stmt->executeUpdate();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de la mise à jour de la voiture : " << e.what() << std::endl;
        return false;
    }
}

// Supprimer une voiture
bool VoitureDAO::supprimerVoiture(int id) {
    try {
        sql::PreparedStatement *stmt = db.getConnection()->prepareStatement(
            "DELETE FROM voitures WHERE id = ?");
        stmt->setInt(1, id);
        
        stmt->executeUpdate();
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de la suppression de la voiture : " << e.what() << std::endl;
        return false;
    }
}
