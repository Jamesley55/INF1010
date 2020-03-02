// To do
#include"Episode.h"
// To do

// constructeur par default 
Episode::Episode()
// To do
{
    nom_ = "";
    duree_ = "";
    numEpisode_ = 0; 
}

// constructeur par parametre
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree)
// To do
{
    numEpisode_ = numEpisode; 
    nom_ = nom;
    duree_= duree; 
}

// operateur == return true si les numero passer en parrametre
// est egale au numEpisode de l'attribut qu'on veut surcharger
bool Episode::operator==(unsigned int numEpisode)
{
    if(numEpisode_ == numEpisode)   return true;

    return false; 
}


bool operator==(unsigned int numEpisode, const Episode& episode)
{
    if (episode.numEpisode_ == numEpisode)
    {
        return true;
    }
    return false;
}

// affiche tout les attributs de l'episode en cascade 
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
   os << episode.duree_ << "" << episode.nom_ << "" << episode.numEpisode_;
   return os; 

}

// assigne des valeur au attribut de l'episode 
std::istream& operator>>(std::istream& is, Episode& episode)
{
     is >> quoted(episode.duree_) >> quoted(episode.nom_) >> episode.numEpisode_;
     return is ; 
}

// return le nombre d'episode 
unsigned int Episode::getNumEpisode() const
{
  return numEpisode_; 
}