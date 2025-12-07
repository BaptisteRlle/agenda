#ifndef AGENDA_HPP
#define AGENDA_HPP

#include <string>
#include <vector>

struct Date {
    int jour, mois, annee;
    int heure, minutes;
};

class Evenement {
public:
    std::string id;
    std::string titre;
    std::vector<std::string> description;
    Date debut, fin;
};

class Agenda {
private:
    std::string titre;
    std::vector<std::string> description;
    std::vector<Evenement> evenements;

public:
    Agenda();

    void modifier();
    void afficher() const;

    void ajouterEvenement();
    void supprimerEvenement();

    void exporterHTML() const;
    void enregistrer(const std::string& nomFichier) const;

    // JSON
    void exporterJSON(const std::string& nomFichier) const;
    bool importerJSON(const std::string& nomFichier);

private:
    bool dateValide(const Date& d) const;
    bool finApresDebut(const Date& d1, const Date& d2) const;
    std::string genererID(int len = 8) const;
};

#endif
