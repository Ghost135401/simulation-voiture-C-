#!/bin/bash

# 🚀 Couleurs pour un style beaugoss
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}🔧 Nettoyage du projet...${NC}"
make clean && echo -e "${GREEN}✔ Nettoyage réussi${NC}" || { echo -e "${RED}❌ Échec du nettoyage${NC}"; exit 1; }

echo -e "${YELLOW}⚙ Génération du Makefile avec qmake...${NC}"
qmake projet.pro && echo -e "${GREEN}✔ Makefile généré${NC}" || { echo -e "${RED}❌ Échec de qmake${NC}"; exit 1; }

echo -e "${BLUE}🛠 Compilation du projet...${NC}"
make && echo -e "${GREEN}✔ Compilation réussie${NC}" || { echo -e "${RED}❌ Échec de la compilation${NC}"; exit 1; }

echo -e "${YELLOW}🚗 Lancement de l'application...${NC}"
./QtApp && echo -e "${GREEN}✔ Exécution terminée${NC}" || echo -e "${RED}❌ Erreur lors de l'exécution${NC}"
