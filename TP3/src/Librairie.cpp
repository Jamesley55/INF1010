#include "Librairie.h"


// To do
Librairie::Librairie(const Librairie& librairie)
{
    *this = librairie; 
}

// To do
Librairie& Librairie::operator=(const Librairie& librairie)
{
    if (&librairie != this) {
		for (std::size_t i = 0; i < librairie.medias_.size(); i++) {
			medias_.push_back(move(librairie.medias_[i]->clone()));
		}
	}

	return *this;
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    medias_.clear();
}

// To do
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
     Media *media = chercherMedia(nomFilm, Media::TypeMedia::Film); 

     return dynamic_cast<Film*>(media); 
    
}

// To do
Serie* Librairie::chercherSerie(const std::string& nomSerie)
{
    Media *medias = chercherMedia(nomSerie, Media::TypeMedia::Serie);
    if(!medias){
        return nullptr; 
    }
    return dynamic_cast<Serie*>(medias);
}

// To do
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
    size_t index = trouverIndexMedia(nomSerie); 
    if(index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Saison){
          *dynamic_cast<GestionnaireSaisons*>(medias_[index].get())+= move(saison);
    }
}

// To do
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
    size_t index = trouverIndexMedia(nomSerie); 
    if(index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Saison){
        *dynamic_cast<GestionnaireSaisons*>(medias_[index].get()) -= numSaison; 
    }
}

// To do
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,
                               std::unique_ptr<Episode> episode)
{
    size_t index = trouverIndexMedia(nomSerie); 
    if(index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Episode){
     
       dynamic_cast<GestionnaireSaisons*>(medias_[index].get())->ajouterEpisode(numSaison, move(episode));
    }
}


void Librairie::retirerEpisode(const std::string& nomSerie, unsigned int numSaison,
                               unsigned int numEpisode)
{
     size_t index = trouverIndexMedia(nomSerie); 
    if(index != MEDIA_INEXSISTANT && medias_[index]->getTypeMedia() == Media::TypeMedia::Episode){
     
       dynamic_cast<GestionnaireSaisons*>(medias_[index].get())->retirerEpisode(numSaison,numEpisode);
    }
}

//! Méthode qui charge les series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un serie à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerMediasDepuisFichier(const std::string& nomFichier,
                                           GestionnaireAuteurs& gestionnaireAuteurs)
{
    // To do
   std::ifstream fichier(nomFichier);
    if (fichier)
    {
        std::string ligne;
	    while (getline(fichier, ligne)) {
		lireLigneMedia(ligne, gestionnaireAuteurs);
	}
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui charge les restrictions des series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (size_t i = 0; i < medias_.size(); i++)
            medias_[i]->supprimerPaysRestreints();

        std::string ligne;
        while (getline(fichier, ligne))
            if (!lireLigneRestrictions(ligne))
                return false;

        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

// To do
size_t Librairie::getNbMedias() const
{
    return medias_.size(); 
}

// To do
std::ostream& operator<<(std::ostream& os, const Librairie& librairie)
{
    for(std::size_t i =0 ; i < librairie.medias_.size(); i++){
     
     os << *(librairie.medias_[i]) ; 

    }
    return os; 
}

// To do
size_t Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
    for(unsigned int i = 0; i < medias_.size(); i++){
            if(nomMedia == medias_[i]->getNom()){
                return i;

            }
    }
    return MEDIA_INEXSISTANT; 
}

// To do
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{ 
    if(media == nullptr){
        return *this; 
    }

    medias_.push_back(std::move(media));
    return *this;  
}

// To do
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
    size_t index = trouverIndexMedia(nomMedia);

    if(index != MEDIA_INEXSISTANT){
        medias_.erase(medias_.begin() +index); 
    }
    return *this;
}

// To do
Media* Librairie::chercherMedia(const std::string& nomMedia, Media::TypeMedia typeMedia)
{
    size_t index = trouverIndexMedia(nomMedia); 
    
    if(index != MEDIA_INEXSISTANT){

        Media *media = medias_[index].get(); 
        if(medias_[index]->getTypeMedia() == typeMedia){
           return media; 
        }
    }
    return nullptr; 
}

