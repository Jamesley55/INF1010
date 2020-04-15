/// Gestionnaire d'utilisateurs.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12
/// modifié 2020-03-15 par Jamesley Joseph

#include "GestionnaireUtilisateurs.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

/// Affiche les informations des utilisateurs gérés par le gestionnaire d'utilisateurs à la sortie du stream donné.
/// \param outputStream         Le stream auquel écrire les informations des utilisateurs.
/// \param gestionnaireFilms    Le gestionnaire d'utilisateurs à afficher au stream.
/// \return                     Une référence au stream.
std::ostream &operator<<(std::ostream &outputStream, const GestionnaireUtilisateurs &gestionnaireUtilisateurs)
{
	outputStream << "Le gestionnaire d'utilisateurs contient " << gestionnaireUtilisateurs.getNombreUtilisateurs()
				 << " utilisateurs:\n";

	for (const auto &[key, value] : gestionnaireUtilisateurs.utilisateurs_)
	{
		outputStream << '\t' << value << '\n';
	}
	return outputStream;
}

/// Ajoute les utilisateurs à partir d'un fichier de données d'utilisateurs.
/// \param nomFichier   Le fichier à partir duquel lire les informations des utilisateurs.
/// \return             True si tout le chargement s'est effectué avec succès, false sinon.
bool GestionnaireUtilisateurs::chargerDepuisFichier(const std::string &nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		utilisateurs_.clear();

		bool succesParsing = true;

		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			std::istringstream stream(ligne);

			std::string id;
			std::string nom;
			int age;
			int pays;

			if (stream >> id >> std::quoted(nom) >> age >> pays)
			{
				ajouterUtilisateur(Utilisateur{id, nom, age, static_cast<Pays>(pays)});
			}
			else
			{
				std::cerr << "Erreur GestionnaireUtilisateurs: la ligne " << ligne
						  << " n'a pas pu être interprétée correctement\n";
				succesParsing = false;
			}
		}
		return succesParsing;
	}
	std::cerr << "Erreur GestionnaireUtilisateurs: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
	return false;
}

/// Ajoute un utilisateur au gestionnaire, en l’insérant dans la map avec son ID comme clé et l’utilisateur comme valeur
/// \param utilisateur      L'utilisateur qui va etre rajouter au gestionnaire.
/// \return                 un bollean qui defini si l'operation a ete un succes ou non
bool GestionnaireUtilisateurs::ajouterUtilisateur(const Utilisateur &utilisateur)
{
	return utilisateurs_.emplace(utilisateur.id, utilisateur).second;
}

/// Supprime un utilisateur du gestionnaire a partir de son ID.
/// \param idUtilisateur    L'id de l'utilisateur qui va etre retirer
/// \return                 un bollean qui defini si l'operation a ete un succes ou non
bool GestionnaireUtilisateurs::supprimerUtilisateur(const std::string &idUtilisateur)
{
	return utilisateurs_.erase(idUtilisateur);
}

/// Retourne le nombre d’utilisateurs présentement dans le gestionnaire.
/// \return     le nombre d'utilisateurs dans le gestionnaire.
std::size_t GestionnaireUtilisateurs::getNombreUtilisateurs() const
{
	return utilisateurs_.size();
}

/// Trouve et retourne un utilisateur en le cherchant a partir de son ID.
/// \param id           L'id de l'utilisateur nous permettant de le retrouver s'il existe.
/// \return             un pointeur vers l’utilisateur trouve, sinon nullptr.
const Utilisateur *GestionnaireUtilisateurs::getUtilisateurParId(const std::string &id) const
{
	return utilisateurs_.find(id) == utilisateurs_.end() ? nullptr : &(utilisateurs_.find(id)->second);
}