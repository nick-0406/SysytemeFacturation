#include <stdio.h>
#include "types.h"
#include "affichage.h"
#include "gestion.h"
#include "traitement.h"

int main(void) {
    Facture factures[MAX_FACTURES];
    Produit produits[MAX_PRODUITS];
    Client clients[MAX_CLIENTS];
    int nbFactures, nbProduits, nbClients, decidion;
    nbFactures = chargerFactures(factures, MAX_FACTURES);
    nbClients = chargerClients(clients, MAX_CLIENTS);
    nbProduits = chargerProduits(produits, MAX_PRODUITS);
    do {
        afficherAccueil();
        scanf(" %d",&decidion);
        switch (decidion) {
            case 1: afficherProduits(produits, nbProduits); break;
                case 2: afficherClients(clients, nbClients); break;
                case 3: {
                    Facture devis = creerFacture(factures,produits,clients,
                        nbFactures, nbProduits, nbClients, 'D');
                    factures[nbFactures++] = devis;//ajout de la nouvelle facture après création
                    imprimerFactures(devis);
                    break;
                }
                case 4: {
                    Facture facture = creerFacture(factures,produits,clients,
                        nbFactures, nbProduits, nbClients, 'F');
                    factures[nbFactures++] = facture;
                    imprimerFactures(facture);//impréssion de la facture après
                    break;
                }
                case 5: afficherFactures(factures, nbFactures); break;
            case 0 : {
                    sauvegarderClients(clients, nbClients);
                    sauvegarderFactures(factures, nbFactures);
                    sauvegarderProduits(produits, nbProduits);
                    break;;
                }
        }
    }while (decidion!=0);

    return 0;
}