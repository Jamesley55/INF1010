/* ////////////////////////////////////////////////////////////////
/	*TD1 : fichier Utilisateur.cpp                                /
/	*travail fait par Jamesley Joseph: 1990552                    /
/					   Wael tarifi :  1991935                     /
/                                                                 /
/	*Date de remise : 28 janvier 2020 à 23h55                     /
/   * Description: Implementation de la classe Utilisateur        /
*//////////////////////////////////////////////////////////////////

#include "Utilisateur.h"

/****************************************************************************
 * Fonction: Utilisateur:: Utilisateur
 * Description:  Constructeur par parametre en utilisant la liste d'initialisation
 * Paramètres: - const std::string& nom : le nom de l'utilisateur
 *             - unsigned int age : l'age de l'utilisateur
 *             - bool estPremium : bool representant le status premium de l'utilisateur
 *             - Pays pays : pays de l'utilisateur
 * Retour: aucun
 ****************************************************************************/
Utilisateur::Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays):
nom_(nom), age_(age), estPremium_(estPremium), pays_(pays), nbFilmsVus_(NB_FILMS_GRATUITS)
{   
}


//! \param film Le film à évaluer.
//! \return Un bool représentant si un film est disponible à l'utilisateur.
/****************************************************************************
 * Fonction: Utilisateur:: filmEstDisponible const
 * Description:  Methode qui retourne si le film est disponible pour un utilisateur
 * Paramètres: - const Film& film : le film a evaluer
 * Retour: (const bool) Un representant si le film est disponible ou non pour un utilisateur
 ****************************************************************************/
bool Utilisateur::filmEstDisponible(const Film& film) const
{
    static constexpr unsigned int AGE_MINIMUM_POUR_FILMS_RESTREINTS = 16;

   
    if(film.estRestreintParAge() && age_ < AGE_MINIMUM_POUR_FILMS_RESTREINTS){
    
        return false; 
    }
    
        return true; 


   

}

/****************************************************************************
 * Fonction: Utilisateur:: nbLimiteFilmsAtteint const
 * Description: Retourner si l'utilisateur a atteint la limite de films qu'il peut regarder
 * Paramètres: aucun 
 * Retour: (bool) bool qui represente si l'utilisateur a atteint la limite de films qu'il peut regarder
 ****************************************************************************/
bool Utilisateur::nbLimiteFilmsAtteint()const{
 
 if(estPremium_)
 {
     return false;
 }
 else if (nbFilmsVus_ == NB_FILMS_GRATUITS)
 {
     return true; 
 }
 return false;

}

/****************************************************************************
 * Fonction: Utilisateur:: regarderFilm
 * Description:  Verifier si l'utilisateur  a le droit de regarder le film ou pas
 * Paramètres: const Film& film : le film 
 * Retour: (bool) un bool qui indique si l'utilisateur peut visionner le film
 ****************************************************************************/
bool Utilisateur::regarderFilm(const Film& film)
{
    
    if(film.estRestreintDansPays(pays_) != true && nbFilmsVus_!= NB_FILMS_GRATUITS)
    {
        nbFilmsVus_++;
        return true; 
    }
     return false; 
}

/****************************************************************************
 * Fonction: Utilisateur:: getNbFilmsVus const
 * Description:  Retourner le nombre de films vus
 * Paramètres: aucun
 * Retour: (unsigned int) le nombre de films vus
 ****************************************************************************/
unsigned int Utilisateur::getNbFilmsVus() const 
{
    return nbFilmsVus_; 
}