// TODO: Faire l'entête de fichier
/* ////////////////////////////////////////////////////////////////
/	*TD1 : fichier Auteur.cpp                                     /
/	*travail fait par Jamesley Joseph: 1990552                    /
/					   Wael tarifi :  1991935                     /
/                                                                 /
/	*Date de remise : 28 janvier 2020 à 23h55                     /
/   * Description: Implementation de la classe Auteur             /
*//////////////////////////////////////////////////////////////////

// TODO: Inclure la définition de la classe appropriée
#include <iostream>
#include "Auteur.h"

// TODO fait : Constructeur par paramètre en utilisant la liste d'initialisation
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance): 
nom_(nom), 
anneeDeNaissance_(anneeDeNaissance), 
nbFilms_(0)
{}


//! Méthode qui affiche un auteur.
//! \param stream Le stream dans lequel afficher.
void Auteur::afficher(std::ostream& stream) const
{
    // Ne modifiez pas cette fonction
    stream << "Nom: " << nom_ << " | Date de naissance: " << anneeDeNaissance_
           << " | Nombre de films: " << nbFilms_;
}

// TODO getNom() const: Retourner le nom
const std::string& Auteur::getNom() const 
{
    return nom_; 
}

// TODO getAnneeDeNaissance() const: Retourner l'annee de naissance
unsigned int Auteur::getAnneeDeNaissance() const 
{  
   return anneeDeNaissance_; 
}
// TODO getNbFilms() const: Retourner le nombre de films de l'auteur

unsigned int Auteur::getNbFilms()const 
{
    return nbFilms_;
}

// TODO setNbFilms(unsigned int nbFilms): Set le nombre de films de l'auteur
void Auteur::setNbFilms(unsigned int nbFilms) 
{
    nbFilms_ = nbFilms; 
}