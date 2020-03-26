/*
 * Titre : Matrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz
 */

#ifndef MATRICE_H
#define MATRICE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

template <typename T>
class Matrice
{

public:
	Matrice();
	// Destructeur
	~Matrice() = default;
	T operator()(const size_t &posY, const size_t &posX) const;
	// Lecture du fichier
	bool chargerDepuisFichier(const std::string &nomFichier);
	bool lireElement(const std::string &elementFichier, const size_t &posY,
					 const size_t &posX);
	// Remplir un matrice
	bool ajouterElement(T element, const size_t &posY, const size_t &posX);
	// Faire une copie
	std::unique_ptr<Matrice<T>> clone() const;
	// Setters
	void setHeight(size_t height);
	void setWidth(size_t width);
	// Getters
	size_t getHeight() const;
	size_t getWidth() const;

private:
	std::vector<std::vector<T>> elements_;
	size_t height_;
	size_t width_;
};

namespace
{
static constexpr int CAPACITE_MATRICE = 100;
}

/**
 * @brief constructeur par défaut de la classe
 */
template <typename T>
inline Matrice<T>::Matrice()
{
	height_ = 0;
	width_ = 0;
	elements_ = CAPACITE_MATRICE;
}
/**
 * @brief retourne le nombre de lignes de la matrice
 * @return l'attribut height_ de l'objet
 */
template <typename T>
inline size_t Matrice<T>::getHeight() const
{
	return height_;
}
/**
 * @brief retourne le nombre de colonnes de la matrice
 * @return l'attribut width_ de l'objet
 */
template <typename T>
inline size_t Matrice<T>::getWidth() const
{
	return width_;
}
template <typename T>
T Matrice<T>::operator()(const size_t &posY, const size_t &posX) const
{
	posY > height_ || posX > width_ ? return T();
	return elements_[posX][posY];
}

template <typename T>
bool Matrice<T>::ajouterElement(T element, const size_t &posY, const size_t &posX)
{
	elements_[posX][posY] = elements;
	return true;
}
template <typename T>
bool Matrice<T>::lireElement(const std::string &elementFichier, const size_t &posY,
							 const size_t &posX)
{
	T element;
	std::stringstream input(elementFichier);
	input >> element;
	return (ajouterElement(element, posY, posX));
}
template <typename T>
bool Matrice<T>::chargerDepuisFichier(const std::string &nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		std::string ligne;
		size_t x = 0;
		size_t y = 0;

		while (std::getline(fichier, ligne))
		{
			if (ligne == "L" && x != 0)
			{
				if (width_ < x)
					setWidth(x);

				y++;
				x = 0;
			}

			else if (ligne != "L")
			{
				lireElement(ligne, y, x);
				x++;
			}
		}
		setHeight(y + 1);
	}
	return true;
}
template <typename T>
std::unique_ptr<Matrice<T>> Matrice<T>::clone() const
{
	auto mat = std::make_unique<Matrice>(*this);
	return std::move(mat);
}
template <typename T>
void Matrice<T>::setHeight(size_t height)
{
	height_ = height;
}
template <typename T>
void Matrice<T>::setWidth(size_t width)
{
	width_ = width;
}
#endif
