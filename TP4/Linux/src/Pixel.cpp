#include "Pixel.h"

/**
 * @brief constructeur par défaut de la classe
 */
Pixel::Pixel() : rouge_(0), vert_(0), bleu_(0) {}
/**
 * @brief constructeur par paramètres de la classe
 * @param rouge, l'élément R du pixel, entre 0 -> 255
 * @param vert, l'élément G du pixel, entre 0 -> 255
 * @param bleu, l'élément B du pixel, entre 0 -> 255
 */
Pixel::Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu)
	: rouge_(rouge), vert_(vert), bleu_(bleu) {}

/**
 * @brief copie d'un pixel
 * @param pixel, le pixel à copier
 */

void Pixel::operator=(const Pixel &pixel)
{
	bleu_ = pixel.bleu_;
	rouge_ = pixel.rouge_;
	vert_ = pixel.vert_;
}

/**
 * @brief Set la valeur du paramètre de pixel
 * @param rouge, l'élément Rouge du pixel
 */

void Pixel::setRouge(int rouge)
{
	rouge_ = rouge < 0 ? uint8_t(0)					   // si rouge est < 0 on initialise la variable rouge_ a zero
													   // sinon on continue sur la prochaine ligne
					   : rouge > 255 ? uint8_t(255)	   // si rouge est > 255 on initialise la variable rouge_ a 255
													   // sinon on continue sur la prochaine ligne
									 : uint8_t(rouge); // on initialise la variable rouge_ a rouge
}

/**
 * @brief Set la valeur du paramètre de pixel
 * @param bleu, l'élément vert du pixel
 */
void Pixel::setVert(int vert)
{
	vert_ = vert < 0 ? uint8_t(0)				   // si vert est < 0 on initialise la variable vert_ a zero
												   // sinon on continue sur la prochaine ligne
					 : vert > 255 ? uint8_t(255)   // si vert est > 255 on initialise la variable vert_ a 255
												   // sinon on continue sur la prochaine ligne
								  : uint8_t(vert); // on initialise la variable vert_ a vert
}
/**
 * @brief Set la valeur du paramètre de pixel
 * @param bleu, l'élément bleu du pixel
 */
void Pixel::setBleu(int bleu)
{
	bleu_ = bleu < 0 ? uint8_t(0)				   // si blue est < 0 on initialise la variable blue_ a zero
												   // sinon on continue sur la prochaine ligne
					 : bleu > 255 ? uint8_t(255)   // si blue est > 255 on initialise la variable blue_ a 255
												   // sinon on continue sur la prochaine ligne
								  : uint8_t(bleu); // on initialise la variable blue_ a vert
}
/**
 * @brief retourn l'attribut rouge_ du pixel
 * @return rouge_ du type uint8_t
 */
uint8_t Pixel::getRouge() const { return rouge_; }
/**
 * @brief retourn l'attribut vert_ du pixel
 * @return vert_ du type uint8_t
 */
uint8_t Pixel::getVert() const { return vert_; }
/**
 * @brief retourn l'attribut bleu_ du pixel
 * @return bleu_ du type uint8_t
 */
uint8_t Pixel::getBleu() const { return bleu_; }

/**
 * @brief Opérateur permetant d'afficher un pixel en hexadécimal
 * @param os, le stream d'affichage
 * @param pixel, le pixel à afficher
 * @return ostream
 */

std::ostream &operator<<(std::ostream &os, Pixel pixel)
{
	os << "#";
	os << std::uppercase
	   << std::hex
	   << std::setw(2)
	   << std::setfill('0')
	   << unsigned(pixel.getRouge())
	   << " " << std::setw(2)
	   << unsigned(pixel.getVert())
	   << " " << std::setw(2)
	   << unsigned(pixel.getBleu());
	return os;
}

/**
 * @brief Opérateur permetant d'afficher un pixel en hexadécimal
 * @param os, le stream des donner
 * @param pixel, le pixel qi recevras les donner 
 * @return istream
 */

std::istream &operator>>(std::istream &is, Pixel &pixel)
{
	int rouge, vert, bleu;
	is >> rouge >> vert >> bleu;

	pixel.setRouge(rouge);
	pixel.setBleu(bleu);
	pixel.setVert(vert);

	return is;
}