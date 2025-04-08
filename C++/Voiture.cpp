#include "Voiture.h"
#include <iostream>

// Constructeur
Voiture::Voiture(double capacite,double litre, double consommation, double acceleration,std::string nom,int id,double vitesse,double deceleration)
    : capacite(capacite), litre(litre), consommation(consommation), acceleration(acceleration),nom(nom),id(id),vitesse(vitesse),deceleration(deceleration){}

// Accélérer
void Voiture::accelerer() {
    if (litre >= consommation) {
        litre -= consommation;
        std::cout << "Vroum ! La voiture accélère. Carburant restant: " << litre << " L" << std::endl;
    } else {
        std::cout << "Carburant insuffisant pour accélérer !" << std::endl;
        return;
    }
}

void Voiture::accelerer(int pourcentage){
    double newConsommation=(pourcentage*consommation)/100;
    double newVitesse=(pourcentage*acceleration)/100;
    if (litre >= newConsommation) {
        litre -= newConsommation;
        vitesse=vitesse+newVitesse;
        std::cout << "Vroum ! La voiture accélère. Carburant restant: " << litre << " L" << std::endl;
        std::cout << "Vitesse augmenté a " << vitesse << std::endl;
    } else {
        vitesse=0;
        std::cout << "Carburant insuffisant pour accélérer !" << std::endl;
    }
}
void Voiture::deccelerer(int pourcentage){
    double newVitesse=(pourcentage*deceleration)/100;
    if (vitesse >0 ) {
        vitesse=vitesse-newVitesse;
        std::cout << "Vitesse dimunué a " << vitesse << std::endl;
    } else {
        vitesse=0;
    }
}

void Voiture::deccelerer(){
        vitesse -= deceleration;
    
        if (vitesse < 0) {
            vitesse = 0; // Empêcher la vitesse négative
        }
    
        std::cout << "La voiture ralentit. Vitesse actuelle : " << vitesse << " km/h" << std::endl;
    }
    


// Faire le plein
void Voiture::fairePlein() {
    litre = capacite;
    vitesse=0;
    std::cout << "Le réservoir est maintenant plein !" << std::endl;
}

// Getters
double Voiture::getLitre() const { return litre; }
double Voiture::getVitesse() const { return vitesse; }
double Voiture::getCapacite() const { return capacite; }
double Voiture::getConsommation() const { return consommation; }
double Voiture::getAcceleration() const { return acceleration; }
double Voiture::getDeceleration() const { return deceleration; }
int Voiture::getId() const {return id;};
std::string Voiture::getNom() const {return nom;};
void Voiture::setLitre(double l) { litre = l; }
void Voiture::setVitesse(double v) { vitesse = v; }
void Voiture::setCapacite(double c) { capacite = c; }
void Voiture::setConsommation(double conso) { consommation = conso; }
void Voiture::setAcceleration(double acc) { acceleration = acc; }
void Voiture::setDeceleration(double dec) { deceleration = dec; }
void Voiture::setId(int i) { id = i; }
void Voiture::setNom(const std::string& n) { nom = n; }
