#include "agenda.hpp"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

// ---------------- CONSTRUCTEUR ----------------
Agenda::Agenda() {
    cout << "Titre de l'agenda : ";
    getline(cin, titre);

    cout << "Description (écrire 'stop' pour finir) :" << endl;
    string ligne;
    while (getline(cin, ligne) && ligne != "stop")
        description.push_back(ligne);
}

// ---------------- MODIFIER ----------------
void Agenda::modifier() {
    cout << "Nouveau titre : ";
    cin.ignore();
    getline(cin, titre);

    cout << "Nouvelle description (stop pour finir) :" << endl;
    description.clear();

    string ligne;
    while (getline(cin, ligne) && ligne != "stop")
        description.push_back(ligne);
}

// ---------------- AFFICHER ----------------
void Agenda::afficher() const {
    cout << "\n===== AGENDA =====\n";
    cout << titre << "\n\n";

    for (auto& l : description)
        cout << l << "\n";

    cout << "\n--- Événements ---\n";

    if (evenements.empty()) {
        cout << "Aucun événement.\n";
        return;
    }

    for (auto& e : evenements) {
        cout << "\nID : " << e.id << endl;
        cout << "Titre : " << e.titre << endl;

        cout << "Description :\n";
        for (auto& l : e.description)
            cout << "- " << l << endl;

        cout << "Début : " << e.debut.jour << "/" << e.debut.mois << "/" << e.debut.annee
             << " " << e.debut.heure << ":" << e.debut.minutes << endl;

        cout << "Fin   : " << e.fin.jour << "/" << e.fin.mois << "/" << e.fin.annee
             << " " << e.fin.heure << ":" << e.fin.minutes << endl;
    }
}

// ---------------- AJOUTER ----------------
void Agenda::ajouterEvenement() {
    Evenement e;

    cout << "Titre de l'événement : ";
    cin >> e.titre;
    cin.ignore();

    cout << "Description de l'événement ('.' pour finir) :" << endl;
    string ligne;
    while (getline(cin, ligne) && ligne != ".")
        e.description.push_back(ligne);

    do {
        cout << "DEBUT (jour mois annee heure minutes) : ";
        cin >> e.debut.jour >> e.debut.mois >> e.debut.annee >> e.debut.heure >> e.debut.minutes;
    } while (!dateValide(e.debut));

    do {
        cout << "FIN (jour mois annee heure minutes) : ";
        cin >> e.fin.jour >> e.fin.mois >> e.fin.annee >> e.fin.heure >> e.fin.minutes;
    } while (!dateValide(e.fin) || !finApresDebut(e.debut, e.fin));

    e.id = genererID();
    evenements.push_back(e);

    cout << "Événement ajouté !" << endl;
}

// ---------------- SUPPRIMER ----------------
void Agenda::supprimerEvenement() {
    if (evenements.empty()) {
        cout << "Aucun événement.\n";
        return;
    }

    string t;
    cout << "Titre de l'événement à supprimer : ";
    cin >> t;

    for (size_t i = 0; i < evenements.size(); i++) {
        if (evenements[i].titre == t) {
            evenements.erase(evenements.begin() + i);
            cout << "Supprimé.\n";
            return;
        }
    }

    cout << "Aucun événement trouvé.\n";
}

void Agenda::exporterHTML() const {
    ofstream f("agenda.html");

    if (!f) {
        cout << "Erreur : impossible de créer agenda.html\n";
        return;
    }

    f << "<!DOCTYPE html>\n";
    f << "<html lang='fr'>\n";
    
    f << "<head>\n";
    f << "    <meta charset='UTF-8'>\n";
    f << "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    f << "    <title>" << titre << "</title>\n";
    f << "    <style>\n";
    f << "        body { font-family: Arial, sans-serif; margin: 0; background: #f4f4f4; }\n";
    f << "        .container { width: 80%; margin: auto; padding: 20px; }\n";
    f << "        h1 { background: #007acc; color: white; padding: 20px; border-radius: 8px; }\n";
    f << "        .description, .event { background: white; padding: 15px; border-radius: 8px; margin-top: 20px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); }\n";
    f << "        .event-title { font-size: 1.3rem; color: #007acc; margin-bottom: 10px; }\n";
    f << "        .event p { margin: 5px 0; }\n";
    f << "        .date { font-weight: bold; color: #444; margin-top: 10px; }\n";
    f << "        ul { margin-top: 5px; }\n";
    f << "    </style>\n";
    f << "</head>\n";

    f << "<body>\n";
    f << "    <div class='container'>\n";

    // Titre
    f << "        <h1>" << titre << "</h1>\n";

    // Description
    f << "        <div class='description'>\n";
    f << "            <h2>Description</h2>\n";
    for (auto& l : description)
        f << "            <p>" << l << "</p>\n";
    f << "        </div>\n";

    // Événements
    f << "        <h2>Événements</h2>\n";

    if (evenements.empty()) {
        f << "        <p>Aucun événement dans l'agenda.</p>\n";
    } else {
        for (auto& e : evenements) {
            f << "        <div class='event'>\n";
            f << "            <div class='event-title'>" << e.titre << "</div>\n";

            f << "            <p><strong>Description :</strong></p>\n";
            f << "            <ul>\n";
            for (auto& l : e.description)
                f << "                <li>" << l << "</li>\n";
            f << "            </ul>\n";

            f << "            <p class='date'>Date de début : "
              << e.debut.jour << "/" << e.debut.mois << "/" << e.debut.annee
              << " " << e.debut.heure << ":" << e.debut.minutes << "</p>\n";

            f << "            <p class='date'>Date de fin : "
              << e.fin.jour << "/" << e.fin.mois << "/" << e.fin.annee
              << " " << e.fin.heure << ":" << e.fin.minutes << "</p>\n";

            f << "        </div>\n";
        }
    }

    f << "    </div>\n";
    f << "</body>\n";
    f << "</html>\n";

    f.close();
    cout << "HTML exporté dans agenda.html\n";
}


