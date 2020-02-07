#ifndef AUTEUR_H
#define AUTEUR_H

#include <string>
#include <vector> 
#include <iostream> 


class Auteur
{
public:
    Auteur() = default;
    Auteur(const std::string& nom, unsigned int anneeDeNaissance);

    void afficher(std::ostream& stream) const;


    const std::string& getNom() const;
    unsigned int getAnneeDeNaissance() const;
    unsigned int getNbFilms() const;
    friend std::ostream& operator<<(std::ostream &o,const Auteur &auteur); 
    
    bool operator== (const std::string & motComparer) const; 
    friend bool operator==(const std::string& motComparer, const Auteur &newAuteur); 
    void setNbFilms(unsigned int nbFilms);

private:
    std::string nom_;
    unsigned int anneeDeNaissance_;
    unsigned int nbFilms_;
};


#endif // AUTEUR_H