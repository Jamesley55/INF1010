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

// To do
Media::Media(Auteur* auteur, Media::TypeMedia typeMedia):
auteur_(auteur), typeMedia_(typeMedia)
{
}

// To do
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

// To do
Media::Media(const Media& serie)
{
    // To do
}


// To do
Media::~Media()
{
    // To do
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

// To do
std::ostream& Media::afficher(std::ostream& os) const
{
    // To do
}

// To do
std::ostream& operator<<(std::ostream& os, const Media& media)
{
    // To do
}

// To do
Media::Genre Media::getGenre() const
{
    return genre_; 
}

// To do
const std::string& Media::getNom() const
{
    return nom_;
}

// To do
Media::TypeMedia Media::getTypeMedia() const
{
    return typeMedia_;
}

Auteur* Media::getAuteur()
{
	return auteur_;
}

// To do
std::istream& Media::lire(std::istream& is)
{
    // To do
}

// To do
std::istream& operator>>(std::istream& is, Media& media)
{
    // To do
}

// To do
std::unique_ptr<Media> Media::clone() const
{
    // To do
}