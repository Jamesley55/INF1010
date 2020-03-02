// To do
#include"GestionnaireSaisons.h"

// vider le vecteur saison
GestionnaireSaisons::~GestionnaireSaisons()
{
    saisons_.clear();
}

// ajoute une saison au Gestionnaire Saison 
//  si la saison existe deja on la rempace par la saison passer en parametre
GestionnaireSaisons& GestionnaireSaisons::operator+=(std::unique_ptr<Saison> saison)
{
    size_t indexSaison = trouverIndexSaison(saison->getNumSaison());
    if (indexSaison!= SAISON_INEXSISTANTE)
    {
        saisons_[indexSaison] = std::move(saisons_[saisons_.size() - 1]);
        saisons_.pop_back();
    }
    saisons_.push_back(std::move(saison));
    sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());
    return *this;

}

// retire la saison passer en parametre dans le vecteur de Saison
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
   size_t  indexSaison = trouverIndexSaison(numSaison);
    if (indexSaison != SAISON_INEXSISTANTE)
    {
        saisons_[indexSaison] = std::move(saisons_[saisons_.size() - 1]);
        saisons_.pop_back();
    }
    return *this;

}

// ajoute un episode a la saison dont le numero est passer en parametre
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
    size_t index = trouverIndexSaison(numSaison);
    if(index != SAISON_INEXSISTANTE){

        *(saisons_[index]) += std::move(episode); 
    }

}

// retirer une Episode dans le vecteur d'episode
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
    size_t index = trouverIndexSaison(numSaison); 

    if(index != SAISON_INEXSISTANTE){
        *(saisons_[index]) -= numEpisode; 
    }
}

/// trouve l'index d'une saison 
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
    for(size_t i = 0; i < saisons_.size();i++)
    {
        if(saisons_[i]->getNumSaison() == numSaison)
        {
            return i ;
        }
    }

    return SAISON_INEXSISTANTE; 

}

// return la saison passer en parametre 
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
  std::size_t  index = trouverIndexSaison(numSaison); 
  if(index == SAISON_INEXSISTANTE){
      return nullptr;
  }
  return saisons_[index].get(); 
}

// return le nombre de saison 
size_t GestionnaireSaisons::getNbSaisons() const
{
    return saisons_.size(); 
}


