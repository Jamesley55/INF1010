/**************************************************
 * Titre: TP3 - Episode.cpp
 * Date: 1 mars 2020
 * Auteurs: Jamesley Joseph, Wael Tarifi
 **************************************************/

#include"Episode.h"


// constructeur par default 
Episode::Episode()
{
    nom_ = "";
    duree_ = "";
    numEpisode_ = 0; 
}

// constructeur par parametre
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree)
{
    numEpisode_ = numEpisode; 
    nom_ = nom;
    duree_= duree; 
}

// Surcharge de l'operateur == retourne true si les numero passer en parrametre
// est egale au numEpisode de l'attribut qu'on veut surcharger
bool Episode::operator==(unsigned int numEpisode)
{
    if(numEpisode_ == numEpisode){
        return true;
    }

    return false; 
}

// Surcharge de l'opérateur == qui permet d'inver les positions de l'entier et de l'épisode 
bool operator==(unsigned int numEpisode, const Episode& episode)
{
    if (episode.numEpisode_ == numEpisode){
        return true;
    }
    return false;
}

// Surcharge de l'opérateur << permettant d'afficher tous les attributs de l'épisode
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
   std::string stringEpisode;
    // uniformisation de  l'affichage
    if (episode.numEpisode_ < 10)
    {
        stringEpisode = "Episode0";
    }
    else
    {
        stringEpisode = "Episode";
    }
    os << stringEpisode << episode.numEpisode_ << ":" << episode.nom_ << "|Duree: " << episode.duree_;

    return os;

}

// Surcharge de l'operateur >> 
// L’opérateur permet d’initialiser tous les attributs de la classe auteur
std::istream& operator>>(std::istream& is, Episode& episode)
{
    is >> episode.numEpisode_ >> std::quoted(episode.nom_) >> std::quoted(episode.duree_);
    return is ; 
}

// Methode qui return le nombre d'episode 
unsigned int Episode::getNumEpisode() const
{
  return numEpisode_; 
}