#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>

class Database {
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

public:
    Database() : con(nullptr) {
        driver = sql::mysql::get_mysql_driver_instance();
    }

    // Fonction pour établir la connexion avec les paramètres fixes
    bool connecter() {
        try {
            // Connexion à la base de données avec des paramètres fixes
            con = driver->connect("tcp://localhost", "root", "vonjy");  // Utilisateur root avec mot de passe vide
            con->setSchema("Daba");  // Base de données "Daba"
            return true;
        } catch (sql::SQLException &e) {
            return false;
        }
    }

    // Fonction pour fermer la connexion
    void fermerConnexion() {
        if (con) {
            delete con;
        }
    }

    // Getter pour la connexion
    sql::Connection* getConnection() {
        return con;
    }
};

#endif // DATABASE_H
