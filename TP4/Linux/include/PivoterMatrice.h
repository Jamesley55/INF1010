/*
 * Titre : PivoterMatrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz
 */

#ifndef PIVOTER_MATRICE_H
#define PIVOTER_MATRICE_H

#include "def.h"

template <class M>
class PivoterMatrice
{
public:
	// Constructeurs
	PivoterMatrice();
	PivoterMatrice(M *matrice);
	// Destructeur
	~PivoterMatrice() = default;
	void pivoterMatrice(Direction direction);

private:
	Coordonnees changerCoordonneesCentreMatrice(Coordonnees coords) const;
	Coordonnees recupererCoordonnees(Coordonnees coords) const;
	M *matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template <class M>
inline PivoterMatrice<M>::PivoterMatrice()
{
	matrice_ = new M();
}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
inline PivoterMatrice<M>::PivoterMatrice(M *matrice) : matrice_(matrice) {}
/**
 * @brief trouver les coordonnées du point par rapport au centre de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const
{
	// TO DO
	return {
		coords.y - int(matrice_->getHeight() / 2), // coordoner en y
		coords.x - int(matrice_->getWidth() / 2)   // coordoner en x
	};
}
/**
 * @brief revenir au système précédent, trouver les coordonnées du point par
 * rapport au premier élément de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const
{
	// TO DO
	return {
		coords.y + int(matrice_->getHeight() / 2), // coordoner en y
		coords.x + int(matrice_->getWidth() / 2)   // coordoner en x
	};
}
template <class M>
void PivoterMatrice<M>::pivoterMatrice(Direction direction)
{
	int x, y;
	std::unique_ptr<M> copie = matrice_->clone();
	size_t Height = matrice_->getHeight();
	size_t width = matrice_->getWidth();

	for (int heightIndex = 0; heightIndex < int(Height); heightIndex++)
	{
		for (int widthIndex = 0; widthIndex < int(width); widthIndex++)
		{

			auto coo = changerCoordonneesCentreMatrice({widthIndex, heightIndex});
			if (direction == Direction::Right)
			{
				x = coo.y, y = -coo.x;
			}
			else if (direction == Direction::Left)
			{
				x = -coo.y, y = coo.x;
			}
			coo = recupererCoordonnees({x, y});
			matrice_->ajouterElement(copie->operator()(heightIndex, widthIndex), coo.y, coo.x);
		}
	}
}

#endif
