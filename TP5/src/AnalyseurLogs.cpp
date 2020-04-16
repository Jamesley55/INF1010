/// Analyseur de statistiques grâce aux logs.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12

#include "AnalyseurLogs.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include "Foncteurs.h"

/// Ajoute les lignes de log en ordre chronologique à partir d'un fichier de logs.
/// \param nomFichier               Le fichier à partir duquel lire les logs.
/// \param gestionnaireUtilisateurs Référence au gestionnaire des utilisateurs pour lier un utilisateur à un log.
/// \param gestionnaireFilms        Référence au gestionnaire des films pour pour lier un film à un log.
/// \return                         True si tout le chargement s'est effectué avec succès, false sinon.
bool AnalyseurLogs::chargerDepuisFichier(const std::string &nomFichier,
										 GestionnaireUtilisateurs &gestionnaireUtilisateurs,
										 GestionnaireFilms &gestionnaireFilms)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		logs_.clear();
		vuesFilms_.clear();

		bool succesParsing = true;

		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			std::istringstream stream(ligne);

			std::string timestamp;
			std::string idUtilisateur;
			std::string nomFilm;

			if (stream >> timestamp >> idUtilisateur >> std::quoted(nomFilm))
			{
				creerLigneLog(timestamp, idUtilisateur, nomFilm, gestionnaireUtilisateurs, gestionnaireFilms);
			}
			else
			{
				std::cerr << "Erreur AnalyseurLogs: la ligne " << ligne
						  << " n'a pas pu être interprétée correctement\n";
				succesParsing = false;
			}
		}
		return succesParsing;
	}
	std::cerr << "Erreur AnalyseurLogs: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
	return false;
}

/// Cree une ligne de log depuis les parametres puis l'ajoute au log.
/// \param timestamp            le moment où l'utilisateur a écouté le film
/// \param idUtilisateur        L'id d'utilisateur
/// \param nomFilm              Le nom du film qui a ete visione.
/// \param gUtilisateurs        gestionnaire dans lequel se trouve l'utilisateur
/// \param gFilms               gestionnaire dans lequel se trouve le film
/// \return                     true si le film et l’utilisateur existaient et le log a été ajouté avec succès, false sinon.
bool AnalyseurLogs::creerLigneLog(const std::string &timestamp,
								  const std::string &idUtilisateur,
								  const std::string &nomFilm,
								  GestionnaireUtilisateurs &gUtilisateurs,
								  GestionnaireFilms &gFilms)
{
	const Utilisateur *user = gUtilisateurs.getUtilisateurParId(idUtilisateur);
	const Film *film = gFilms.getFilmParNom(nomFilm);
	if (film != nullptr && user != nullptr)
	{

		ajouterLigneLog(LigneLog{timestamp, user, film});
		return true;
	}
	return false;
}

///Ajoute  une  ligne  de  log  en  ordre  chronologique  dans  le vecteur  de  logs  tout  en mettant à jour le nombre de vues
/// \param ligneLog    La ligne de log du film vue a ajouter.
void AnalyseurLogs::ajouterLigneLog(const LigneLog &ligneLog)
{
	logs_.insert(std::upper_bound(logs_.begin(), logs_.end(), ligneLog, ComparateurLog()), ligneLog);
	vuesFilms_[ligneLog.film]++;
}

/// Retourne le nombre de vues pour un film donne en parametre.
/// \param film                 le film pour lequel on veut calculer le nombre e vue
/// \return                     le nombre de vuesdu film
int AnalyseurLogs::getNombreVuesFilm(const Film *film) const
{
	return std::count_if(logs_.begin(), logs_.end(), [film](LigneLog ligne) { return ligne.film == film; });
}

/// Retourne le film le plus visionne depuis vuesFilms_.
/// \return                    un pointeur vers le film le plus populaire.
const Film *AnalyseurLogs::getFilmPlusPopulaire() const
{
	return logs_.size() == 0 ? nullptr : std::max_element(vuesFilms_.begin(), vuesFilms_.end(), ComparateurSecondElementPaire<const Film *, int>())->first;
}

/// retourne un vecteur contenant la liste des n paires de pointeurs vers les films les plus populaires et leur nombre de vues.
/// \param nombre                le nombre de films les plus populaires à retourne.
/// \return                     Un vecteur de paire des N films plus populaires.
std::vector<std::pair<const Film *, int>> AnalyseurLogs::getNFilmsPlusPopulaires(std::size_t nombre) const
{
	std::vector<std::pair<const Film *, int>> filmsPlusPopulaire(std::min(logs_.size(), nombre));
	std::partial_sort_copy(vuesFilms_.begin(), vuesFilms_.end(), filmsPlusPopulaire.begin(), filmsPlusPopulaire.end(),
						   [](const std::pair<const Film *, int> &pair1, const std::pair<const Film *, int> &pair2) { return pair1.second > pair2.second; });
	filmsPlusPopulaire.erase(std::remove_if(filmsPlusPopulaire.begin(), filmsPlusPopulaire.end(), [](auto pair) { return pair.second == 0; }), filmsPlusPopulaire.end());
	return filmsPlusPopulaire;
}

/// Retourne le nombre de films vus par un utilisateur
/// \param utilisateur          l’utilisateur pour lequel on veut compter le nombre de vues
/// \return                     le nombre d films vue par l'utilisateur.
int AnalyseurLogs::getNombreVuesPourUtilisateur(const Utilisateur *utilisateur) const
{
	return std::count_if(logs_.begin(), logs_.end(),
						 [utilisateur](LigneLog ligne) { return ligne.utilisateur == utilisateur; });
}

/// Retourne un vecteur des films vu par un utilisateur.
/// \param utilisateur          L'utilisateur a extraire les films visionne.
/// \return                     Un vecteur des films vus par un utilisateur
std::vector<const Film *> AnalyseurLogs::getFilmsVusParUtilisateur(const Utilisateur *utilisateur) const
{
	std::vector<const Film *> film;
	std::for_each(logs_.begin(), logs_.end(),
				  [utilisateur, &film](LigneLog ligne) {if ((ligne.utilisateur == utilisateur) && 
				  !(std::count(film.begin(), film.end(), ligne.film))) film.push_back(ligne.film); });
	return film;
}
