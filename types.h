#ifndef TYPES_H
#define TYPES_H
//énumération pour le type (facture/devis)
typedef enum {
    DEVIS,
    FACTURE
} TypeFacture;
//structures utiles
typedef struct {
    int id;
    int nombre;
    float prix;
}ContenuFacture;

typedef struct {
    int jour;
    int mois;
    int annee;
}Date;

typedef struct {
   int idFacture;
    int idClient;
    Date date;
    TypeFacture type;
    int nombreContenu;
    ContenuFacture contenu[10];
    float totalPrix;
}Facture;

typedef struct {
    int id;
    char nom[50];
    char email[50];
}Client;

typedef struct {
    int id;
    char nom[50];
    int stock;
    float prixUnitaireHT;
    float TVA;
}Produit;
//mes constantes
#define MAX_FACTURES 1000
#define MAX_CLIENTS 50
#define MAX_PRODUITS 100
#define TAILLE_LIGNE 128

#endif