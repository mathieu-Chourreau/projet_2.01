#include "lecteur.h"
#include <QDialog>
#include <QDebug>


Lecteur::Lecteur()
{
    _numDiaporamaCourant = 0;   // =  le lecteur est vide
}

void Lecteur::avancer()
{
    // Si la position de l'image courante est inférieure au nombre d'images du diaporama  - 1
    // alors on peut incrémenter la position de l'image courante
    if(_posImageCourante < nbImages() - 1)
    {
        _posImageCourante++;
    }
    // Sinon on remet la position de l'image courante à 0 car l'image actuelle est la dernière du diaporama
    else
    {
        _posImageCourante = 0;
    }

    // Vérifie si le bouton fonctionne
    qDebug()<<"avancer"<< Qt::endl;
}

void Lecteur::reculer()
{
    // Si la position de l'image courante est supérieur à 0
    // alors on peut décrémenter la position de l'image courante
    if(_posImageCourante > 0 )
    {
        _posImageCourante--;
    }
    // Sinon on remet la position de l'image courante à "nombres d'images - 1" car l'image actuelle est la première du diaporama
    else
    {
        _posImageCourante = nbImages() - 1;
    }

    // Vérifie si le bouton fonctionne
    qDebug()<<"reculer"<< Qt::endl;
}

void Lecteur::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama(); // charge le diaporama courant
    }
}

//echange
void Lecteur::echanger(Image* image1, Image*image2)
{
    // variable
    Image copieImage;

    //echange
    copieImage = *image1;
    *image1 = *image2;
    *image2 = copieImage;
}

void Lecteur::faireMonteeLaBulleIci(Diaporama _diaporama, unsigned short int bDeb , short unsigned int ici)
{
    //Faire monter tri bulleIci
    for (unsigned short int i = bDeb; i < ici; i++)
    {
        if (_diaporama[i]->getRang() >_diaporama[i+1]->getRang())
        {
            echanger(_diaporama[i], _diaporama[i+1]);
        }
    }
}

void Lecteur::triBulle (Diaporama _diaporama)
{
    short unsigned int bDeb;
    //TRAITEMENTS
    bDeb=0;

    for (unsigned short int ici = nbImages() - 1; ici > bDeb; ici--)
    {
        faireMonteeLaBulleIci(_diaporama, bDeb, ici);
    }
}

void Lecteur::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */
    Image* imageACharger;
    imageACharger = new Image(3, "personne", "Blanche Neige", "F:\\1erAnnee\\S2\\S2.01_fin\\cartesDisney\\Disney_4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", "F:\\1erAnnee\\S2\\S2.01_fin\\cartesDisney\\Disney_21.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Mickey", "F:\\1erAnnee\\S2\\S2.01_fin\\cartesDisney\\Disney_19.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Grincheux", "F:\\1erAnnee\\S2\\S2.01_fin\\cartesDisney\\Disney_31.gif");
    _diaporama.push_back(imageACharger);


     //trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama

     triBulle(_diaporama);

     _posImageCourante = 0;

     cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
     cout << nbImages() << " images chargees dans le diaporama" << endl;

}

void Lecteur::viderDiaporama()
{
    if (nbImages () > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back(); /* Removes the last element in the vector,
                                      effectively reducing the container size by one.
                                      AND deletes the removed element */
        }
     _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;

}

void Lecteur::afficher()
{
    /* affiche les informations sur le lecteur :
     * 1) vide (si num. de diaporama = 0) OU BIEN  numéro de diaporama affiché
     * 2) Si un diaporama courant est chargé (num. de diaporama > 0), affiche l'image courante OU BIEN 'diaporama vide'
     *     si ce diaporama n'a aucun image */
    if (numDiaporamaCourant() == 0)
    {
        cout << "Lecteur vide" << endl ;
    }
    else
    {
        cout << "Diaporama num. " << numDiaporamaCourant() << endl;

        if (nbImages() > 0)
        {
            cout << "image courante : ";
            cout << endl;
        }
        else
        {
            cout << "diaporama vide" << endl ;
        }

    }
}

unsigned int Lecteur::nbImages()
{
    return _diaporama.size();
}

Image *Lecteur::imageCourante()
{
   return _diaporama[_posImageCourante];
}

unsigned int Lecteur::numDiaporamaCourant()
{
    return _numDiaporamaCourant;
}
