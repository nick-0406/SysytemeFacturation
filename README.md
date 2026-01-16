# Système de facturation – Programmation modulaire en C

## 1. Présentation générale

Ce projet implémente un système de facturation en langage **C**, reposant sur la **programmation modulaire** et l’exploitation de **fichiers CSV**.  
Il permet la gestion des clients, des produits, des devis et des factures, avec calcul automatique des montants et mise à jour des stocks.

Les données sont persistées exclusivement via des fichiers CSV afin de simuler un système de gestion simple et autonome.

---

## 2. Fichiers CSV utilisés

### Clients
Format :
id;nom;email

shell
Copier le code

### Produits
Format :
id;nom;stock;prix_unitaire;TVA

shell
Copier le code

### Factures (registre global)
Format :
id_facture;id_client;date;type;contenus;total

go
Copier le code

Le champ `contenus` correspond à une liste d’éléments de la forme :
id_produit-nombre-prix

yaml
Copier le code
séparés par des espaces.

---

## 3. Création d’un devis ou d’une facture

Lors de la création d’un devis ou d’une facture :

- Les informations sont immédiatement ajoutées au fichier `factures.csv`
- Un numéro de facture est généré automatiquement
- Un fichier CSV dédié est créé pour le document généré

Nom du fichier :
- `devis.csv` pour un devis
- `facture.csv` pour une facture

Ce fichier contient le détail complet du document, incluant :
- les informations du client
- la date
- la liste détaillée des produits
- les montants calculés
- le statut du document

---

## 4. Gestion du statut

Chaque devis ou facture possède un champ **statut** permettant de suivre son état :

- `EN_COURS`
- `PAYEE`

Ce statut est associé au numéro de facture généré et permet un suivi clair des opérations.

---

## 5. Structure modulaire du code

Le projet est organisé en modules indépendants :

- **client** : gestion et recherche des clients
- **produit** : gestion des produits, des stocks et des prix
- **facture** : création, calcul et sauvegarde des devis et factures
- **utilitaire** : validation des entrées et fonctions communes
- **main** : gestion du menu et orchestration globale

Chaque module dispose de son fichier `.c` et `.h` afin d’assurer une séparation claire des responsabilités.

---

## 6. Fonctionnement global

1. Chargement des données depuis les fichiers CSV  
2. Interaction utilisateur pour la création d’un devis ou d’une facture  
3. Calcul des montants et application de la TVA  
4. Mise à jour automatique des stocks pour les factures  
5. Sauvegarde immédiate des données et génération du fichier associé  

---

## 7. Objectifs du projet

- Appliquer la programmation modulaire en C
- Manipuler des fichiers CSV de manière robuste
- Gérer des structures de données imbriquées
- Simuler un système réel de facturation commerciale
