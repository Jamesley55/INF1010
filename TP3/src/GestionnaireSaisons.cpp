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
    sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());
    size_t index = saison->getNumSaison();
    if(trouverIndexSaison(index)== SAISON_INEXSISTANTE) saisons_.push_back(std::move(saison));
    else saisons_.erase(saisons_.begin +index); saisons_.push_back(std::move(saison));

    return *this; 
}

// retire la saison passer en parametre dans le vecteur de Saison
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
    size_t  index = trouverIndexSaison(numSaison);
    saisons_.erase(saisons_.begin()+index);
    return *this;
}

// ajoute un episode a la saison dont le numero est passer en parametre
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
    size_t index = trouverIndexSaison(numSaison);
    saisons_;  
   // std::unique_ptr<Saison> sainsonEP = dynamic_cast<Episode>(std::move(episode));  
}

// To do
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
    
}

/// To do
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
    for(size_t i =0; i < saisons_.size();i++)
    {
        if(numSaison == this->saisons_[i]->getNumSaison())
        {
            return i ;
        }
    }
    return -1; 

}

// To do
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
   return  saisons_[numSaison].get();
    
}

// To do
size_t GestionnaireSaisons::getNbSaisons() const
{
    return saisons_.size(); 
}
