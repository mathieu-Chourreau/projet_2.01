#include "lecteurvue.h"
#include "lecteur.h"
#include "image.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // créer le modèle
    Image *i = new Image();

    // créer la présentation
    Lecteur *l = new Lecteur();

    // créer la vue
    LecteurVue lv;

    // faire pointer la présentation vers la vue et le modèle
    l->setLecteurVue(&lv);
    l->setImage(i);

    // faire pointer la vue vers la présentation
    lv.setLecteur(l);

    // initialiser la vue en conformité avec l'état initial du modèle
    l->getLecteurVue()->mettreAJourVue();
    lv.show();


    return a.exec();
}
