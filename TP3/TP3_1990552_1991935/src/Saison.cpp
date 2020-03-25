/**************************************************
 * Titre: TP3 - Saison.cpp
 * Date: 1 mars 2020
 * Auteurs: Jamesley Joseph, Wael Tarifi
 **************************************************/
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
        episodes_.push_back(std::make_unique<Episode>(*saison.episodes_[i]));

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
    size_t indexEpisode = trouverIndexEpisode(episode->getNumEpisode());
    if (indexEpisode != EPISODE_INEXSISTANTE)
    {
        episodes_[indexEpisode] = std::move(episodes_[episodes_.size() - 1]);
        episodes_.pop_back();
    }
    episodes_.push_back(std::move(episode));
    sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
    return *this;

}

//  retire un episode du vecteur episode 
Saison& Saison::operator-=(unsigned int numEpisode)
{
    size_t  indexEpisode = trouverIndexEpisode(numEpisode);
    if (indexEpisode != EPISODE_INEXSISTANTE)
    {
        episodes_[indexEpisode] = std::move(episodes_[episodes_.size() - 1]);
        episodes_.pop_back();
    }
    return *this;

}

// Surcharge de l'opérateur == qui compare le numéro en paramètre au numéro des épisodes
bool Saison::operator==(unsigned int numSaison)
{
    return (numSaison_ == numSaison); 
}

// Surcharge de l'opérateur == qui permet de compare le numéro en paramètre au numéro des épisodes
bool operator==(unsigned int numSaison, const Saison& saison)
{
  return (saison.numSaison_ == numSaison);

}


// affiche tout les attributs de la saison  et tout les episode a l'interieur du vector  episodes_
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
    std::string etatSaison;
    std::string stringSaison;

    //uniformisation de l'affichage 
    if (saison.episodes_.size() == saison.nbEpisodesmax_){
        etatSaison = "(Terminer)";
    }
    else {
        etatSaison = "(Encour)";
    }
    if (saison.numSaison_ < 10)  {
        stringSaison= "Saison0";
    }
    else{
        stringSaison = "Saison";
    }
    os << stringSaison << saison.numSaison_ << ":" << saison.episodes_.size() << "/"
       << saison.nbEpisodesmax_ << etatSaison << std::endl;
    for (size_t i = 0; i < saison.episodes_.size(); i++)
    {
        os << "\t\t" << *(saison.episodes_[i]) << std::endl;
    }
    return os; 
}   

// initialiser tout les atributs de la classe saison
std::istream& operator>>(std::istream& is, Saison& saison)
{
   is >> saison.numSaison_>> saison.nbEpisodesmax_;  
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
   return episodes_.size();
}

 // trouve l'index d'une episode dans une saison
size_t Saison::trouverIndexEpisode(unsigned int numEpisode) 
{

    for(size_t  i= 0; i < episodes_.size(); i++)
    {
        if(numEpisode == episodes_[i]->getNumEpisode()){ 
            return i ;
        }
    }
    return EPISODE_INEXSISTANTE ; 
}