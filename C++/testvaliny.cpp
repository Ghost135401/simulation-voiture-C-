#include <iostream>
#include "HistoriqueDAO.h"  // Utiliser le header HistoriqueDAO.h
#include "Voiture.h"

int main() {
    Database db;

    // Établir la connexion à la base de données
    if (db.connecter()) {

        HistoriqueDAO historiqueDAO;
        Voiture v1=Voiture(50,50,2,3,"Voiture 1",1,0,1);
        double moyenne=HistoriqueDAO.moyenneConsommation(50,1);
        std::cout << "Moyenne Consommation/100km :" << moyenne << "litre" std::endl;

        
        db.fermerConnexion();
    } else {
        std::cerr << "Impossible de se connecter à la base de données." << std::endl;
    }

    return 0;
}
