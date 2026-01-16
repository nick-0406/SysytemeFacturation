#include <stdio.h>
#include "affichage.h"
#include "types.h"

void afficherAccueil() {
    printf("\n=========== SYSTEME DE FACTURATION ==============\n");
    printf("1. Afficher la liste des produits\n");
    printf("2. Afficher la liste des clients\n");
    printf("3. Creer un devis\n");
    printf("4. Creer une facture\n");
    printf("5. Afficher toutes les factures\n");
    printf("0. Quitter\n");
}

void afficherProduits(Produit produit[], int nombreProduit) {
    printf("---------Liste des Produits-----------\n\n");
    printf("id;nom;Stock;prix_unitaire;TVA\n");
    for (int i = 0; i < nombreProduit; i++) {
        printf("%d;%s;%d;%2.2f;%2.2f\n",produit[i].id,produit[i].nom,produit[i].stock,produit[i].prixUnitaireHT
            , produit[i].TVA);

    }
}
void afficherClients(Client client[], int nombreClient) {
    printf("---------Liste des Clients-----------\n\n");
    printf(" id        nom            email\n");
    for (int i = 0; i < nombreClient; i++) {
        printf("%2d    %-20s%-20s\n",client[i].id,client[i].nom,client[i].email);
    }
}
void afficherFactures(Facture facture[], int nombreFacture) {
    printf("---------Liste des Factures-----------\n\n");
    for (int i = 0; i < nombreFacture; i++) {
        printf("id_facture : %2d\n",facture[i].idFacture);
        printf("id_client : %2d\n",facture[i].idClient);
        printf("date : %2d-%2d-%d\n",facture[i].date.jour,facture[i].date.mois,facture[i].date.annee);
        printf("type : %s\n", facture[i].type==FACTURE ? "FACTURE":"DEVIS");
        printf("id_produit || nombre_produit || prix\n");
        for (int j =0; j<facture[i].nombreContenu; j++)
            printf("  %2d          %2d     %2.2f\n", facture[i].contenu[j].id,facture[i].contenu[j].nombre
            ,facture[i].contenu[j].prix);
        printf("Total prix %s : %.2f",facture[i].type==FACTURE ? "facture":"devis", facture[i].totalPrix);
        printf("\n\n");
    }
}