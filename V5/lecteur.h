#ifndef LECTEUR_H
#define LECTEUR_H
#include "image.h"
#include "database.h"
#include <vector>
#include <QObject>
#include <QDebug>



typedef vector<Image*> Diaporama;   // Structure de données contenant les infos sur les images

class LecteurVue;
class Lecteur : public QObject
{
    Q_OBJECT

public:
    //getters et setters des attributs privés de LecteurVue
    LecteurVue* getLecteurVue();
    void setLecteurVue(LecteurVue* lv);

    //getters et setters des attributs privés de Image
    Image* getImage();
    void setImage(Image* i);

public:
    Lecteur();
    void avancer();             // incrémente _posImageCourante, modulo nbImages()
    void reculer();             // décrémente _posImageCourante, modulo nbImages()
    void afficher();            // affiche les informations sur lecteur-diaporama et image courante
    unsigned int nbImages();    // affiche la taille de _diaporama
    Image* imageCourante();     // retourne le pointeur vers l'image courante
    unsigned int numDiaporamaCourant();
    void viderDiaporama();      // vide _diaporama de tous ses objets image et les delete
    void changerDiaporama(unsigned int pNumDiaporama);    // permet de choisir un diaporama, 0 si aucun diaporama souhaité

private:
    unsigned int _numDiaporamaCourant;   // numéro du diaporama courant, par défaut 0
    Diaporama _diaporama;            // pointeurs vers les images du diaporama
    unsigned int _posImageCourante;  /* position, dans le diaporama,
                                        de l'image courante.
                                        Indéfini quand diaporama vide.
                                        Démarre à 0 quand diaporama non vide */
private:

    void chargerDiaporama();    // charge dans _diaporama les images du _numDiaporamaCourant
    void echanger(Image*, Image*);
    void faireMonteeLaBulleIci(Diaporama, unsigned short int, short unsigned int);
    void triBulle (Diaporama);

    Image *_image;   // pointeur sur le modèle
    LecteurVue *_leLecteurVue;  // pointeur sur la vue
    Database *db;

};

#endif // LECTEUR_H
