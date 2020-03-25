/**************************************************
 * Titre: TP3 - Film.cpp
 * Date: 1 mars 2020
 * Auteurs: Jamesley Joseph, Wael Tarifi
 **************************************************/

#include "Film.h"

// constructeur par defaut de la classe film
Film::Film(Auteur *auteur) : Media(auteur, Media::TypeMedia::Film),
                             duree_("")
{
    auteur->setNbMedias(auteur->getNbMedias() + 1);
}

// constructeur par parametre de la classe film
Film::Film(const std::string &nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur *auteur, const std::string &duree) : Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia::Film),
                                                                                duree_(duree)
{
}

// Méthode qui affiche tous les attributs de Film
std::ostream &Film::afficher(std::ostream &os) const
{
    Media::afficher(os);
    os << "/tDuree: " << duree_;
    return os;
}

// To do
std::istream &Film::lire(std::istream &is)
{
    Media::lire(is);
    is >> std::quoted(duree_);
    return is;
}

// Méthode qui permet de créer une copie de l'objet courant
std::unique_ptr<Media> Film::clone() const
{
    return std::make_unique<Media>(*this);
}
