#ifndef LECTEURVUE_H
#define LECTEURVUE_H
#include "image.h"
#include <QMainWindow>
#include <QString>
#include "lecteur.h"
#include <QTimer>
#include <QLabel>
#include "dialogvitesse.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);
    ~LecteurVue();
    void mettreAJourVue();

    //getters et setters des attributs privés de Lecteur
    Lecteur* getLecteur();
    void setLecteur(Lecteur* l);

    //getters et setters des attributs privés de Image
    Image* getImage();
    void setImage(Image* i);

private slots:
    void lancerDiapo();                // Lance un timer qui appelle la méthode demandeAvancerDiapo() à intervalles régulières
    void arreterDiapo();               // Arrete le timer
    void demandeAvancerDiapo();        // Appel la méthode avancer() de Lecteur
    void demandeReculerDiapo();        // Appel la méthode reculer() de Lecteur
    void aProposDe();                  // Affiche un message qui donne des informations sur l'application
    void quitter();                    // Ferme la fenêtre
    void demandeChargerDiaporama();    // Appel la méthode chargerDiaporama() de Lecteur
    void demandeEnleverDiaporama();    // Appel la méthode viderDiaporama() de Lecteur
    void demandeChangerVitesseDiapo();          // Modifie la vitesse de défilement des images en changeant l'interevalle du timer
    void changerCategorie();           // Trie les images du diaporama en fonction des catégories choisies par l'utilisateur


private:
    QLabel *lBarreEtat;
    double vitesseDiapo;
    Ui::LecteurVue *ui;
    Lecteur *_leLecteur;
    Image *_image;
    QTimer *timer;
    DialogVitesse* maDlg;
};
#endif // LECTEURVUE_H
