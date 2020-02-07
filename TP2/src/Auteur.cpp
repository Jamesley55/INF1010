#include "Auteur.h"
#include <iostream>

//! Constructeur de la classe Auteur
//! \param nom              Nom de l'auteur
//! \param anneeDeNaissance Année de naissance de l'auteur
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance)
    : nom_(nom)
    , anneeDeNaissance_(anneeDeNaissance)
    , nbFilms_(0)
{
}

//! Méthode qui affiche un auteur
//! \param stream Le stream dans lequel afficher
std::ostream& operator<<(std::ostream &o ,const Auteur &auteur)
{
    return o << "Nom: " << auteur.nom_<< " | Date de naissance: " << auteur.anneeDeNaissance_
           << " | Nombre de films: " << auteur.nbFilms_;
}

bool Auteur::operator==(const std::string &motComparer) const{
   if(this->nom_ == motComparer) return true; 
   return false; 
}
bool operator==( const std::string & motComparer, Auteur & newAuteur) {
    if(newAuteur.getNom() == motComparer) return true; 
    return false; 
}
//! Méthode qui retourne le nom de l'auteur
//! \return Le nom de l'auteur
const std::string& Auteur::getNom() const
{
    return nom_;
}

//! Méthode qui retourne l'année de naissance de l'auteur
//! \return L'année de naissance de l'auteur
unsigned int Auteur::getAnneeDeNaissance() const
{
    return anneeDeNaissance_;
}

//! Méthode qui retourne le nombre de films de l'auteur
//! \return Le nombre de films de l'auteur
unsigned int Auteur::getNbFilms() const
{
    return nbFilms_;
}

//! Méthode qui set le nombre de films de l'auteur
//! \param nbFilms  Le nombre de films de l'auteur
void Auteur::setNbFilms(unsigned int nbFilms)
{
    nbFilms_ = nbFilms;
}