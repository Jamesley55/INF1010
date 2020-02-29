// To do
#include"Serie.h"

// constructeur par defaut de la classe Serie
Serie::Serie(Auteur* auteur):
Media(auteur, Media::TypeMedia::Serie),
GestionnaireSaisons()
{    
}

// constructeur par parametre de la classe Serie
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur):
Media(nom,anneeDeSortie,genre, pays, estRestreintParAge, auteur, Media::TypeMedia::Serie),
GestionnaireSaisons()
{
}

// constructeur par copie de la classe Serie
Serie::Serie(const Serie& serie):
Media(serie.nom_, serie.anneeDeSortie_, serie.genre_,serie.pays_, serie.estRestreintParAge_,serie.auteur_, serie.typeMedia_)
{
    // To do
}

// To do
std::ostream& Serie::afficher(std::ostream& os) const
{
    Media::afficher(os);
    for(unsigned int i = 0; i < saisons_.size(); i++){

      os << *saisons_[i]; 
    }
    return os; 
}

// To do
std::unique_ptr<Media> Serie::clone() const
{
    return std::make_unique<Media>(*this); 
}