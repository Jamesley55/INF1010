/*
 * Titre : AgrandirMatrice.h - Travail Pratique #4 - Programmation Orient�e
 * Objet Date : 27 F�vrier 2020 Auteur : Nabil Dabouz
 */

#ifndef AGRANDIR_MATRICE_H
#define AGRANDIR_MATRICE_H

#include "def.h"

template <class M>
class AgrandirMatrice
{
public:
	AgrandirMatrice();
	AgrandirMatrice(M *matrice);
	~AgrandirMatrice() = default;
	Coordonnees trouverLePlusProcheVoisin(const unsigned int &rapport,
										  size_t posY, size_t posX) const;
	void redimensionnerImage(const unsigned int &rapport);

private:
	M *matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template <class M>
AgrandirMatrice<M>::AgrandirMatrice()
{
	matrice_ = new Matrice();
}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
AgrandirMatrice<M>::AgrandirMatrice(M *matrice) : matrice_(matrice) {}
/**
 * @brief trouver le point le plus proche du point (posX, posY) dans la matrice
 * originale
 * @param rapport, le rapport du redimensionnement de l'image
 * @param posX, la colonne du point dans la nouvelle image
 * @param posY, la ligne du point dans la nouvelle image
 * @return coordonnées du point le plus proche
 */
template <class M>
Coordonnees
AgrandirMatrice<M>::trouverLePlusProcheVoisin(const unsigned int &rapport,
											  size_t posY, size_t posX) const
{

	return {int(posY / rapport), int(posX / rapport)};
}
template <class M>
void AgrandirMatrice<M>::redimensionnerImage(const unsigned int &rapport)
{

	std::unique_ptr<M> copie = matrice_->clone();

	matrice_->setHeight(rapport * matrice_->getHeight());
	matrice_->setWidth(rapport * matrice_->getWidth());

	size_t tailleMatrice = matrice_->getHeight();

	for (size_t heightIndex = 0; heightIndex < tailleMatrice; heightIndex++)
	{
		for (size_t widthIndex = 0; widthIndex < tailleMatrice; widthIndex++)
		{
			Coordonnees position = trouverLePlusProcheVoisin(rapport, heightIndex, widthIndex);
			matrice_->ajouterElement(copie->operator()(position.y, position.x), heightIndex, widthIndex);
		}
	}
}

#endif
