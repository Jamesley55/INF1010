/// Gestionnaire de films.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12
/// modifier 2020-04-15 par Jamesley Joseph

#include "GestionnaireFilms.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Film.h"
#include "Foncteurs.h"
#include "RawPointerBackInserter.h"

/// Constructeur par copie.
/// \param other    Le gestionnaire de films à partir duquel copier la classe.
GestionnaireFilms::GestionnaireFilms(const GestionnaireFilms &other)
{
	films_.reserve(other.films_.size());
	filtreNomFilms_.reserve(other.filtreNomFilms_.size());
	filtreGenreFilms_.reserve(other.filtreGenreFilms_.size());
	filtrePaysFilms_.reserve(other.filtrePaysFilms_.size());

	for (const auto &film : other.films_)
	{
		ajouterFilm(*film);
	}
}

/// Opérateur d'assignation par copie utilisant le copy-and-swap idiom.
/// \param other    Le gestionnaire de films à partir duquel copier la classe.
/// \return         Référence à l'objet actuel.
GestionnaireFilms &GestionnaireFilms::operator=(GestionnaireFilms other)
{
	std::swap(films_, other.films_);
	std::swap(filtreNomFilms_, other.filtreNomFilms_);
	std::swap(filtreGenreFilms_, other.filtreGenreFilms_);
	std::swap(filtrePaysFilms_, other.filtrePaysFilms_);
	return *this;
}

/// Affiche les informations des films gérés par le gestionnaire de films à la sortie du stream donné.
/// \param outputStream         Le stream auquel écrire les informations des films.
/// \param gestionnaireFilms    Le gestionnaire de films à afficher au stream.
/// \return                     Une référence au stream.
std::ostream &operator<<(std::ostream &outputStream, const GestionnaireFilms &gestionnaireFilms)
{
	// TODO: Uncomment une fois que la fonction getNombreFilms est écrite
	outputStream << "Le gestionnaire de films contient " << gestionnaireFilms.getNombreFilms() << " films.\n"
				 << "Affichage par catégories:\n";

	// TODO: Réécrire l'implémentation avec des range-based for et structured bindings (voir énoncé du TP)
	for (const auto &[key, value] : gestionnaireFilms.filtreGenreFilms_)
	{
		Film::Genre genre = key;
		std::vector<const Film *> listeFilms = value;
		outputStream << "Genre: " << getGenreString(genre) << " (" << listeFilms.size() << " films):\n";
		for (std::size_t i = 0; i < listeFilms.size(); i++)
		{
			outputStream << '\t' << *listeFilms[i] << '\n';
		}
	}
	return outputStream;
}

/// Ajoute les films à partir d'un fichier de description des films.
/// \param nomFichier   Le fichier à partir duquel lire les informations des films.
/// \return             True si tout le chargement s'est effectué avec succès, false sinon.
bool GestionnaireFilms::chargerDepuisFichier(const std::string &nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		films_.clear();
		filtreNomFilms_.clear();
		filtreGenreFilms_.clear();
		filtrePaysFilms_.clear();

		bool succesParsing = true;

		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			std::istringstream stream(ligne);

			std::string nom;
			int genre;
			int pays;
			std::string realisateur;
			int annee;

			if (stream >> std::quoted(nom) >> genre >> pays >> std::quoted(realisateur) >> annee)
			{
				ajouterFilm(Film{nom, static_cast<Film::Genre>(genre), static_cast<Pays>(pays), realisateur, annee});
			}
			else
			{
				std::cerr << "Erreur GestionnaireFilms: la ligne " << ligne
						  << " n'a pas pu être interprétée correctement\n";
				succesParsing = false;
			}
		}
		return succesParsing;
	}
	std::cerr << "Erreur GestionnaireFilms: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
	return false;
}

/// Trouve et retourne un film en le cherchant à partir de son nom.
/// \param nom          Le nom du film a trouver.
/// \return             Un pointeur vers le film trouve, retourne nullptr si aucun film avec ce om n'a ete trouver
const Film *GestionnaireFilms::getFilmParNom(const std::string &nom) const
{
	return filtreNomFilms_.find(nom) == filtreNomFilms_.end() ? nullptr : (filtreNomFilms_.find(nom)->second);
}

