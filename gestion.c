#include <stdio.h>
#include "types.h"
#include "gestion.h"
#include <stdbool.h>
#include <string.h>

/*
 *creation d'une (facture/devis) en fonction du caractere passe en argument 'F' pour FACTURE et 'D' pour DEVIS)
 */
Facture creerFacture(Facture factures[], Produit produits[],
    Client clients[], int nbFactures, int nbProduits, int nbClients, char typeStr) {
    Facture facture;
    int i=0, choix,selection;
    facture.totalPrix=0;
    float somme; char name[15];
    bool valid = true, accept = true;
    //l'id de la nouvelle facture est directment consecutive à celui de la plus recente facture
    facture.idFacture = factures[nbFactures-1].idFacture+1;
    do {
        accept = true;i =0;
        printf("%s ",valid? "Entrer l'id du client :": "l'id saisi est inexistant ou incorrect:");
        scanf(" %d",&facture.idClient);
        //determination de l'index de l'objet dont l'id correspond à celui present dans la table des clients
        while (i<nbClients && facture.idClient!=clients[i].id)
            i++;
        if (i==nbClients)//si on dépasse la derniere case et que l'ona toujour rien trouvé, alors l'id est inconnu
            accept = false;
        valid = false;
    }while (!accept);//tant que l'id ne correspond pas à celui d'un client, on réitère
    valid = true;
    char dateStr[11];
    do {
        fflush(stdin);//on vide la memoire tempon et récupère la date sous le format YY-MM-DD
        printf("%s ",valid? "Saisir la date de la facture sous ce format YY-MM-DD :":"Format de date YY-MM-DD invalide :");
        fgets(dateStr,11,stdin);dateStr[strlen(dateStr)-1] = '\0';
        valid = false;
    }while (sscanf(dateStr,"%d-%d-%d", &facture.date.annee,&facture.date.mois,&facture.date.jour)!=3
        || facture.date.annee!=2025 || facture.date.mois<1 || facture.date.mois>12 ||
        facture.date.jour<1 || facture.date.jour>30);

    if (typeStr=='F')//Détermination du type en fonction du caratère passé en argument
        facture.type = FACTURE;
    else
        facture.type = DEVIS;
    facture.nombreContenu =0;
    printf("Ajout du contenu\n");
    do {
        valid =true;
        //Gestion de lq recherche : Demander s'il faut effectuer une recherche si oui par nom ou par prix
        printf("1. pour rechercher           autre. pour passer: ");
        scanf(" %d",&selection);
        if (selection==1) {
            do {
                printf ("1. Par nom            2. par montant : ");
                scanf (" %d",&selection);
                if (selection==2) {
                    printf("Entrer la somme a rechercher : ");
                    scanf(" %f",&somme);
                    triProduits(produits, nbProduits, NULL, somme);
                }
                if (selection==1) {
                    fflush(stdin);
                    printf("Entrer le nom du produit a rechercher : ");
                    fgets(name,15,stdin);name[strlen(name)-1]='\0';
                    triProduits(produits,nbProduits,name,0);
                }
            }while (selection!=2 && selection!=1);
        }
        //construction des éléments constitutifs de la factures
    do {
        i=0;
        accept = true;
        printf("%s ", valid ?"Saisir l'id du produit :":"id inexistant (id produit) :");
        scanf(" %d",&facture.contenu[facture.nombreContenu].id);
        while (i<nbProduits && facture.contenu[facture.nombreContenu].id!=produits[i].id)
            i++;
        if (i==nbProduits)
            accept = false;
        valid = false;
    }while (!accept);
    valid = true;
    if (produits[i].stock>0) {
        do {
            printf("%s ",valid? "Saisir le nombre :":"Nombre de prduit incorrect ou insuffisant :");
            scanf(" %d",&facture.contenu[facture.nombreContenu].nombre);
            valid = false;
        }while (facture.contenu[facture.nombreContenu].nombre <= 0 || facture.contenu[facture.nombreContenu].nombre>produits[i].stock);
    }
    if (facture.type==FACTURE)
        produits[i].stock -= facture.contenu[facture.nombreContenu].nombre;
    facture.contenu[facture.nombreContenu].prix = produits[i].prixUnitaireHT * (float)facture.contenu[facture.nombreContenu].nombre;
        facture.totalPrix+=facture.contenu[facture.nombreContenu].prix;
    facture.nombreContenu++;
        printf("\nVoulez-vous ajouter du contenu ? (1. OUI   autre. NON) :");
        scanf(" %d", &choix);
    }while (choix==1);
    return facture;
}
/*
 *cette fonction récupère les données obtenues des produits et mise à jour et les sauvegarde dans un fichier csv
 */
