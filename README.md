# Projet Agenda en C++

Ce projet est une application console en C++ permettant de gérer un
agenda avec titre, description et événements.\
Il inclut plusieurs fonctionnalités comme l'ajout, la suppression,
l'export et l'import de données.\
Ce programme a été développé dans le cadre d'un projet pédagogique en
BUT Informatique.

## 1. Fonctionnalités du programme

### Gestion de l'agenda

-   Création d'un agenda avec titre et description
-   Modification du titre et de la description
-   Affichage de l'agenda et de ses événements

### Gestion des événements

-   Ajout d'un événement
    -   Titre
    -   Description multiligne
    -   Date et heure de début
    -   Date et heure de fin
    -   Vérification de cohérence entre les dates
    -   Identifiant unique généré automatiquement
-   Suppression d'un événement par titre

### Sauvegarde et export

-   Enregistrement dans un fichier texte (.txt)
-   Exportation en HTML (agenda.html)
-   Exportation en JSON (.json)
-   Importation (partielle) d'un fichier JSON

### Contrôles intégrés

-   Validation des dates
-   Vérification fin \> début
-   Gestion d'erreurs de saisie



## 2. Structure du projet

agenda/ 
├── agenda.hpp 
├── agenda.cpp 
├── main.cpp 
└── README.md

## 3. Compilation

g++ -Wall main.cpp agenda.cpp -o agenda

## 4. Exécution

./agenda

## 5. Menu du programme

F01 - Modifier l'agenda 
F02 - Afficher 
F03 - Ajouter un événement 
F04 - Supprimer un événement 
F05 - Exporter HTML 
F06 - Enregistrer TXT
F07 - Exporter JSON 
F08 - Importer JSON 
F09 - Quitter


