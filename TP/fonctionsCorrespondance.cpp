#include "fonctionsCorrespondance.h"
#include <iostream>

fonctionsCorrespondance::fonctionsCorrespondance(const ImageNiveauxGris &im): m_image(im), m_histogramme(im)
{
    m_fonction.resize(m_image.getNiveauxIntensite(),0);
}

fonctionsCorrespondance::~fonctionsCorrespondance()
{
    std::vector<int>().swap(m_fonction);
}

ImageNiveauxGris fonctionsCorrespondance::negatif()
{
    ImageNiveauxGris res(m_image.getNbColonnes(),m_image.getNbLignes(), m_image.getNiveauxIntensite(), m_image.getModeEncodage());

    for(int i = 0; i < res.getNbColonnes(); i++) {
        for(int j = 0; j < res.getNbLignes(); j++) {
            res.elementTableauPixels(j,i) = m_image.getNiveauxIntensite() - m_image.elementTableauPixels(j,i);
        }
    }

    return res;
}

ImageNiveauxGris fonctionsCorrespondance::seuillage(const unsigned int seuil)
{
    ImageNiveauxGris res(m_image.getNbColonnes(),m_image.getNbLignes(), m_image.getNiveauxIntensite(), m_image.getModeEncodage());

    for(int i = 0; i < res.getNbColonnes(); i++) {
        for(int j = 0; j < res.getNbLignes(); j++) {
            if(m_image.elementTableauPixels(j,i) > seuil)
                res.elementTableauPixels(j,i) = m_image.getNiveauxIntensite();
            else res.elementTableauPixels(j,i) = 0;
        }
    }

    return res;
}

ImageNiveauxGris fonctionsCorrespondance::translationPositive(const unsigned int pas)
{
    ImageNiveauxGris res(m_image.getNbColonnes(),m_image.getNbLignes(), m_image.getNiveauxIntensite(), m_image.getModeEncodage());

    for(int i = 0; i < res.getNbColonnes(); i++) {
        for(int j = 0; j < res.getNbLignes(); j++) {
                if(m_image.elementTableauPixels(j,i) + pas > m_image.getNiveauxIntensite())
                    res.elementTableauPixels(j,i) = m_image.getNiveauxIntensite();
                else res.elementTableauPixels(j,i) = m_image.elementTableauPixels(j,i) + pas;
        }
    }

    return res;
}

ImageNiveauxGris fonctionsCorrespondance::translationNegative(const unsigned int pas)
{
    ImageNiveauxGris res(m_image.getNbColonnes(),m_image.getNbLignes(), m_image.getNiveauxIntensite(), m_image.getModeEncodage());

    for(int i = 0; i < res.getNbColonnes(); i++) {
        for(int j = 0; j < res.getNbLignes(); j++) {
                if(m_image.elementTableauPixels(j,i) < pas){
                    res.elementTableauPixels(j,i) = 0;
                }
                else res.elementTableauPixels(j,i) = m_image.elementTableauPixels(j,i) - pas;
        }
    }

    return res;
}

ImageNiveauxGris fonctionsCorrespondance::recadrage(const unsigned int min, const unsigned int max)
{
    ImageNiveauxGris res(m_image.getNbColonnes(),m_image.getNbLignes(), m_image.getNiveauxIntensite(), m_image.getModeEncodage());

    for(unsigned int i =0; i < m_fonction.size(); i++){
        if(i <= min ){
            m_fonction[i] = 0;
        }
        else if(i >= max) {
            m_fonction[i] = m_image.getNiveauxIntensite();
        }
        else {
            m_fonction[i] = m_image.getNiveauxIntensite()*i/(max-min) - min*m_image.getNiveauxIntensite()/(max-min);
        }
    }

    for(unsigned int i =0; i < m_fonction.size(); i++){
        std::cout<<m_fonction[i]<<" ";
    }
    std::cout<<std::endl;

    for(unsigned int i = 0; i < res.getNbColonnes(); i++) {
        for(unsigned int j = 0; j < res.getNbLignes(); j++) {
                /*if(m_image.elementTableauPixels(j,i) < min){
                    res.elementTableauPixels(j,i) = 0;
                }
                else if(m_image.elementTableauPixels(j,i) > max){
                    res.elementTableauPixels(j,i) = m_image.getNiveauxIntensite();
                }
                else res.elementTableauPixels(j,i) = m_image.elementTableauPixels(j,i);*/
                //sstd::cout<<m_image.elementTableauPixels(j,i)<<" ";
                res.elementTableauPixels(j,i) = m_fonction[m_image.elementTableauPixels(j,i)];

        }
    }
     std::cout<<std::endl;
/*
    Histogramme h = Histogramme(res);
    h.sauverDansFichierTXT("res_recadrage.txt");
*/
    return res;
}