/// Ajoute un film au gestionnaire et met à jour les filtres en conséquence.
/// \param film         Le film a ajouter au gestionnaire.
/// \return             un bollean qui defini si l'operation a ete un succes ou non
bool GestionnaireFilms::ajouterFilm(const Film &film)
{
	if (getFilmParNom(film.nom) == nullptr)
	{

		films_.push_back(std::make_unique<Film>(film));
		const Film *filmPtr = films_.back().get();
		filtreGenreFilms_[film.genre].push_back(filmPtr);
		filtrePaysFilms_[film.pays].push_back(filmPtr);
		return filtreNomFilms_.emplace(film.nom, filmPtr).second;
	}
	return false;
}

/// Supprime un film du gestionnaire à partir de son nom
/// \param nomFilm      Le nom du film a supprimer
/// \return             un bollean qui defini si l'operation a ete un succes ou non
bool GestionnaireFilms::supprimerFilm(const std::string &nomFilm)
{
	auto *film = getFilmParNom(nomFilm);
	if (film != nullptr)
	{
		// code a ignorer losque j'initialise de cette facon avec ou avec auto les tests ne fonctionnent pas ??
		{
			std::vector<const Film *> genreFilm = filtreGenreFilms_[film->genre]; //  ignorer
			std::vector<const Film *> paysFilm = filtrePaysFilms_[film->pays];	  // ignorer
		}

		filtreGenreFilms_[film->genre].erase(std::remove(filtreGenreFilms_[film->genre].begin(), filtreGenreFilms_[film->genre].end(), film),
											 filtreGenreFilms_[film->genre].end());
		filtrePaysFilms_[film->pays].erase(std::remove(filtrePaysFilms_[film->pays].begin(), filtrePaysFilms_[film->pays].end(), film),
										   filtrePaysFilms_[film->pays].end());
		films_.erase(std::remove_if(films_.begin(), films_.end(), [nomFilm](std::unique_ptr<Film> &film) { return film->nom == nomFilm; }),
					 films_.end());
		return filtreNomFilms_.erase(nomFilm);
	}
	return false;
}

/// Retourne le nombre de films présentement dans le gestionnaire
/// \return  le nombre de films dans le gestionnaire
std::size_t GestionnaireFilms::getNombreFilms() const
{
	return films_.size();
}

/// Retourne une copie de la liste des films appartenant à un genre donné
/// \param genre        Le genre des films a trouver
/// \return             Un vecteur de pointeur vers les film trouve ou un  vecteur vide si aucun film du genre a ete trouver.
std::vector<const Film *> GestionnaireFilms::getFilmsParGenre(Film::Genre genre) const
{
	return filtreGenreFilms_.find(genre) == filtreGenreFilms_.end() ? std::vector<const Film *>() : (filtreGenreFilms_.find(genre)->second);
}

/// Retourne une copie de la liste des films appartenant à un pays donné
/// \param pays         Le pays des films a trouver
/// \return             Un vecteur de pointeur vers les film trouve ou un  vecteur vide si aucun film du pays.
std::vector<const Film *> GestionnaireFilms::getFilmsParPays(Pays pays) const
{
	return filtrePaysFilms_.find(pays) == filtrePaysFilms_.end() ? std::vector<const Film *>() : (filtrePaysFilms_.find(pays)->second);
}

/// Retourne une copie de la liste des films appartenant entre deux annees donné.
/// \param anneeDebut   L'annee de la borne inferieure de l'intervalle de recherche.
/// \param anneeFin     L'annee de la borne superieure de l'intervalle de recherche.
/// \return             Un vecteur de pointeur vers les film dans l'intervalle, vecteur vide si aucun film.
std::vector<const Film *> GestionnaireFilms::getFilmsEntreAnnees(int anneeDebut, int anneeFin)
{
	std::vector<const Film *> film;
	std::copy_if(films_.begin(), films_.end(), RawPointerBackInserter(film), EstDansIntervalleDatesFilm(anneeDebut, anneeFin));
	return film;
}
