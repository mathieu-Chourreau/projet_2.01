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

    // Activer tous les filtres
    ui -> checkBoxAnimal -> setChecked(true);
    ui -> checkBoxObjet -> setChecked(true);
    ui -> checkBoxPersonnage -> setChecked(true);

    // Connexions de tous les Signals et Slots
    connect(ui->bArreterDiapo,SIGNAL(clicked()),this,SLOT(arreterDiapo()));
    connect(ui->bLancerDiapo,SIGNAL(clicked()),this,SLOT(lancerDiapo()));
    connect(ui->bAvancerDiapo,SIGNAL(clicked()),this,SLOT(demandeAvancerDiapo()));
    connect(ui->bReculerDiapo,SIGNAL(clicked()),this,SLOT(demandeReculerDiapo()));

    connect(ui->actionA_propos_de,SIGNAL(triggered()),this,SLOT(aProposDe()));
    connect(ui->actionquitter,SIGNAL(triggered()),this,SLOT(quitter()));
    connect(ui->actionCharger_diaporama,SIGNAL(triggered()),this,SLOT(demandeChargerDiaporama()));
    connect(ui->actionEnlever_diaporama,SIGNAL(triggered()),this,SLOT(demandeEnleverDiaporama()));
    connect(ui->actionVitesse_de_defilement,SIGNAL(triggered()),this,SLOT(demandeChangerVitesseDiapo()));

    connect(ui->checkBoxPersonnage, SIGNAL(stateChanged(int)), this, SLOT(demandeFiltrerDiapo()));
    connect(ui->checkBoxAnimal, SIGNAL(stateChanged(int)),this,SLOT(demandeFiltrerDiapo()));
    connect(ui->checkBoxObjet, SIGNAL(stateChanged(int)),this,SLOT(demandeFiltrerDiapo()));

    // Initialisation du Timer pour le mode Auto
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(lancerDiapo()));

    // Initialisation de la barre d'état en Mode Manuel
    lBarreEtat = new QLabel(this);

    lBarreEtat -> setText(" Mode Manuel");
    ui -> barreEtat -> insertWidget(0,lBarreEtat);

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
    // Si aucun diaporama n'est chargé
    if(getLecteur()->numDiaporamaCourant() == 0)
    {
        // Mettre à jour les labels pour afficher l'interface vide
        ui -> lImage -> setPixmap(QPixmap());
        ui -> lValeurTitreDiapo -> setText("...");
        ui -> lValeurTitreImage -> setText("...");
        ui -> lValeurRangActuel -> setText("...");
        ui -> lValeurRangMax -> setText("...");
        ui -> lValeurCategorie -> setText("...");
    }
    // Sinon mettre à jour la vue pour afficher les informations de l'iamge actuelle
    else
    {
        // Création de l'image en utilisant la méthode imageCourante de Lecteur
        getLecteur()->setImage(getLecteur()->imageCourante());

        // Mettre à jour les labels de la vu en appelant les méthodes de Image

        ui -> lImage -> setPixmap(QPixmap(QString::fromStdString(getLecteur() -> getImage() -> getChemin())));
        ui -> lValeurTitreDiapo -> setText(getLecteur() -> getTitreDiapo());
        ui -> lValeurTitreImage -> setText(QString::fromStdString(getLecteur()->getImage()-> getTitre()));
        ui -> lValeurRangActuel -> setText(QString::number(getLecteur()->getImage()-> getRang()));
        ui -> lValeurRangMax -> setText(QString::number(getLecteur()-> nbImages()));
        ui -> lValeurCategorie -> setText(QString::fromStdString(getLecteur()->getImage()-> getCategorie()));
    }

}

