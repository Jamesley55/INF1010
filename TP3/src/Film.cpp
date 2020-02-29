// To do
#include "Film.h"

// constructeur par defaut de la classe film
Film::Film(Auteur* auteur):
Media(auteur, Media::TypeMedia::Film),
duree_("unknow")
{
}

// constructeur par parametre de la classe film 
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur, const std::string& duree):
Media(nom ,anneeDeSortie ,genre ,pays ,estRestreintParAge ,auteur, Media::TypeMedia::Film),
duree_(duree)
{
}

// To do
std::ostream& Film::afficher(std::ostream& os) const
{
    os << duree_; 
    Media::afficher(os); 
    return os ; 

}

// To do
std::istream& Film::lire(std::istream& is)
{
     is >> duree_;
     Media::lire(is); 
     return is; 

}

// To do
std::unique_ptr<Media> Film::clone() const
{
 return std::make_unique<Media>(*this); 
}