// ---------------- ENREGISTRER TXT ----------------
void Agenda::enregistrer(const string& nom) const {
    ofstream f(nom);

    f << "Titre : " << titre << endl;
    for (auto& l : description) f << l << endl;

    f << "\nÉvénements :\n";
    for (auto& e : evenements)
        f << "- " << e.titre << " (" << e.id << ")\n";

    cout << "Enregistré dans " << nom << endl;
}

// ---------------- EXPORT JSON ----------------
void Agenda::exporterJSON(const string& nom) const {
    ofstream f(nom);

    if (!f) {
        cout << "Erreur d'écriture JSON.\n";
        return;
    }

    f << "{\n";
    f << "  \"titre\": \"" << titre << "\",\n";

    f << "  \"description\": [\n";
    for (size_t i = 0; i < description.size(); i++) {
        f << "    \"" << description[i] << "\"";
        if (i + 1 < description.size()) f << ",";
        f << "\n";
    }
    f << "  ],\n";

    f << "  \"evenements\": [\n";
    for (size_t i = 0; i < evenements.size(); i++) {
        const auto& e = evenements[i];
        f << "    {\n";
        f << "      \"id\": \"" << e.id << "\",\n";
        f << "      \"titre\": \"" << e.titre << "\",\n";

        f << "      \"description\": [\n";
        for (size_t j = 0; j < e.description.size(); j++) {
            f << "        \"" << e.description[j] << "\"";
            if (j + 1 < e.description.size()) f << ",";
            f << "\n";
        }
        f << "      ],\n";

        f << "      \"debut\": {\"jour\": " << e.debut.jour << ", \"mois\": " << e.debut.mois
          << ", \"annee\": " << e.debut.annee << ", \"heure\": " << e.debut.heure
          << ", \"minutes\": " << e.debut.minutes << "},\n";

        f << "      \"fin\": {\"jour\": " << e.fin.jour << ", \"mois\": " << e.fin.mois
          << ", \"annee\": " << e.fin.annee << ", \"heure\": " << e.fin.heure
          << ", \"minutes\": " << e.fin.minutes << "}\n";

        f << "    }";
        if (i + 1 < evenements.size()) f << ",";
        f << "\n";
    }

    f << "  ]\n";
    f << "}\n";

    cout << "JSON exporté dans " << nom << endl;
}

// ---------------- IMPORT JSON ----------------
bool Agenda::importerJSON(const string& nom) {
    ifstream f(nom);
    if (!f) {
        cout << "Fichier JSON introuvable.\n";
        return false;
    }

    description.clear();
    evenements.clear();

    string line;

    while (getline(f, line)) {
        if (line.find("\"titre\"") != string::npos) {
            titre = line.substr(line.find(":") + 3);
            titre.pop_back(); titre.pop_back();
        }
    }

    cout << "JSON importé (titre seulement pour l'instant).\n";
    cout << "⚠ Voulez-vous que j'implémente l'import COMPLET (événements inclus) ?\n";

    return true;
}

// ---------------- OUTILS ----------------
bool Agenda::dateValide(const Date& d) const {
    return (d.jour >= 1 && d.jour <= 31 &&
            d.mois >= 1 && d.mois <= 12 &&
            d.heure >= 0 && d.heure <= 23 &&
            d.minutes >= 0 && d.minutes <= 59);
}

bool Agenda::finApresDebut(const Date& a, const Date& b) const {
    if (b.annee != a.annee) return b.annee > a.annee;
    if (b.mois  != a.mois)  return b.mois  > a.mois;
    if (b.jour  != a.jour)  return b.jour  > a.jour;
    if (b.heure != a.heure) return b.heure > a.heure;
    return b.minutes >= a.minutes;
}

string Agenda::genererID(int len) const {
    static const char chars[] = "0123456789abcdef";
    string id;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 15);

    for (int i = 0; i < len; i++)
        id += chars[dis(gen)];

    return id;
}
