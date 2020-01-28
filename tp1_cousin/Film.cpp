
#include <Pays.h>
#include <typesafe_enum.h>
#include "Film.h"
namespace
{
    constexpr std::size_t CAPACITE_PAYS_INITIALE = 2;

    //! Fonction qui convertit le enum Film::Genre en string.
    //! \param genre    Le genre à convertir.
    //! \return         Le string qui représente le enum.
    const std::string& getGenreString(Film::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Pays>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string.
    //! \param pays     Le pays à convertir.
    //! \return         Le string qui représente le enum.
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

//! Méthode Constructeur par paramètre qui utilise la liste d'initialisation.
//! \param  nom               Le nom du film.
//! \param anneeDeSortie      L'annee de sortie du film.
//! \param genre              Le genre du film.
//! \param pays               Le pays de la création du film.
//! \param estRestreintParAge Paramètre booléen indiquant si le film est restreint par age.
//! \param Auteur             Auteur du film.
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur)
    : nom_(nom)
    , anneeDeSortie_(anneeDeSortie)
    , genre_(genre)
    , pays_(pays)
    , estRestreintParAge_(estRestreintParAge)
    , auteur_(auteur)
    , paysRestreints_(std::make_unique<Pays[]>(CAPACITE_PAYS_INITIALE))
    , nbPaysRestreints_(0)
    , capacitePaysRestreints_(CAPACITE_PAYS_INITIALE)
{}

//! Méthode qui ajoute un pays à liste des pays restreints du film.
//! \param pays Pays à ajouter à la liste.
void Film::ajouterPaysRestreint(Pays pays)
{
    static constexpr unsigned int AUGMENTATION_CAPACITE_PAYS = 2;
    
    if (nbPaysRestreints_ >= capacitePaysRestreints_)
    {
        capacitePaysRestreints_ *= AUGMENTATION_CAPACITE_PAYS;
        std::unique_ptr<Pays[]> temp = std::make_unique<Pays[]>(capacitePaysRestreints_);
        for (std::size_t i = 0; i < nbPaysRestreints_; i++)
        {
            temp[i] = paysRestreints_[i];
        }
        paysRestreints_ = std::move(temp);
    }
    
        paysRestreints_[nbPaysRestreints_] = pays;
        nbPaysRestreints_++;
}

//! Méthode qui met le nombre de pays restreints à 0.
void Film::supprimerPaysRestreints() 
{
    nbPaysRestreints_ = 0;
}

//! Méthode qui vérifie si le film est restreint dans le pays passé en paramètre.
//! \param  pays Le pays qu'on vérifie.
//! \return      Un bool représentant si le film est restreint dans le pays passé en paramètre.
bool Film::estRestreintDansPays(Pays pays) const
{
    for (std::size_t i = 0; i < nbPaysRestreints_; i++)
    {
        if (pays == paysRestreints_[i])
        {
             return true;
        }
    }
    return false;
}

//! Méthode qui affiche le film.
//! \param stream Le stream dans lequel afficher.
void Film::afficher(std::ostream& stream) const
{
    // Ne modifiez pas cette fonction
    stream << nom_ << "\n\tDate de sortie: " << anneeDeSortie_
           << "\n\tGenre: " << getGenreString(genre_) << "\n\tAuteur: " << auteur_->getNom()
           << "\n\tPays: " << getPaysString(pays_)
           << (nbPaysRestreints_ == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

    for (std::size_t i = 0; i < nbPaysRestreints_; i++)
    {
        stream << "\n\t\t" << getPaysString(paysRestreints_[i]);
    }
    stream << '\n';
}

//! Méthode qui récupère l'attribut privé genre_.
//! \param aucun
//!\return Un enum de type Genre appartenant à la classe Film représentant le genre du film.
Film::Genre Film::getGenre() const
{
    return genre_;
}

//! Méthode qui récupère l'attribut privé estRestreintParAge_.
//! \param aucun
//! \return Un bool representant si le film est restreint par age ou non.
bool Film::estRestreintParAge() const 
{
    return estRestreintParAge_;
}

//! Méthode qui récupère l'attribut privé nom_.
//! \param aucun
//! \return Un string& representant le nom du film.
const std::string& Film::getNom() const
{
    return nom_;
}

//! Méthode qui récupère l'attribut privé auteur_.
//! \param aucun
//! \return Un pointeur vers l'objet Auteur representant l'auteur du film.
Auteur* Film::getAuteur() 
{
    return auteur_;
}