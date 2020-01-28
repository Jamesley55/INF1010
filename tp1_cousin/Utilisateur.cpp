
#include "Utilisateur.h"
//! Méthode Constructeur par parametre qui initialise les valeurs membres.
//! \param nom        Le nom de l'utilisateur.
//! \param age        L'age de l'utilisateur.
//! \param estPremium Un bool representant si l'utilisateur est premium ou non.
//! \param pays       Le pays de l'utilisateur.
Utilisateur::Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays)
    : nom_(nom)
    , age_(age)
    , nbFilmsVus_(0)
    , estPremium_(estPremium)
    , pays_(pays)
{}

//! Méthode qui retourne si le film est disponible pour un utilisateur.
//! \param film Le film à évaluer.
//! \return     Un bool représentant si un film est disponible à l'utilisateur.
bool Utilisateur::filmEstDisponible(const Film& film) const
{
    static constexpr unsigned int AGE_MINIMUM_POUR_FILMS_RESTREINTS = 16;

    if(!film.estRestreintDansPays(pays_))
    {
        if(!film.estRestreintParAge())
        {
            return true;
        }
        else 
        {
            if(age_ >= AGE_MINIMUM_POUR_FILMS_RESTREINTS)
            {
                return true;
            }
        }
    }
    return false;
}

//! Méthode qui retourne si un utilisateur a atteint la limite de films permise.
//! \param aucun
//! \return Un bool représentant si la limite a ete atteinte ou non.
bool Utilisateur::nbLimiteFilmsAtteint() const
{
    if(!estPremium_ && nbFilmsVus_ >= NB_FILMS_GRATUITS)
    {
        return true;
    }
   return false;
}

//! Méthode qui verifie si l'utilisateur peut regarder le film passe en parametre.
//! \param film Le film à évaluer.
//! \return     Un bool représentant si l'utilisateur peut regarder le film.
bool Utilisateur::regarderFilm(const Film& film)
{
    if(filmEstDisponible(film) && !nbLimiteFilmsAtteint())
    {
        nbFilmsVus_++;
        return true;
    }
    return false;
}

//! Méthode qui recupere le nombre de films vus par un utilisateur.
//! \param aucun
//! \return Un unsigned int representant le nombre de films vus par l'utilisateur.
unsigned int Utilisateur::getNbFilmsVus() const
{
    return nbFilmsVus_;
}