// To do
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomMedia;

    int mediaValeurEnum;
    stream >> mediaValeurEnum;
    if (stream >> std::quoted(nomMedia))
    {
        Media* media = chercherMedia(nomMedia, to_enum<Media::TypeMedia>(mediaValeurEnum));

        if (media == nullptr)
        {
            // Media n'existe pas
            return false;
        }

        int paysValeurEnum;
        while (stream >> paysValeurEnum)
        {
            media->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
        }
        return true;
    }
    return false;
}

// To do
bool Librairie::lireLigneMedia(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    lireLigneMediaFunction fonctionLireligne[] = {&Librairie::lireLigneFilm,
                                                  &Librairie::lireLigneSerie,
                                                  &Librairie::lireLigneSaison,
                                                  &Librairie::lireLigneEpisode};
    std::istringstream stream(ligne);
    int typeMediaValeurEnum;

    if (stream >> typeMediaValeurEnum)
        return invoke(fonctionLireligne[typeMediaValeurEnum], *this, stream, gestionnaireAuteurs);

    return false;
}

// To do
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
    return medias_; 
}

// To do
bool Librairie::lireLigneEpisode(std::istream& is, GestionnaireAuteurs&)
{
    Episode episode;
	is >>  episode;
	auto ptrEpisode = std::make_unique<Episode>(episode);
	std::string nomSerie;
	int numSaison;
	is >> quoted(nomSerie) >> numSaison;
	ajouterEpisode(nomSerie, numSaison, move(ptrEpisode));

	return true;
}

// To do
bool Librairie::lireLigneSaison(std::istream& is, GestionnaireAuteurs&)
{
    Saison saison;
	is >>  saison;
	auto ptrSaison = std::make_unique<Saison>(saison);
	std::string nomSaison;
	is >> quoted(nomSaison);
	ajouterSaison(nomSaison, move(ptrSaison));

	return true;
}

// To do
bool Librairie::lireLigneSerie(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::string nomAuteur;
	is >> quoted(nomAuteur);
	Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
	if (auteur) {
	    auto  serie = std::make_unique<Serie>(Serie(auteur));
		is >> *serie;
		if (!chercherMedia(serie->getNom(), Media::TypeMedia(1))) {
			*this += move(serie);
			auteur->setNbMedias(auteur->getNbMedias() + 1);
			return true;
		}
	}
	return false;
}

// To do
bool Librairie::lireLigneFilm(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
   std::string nomAuteur;
   is >> nomAuteur; 
   Auteur* auteur =  gestionnaireAuteurs.chercherAuteur(nomAuteur);
   if(auteur){

        auto film = std::make_unique<Film>(Film(auteur));
		is >> *film;
		if (!chercherMedia(film->getNom(), Media::TypeMedia(0))) {
			*this += move(film);
			auteur->setNbMedias(auteur->getNbMedias() + 1);
			return true;
            }
   }
   return false; 

}

// To do
size_t Librairie::getNbFilms() const
{
    size_t nbFilm  = 0;

 for(size_t i =0; i < medias_.size(); i++)
 {
     
     if(medias_[i]->getTypeMedia() == Media::TypeMedia::Film)
     {
         nbFilm++;
     }
 }
 return nbFilm; 
}

// To do
size_t Librairie::getNbSeries() const
{
    size_t nbSeries  = 0;

 for(size_t i =0; i < medias_.size(); i++)
 {
     
     if(medias_[i]->getTypeMedia() == Media::TypeMedia::Serie)
     {
         nbSeries++;
     }
 }
 return nbSeries; 
}

// To do
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
    size_t index = trouverIndexMedia(nomSerie);
	if (index!=-MEDIA_INEXSISTANT) {
		if (auto serie = dynamic_cast<Serie*>(medias_[index].get())) {
			return serie->getNbSaisons();
		}
	}
	return 0;
}

// To do
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
size_t index = trouverIndexMedia(nomSerie);
	if (index != MEDIA_INEXSISTANT) {
		if (auto serie = dynamic_cast<Serie*>(medias_[index].get())) {
			if(serie->getSaison(numSaison)){
				return serie->getSaison(numSaison)->getNbEpisodes();
			}
		}
			
	}
	return 0;}
