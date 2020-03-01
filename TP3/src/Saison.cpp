// To do
#include"Saison.h"


// constructeur par default 
Saison::Saison():
numSaison_(0),
nbEpisodesmax_(0)
{
}

// constructeur par parametre
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax):
numSaison_(numSaison),
nbEpisodesmax_(nbEpisodemax)
{
}

// cree une copie de l'objet passer en parametre 
Saison::Saison(const Saison& saison):
numSaison_(saison.numSaison_),
nbEpisodesmax_(saison.nbEpisodesmax_)
{
     episodes_.clear();
    for (unsigned int i = 0; i < saison.episodes_.size(); i++)
    {
        auto ptrEpisode = std::make_unique<Episode>(*(saison.episodes_[i]));
        episodes_.push_back(std::move(ptrEpisode));
    }
}


// vide le vecteur episode
Saison::~Saison()
{
    episodes_.clear();
}

// rajoute un episode dans le vecteur d'episode si il n'existe pas deja
// si il existe deja on supprime le derniere element et on rajoute le plus recent
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
    sort(episodes_.begin(),episodes_.end(), Episode::SortByNumEpisode());
    unsigned int  index = episode->getNumEpisode();
    size_t indexEpisode = trouverIndexEpisode(index);
    if(indexEpisode != EPISODE_INEXSISTANTE){ 
        episodes_.push_back(std::move(episode)); 
    }
    else {
        episodes_.erase(episodes_.begin()+ index); 
        episodes_.push_back(std::move(episode));
    }
    return *this;
}

//  retire un episode du vecteur episode 
Saison& Saison::operator-=(unsigned int numEpisode)
{
   size_t index = trouverIndexEpisode(numEpisode);
   episodes_.erase(episodes_.begin()+index);
   return *this;
}

// return true si le numero passer en parametre est egale 
// au numSaison de l'objet qu'on veut surcharger 
bool Saison::operator==(unsigned int numSaison)
{
    if(numSaison_ == numSaison) return true; 
    return false;
}

bool operator==(unsigned int numSaison, const Saison& saison)
{
    if (saison.numSaison_ == numSaison)
    {
        return true;
    }
    return false;
}


// affiche tout les attribu de la saison  et tout les episode a l'interieur du vector  episodes_
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
     os << saison.nbEpisodesmax_ << ""<< saison.numSaison_;
     for(size_t i = 0; i < saison.episodes_.size(); i++)
     {
         os << saison.episodes_[i].get();
     }
     return os; 
}   

// initialiser out les atributs de la classe saison
std::istream& operator>>(std::istream& is, Saison& saison)
{
   is >> saison.nbEpisodesmax_ >> saison.numSaison_; 
   for(size_t i =0; i < saison.episodes_.size(); i++)
   {
       is >> *saison.episodes_[i].get();
   }
    
    return is;
}

// retourne le nombre de saison
unsigned int Saison::getNumSaison() const
{
    return numSaison_;
}

// retourne de nombre d'episode dans la saison
size_t Saison::getNbEpisodes() const
{
   return nbEpisodesmax_;
}

 // trouve l'index d'une episode dans une saison
size_t Saison::trouverIndexEpisode(unsigned int numEpisode) 
{

    for(size_t  i= 0; i < this->episodes_.size(); i++)
    {
        if(numEpisode == this->episodes_[i]->getNumEpisode()) return i ;
    }
    return -1 ; 
}