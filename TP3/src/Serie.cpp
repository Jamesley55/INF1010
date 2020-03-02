// To do
#include"Serie.h"

// constructeur par defaut de la classe Serie
Serie::Serie(Auteur* auteur):
Media(auteur, Media::TypeMedia::Serie),
GestionnaireSaisons()
{    
     auteur->setNbMedias(auteur->getNbMedias() + 1);

}

// constructeur par parametre de la classe Serie
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur):
Media(nom,anneeDeSortie,genre, pays, estRestreintParAge, auteur, Media::TypeMedia::Serie),
GestionnaireSaisons()
{
}

// constructeur par copie de la classe Serie
Serie::Serie(const Serie& serie)
: Media(serie), 
GestionnaireSaisons()
{
  saisons_.clear();
    for (unsigned int i = 0; i < serie.saisons_.size(); i++)
    {
        auto saison_ptr = std::make_unique<Saison>(*(serie.saisons_[i]));
        saisons_.push_back(std::move(saison_ptr));
    }

}

// To do
std::ostream& Serie::afficher(std::ostream& os) const
{
    Media::afficher(os);
    for(unsigned int i = 0; i < saisons_.size(); i++){

      os << "\t" <<*saisons_[i]; 
    }
    return os; 
}

// To do
std::unique_ptr<Media> Serie::clone() const
{
    return std::make_unique<Media>(*this); 
}