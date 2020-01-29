// TODO: Faire l'entête de fichier
/* ////////////////////////////////////////////////////////////////
/	*TD1 : fichier Gestionnaireauteurs.cpp                        /
/	*travail fait par Jamesley Joseph : 1990552                   /
/					   Wael tarifi :  1991935                     /
/                                                                 /
/	*Date de remise : 28 janvier 2020 à 23h55                     /
/   * Description: Implementation de la classe GestionnaireAuteurs/
*//////////////////////////////////////////////////////////////////
// TODO: Inclure la définition de la classe appropriée
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include"GestionnaireAuteurs.h"
 using namespace std; 
// TODO: Constructeur par défault en utilisant la liste d'initialisation
 GestionnaireAuteurs::GestionnaireAuteurs():
 nbAuteurs_(0)
 {}

// TODO ajouterAuteur(const Auteur& auteur)
// Ajouter un auteur au tableau des auteurs.
// Retourner false si il n'y a plus de place dans le tableau.
bool GestionnaireAuteurs::ajouterAuteur(const Auteur& auteur)
{
     if(nbAuteurs_ >= NB_AUTEURS_MAX)
     {
         return false; 
     }
     else
     {
         nbAuteurs_++;
         auteurs_[nbAuteurs_] = auteur; 
         return true; 
     }
}


// TODO chercherAuteur(const std::string& nomAuteur)
 Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur)
 {
         for(std::size_t i =0; i < nbAuteurs_; i++)
         {
             if(auteurs_[i].getNom()==nomAuteur)
             {
                    
                    return &auteurs_[i]; 
                    
             }
             
         }
         return nullptr; 
 }
// Chercher dans la liste des auteurs si un auteur comporte le nom passé en
// paramètre. Retourner un nullptr si ce n'est pas le cas.

//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs.
//! \param nomFichier   Le nom du fichier à charger.
//! \return             Un bool représentant si le chargement a été un succès.
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // TODO: envoyer chaque ligne à lireLigneAuteur
        string ligne = ""; 
        while (getline(fichier,ligne))
        {
             if(!lireLigneAuteur(ligne))
             {
                 return false; 
             }
        }
        return true;
            

    }
    else{
     
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
         }
 return false;      

}

//! Méthode qui affiche la liste des auteurs.
//! \param stream Le stream dans lequel afficher.
void GestionnaireAuteurs::afficher(std::ostream& stream) const
{
    // Ne pas modifier cette méthode
    for (std::size_t i = 0; i < nbAuteurs_; i++)
    {
        auteurs_[i].afficher(stream);
        stream << '\n';
    }
}

// TODO getNbAuteurs() const: Retourner le nombre d'auteurs dans la liste
std::size_t GestionnaireAuteurs::getNbAuteurs() const {return nbAuteurs_; }

//! Méthode qui ajoute un auteur avec un string.
//! \param ligne Le string qui comporte tous les attributs de l'auteur.
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nom;
    unsigned int age;

    // TODO
    // Utiliser l'opérateur d'extraction (>>) depuis le stream
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)

       stream >> std::quoted(nom) >> age; // li le nom qui se trouve entre "" et l'age 
    // puisque l'age est une int alors il n'y a pas de quote. 

      Auteur nouvelleAuteur(nom,age); 
      return ajouterAuteur(nouvelleAuteur); 
    
   
     

    
}