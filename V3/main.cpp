#include "lecteurvue.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LecteurVue lv;
    Lecteur *l;
    Image *i;

    l = new Lecteur;
    i = new Image;

    lv.setLecteur(l);
    lv.setImage(i);

    lv.show();
    return a.exec();
}
