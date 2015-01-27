#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include "image.h"

#include <vector>

class Histogramme
{
private:
	std::vector<int> m_tableauDonnees;
	std::vector<int> m_cumule;
public:
    Histogramme(const Image & img);
	Histogramme();
	// Histogramme(const ImageCouleur & img); travailler sur la luminance
	~Histogramme();

	int getHistogramme(const int i);
	int getCumule(const int i);

	void sauverDansFichierTXT();
	void sauverDansFichierTXT(const std::string & nomFichierTXT);

	void lireDansFichierTXT(const std::string & nomFichierTXT);
};

#endif
