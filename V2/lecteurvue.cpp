#include "lecteurvue.h"
#include "ui_lecteurvue.h"
#include <QDebug>
#include <QDialog>
#include <QMessageBox>

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{

    ui->setupUi(this);

    // Connexions de tous les Signals et Slots
    connect(ui->bArreterDiapo,SIGNAL(clicked()),this,SLOT(arreterDiapo()));
    connect(ui->bLancerDiapo,SIGNAL(clicked()),this,SLOT(lancerDiapo()));
    connect(ui->bAvancerDiapo,SIGNAL(clicked()),this,SLOT(demandeAvancerDiapo()));
    connect(ui->bReculerDiapo,SIGNAL(clicked()),this,SLOT(demandeReculerDiapo()));

    connect(ui->actionA_propos_de,SIGNAL(triggered()),this,SLOT(aProposDe()));
    connect(ui->actionquitter,SIGNAL(triggered()),this,SLOT(quitter()));
    connect(ui->actionCharger_diaporama,SIGNAL(triggered()),this,SLOT(demandeChargerDiaporama()));
    connect(ui->actionEnlever_diaporama,SIGNAL(triggered()),this,SLOT(demandeEnleverDiaporama()));
    connect(ui->actionvitesse_de_defilement,SIGNAL(triggered()),this,SLOT(vitesseDefilement()));


    // Initialisation de la barre d'état en Mode Manuel
    ui -> lBarreEtat -> showMessage("Mode Manuel");

    // Desactivation des boutons pour éviter les erreurs
    ui -> bReculerDiapo -> setEnabled(false);
    ui -> bAvancerDiapo -> setEnabled(false);
    ui -> bLancerDiapo -> setEnabled(false);
    ui -> bArreterDiapo -> setEnabled(false);
}

LecteurVue::~LecteurVue()
{
    delete ui;
}

void LecteurVue::mettreAJourVue()
{
    // Création de l'image en utilisant la méthode imageCourante de Lecteur
    setImage(getLecteur()->imageCourante());

    // Met à jour les labels de la vu en appelant les méthodes de Image
    ui -> lImage -> setPixmap(QPixmap(QString::fromStdString(getImage() -> getChemin())));
    ui -> lValeurTitreImage -> setText(QString::fromStdString(getImage()-> getTitre()));
    ui -> lValeurRangActuel -> setText(QString::number(getImage()-> getRang()));
    ui -> lValeurRangMax -> setText(QString::number(getLecteur()-> nbImages()));
    ui -> lValeurCategorie -> setText(QString::fromStdString(getImage()-> getCategorie()));
}

Lecteur *LecteurVue::getLecteur()
{
    return _leLecteur;
}

void LecteurVue::setLecteur(Lecteur *l)
{
    _leLecteur =l;
}

Image *LecteurVue::getImage()
{
    return _image;
}

void LecteurVue::setImage(Image *i)
{
    _image = i;
}

void LecteurVue::arreterDiapo()
{
    // Vérifie si le bouton fonctionne
    qDebug()<< "Je demande d'arreter le diaporama"<< Qt::endl;


}

void LecteurVue::lancerDiapo()
{
    // Vérifie si le bouton fonctionne
    qDebug()<< "Je demande de lancer le diaporama"<< Qt::endl;
}

void LecteurVue::demandeAvancerDiapo()
{
    // Appel la méthode avancer de Lecteur
    getLecteur()->Lecteur::avancer();

    // Met à jour LecteurVue
    mettreAJourVue();
}

void LecteurVue::demandeReculerDiapo()
{
    // Appel la méthode reculer de Lecteur
    getLecteur()->Lecteur::reculer();

    // Met à jour LecteurVue
    mettreAJourVue();
}

void LecteurVue::aProposDe()
{
    // affiche un message à l'ecran
    QMessageBox::information(nullptr, "A propos de ...", "Version : V2 \n \n Date de Création : ... \n \n Créateurs : Nathan PIEL // Léo FERME // Mathieu CHOURREAU");
}

void LecteurVue::quitter()
{
    // Ferme la fenêtre principale
    close();
}

void LecteurVue::demandeChargerDiaporama()
{
    // Appel de la méthode chargerDiaporama de Lecteur
    getLecteur()->Lecteur::chargerDiaporama();

    // Met à jour LecteurVue
    mettreAJourVue();

    // Activation des boutons
    ui -> bReculerDiapo -> setEnabled(true);
    ui -> bAvancerDiapo -> setEnabled(true);
    ui -> bLancerDiapo -> setEnabled(true);
    ui -> bArreterDiapo -> setEnabled(true);
}

void LecteurVue::demandeEnleverDiaporama()
{
    // Vérifie si le bouton fonctionne
    qDebug()<< "Je demande d'enlever le diapormama"<< Qt::endl;
}

void LecteurVue::vitesseDefilement()
{
    // Vérifie si le bouton fonctionne
    qDebug()<< "Je change la vitesse de défilement"<< Qt::endl;
}

void LecteurVue::changerCategorie()
{
    // Vérifie si le bouton fonctionne
    qDebug()<< "Je change de catégorie"<< Qt::endl;
}