void sauvegarderProduits(Produit produits[], int nbProduit) {
    FILE *f =fopen("produits.csv","w");
    if (!f)
        printf("Erreur impossible d'ouvrir le fichier produits.csv en ecriture\n");
    else {
        fprintf(f,"id;nom;prix_unitaire;TVA;stock\n");
        for (int i=0;i<nbProduit;i++) {
            fprintf(f,"%d;%s;%.2f;%.2f;%d\n",produits[i].id,produits[i].nom,produits[i].prixUnitaireHT,
                produits[i].TVA,produits[i].stock);
        }
    }
    fclose(f);
}
/*
 *cette fonction récupère les données obtenues des factures et mise à jour et les sauvegarde dans un fichier csv
 */
void sauvegarderFactures(Facture factures[], int nbFacture) {
    FILE *f =fopen("factures.csv","w");
    if (!f)
        printf("Erruer impossible d'ouvrir le fichier factures.csv en ecriture\n");
    else {
        fprintf(f,"id_facture;id_client;date(YY-MM-DD);type;contenu(s);prix_total_operation\n");
        for (int i=0;i<nbFacture;i++) {
            fprintf(f,"%d;%d;%d-%d-%d;%s;",factures[i].idFacture,factures[i].idClient,
                factures[i].date.annee,factures[i].date.mois,factures[i].date.jour,factures[i].type==FACTURE?"FACTURE":"DEVIS");
            for (int j=0;j<factures[i].nombreContenu;j++)
                fprintf(f," %d-%d-%.2f",factures[i].contenu[j].id,factures[i].contenu[j].nombre,factures[i].contenu[j].prix);
            fprintf(f,";%.2f\n",factures[i].totalPrix);
        }
    }
    fclose(f);
}
/*
 *cette fonction récupère les données obtenues des clients et mise à jour et les sauvegarde dans un fichier csv
 */
void sauvegarderClients(Client clients[], int nbClient) {
    FILE *f =fopen("clients.csv","w");
    if (!f)
        printf("Erreur impossible d;ouvrir le fichier clients.csv en ecriture\n");
    else {
        fprintf(f,"id;nom;email\n");
        for (int i=0;i<nbClient;i++) {
            fprintf(f,"%d;%s;%s\n",clients[i].id,clients[i].nom,clients[i].email);
        }
    }
    fclose(f);
}
/*
 *Fonction de tris des produits
 */
void triProduits(Produit produit[], int nbProduit, char nom[], float prix) {
    int trouver =0;//nombre de résultats trouvés
    if (nom==NULL) {
        for (int i=0;i<nbProduit;i++) {
            if (prix>0 && prix<= produit[i].prixUnitaireHT) {//comparaison si les differents prix dans la table
                //des produits sont individuellement supérieurs au prix saisi
                trouver+=1;
                printf("%2d;%s;%.2f;%.2f;%d\n",produit[i].id,produit[i].nom,produit[i].prixUnitaireHT
                    ,produit[i].TVA,produit[i].stock);
            }
        }
        if (trouver==0)//si pas de résultat trouvé, message alertant
            printf("aucun resultat trouve pour %.2f\n", prix);
    }
    else {
        for (int i=0;i<nbProduit;i++) {
    //comparaison entre le nom saisi et les différents noms des produits en se fixant sur un même nombre de caractères
            if (strncmp(produit[i].nom, nom, strlen(nom))==0) {
                trouver+=1;
                printf("%2d;%s;%.2f;%.2f;%d\n",produit[i].id,produit[i].nom,produit[i].prixUnitaireHT
                     ,produit[i].TVA,produit[i].stock);
            }
        }
        if (trouver==0)//Si aucun résultat trouvé, message correspondant
            printf("aucun resultat trouve pour %s\n", nom);
    }
}