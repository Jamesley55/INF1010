
#include <iostream>
#include "Auteur.h"

//! Méthode Constructeur par paramètre qui utilise la liste d'initialisation.
//! \param  nom             Le nom de l'auteur.
//! \param anneeDeNaissance L'annee de naissance de l'auteur.
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance)
        : nom_(nom)
        , anneeDeNaissance_(anneeDeNaissance)
        , nbFilms_(0)
{}

//! Méthode qui affiche un auteur.
//! \param stream Le stream dans lequel afficher.
void Auteur::afficher(std::ostream& stream) const
{
    // Ne modifiez pas cette fonction
    stream << "Nom: " << nom_ << " | Date de naissance: " << anneeDeNaissance_
           << " | Nombre de films: " << nbFilms_;
}

//! Méthode qui récupère l'attribut privé nom_ de l'auteur.
//! \param aucun
//!\return Un const string& représentant le nom de l'auteur.
const std::string& Auteur::getNom() const 
{
    return nom_;
}

//! Méthode qui récupère l'attribut privé anneDeNaissance_ de l'auteur.
//! \param aucun
//!\return Un unsigned int représentant l'année de naissance de l'auteur.
unsigned int Auteur::getAnneeDeNaissance() const 
{
    return anneeDeNaissance_;
}

//! Méthode qui récupère l'attribut nbFilms_ de l'auteur.
//! \param aucun
//!\return Un unsigned int représentant le nombre de films de l'auteur.
unsigned int Auteur::getNbFilms () const 
{
    return nbFilms_;
}

//! Méthode qui assigne nbFilms à l'attribut privé nbFilms_.
//! \param nbFilms Un nombre de films de l'auteur.
void Auteur::setNbFilms (unsigned int nbFilms) 
{
    nbFilms_ = nbFilms;
}
