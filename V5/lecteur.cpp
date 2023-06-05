#include "lecteur.h"
#include "lecteurvue.h"
#include <QSqlQuery>
#include <QDialog>
#include <QDebug>


Lecteur::Lecteur()
{
    _numDiaporamaCourant = 0;   // =  le lecteur est vide
}

Image *Lecteur::getImage()
{
    return _image;
}

LecteurVue *Lecteur::getLecteurVue()
{
    return _leLecteurVue;
}

void Lecteur::setLecteurVue(LecteurVue *lv)
{
    _leLecteurVue =lv;
}

void Lecteur::setImage(Image *i)
{
    _image = i;
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


    // Met à jour LecteurVue
    getLecteurVue()->mettreAJourVue();

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

    // Met à jour LecteurVue
    getLecteurVue()->mettreAJourVue();

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

    // Met à jour LecteurVue
    getLecteurVue()->mettreAJourVue();
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
    db=new Database();
    db->openDataBase();


    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */
    Image* imageACharger;
    QSqlQuery maRequete;
    // ecrire et lancer la requete Sql + on choisit le diaporama de madame Dagorret par défault
    QString leContenuRequete=("SELECT rang, titrePhoto, uriPhoto, nomFamille "
                       "FROM Diapos D "
                       "JOIN DiaposDansDiaporama DDD ON D.idphoto = DDD.idDiapo "
                       "JOIN Diaporamas ON DDD.idDiaporama = Diaporamas.idDiaporama "
                       "JOIN Familles F ON D.idFam = F.idFamille "
                       "WHERE Diaporamas.idDiaporama= 1 "
                       "ORDER BY rang; ");

    //initialisation des variables
    unsigned int rang;
    QString titrePhoto;
    QString uriPhoto;
    QString nomFamille;
    std::string cheminAcces="F:/1erAnnee/S2/S2.01_fin"; //A modifier selon votre chemin d'acces

    if(maRequete.exec(leContenuRequete))
     {
        for(int i = 0; maRequete.next(); i++)
        {
            rang = maRequete.value(0).toInt();
            titrePhoto = maRequete.value(1).toString();
            uriPhoto = maRequete.value(2).toString();
            nomFamille = maRequete.value(3).toString();

            std::string _nomFamille = nomFamille.toStdString();
            std::string _titrePhoto = titrePhoto.toStdString();
            std::string _uriPhoto = cheminAcces + uriPhoto.toStdString();

            imageACharger = new Image(rang, _nomFamille, _titrePhoto, _uriPhoto);
            _diaporama.push_back(imageACharger);


        }
    }
     //trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama

     //triBulle(_diaporama);

     _posImageCourante = 0;

     //cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
     //cout << nbImages() << " images chargees dans le diaporama" << endl;

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
     _numDiaporamaCourant = 0;
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
