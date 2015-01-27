#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "contour.h"
#include "image.h"
#include "histogramme.h"
#include "fonctionsCorrespondance.h"
#include "fourier.h"
#include "filtre.h"

int main(int argc, char* argv[])
{

	std::string out = "fourier.pgm", out2 = "retour.pgm";
 /*   if (argc < 2)
        in = "Image/lena.ascii.pgm";
    else in = argv[1];

    if (argc > 2)
        out = argv[2];
    else out = "Image/res.pgm";

   Image im(in);

    //Image im2(im);

    //im2.sauverDansFichierPGM(out);

  FonctionsCorrespondance f(im);

  Image res = f.translation(200);
   //Image res(im);

 	Histogramme h = Histogramme(im);
	h.sauverDansFichierTXT("im.txt");
 	h = Histogramme(res);
	h.sauverDansFichierTXT("res.txt");

   im.sauverDansFichierPGM(out);
*/
    Image img("Image/lena.ascii.pgm");
	Fourier f;
	f.calculeFourierRapide(img);
	Filtre filtre(f);
	filtre.passeHautIdeal(10);
	Image test(img.getNbColonnes(), img.getNbLignes(), 
		img.getNiveauxIntensite(), img.getModeEncodage());
	test.m_tableauPixels.resize(f.m_fourier.size());
	for(int i = 0; i < f.m_fourier.size(); i++) {
		test.m_tableauPixels[i] = (f.m_fourier[i].real() > 0.025)? 255 : 0;
	}
	std::cout << std::endl;
	Image ret = f.fftinverseImg();
	test.sauverDansFichierPGM(out);
	ret.sauverDansFichierPGM(out2);

    return 0;
}
