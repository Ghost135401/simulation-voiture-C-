#ifndef HISTORIQUEDAO_H
#define HISTORIQUEDAO_H

#include "Historique.h"
#include "Database.h"  // Pour accéder à la base de données
#include <string>
#include <vector>
#include <QDateTime>


class HistoriqueDAO {
private:
    Database db;

public:
    HistoriqueDAO();  // Constructeur
    ~HistoriqueDAO();  // Destructeur

    bool ajouterHistorique(const Historique& historique);  // Ajouter un historique
    std::vector<Historique> getHistorique(int voitureId);  // Récupérer l'historique par ID de voiture
    std::vector<Historique> getAllHistoriques();  // Récupérer tous les historiques
    double calculerDistanceParcourue(int a,double z);
    double calculerDistanceParcourue1(int a,double z);
 
   
};

#endif
