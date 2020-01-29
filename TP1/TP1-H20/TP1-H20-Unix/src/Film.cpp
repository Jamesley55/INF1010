/* ////////////////////////////////////////////////////////////////
/	*TD1 : fichier Film.cpp                                       /
/	*travail fait par Jamesley Joseph : 1990552                   /
/					   Wael tarifi :  1991935                     /
/                                                                 /
/	*Date de remise : 28 janvier 2020 à 23h55                     /
/   * Description: Implementation de la classe Film               /
*//////////////////////////////////////////////////////////////////
#include <iostream>
#include "Pays.h"
#include "typesafe_enum.h"
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

/****************************************************************************
 * Fonction: Film:Film
 * Description: Constructeur par parametre en utilisant la liste d'initialisation
 * Paramètres: - const std:: string& nom : nom du film
 *             - unsigned int anneDeSortie : annee de sortie du film
 *             - Genre genre : genre du film
 *             - Pays pays : pays du film
 *             - bool estRestreintParAge : si le film est restreint pas l'age ou pas
 *             - Auteur *auteur : auteur du film
 * Retour: aucun
 ****************************************************************************/
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
bool estRestreintParAge, Auteur* auteur):

   nom_(nom),
   anneeDeSortie_(anneeDeSortie), 
   genre_(genre),
   pays_(pays),
   estRestreintParAge_(estRestreintParAge),
   auteur_(auteur),
   paysRestreints_(std::make_unique<Pays[]>(CAPACITE_PAYS_INITIALE)),
    nbPaysRestreints_(0),
    capacitePaysRestreints_(CAPACITE_PAYS_INITIALE)
{}


//! \param pays Pays à ajouter à la liste.
/****************************************************************************
 * Fonction: Film:ajouterPaysRestreint
 * Description: Méthode qui ajoute un pays à liste des pays restreints du film..
 * Paramètres: - Pays pay : Pays a ajouter a la liste
 * Retour: aucun
 ****************************************************************************/
void Film::ajouterPaysRestreint(Pays pays)
{
    static constexpr unsigned int AUGMENTATION_CAPACITE_PAYS = 2;

    
    if(nbPaysRestreints_ == capacitePaysRestreints_) // Verifie si assez de mémoire est allouée
    {
        capacitePaysRestreints_*=AUGMENTATION_CAPACITE_PAYS; // on double la capaciter du tableau

       // on cree une nouveau pointeur qui pointe vers un tableau qui est le double de la capaciter
       //  que l'ancien 
       auto NouvelleRepo = std::make_unique<Pays[]>(capacitePaysRestreints_);
       //on envoie les valeur des pays restrients dans un tableau plus grand
       paysRestreints_ = std::move(NouvelleRepo);
    }
    // on rajout le nouveau pays restrient a la liste des pays restreints
    paysRestreints_[nbPaysRestreints_] = pays;
    // on augemente le nombre de pays restrients par 1 
	nbPaysRestreints_++;
    
}

/****************************************************************************
 * Fonction: Film:supprimerPaysRestreints
 * Description: reinitialiser le nombre de pays restrients a zero
 * Paramètres: aucun
 * Retour: aucun
 ****************************************************************************/
void Film::supprimerPaysRestreints()
{
    nbPaysRestreints_ = 0; 
}


/****************************************************************************
 * Fonction: Film:estRestreintDansPays const
 * Description:  Chercher si le pays en paramètre se retrouve dans la liste des pays restreints.
 * Paramètres: - Pays pays : Le pays a voir si il est restreint ou pas
 * Retour: (const bool) Si le pays dans la liste des pays restreints(true) ou pas (false)
 ****************************************************************************/
bool Film::estRestreintDansPays(Pays pays) const 
{
    for(size_t i = 0 ; i< capacitePaysRestreints_; i++)
    { 
        // on cherche dans la liste des pays restrient si un pays correspond au pays passer en parametre
        if(paysRestreints_[i] == pays)
        {
             return true; 
        }
    }
    // si on ne trouve pas de pays on retourne false; 
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

/****************************************************************************
 * Fonction: Film:getGenre() const
 * Description:  Retourne le genre du film
 * Paramètres: aucun
 * Retour: (const Film::Genre) le genre du film
 ****************************************************************************/
Film::Genre Film::getGenre() const
{
     return genre_; 
}

/****************************************************************************
 * Fonction: Film:: estRestreintParAge const
 * Description:  Retourne si le film est resteint par l'age ou pas
 * Paramètres: aucun
 * Retour: (const bool) le parametre de restriction par age de la class Film
 ****************************************************************************/
bool Film::estRestreintParAge() const 
{
    return estRestreintParAge_;  
}

/****************************************************************************
 * Fonction: Film:: getNom const
 * Description:  Retourne le nom du film
 * Paramètres: aucun
 * Retour: (const std::string&) le nom du film
 ****************************************************************************/
  const std::string& Film::getNom() const 
  {
      return nom_;
  }
  
/****************************************************************************
 * Fonction: Film:: getAuteur
 * Description:  Retourne l'auteur du film
 * Paramètres: aucun
 * Retour: (Auteur*) l'auteur du film
 ****************************************************************************/
Auteur* Film::getAuteur() {

    return auteur_;
}