/// Foncteurs.
/// \author Jamesley Joseph
/// \date 2020-04-15

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include "LigneLog.h"

class EstDansIntervalleDatesFilm
{
public:
	/// Constructeur par parametre de la classe EstDansIntervalleDatesFilm
	/// \param bornInferieurAnnee               la borne inferieur d'annee dans l'interval
	/// \param bornSuperieurAnnee               la borne superieur d'annee dans l'interval
	EstDansIntervalleDatesFilm(int borneInferieurAnnee,
							   int BorneSuperieurAnnee)
		: borneInferieurAnnee_(borneInferieurAnnee),
		  borneSuperieurAnnee_(BorneSuperieurAnnee)
	{
	}

	/// Retourne true si l’année de sortie est à l’intérieur de l’intervalle d’années (inclusivement), false sinon
	/// \param film			         Le film sur lequel on va analyser son anee de sortie
	/// \return						 un bollean qui defini  si le film est dans l'intervalle ou non
	bool operator()(const std::unique_ptr<Film> &film) const
	{
		return (borneInferieurAnnee_ <= film->annee && film->annee <= borneSuperieurAnnee_);
	}

private:
	int borneInferieurAnnee_;
	int borneSuperieurAnnee_;
};

class ComparateurLog
{
public:
	/// Il  retourne  true  si la  date  de  la première LigneLogenvoyée en paramètre
	/// est strictement plus ancienneque la date de la deuxième LigneLog, false sinon
	/// \param ligneLog1	        Le premier log qui doit etre plus recent que le deuxieme.
	/// \param ligneLog2	        Le deuxieme log qui doit etre plus vieux que le premier.
	/// \return						un bollean qui defini si le premier log est plus recent que le deuxieme ou non
	bool operator()(const LigneLog &ligneLog1, const LigneLog &ligneLog2) const
	{
		return ligneLog1.timestamp < ligneLog2.timestamp;
	}
};

template <typename T1, typename T2>
class ComparateurSecondElementPaire
{
public:
	///retourne true si le second élément de la première paire est strictement
	///inférieur au second élément de la deuxième paire, false sinon.
	/// \param paire1   Le premier paire que ca valeur doit etre inferieur a la  deuxieme.
	/// \param paire2   Le deuxieme paire que ca valeur doit etre superieur a la premier.
	/// \return         un bollean qui defini si la premier paire est inferieur a la deuxieme ou non
	bool operator()(const std::pair<T1, T2> &paire1, const std::pair<T1, T2> &paire2)
	{
		return paire1.second < paire2.second;
	}
};

#endif // FONCTEURS_H
