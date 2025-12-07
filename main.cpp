#include <iostream>
#include "agenda.hpp"

using namespace std;

int main() {
    Agenda agenda;
    string choix, fichier;

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "F01 - Modifier l'agenda\n";
        cout << "F02 - Afficher\n";
        cout << "F03 - Ajouter un événement\n";
        cout << "F04 - Supprimer un événement\n";
        cout << "F05 - Exporter en HTML\n";
        cout << "F06 - Enregistrer TXT\n";
        cout << "F07 - Exporter JSON\n";
        cout << "F08 - Importer JSON\n";
        cout << "F09 - Quitter\n";
        cout << "Choix : ";
        cin >> choix;

        if (choix == "F01") agenda.modifier();
        else if (choix == "F02") agenda.afficher();
        else if (choix == "F03") agenda.ajouterEvenement();
        else if (choix == "F04") agenda.supprimerEvenement();
        else if (choix == "F05") agenda.exporterHTML();
        else if (choix == "F06") {
            cout << "Nom fichier : ";
            cin >> fichier;
            agenda.enregistrer(fichier);
        }
        else if (choix == "F07") {
            cout << "Nom fichier JSON : ";
            cin >> fichier;
            agenda.exporterJSON(fichier);
        }
        else if (choix == "F08") {
            cout << "Nom fichier JSON : ";
            cin >> fichier;
            agenda.importerJSON(fichier);
        }
        else if (choix == "F09") break;
        else cout << "Option invalide.\n";
    }

    return 0;
}
