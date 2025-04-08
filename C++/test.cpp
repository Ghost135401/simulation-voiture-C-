#include <iostream>
#include "HistoriqueDAO.h"
#include "Historique.h"

int main() {
    // Création d'un objet Historique
    // Exemple : Vitesse = 120.5 km/h, Accélération = 3.2 m/s², VoitureId = 1
    Historique historique(1,50,120.5, 3.2, 1);

    // Création d'un objet HistoriqueDAO pour interagir avec la base de données
    HistoriqueDAO historiqueDAO;

    // Ajouter l'historique à la base de données
    if (historiqueDAO.ajouterHistorique(historique)) {
        std::cout << "Historique ajouté avec succès !" << std::endl;
    } else {
        std::cerr << "Erreur lors de l'ajout de l'historique." << std::endl;
    }

    // Récupérer l'historique par ID de voiture (exemple : ID de voiture = 1)
    std::vector<Historique> historiques = historiqueDAO.getHistorique(4);

    // Afficher tous les historiques récupérés
    std::cout << "\nHistorique pour la voiture ID 1 : " << std::endl;
    for (const auto& hist : historiques) {
        hist.afficherHistorique();  // Affiche l'historique
        std::cout << std::endl;
    }

    return 0;
}
