/* ////////////////////////////////////////////////////////////////
/	*TD1 : fichier librairie.cpp                                  /
/	*travail fait par Jamesley Joseph: 1990552                    /
/					   Wael tarifi :  1991935                     /
/                                                                 /
/	*Date de remise : 28 janvier 2020 à 23h55                     /
/   * Description: Implementation de la classe librairie          /
*//////////////////////////////////////////////////////////////////
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "debogageMemoire.h"
#include "typesafe_enum.h"
#include "Librairie.h"


namespace
{
    constexpr std::size_t CAPACITE_FILMS_INITIALE = 2;
    constexpr int FILM_INEXSISTANT = -1;
} // namespace

/****************************************************************************
 * Fonction: Librairie:: Libraire
 * Description:  Constructeur par defaut de la class Librairie
 * Paramètres: aucun
 * Retour: aucun
 ****************************************************************************/
Librairie::Librairie():
 nbFilms_(0),
 capaciteFilms_(CAPACITE_FILMS_INITIALE)
{
    films_= new Film *[CAPACITE_FILMS_INITIALE]; 
}

/****************************************************************************
 * Fonction: Librairie:: ~Libraire
 * Description:  Destructeur de Librairie
 * Paramètres: aucun
 * Retour: aucun
 ****************************************************************************/
Librairie::~Librairie()
{
   supprimerFilms();
   for (int i=0; i<nbFilms_; i++)
   {
    delete [] films_[i];
    delete [] films_;}
    // delete[] films_; // on suprime de tableau 
   films_ = nullptr;  // on desalou la memoire du tableau 
}



//! \param film Le film alloué dynamiquement à ajouter à la liste. La classe
//! devient propriétaire du
//!             film.
/****************************************************************************
 * Fonction: Librairie:: ajouterFilm
 * Description:  Methode qui ajoute un film a la liste des fims
 * Paramètres: Film* film : le film alloue dynamiquement a ajouter a la liste
 * Retour: aucun
 ****************************************************************************/
void Librairie::ajouterFilm(Film* film)
{
    static constexpr unsigned int AUGMENTATION_CAPACITE_FILMS = 2;

    
    
    
    if(film!= nullptr){


         if(nbFilms_ == capaciteFilms_) // Verifie si assez de mémoire est allouée
        {
        capaciteFilms_ *= AUGMENTATION_CAPACITE_FILMS;  // si il n'ya pas assez de memoire on double la capaciter
        Film** temp = new Film *[ capaciteFilms_]; 

           for(unsigned int i = 0; i< nbFilms_; i++){
            
            temp[i] = films_[i]; // on envoie les valeur de lancien tableau du nouveau tableau; 
            }
             delete [] films_; // on desalou l'espace du lancien tableau (delete[])
             films_ = nullptr; 
             films_ = temp;  // on envoie les valeur du tableau temporaire au tableau film_
             delete [] temp; // on desalou l'espace memoire de 
             // la variable temporaire puisquelle n'est plus necessaire 
             temp = nullptr;
        }
        Auteur *auteur = film->getAuteur();
        auteur->setNbFilms(auteur->getNbFilms() + 1);
        films_[nbFilms_] = film; //Ajouter le film au tableau seulement si film n'est pas un nullptr 
        nbFilms_++;
    
    }
    // (AUGMENTATION_CAPACITE_FILMS) 
}

/****************************************************************************
 * Fonction: Librairie:: retirerFilm
 * Description:  Retirer un film ayant le meme nom que celui envoye en parametre
 * Paramètres: const std::string& nomFilm : le nom du film a retirer
 * Retour: aucun
 ****************************************************************************/
void Librairie::retirerFilm(const std::string& nomFilm)
{
      if(trouverIndexFilm(nomFilm) != FILM_INEXSISTANT){ // on s'assure que le film existe
      int index = trouverIndexFilm(nomFilm); // on trouve lindex du film
      delete films_[index];  // on desalou l'espace memoire du film quon veut retirer 
      films_[index]= nullptr; 
      
      // on s'assure qu'il n'y a pas de trou dans le tableau 
      // on "shift" tout les donner vers la gauche
      for(size_t i = index + 1; i < nbFilms_; i++){
           films_[i - 1] = films_[i];
           films_[i] = nullptr;
       }
       nbFilms_--; 
      }
      


}

/****************************************************************************
 * Fonction: Librairie:: chercherFilm
 * Description:  Retourner un vers le film recherche, si le film n'existe pas retourner nullptr
 * Paramètres: const std:: string &nomFilm : le nom du film a rechercher
 * Retour: (Film*) le pointeur du film a recherche
 ****************************************************************************/
Film* Librairie::chercherFilm(const std::string& nomFilm) {

            if(trouverIndexFilm(nomFilm)!= FILM_INEXSISTANT)
            {
            int index = trouverIndexFilm(nomFilm);
             return films_[index]; 
            }   
            else {
                return nullptr; 
            }     
}


