/* ////////////////////////////////////////////////////////////////
/	*TD1 : fichier Auteur.cpp                                     /
/	*travail fait par Jamesley Joseph: 1990552                    /
/					   Wael tarifi :  1991935                     /
/                                                                 /
/	*Date de remise : 28 janvier 2020 à 23h55                     /
/   * Description: Implementation de la classe Auteur             /
*//////////////////////////////////////////////////////////////////

#include <iostream>
#include "Auteur.h"


/****************************************************************************
 * Fonction: Auteur:Auteur
 * Description: Constructeur par parametre
 * Paramètres: - const std:: string& nom : nom de l'auteur
 *             - unsigned int anneeDeNaissane : annee de naissance de l'auteur
 * Retour: aucun
 ****************************************************************************/
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

/****************************************************************************
 * Fonction: Auteur:getNom
 * Description: Retourne le nom de l'auteur
 * Paramètres: aucun
 * Retour: (const string) le nom de l'auteur
 ****************************************************************************/
const std::string& Auteur::getNom() const 
{
    return nom_; 
}

/****************************************************************************
 * Fonction: Auteur:getAnneeDeNaissance
 * Description: Retourne l'annee de naissance de l'auteur
 * Paramètres: aucun
 * Retour: (unsigned int) l'annee de naissance de l'auteur
 ****************************************************************************/
unsigned int Auteur::getAnneeDeNaissance() const 
{  
   return anneeDeNaissance_; 
}

/****************************************************************************
 * Fonction: Auteur:getNbFilms
 * Description: Retourne le nombre de film de l'auteur
 * Paramètres: aucun
 * Retour: (unsigned int) le nombre de film de l'auteur
 ****************************************************************************/
unsigned int Auteur::getNbFilms()const 
{
    return nbFilms_;
}

/****************************************************************************
 * Fonction: Auteur:setNbFilms
 * Description: Modifie le nombre de film de l'auteur
 * Paramètres: unsigned int NbFilms: un nombre de film 
 * Retour: aucun
 ****************************************************************************/
void Auteur::setNbFilms(unsigned int nbFilms) 
{
    nbFilms_ = nbFilms; 
}