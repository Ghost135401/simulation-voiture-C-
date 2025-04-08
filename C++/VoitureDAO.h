#ifndef VOITUREDAO_H
#define VOITUREDAO_H

#include "Voiture.h"
#include "Database.h"  // Pour accéder à la base de données
#include <string>
#include <vector>

class VoitureDAO {
private:
    Database db;

public:
    VoitureDAO();  // Constructeur
    ~VoitureDAO();  // Destructeur

    bool ajouterVoiture(const Voiture& voiture);  // Ajouter une voiture
    std::vector<Voiture> getVoiture(int id);  // Récupérer une voiture par ID
    std::vector<Voiture> getVoitureByName(std::string nom);  // Récupérer une voiture par ID
    std::vector<Voiture> getAllVoitures();  // Récupérer toutes les voitures
    bool mettreAJourVoiture(const Voiture& voiture);  // Mettre à jour les informations d'une voiture
    bool supprimerVoiture(int id);  // Supprimer une voiture
};

#endif
