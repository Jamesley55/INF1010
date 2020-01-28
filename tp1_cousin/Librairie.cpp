
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

//! Méthode Constructeur par défaut qui initialise le tableau de pointeurs de films, met le nombre de films a 0
//! et met la capacite de films de la librairie a 2.
Librairie::Librairie()
    : films_(new Film*[CAPACITE_FILMS_INITIALE]())
    , nbFilms_(0)
    , capaciteFilms_(CAPACITE_FILMS_INITIALE)
{}

//! Méthode destructeur qui s'assure de bien désallouer les pointeurs utiliser dans librairie et met le nombre de films à 0.
Librairie::~Librairie()
{
    supprimerFilms();
    delete[] films_;
    films_ = 0;
}

//! Méthode qui ajoute un film à la liste des films.
//! \param film Le film alloué dynamiquement à ajouter à la liste. La classe
//! devient propriétaire du
//!             film.
void Librairie::ajouterFilm(Film* film)
{
    static constexpr unsigned int AUGMENTATION_CAPACITE_FILMS = 2;

    if(nbFilms_ >= capaciteFilms_)
    {
        capaciteFilms_ *= AUGMENTATION_CAPACITE_FILMS;
        Film** temp = new Film*[capaciteFilms_];
        for(std::size_t i = 0; i < nbFilms_; i++)
        {
            temp[i] = films_[i];
        }
        delete [] films_;
        films_ = temp;
    }
    
    if(film != nullptr)
    {
        films_[nbFilms_] = film;
        nbFilms_++;
    }
}

//! Méthode qui retire un film de la liste de films.
//! \param nomFilm Un string& représentant le nom du film que l'on veut retirer passé par référence constante.
void Librairie::retirerFilm(const std::string& nomFilm)
{
    int index = trouverIndexFilm(nomFilm);
    if(index != FILM_INEXSISTANT)
    {
        delete films_[index];
        films_[index] = films_[--nbFilms_];
    }    
}

//! Méthode qui cherche un film dans la liste ayant le nom correspondant en utilisant trouverIndexFilm.
//! \param NomFilm Un string& représentant le nom du film que l'on veut trouver passé par référence constante.
//! \return        un pointeur vers le film trouvé ou un nullptr si le film n'existe pas.
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    int index = trouverIndexFilm(nomFilm);
    if(index != FILM_INEXSISTANT)
    {
        return films_[index];
    }
    return nullptr;
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
    std::string ligne;
    if (fichier)
    {
        supprimerFilms();
        while(getline(fichier, ligne))
        {
            if(!lireLigneFilm(ligne, gestionnaireAuteurs))
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

//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un
//! succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    std::string ligne;
    if(fichier)
    {
         for(std::size_t i = 0; i < nbFilms_; i++)
        {
            films_[i]->supprimerPaysRestreints();
        }
        while(getline(fichier, ligne))
        {
            if(!lireLigneRestrictions(ligne))
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

//! Méthode qui récupère l'attribut privé nbFilms_ de la liste de films.
//! \param aucun
//!\return Un size_t représentant le nombre de films dans la liste de films.
std::size_t Librairie::getNbFilms() const
{
    return nbFilms_;
}

//! Méthode qui désalloue chaque pointeur de la liste de films et met le nombre de films à 0.
void Librairie::supprimerFilms()
{
    for(std::size_t i = 0; i < nbFilms_; i++)
    {
        delete films_[i];
    }
    nbFilms_ = 0;
}

//! Méthode qui ajoute les restrictions d'un film avec un string.
//! \param ligne Le string comportant les restrictions du film.
//! \return      Un bool représentant si l'opération est un succès.
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    int pays;

    if(stream >> std::quoted(nomFilm))
    {
        if (chercherFilm(nomFilm) == nullptr)
        {
            return false;
        }
        while(stream >> pays)
        {
            chercherFilm(nomFilm)->ajouterPaysRestreint(to_enum<Pays>(pays));
        }
        return true;
    }
    return false;
}

//! Méthode qui ajoute un film avec un string comportant les attributs du film.
//! \param ligne                Le string comportant les attributs du film.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour
//! associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un
//! succès.
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;
    
    if(stream>> std::quoted(nomFilm) >> anneeSortie >> genreValeurEnum >> paysValeurEnum >> estRestreintParAge >> std::quoted(nomAuteur))
    {
        if((gestionnaireAuteurs.chercherAuteur(nomAuteur)) != nullptr)
        {
            Film* film = new Film(nomFilm, anneeSortie, (to_enum<Film::Genre>(genreValeurEnum)), (to_enum<Pays>(paysValeurEnum)), estRestreintParAge, (gestionnaireAuteurs.chercherAuteur(nomAuteur)));
            ajouterFilm(film);
            (film->getAuteur())->setNbFilms((film->getAuteur())->getNbFilms() + 1);
            return true;
        }
    }
    return false;
}

//! Méthode qui trouve l'index du film ayant le nom passé en paramètre.
//! \param nomFilm Le nom du film passe en parametre.
//! \return        Un int correspondant a l'index dans le tableau de film ou -1 si le film ne s'y trouve pas.
int Librairie::trouverIndexFilm(const std::string& nomFilm) const
{    
    for(std::size_t i = 0; i < nbFilms_; i++)
    {
        if(nomFilm == films_[i]->getNom())
        {
            return static_cast<int>(i);
        }
    }
    return FILM_INEXSISTANT;
}