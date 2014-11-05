#include "imageniveauxgris.h"
#include <fstream>
#include <iostream>

ImageNiveauxGris::ImageNiveauxGris(const std::string & nomFichierPGM)
{
    /** On considère pour le moment que le fichier ne contient pas de commentaires */

    int temp = 0;
    char t;
    std::ifstream fichier;
    // vérifier extension PGM
    fichier.open(nomFichierPGM.c_str());

    if(fichier)
    {
        fichier >> m_mode_encodage ;
        fichier >> m_nbColonnes >> m_nbLignes >> m_niveauxIntensite;
        m_tableauPixels.resize(m_nbColonnes * m_nbLignes);

        if(m_mode_encodage.compare("P5") == 0) {
            for(int i = 0; i < m_nbColonnes; i++) {
                for(int j = 0; j < m_nbLignes; j++) {
                    fichier >> t ;
                    
                    if(m_niveauxIntensite > 255) {
                        char t2;
                        fichier >> t2 ;

                        elementTableauPixels(j, i) = t*256 + t2;
                         std::cout <<t+256<<t2<<std::endl;  
                   }
                   else elementTableauPixels(j, i) = (int)t;
                
                }
            }
        }
        else if(m_mode_encodage.compare("P2") == 0) {
            
            for(int i = 0; i < m_nbColonnes; i++) {
                for(int j = 0; j < m_nbLignes; j++) {
                    fichier >> temp ;
                    elementTableauPixels(j, i) = temp;
                }
            }
        } 
        else std::cerr << "Mauvais format de fichier." << std::endl;
        
        fichier.close();
    }
    else std::cerr << "Impossible d'ouvrir le fichier pour le lire." << std::endl;
}

ImageNiveauxGris::~ImageNiveauxGris()
{
    std::vector<int>().swap(m_tableauPixels);
}


int & ImageNiveauxGris::elementTableauPixels(int ligne, int colonne)
{
    return m_tableauPixels[ligne * m_nbColonnes + colonne];
}

const int & ImageNiveauxGris::elementTableauPixels(int ligne, int colonne) const
{
    return m_tableauPixels[ligne * m_nbColonnes + colonne];
}

void ImageNiveauxGris::sauverDansFichierPGM(const std::string & nomFichierPGM) const 
{

    std::ofstream fichier;
    fichier.open((nomFichierPGM).c_str());

    if(fichier) {

        fichier << m_mode_encodage << " \n" << m_nbColonnes <<" "
            << m_nbLignes <<"\n"<< m_niveauxIntensite<<" \n";

        for(int i = 0; i < m_nbColonnes; i++) {
            for(int j = 0; j < m_nbLignes; j++) {
                if(m_mode_encodage.compare("P2") == 0) fichier << elementTableauPixels(j, i) <<" ";
                else  fichier << (char)elementTableauPixels(j, i);
            }
        }

        fichier.close();
    }
    else
        std::cerr << "Impossible d'ouvrir le fichier pour écrire dedans." << std::endl;

}
