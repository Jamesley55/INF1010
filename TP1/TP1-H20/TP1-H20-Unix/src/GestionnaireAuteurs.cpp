/* ////////////////////////////////////////////////////////////////
/	*TD1 : fichier Gestionnaireauteurs.cpp                        /
/	*travail fait par Jamesley Joseph : 1990552                    /
/					   Wael tarifi :  1991935                     /
/                                                                 /
/	*Date de remise : 28 janvier 2020 à 23h55                     /
/   * Description: Implementation de la classe GestionnaireAuteurs/
*//////////////////////////////////////////////////////////////////
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include"GestionnaireAuteurs.h"
 using namespace std; 

/****************************************************************************
 * Fonction: GestionnaireAuteurs:: GestionnaireAuteurs
 * Description:  Constructeur par defaut de la class GestionnaireAuteurs
 * Paramètres: aucun
 * Retour: aucun
 ****************************************************************************/
 GestionnaireAuteurs::GestionnaireAuteurs():
 nbAuteurs_(0)
 {}


/****************************************************************************
 * Fonction: GestionnaireAuteurs:: GestionnaireAuteurs
 * Description:  Ajouter un auteur au tableau des auteurs
 * Paramètres: const Auteur& auteur : l'auteur a ajoute
 * Retour: (bool) un bool representant si l'auteur a ete aujoute(true) ou pas(false)
 ****************************************************************************/
bool GestionnaireAuteurs::ajouterAuteur(const Auteur& auteur)
{
     if(nbAuteurs_ == NB_AUTEURS_MAX)
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


/****************************************************************************
 * Fonction: GestionnaireAuteurs:: chercherAuteur
 * Description:  Chercher dans la liste des auteurs si un auteur comporte le nom passe en parametre.
 * Paramètres: const std:: string& nomAuteur : le nom de l'auteur a trouve
 * Retour: (Auteur*) : un pointeur vers l'auteur dans la liste
 ****************************************************************************/
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

//! \param nomFichier   Le nom du fichier à charger.
//! \return             Un bool représentant si le chargement a été un succès.

/****************************************************************************
 * Fonction: GestionnaireAuteurs:: chargerDepuisFichier
 * Description: Methode qui prend un nom de fichier en parametre et qui charge les auteurs
 * Paramètres: const std::string& nomFichier : le nom du fichier
 * Retour: (bool) Un bool representant si le chargement a ete un succes
 ****************************************************************************/
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier) // on verifie dabord si le fichier existe
    {
        // TODO: envoyer chaque ligne à lireLigneAuteur
        string ligne = ""; 
        while (getline(fichier,ligne)) // li chaque ligne  du fichier une par une 
        {
             if(!lireLigneAuteur(ligne))
             {
                 return false; // on retourne false si le fichier est vide; 
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

/****************************************************************************
 * Fonction: GestionnaireAuteurs:: getNbAuteurs const
 * Description:  Retourne le nombre d'auteur dans la liste
 * Paramètres: aucun
 * Retour: (std::size_t) : le nombre d'auteur dans la liste
 ****************************************************************************/
std::size_t GestionnaireAuteurs::getNbAuteurs() const {return nbAuteurs_; }


//! \param ligne Le string qui comporte tous les attributs de l'auteur.
/****************************************************************************
 * Fonction: GestionnaireAuteurs:: lireLigneAuteur
 * Description:  Methode qui ajoute un auteur avec un string
 * Paramètres: const std::string& ligne : Le ligne de ficher qui contient les attributs de l'auteur
 * Retour: (bool) un bool representant si l'operation a ete effectue avec succes
 ****************************************************************************/
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne)
{
    std::istringstream stream(ligne); // li la ligne du fichier
    std::string nom;
    unsigned int age;

       stream >> std::quoted(nom) >> age; // intisialise l'attribut nom au premier mot entre guillemet
       // ainsi que l'atribue d'age   

      Auteur nouvelleAuteur(nom,age);  // cree un nouveallAuteur avec les parametre initialiser 
      return ajouterAuteur(nouvelleAuteur); // ajoute l'auteur a la liste des auteurs
    
   
     

    
}