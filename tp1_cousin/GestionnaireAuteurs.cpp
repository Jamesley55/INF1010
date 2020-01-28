
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "GestionnaireAuteurs.h"

//! Méthode Constructeur par défaut qui initialise le nombre d'auteurs à 0.
GestionnaireAuteurs::GestionnaireAuteurs()
    :nbAuteurs_(0)
{} 
        
//! Méthode qui ajoute un Auteur à la liste des Auteurs.
//! \param  Auteur L'objet Auteur passé par référence constante.
//! \return        Un bool représentant si l'ajout à la liste a été un succès.
bool GestionnaireAuteurs::ajouterAuteur(const Auteur& auteur) {
    if (nbAuteurs_ < NB_AUTEURS_MAX) 
    {
        auteurs_[nbAuteurs_] = auteur;
        nbAuteurs_++;
        return true;
    }
    return false;
}

//! Méthode qui cherche dans la liste des auteurs un auteur comportant le nom passé en paramètre.
//! \param nomAuteur Le nom de l'auteur passé par référence constante.
//! \return          Un pointeur vers un objet auteur ou un nullptr si l'auteur n'existe pas.
Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur) {
    for (std::size_t i = 0; i < nbAuteurs_; i++)
    {
        if ((auteurs_[i].getNom()) == nomAuteur) 
        {
            return &(auteurs_[i]);
        }
    }
    return nullptr;
}

//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs.
//! \param nomFichier   Le nom du fichier à charger.
//! \return             Un bool représentant si le chargement a été un succès.
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    std::istringstream stream;
    std::string ligne;
    if (fichier)
    {
        // TODO: envoyer chaque ligne à lireLigneAuteur
        while (getline(fichier, ligne)) 
        {
            if (!lireLigneAuteur(ligne))
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui affiche la liste des auteurs.
//! \param stream Le stream dans lequel afficher.
void GestionnaireAuteurs::afficher(std::ostream& stream) const
{
    // Ne pas modifier cette méthode
    for (std::size_t i = 0; i < nbAuteurs_; i++)
    {
        auteurs_[i].afficher(stream);
        stream << '\n';
    }
}

//! Méthode qui récupère l'attribut privé nbAuteurs_ de la liste d'auteurs.
//! \param aucun
//!\return Un size_t représentant le nombre d'auteurs dans la liste d'auteurs.
std::size_t GestionnaireAuteurs::getNbAuteurs() const
{
    return nbAuteurs_;
}

//! Méthode qui ajoute un auteur avec un string.
//! \param ligne Le string qui comporte tous les attributs de l'auteur.
//! \return      un bool représentant si la lecture a été un succès.
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nom;
    unsigned int age;

    if (stream >> std::quoted(nom) >> age)
    {
        Auteur auteur(nom, age);
        return ajouterAuteur(auteur);
    }
    return false;
}
