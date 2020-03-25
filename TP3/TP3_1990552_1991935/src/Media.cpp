/**************************************************
 * Titre: TP3 - Media.cpp
 * Date: 1 mars 2020
 * Auteurs: Jamesley Joseph, Wael Tarifi
 **************************************************/

#include "Media.h"

namespace
{
    //! Fonction qui convertit le enum Media::Genre en string
    //! \param genre    Le genre à convertir
    //! \return         Le string qui représente le enum
    const std::string& getGenreString(Media::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Media::Genre>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string
    //! \param pays     Le pays à convertir
    //! \return         Le string qui représente le enum
    const std::string& getPaysString(Pays pays)
    {
        static const std::string NOMS_PAYS[] = {"Bresil",
                                                "Canada",
                                                "Chine",
                                                "EtatsUnis",
                                                "France",
                                                "Japon",
                                                "RoyaumeUni",
                                                "Russie",
                                                "Mexique"};
        auto index = enum_value(pays);
        assert(valid_as_enum<Pays>(index));
        return NOMS_PAYS[index];
    }
} // namespace

// Constructeur par default 
Media::Media(Auteur* auteur, Media::TypeMedia typeMedia):
nom_(""),
anneeDeSortie_(0),
genre_(Genre()),
pays_(Pays()),
estRestreintParAge_(false),
auteur_(auteur), 
typeMedia_(typeMedia)
{
}

// Constructeur par paramètres
Media::Media(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur, Media::TypeMedia typeMedia):
nom_(nom), 
anneeDeSortie_(anneeDeSortie),
genre_(genre),
 pays_(pays),
estRestreintParAge_(estRestreintParAge)
, auteur_(auteur),
typeMedia_(typeMedia)
{
}

// Constructeur par copie
Media::Media(const Media& serie):
nom_(serie.nom_),
anneeDeSortie_(serie.anneeDeSortie_),
genre_(serie.genre_),
estRestreintParAge_(serie.estRestreintParAge_),
pays_(serie.pays_),
typeMedia_(serie.typeMedia_),
auteur_(serie.auteur_)
{
    paysRestreints_.clear(); 
    for( unsigned int i  = 0; i < serie.paysRestreints_.size(); i++){
      paysRestreints_.push_back(serie.paysRestreints_[i]); 

    }
}


// Destructeur vituel
Media::~Media()
{
    auteur_->setNbMedias(auteur_->getNbMedias()-1);
}

//! Méthode qui ajoute un pays à liste des pays restreints du film
void Media::ajouterPaysRestreint(Pays pays)
{
    paysRestreints_.push_back(pays);
}

//! Méthode qui supprime les pays restreints
void Media::supprimerPaysRestreints()
{
    paysRestreints_.clear();
}

//! Méthode qui retourne si un pays est dans la liste des pays restreints du film
bool Media::estRestreintDansPays(Pays pays) const
{
    for (std::size_t i = 0; i < paysRestreints_.size(); i++)
    {
        if (paysRestreints_[i] == pays)
        {
            return true;
        }
    }
    return false;
}

// Méthode qui retourne si le film est restreint aux moins de 16 ans
// \return Un bool représentant si le film est restreint aux moins de 16 ans
bool Media::estRestreintParAge() const
{
    return estRestreintParAge_;
}

// Méthode qui affiche les informations du média
std::ostream& Media::afficher(std::ostream& os) const
{
    os << 
    nom_ << 
    "\n\tDate de sortie: " <<  anneeDeSortie_ << 
    "\n\tGenre: " << getGenreString(genre_) <<
    "\n\tAuteur: " <<auteur_->getNom() <<
    "\n\tPays: "  << getPaysString(pays_); 

    if (paysRestreints_.size()==0){
      os << "\n\tAucun pays restreint."; 
    }
    else{
        os <<"\n\tPays restreints:";
    for(unsigned int i =0; i < paysRestreints_.size(); i++){
        os << "\n\t\t" << getPaysString(paysRestreints_[i]); 
    }
    }
    os << "\n"; 

    return os; 

}

// Surcharge de l'opérateur << permettant d'afficher les médias
std::ostream& operator<<(std::ostream& os, const Media& media)
{
     media.afficher(os);
     return os; 
}

// Méthode qui retourne le genre du média
Media::Genre Media::getGenre() const
{
    return genre_; 
}

// Méthode qui retourne le nom
const std::string& Media::getNom() const
{
    return nom_;
}

// Méthode qui retourne le type de média
Media::TypeMedia Media::getTypeMedia() const
{
    return typeMedia_;
}

// Méthode qui retourne l'auteur
Auteur* Media::getAuteur()
{
	return auteur_;
}

// Méthode qui permet de lire une ligne et d'en retirer les informations du média
std::istream& Media::lire(std::istream& is)
{
    int genre;
    int pays; 

    is 
    >> std::quoted(nom_)
    >> anneeDeSortie_
    >> genre 
    >> pays 
    >> estRestreintParAge_;
   genre_ = to_enum<Media::Genre>(genre);
   pays_ = to_enum<Pays>(pays); 
   

    return is ; 



}

// Surcharge de l'opérateur >> permettant de lire les informations du média
std::istream& operator>>(std::istream& is, Media& media)
{
   
    media.lire(is);
    return is; 
}

// Méthode qui crée une copie de l'objet courant
std::unique_ptr<Media> Media::clone() const
{
     return std::make_unique<Media>(*this); 
}