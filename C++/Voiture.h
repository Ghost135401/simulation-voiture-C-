#include <string>
#ifndef VOITURE_H
#define VOITURE_H

class Voiture {
private:
    double capacite;        // Capacité du réservoir en litres
    double litre;          // Niveau actuel de carburant en litres
    double consommation;   // Consommation en litres par accélération
    double acceleration;   // Accélération du véhicule
    std::string nom;
    int id;
    double vitesse;
    double deceleration;

public:
    // Constructeur
    Voiture(double capacite,double litre, double consommation, double acceleration,std::string nom,int id,double vitesse,double deceleration);
    
    // Accélérer la voiture
    void accelerer();
    void deccelerer();
    void deccelerer(int a);
    void accelerer(int a);

    int getId() const;

    double getDeceleration() const;

    std::string getNom() const;
    
    // Faire le plein
    void fairePlein();
    
    // Obtenir le niveau actuel de carburant
    double getLitre() const;

    double getVitesse() const;
    
    // Obtenir la capacité du réservoir
    double getCapacite() const;
    
    // Obtenir la consommation par accélération
    double getConsommation() const;
    
    // Obtenir l'accélération
    double getAcceleration() const;
    void setLitre(double l);
    void setVitesse(double v);
    void setCapacite(double c);
    void setConsommation(double conso);
    void setAcceleration(double acc);
    void setDeceleration(double dec);
    void setId(int i);
    void setNom(const std::string& n);
};

#endif
