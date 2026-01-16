#ifndef TRAITEMENT_H
#define TRAITEMENT_H
#include "types.h"
//Lire le fichier produits.csv et l'enregistrer dans un tableau de produits
int chargerProduits(Produit produit[], int max);
//Lire le fichier produits.csv et l'enregistrer dans un tableau de clients
int chargerClients(Client client[], int max);
//Lire le fichier produits.csv et l'enregistrer dans un tableau de factures
int chargerFactures(Facture facture[], int max);
//imprimer une nouvelle facture créée avec tous ses détails
void imprimerFactures(Facture facture);

#endif
