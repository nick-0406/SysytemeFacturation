#ifndef GESTION_H
#define GESTION_H
//Cree une facture ou un devis a partir des differentes informations enregistrees
Facture creerFacture(Facture factures[], Produit produits[],
    Client clients[], int nbFactures, int nbProduits, int nbClients, char typeStr);
//ouvre un fichier en lecture et sauvegarde les informations des produits mises a jours
void sauvegarderProduits(Produit produit[], int nbProduit);
//ouvre un fichier en lecture et sauvegarde les informations des Factures mises a jours
void sauvegarderFactures(Facture factures[], int nbFacture);
//ouvre un fichier en lecture et sauvegarde les informations des clients mises a jours
void sauvegarderClients(Client clients[], int nbClient);
//Effectue le tri en fonction du prix et du nom en fonction de la selection
void triProduits(Produit produit[], int nbProduit, char nom[], float prix);
#endif