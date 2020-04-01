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
	elements_ = std::vector<std::vector<T>>(CAPACITE_MATRICE);
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

/**
 * @brief Retourne l’élément se trouvant à la ligne posY et la colonne posX du tableau elements_.
 * @param posY, la colonne du point dans la nouvelle image
 * @param posX, la ligne du point dans la nouvelle image
 * @return l'élément a la position (x,y), si non trouvé, retourne T()
 */
template <typename T>
T Matrice<T>::operator()(const size_t &posY, const size_t &posX) const
{
	if (posY > height_ || posX > width_)
	{
		return T();
	}
	return elements_[posX][posY];
}
/**
 * @brief ajoute un element dans un tableau d'element 
 * @param element l'element quon veut ajouter  dans le tableau 
 * @param posY, la position  y de l'ement a ajouter dans le tableau 
 * @param posX, la position x de l'element a ajouter dans le tableau 
 * @return true si l'operation est un succes
 */
template <typename T>
bool Matrice<T>::ajouterElement(T element, const size_t &posY, const size_t &posX)
{
	if (posY > height_ || posX > width_)
	{
		return false;
	}
	elements_[posY][posX] = element;
	return true;
}

template <typename T>
bool Matrice<T>::lireElement(const std::string &elementFichier, const size_t &posY,
							 const size_t &posX)
{
	std::istringstream input(elementFichier);
	T element;
	if (input >> element)
	{
		return (ajouterElement(element, posY, posX));
	}
	return false;
}

/* @brief Lit les éléments d'une matrice depuis un fichier et les ajoutes
 * @param nomFichier, le fichier contenant la matrice
 * @return un bool; true si l'opération a réussi, sinon false si échec
 */
template <typename T>
bool Matrice<T>::chargerDepuisFichier(const std::string &nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier.is_open())
	{
		std::string str;
		int taille = 0;
		while (!fichier.eof())
		{
			fichier >> str;
			if (str == "L")
			{
				taille++;
			}
		}

		for (int i = 0; i < taille; i++)
		{
			elements_[i].resize(taille);
		}

		width_ = height_ = taille;

		fichier.clear();
		fichier.seekg(0, std::ios::beg);
		std::string line;
		int y = 0;
		std::getline(fichier, line);
		for (int i = 0; i < taille; i++)
		{
			for (int j = 0; j < taille; j++)
			{
				std::getline(fichier, line);
				lireElement(line, y, j);
			}
			++y;
			std::getline(fichier, line);
		}

		return true;
	}
	std::cout << "fichier introuvable";
	return false;
}
/**
 * @brief Copie une matrice  
 * @return un pointeur vers la matrice copiée
 */

template <typename T>
std::unique_ptr<Matrice<T>> Matrice<T>::clone() const
{
	auto clone = std::make_unique<Matrice>(*this);
	return std::move(clone);
}

/** @brief Set la valeur height_ et fait un resize de la matrice
 * @param height, la valeur à setter height_
 */
template <typename T>
void Matrice<T>::setHeight(size_t height)
{
	bool a = (height > CAPACITE_MATRICE);
	bool b = (height < 0);
	height_ = height - (height - CAPACITE_MATRICE) * a - height * b;
	elements_.resize(height);
}
/**
 * @brief Set la valeur width_ et fait un resize de la matrice
 * @param width, la valeur à setter width_
 */

template <typename T>
void Matrice<T>::setWidth(size_t width)
{
	bool a = (width > CAPACITE_MATRICE);
	bool b = (width < 0);
	width_ = width - (width - CAPACITE_MATRICE) * a - width * b;
	for (unsigned int i = 0; i < elements_.size(); i++)
		elements_[i].resize(width_);
}
#endif
