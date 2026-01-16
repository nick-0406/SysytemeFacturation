#include "traitement.h"
#include <stdio.h>
#include <string.h>

#include "types.h"
/*
 *Lit un fichier produits.csv, enregistre toutes ses informations dans un tableau de produits
 * afin d'effectuer des traitements
 */
int chargerProduits(Produit produit[], int max) {
    FILE* f = fopen("produits.csv", "r");//ouverture du fichier
    if (!f)
        return 0;
    char ligne[TAILLE_LIGNE];
    fgets(ligne, 128, f);//sauter la ligne des entêtes
    int i =0;
    //vérification de la possibilité de lecture des données et de récupération des informations
    while (fgets(ligne, TAILLE_LIGNE, f) && i<max &&
      sscanf(ligne, "%d;%49[^;];%f;%f;%d", &produit[i].id, produit[i].nom
          , &produit[i].prixUnitaireHT, &produit[i].TVA, &produit[i].stock)) {
        i++;
    }
    fclose(f);
    return i;
}
/*
 *Lit un fichier produits.csv, enregistre toutes ses informations dans un tableau de clients
 * afin d'effectuer des traitements
 */
int chargerClients(Client client[], int max) {
    FILE* f = fopen("clients.csv", "r");
    if (!f)
        return 0;
    char ligne[TAILLE_LIGNE];
    fgets(ligne, TAILLE_LIGNE, f);//sauter la ligne des entêtes
    int i =0;
    //vérification de la possibilité de lecture des données et de récupération des informations
    while (fgets(ligne, TAILLE_LIGNE, f) && i<max &&
        sscanf(ligne, "%d;%49[^;];%49[^\n]", &client[i].id,client[i].nom, client[i].email)) {

        i++;
    }
    fclose(f);
    return i;
}
/*
 *Lit un fichier produits.csv, enregistre toutes ses informations dans un tableau de factures
 * afin d'effectuer des traitements
 */
int chargerFactures(Facture facture[], int max) {
    FILE* f = fopen("D://factures.csv", "r");
    if (!f)
        return 0;
    char ligne[TAILLE_LIGNE];
    fgets(ligne, TAILLE_LIGNE, f);//sauter la ligne des entêtes
    int i =0,len=0;
    char type[9], contenus[80],*p;
    /*
 *Lit un fichier produits.csv, enregistre toutes ses informations dans un tableau de factures
 * afin d'effectuer des traitements
 */
    while (fgets(ligne, TAILLE_LIGNE, f) && i<max &&
        sscanf(ligne, "%d;%d;%d-%d-%d;%7[^;];%79[^\n]", &facture[i].idFacture,&facture[i].idClient
            ,&facture[i].date.annee,&facture[i].date.mois,&facture[i].date.jour, type, contenus)) {
        //Récupération de la chaine de caractère la date suivi d'un test pour déterminer son type
        if (strcmp(type, "FACTURE")==0)
            facture[i].type = FACTURE;
        else
            facture[i].type = DEVIS;
        facture[i].nombreContenu =0;
        p =contenus;// pointeur de suppresion du début de "contenu" pour chaque lecture des données
        //la variable "contenus" contient les informations de completion d'une facture
        facture[i].totalPrix= 0;
        while (sscanf(p, "%d-%d-%f%n",&facture[i].contenu[facture[i].nombreContenu].id,
                &facture[i].contenu[facture[i].nombreContenu].nombre,
                &facture[i].contenu[facture[i].nombreContenu].prix,&len)==3){
            facture[i].totalPrix+=facture[i].contenu[facture[i].nombreContenu].prix;
            facture[i].nombreContenu++;
    //tant que la lecture est possible, on récupère les informations nécéssaires via sscanf et on supprime
            p+=len;//le nombre de caractères qui ont été utilisées pour la précedente lecture.
        }
        i++;
    }
    fclose(f);//fermeture du fichier
    return i;
}
void imprimerFactures(Facture facture) {
    //test pour créer un ficheir avec un nom de fichier correspondant à son type (facture/devis)
    FILE*f;
    if (facture.type==FACTURE) {
        f = fopen("facture.csv", "w");
    if (!f) {
        printf("Erreur d'ouverture de facture.csv\n");
        return;
    }
    }
    else {
        f = fopen("devis.csv", "w");
        if (!f) {
            printf("Erreur d'ouverture de devis.csv\n");
            return;
        }
    }
// Affichage de tous les details du fichier. EN_COURS pour un devis, et PAYEE pour une facture
    fprintf(f,"Format : %c%d-%s%d                      Statut : %s                \n",facture.type==FACTURE?'F':'D',
        facture.date.annee,facture.idFacture<10 ?"00":"",facture.idFacture ,facture.type==FACTURE? "PAYEE":"EN_COURS");
    fprintf(f,"id_facture : %d     id_client : %d   Date : %d-%d-%d\n",facture.idFacture
        ,facture.idClient, facture.date.annee, facture.date.mois,facture.date.jour);
    fprintf(f,"id produit  nombre  montant \n");
    for (int i = 0; i < facture.nombreContenu; i++)
        fprintf(f,"%2d             %2d       %.2f\n",facture.contenu[i].id,facture.contenu[i].nombre,
            facture.contenu[i].prix);
    fprintf(f,"montant total : %.2f\n",facture.totalPrix);
    fclose(f);
}