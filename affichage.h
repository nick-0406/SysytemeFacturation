#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include "types.h"
//Affiche les differentes option possibles
void afficherAccueil();
//Affiche la totalite des produits
void afficherProduits(Produit produit[], int nombreProduit);
//Affiche les differents clients presents
void afficherClients(Client client[], int nombreClient);
//Affiches les informations des factures enregistrées
void afficherFactures(Facture facture[], int nombreFacture);
#endif