bool LecteurVue::filtrerAvecPersonnage()
{
    if(ui -> checkBoxPersonnage -> isChecked())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LecteurVue::filtrerAvecObject()
{
    if(ui -> checkBoxObjet -> isChecked())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LecteurVue::filtrerAvecAnimal()
{
    if(ui -> checkBoxAnimal -> isChecked())
    {
        return true;
    }
    else
    {
        return false;
    }
}

Lecteur *LecteurVue::getLecteur()
{
    return _leLecteur;
}

void LecteurVue::setLecteur(Lecteur *l)
{
    _leLecteur =l;
}

void LecteurVue::arreterDiapo()
{
    // Modifie la barre d'état
    lBarreEtat -> setText(" Mode Manuel");

    // Arret du timer pour stopper le défilement des images
    timer->stop();

    ui -> bArreterDiapo -> setEnabled(false);
    ui -> bReculerDiapo -> setEnabled(true);
    ui -> bAvancerDiapo -> setEnabled(true);
}

void LecteurVue::lancerDiapo()
{
   // Modifie la barre d'état
    lBarreEtat -> setText(" Mode Automatique");

   // Lancement du timer avec la vitesse de la base de donnée
   timer->start(vitesseDiapo);

   // Fait défiler les images
   demandeAvancerDiapo();

   ui -> bReculerDiapo -> setEnabled(false);
   ui -> bAvancerDiapo -> setEnabled(false);
   ui -> bArreterDiapo -> setEnabled(true);
}

void LecteurVue::demandeAvancerDiapo()
{
    // Appel la méthode avancer de Lecteur
    getLecteur()->Lecteur::avancer();
}

void LecteurVue::demandeReculerDiapo()
{
    // Appel la méthode reculer de Lecteur
    getLecteur()->Lecteur::reculer();
}

void LecteurVue::aProposDe()
{
    // affiche un message à l'ecran
    QMessageBox::information(nullptr, "A propos de ...", "Version : V6 \n \n Date de Création : ... \n \n Créateurs : Nathan PIEL // Léo FERME // Mathieu CHOURREAU");
}

void LecteurVue::quitter()
{
    // Ferme la fenêtre principale
    close();
}

void LecteurVue::demandeChargerDiaporama()
{
    // Création d'une nouvelle fenêtre de Dialog basée sur le modele DialogVitesse
    maDlgDiapo  = new DialogDiaporama(this);

    // Stockage dans reponse la validation du dialog de l'utilisateur
    int reponse = maDlgDiapo -> exec();

    // Si l'utilisateur a validé son dialog
    if (reponse == QDialog::Accepted)
    {
        // Alors on récupère la nouvelle vitesse de défilement du diaporama
        diapoACharger = maDlgDiapo -> chargerLeDiapo();

        // Appel de la méthode chargerDiaporama de Lecteur
        getLecteur()->Lecteur::changerDiaporama(diapoACharger);

        // Modifier la vitesse de defilement avec celle de la base de données
        vitesseDiapo = getLecteur() -> vitesseDefilement();

        // Met à jour LecteurVue
        mettreAJourVue();

        // Activation des boutons
        ui -> bReculerDiapo -> setEnabled(true);
        ui -> bAvancerDiapo -> setEnabled(true);
        ui -> bLancerDiapo -> setEnabled(true);
    }
}

void LecteurVue::demandeEnleverDiaporama()
{
    // Appel de la méthode viderDiaporama de Lecteur
    getLecteur()->Lecteur::viderDiaporama();

    // Met à jour LecteurVue
    mettreAJourVue();

    // Remettre la barre etat en mode Manuel
    lBarreEtat -> setText(" Mode Manuel");

    // Arret du mode Automatique
    timer->stop();

    // Désactivation des boutons
    ui -> bReculerDiapo -> setEnabled(false);
    ui -> bAvancerDiapo -> setEnabled(false);
    ui -> bLancerDiapo -> setEnabled(false);
    ui -> bArreterDiapo -> setEnabled(false);
}

void LecteurVue::demandeChangerVitesseDiapo()
{

    // Création d'une nouvelle fenêtre de Dialog basée sur le modele DialogVitesse
    maDlgVitesse  = new DialogVitesse(this);

    // Stockage dans reponse la validation du dialog de l'utilisateur
    int reponse = maDlgVitesse -> exec();

    // Si l'utilisateur a validé son dialog
    if (reponse == QDialog::Accepted)
    {
        // Alors on récupère la nouvelle vitesse de défilement du diaporama
        vitesseDiapo = maDlgVitesse -> vitesseDiapo();
    }

}

void LecteurVue::demandeFiltrerDiapo()
{
    if(getLecteur() -> numDiaporamaCourant() != 0)
    {
        if(filtrerAvecPersonnage() == false && filtrerAvecAnimal() == false &&  filtrerAvecObject() == false)
        {
            QMessageBox::information(nullptr, "Erreur de filtrage","Veuillez selectionner au moins une catégorie");
        }
        else
        {
        getLecteur() -> filtrerLeDiapo();
        mettreAJourVue();
        }
    }
}