//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour
//! associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si le chargement a été un
//! succès.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
                                          GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        
        std::string ligne;
        for (unsigned int i = 0; i < nbFilms_; i++)
		{
			(films_[i]->getAuteur())->setNbFilms(0);
		}
		supprimerFilms(); 
        while(getline(fichier,ligne)){
            lireLigneFilm(ligne,gestionnaireAuteurs);
            
            return false;
            
        }
        return true; 
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return true; 
}

//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un
//! succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // TODO

         for(std::size_t i=0; i< nbFilms_; i++){
             films_[i]->supprimerPaysRestreints();

         }

        std::string ligne;
        while(getline(fichier,ligne)){
            if(lireLigneRestrictions(ligne))
            {
            return false;
            }
         }
         return true; 
    }

    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui affiche la liste des films.
//! \param stream Le stream dans lequel afficher.
void Librairie::afficher(std::ostream& stream) const
{
    // Ne pas modifier cette méthode
    for (std::size_t i = 0; i < nbFilms_; i++)
    {
        films_[i]->afficher(stream);
        stream << '\n';
    }
}

/****************************************************************************
 * Fonction: Librairie:: getNbFilms() const
 * Description:  Retourne le nombre de films
 * Paramètres: aucun
 * Retour: (size_t) le nombre de film
 ****************************************************************************/
std::size_t Librairie::getNbFilms() const
{
       return nbFilms_;
}

/****************************************************************************
 * Fonction: Librairie:: supprimerFilms
 * Description:  Supprimer les films du tableau
 * Paramètres: aucun
 * Retour: aucun
 ****************************************************************************/
void Librairie::supprimerFilms()
{ 
    for(std::size_t i = 0; i<nbFilms_; i++){

        films_[i]->getAuteur()->setNbFilms(0);
        delete films_[i];
        films_[i]=nullptr;

    }

        nbFilms_= 0; 
}

/****************************************************************************
 * Fonction: Librairie:: lireLigneRestrictions
 * Description:  Methode qui ajoute les restrictions d'un film avec un string
 * Paramètres: const std::string &ligne : le string comportant les restrictions du film
 * Retour: (bool) un bool representant le succes ou non de la fonction
 ****************************************************************************/
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    stream >> std::quoted(nomFilm) ; 
    
     int PaysValeurEnum; 
     
     if(trouverIndexFilm(nomFilm) != FILM_INEXSISTANT)
     {
            
            while(stream >> PaysValeurEnum)
            {
                 films_[trouverIndexFilm(nomFilm)]->ajouterPaysRestreint(to_enum<Pays>(PaysValeurEnum));
                 return true;
            }
     }
     return false; 
    
}

/****************************************************************************
 * Fonction: Librairie:: lireLigneFilm
 * Description:  Methode qui ajoute un film avec un string comportant les attributs du film
 * Paramètres: - const std::string& ligne : le string comportant les attributs du film
 *             - GestionnaireAuteurs& gestionnaireAuteurs : le gestionnare des auteurs
 * Retour: (bool) un bool representant le succes ou non de la fonction 
 ****************************************************************************/
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;

    stream >> std::quoted(nomFilm) >> anneeSortie >> genreValeurEnum  >> paysValeurEnum>>
    estRestreintParAge >> std::quoted(nomAuteur); // intisialise  tout les attributs
    //  de la clas film par la valeur lu dans le fichier 
      
    if(gestionnaireAuteurs.chercherAuteur(nomAuteur) == nullptr)  return false;  // si l'auteur n'exise pas la fonction a echouer

    
    else{
         
        Film* NouveauFilm = new Film(nomFilm, anneeSortie, 
        to_enum<Film::Genre>(genreValeurEnum), to_enum<Pays>(paysValeurEnum), 
        estRestreintParAge, gestionnaireAuteurs.chercherAuteur(nomAuteur)); 
        // on initialise un nouveau film avec les valeur lu dans le fichier et on l'ajoute a a liste des films 
        ajouterFilm(NouveauFilm);
        return true; 
        
    }

}

/****************************************************************************
 * Fonction: Librairie:: trouverIndexFilm const
 * Description:  Retourner l'indexe du film comportant le nom envoye en parametre
 * Paramètres: const std::string& nomFilm
 * Retour: (int) l'indexe du film trouve (-1 pour FILM_INEXISTANT)
 ****************************************************************************/
int Librairie::trouverIndexFilm(const std::string& nomFilm) const 
{
    for(unsigned int  i = 0; i < nbFilms_; i++)
    {
        if(nomFilm == films_[i]->getNom())
        {
            return i; 
        }
        
    }
    return FILM_INEXSISTANT;

}