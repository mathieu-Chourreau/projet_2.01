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
    connect(ui->actionVitesse_de_defilement,SIGNAL(triggered()),this,SLOT(demandeChangerVitesseDiapo()));

    // Initialisation du Timer pour le mode Auto
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(lancerDiapo()));

    // Initialisation de la barre d'état en Mode Manuel
    lBarreEtat = new QLabel(this);

    lBarreEtat -> setText(" Mode Manuel");
    ui -> barreEtat -> insertWidget(1,lBarreEtat);

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
        setImage(getLecteur()->imageCourante());

        // Mettre à jour les labels de la vu en appelant les méthodes de Image

        ui -> lImage -> setPixmap(QPixmap(QString::fromStdString(getImage() -> getChemin())));
        ui -> lValeurTitreDiapo -> setText( QString::number(getLecteur()-> numDiaporamaCourant()));
        ui -> lValeurTitreImage -> setText(QString::fromStdString(getImage()-> getTitre()));
        ui -> lValeurRangActuel -> setText(QString::number(getImage()-> getRang()));
        ui -> lValeurRangMax -> setText(QString::number(getLecteur()-> nbImages()));
        ui -> lValeurCategorie -> setText(QString::fromStdString(getImage()-> getCategorie()));
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
    // Modifie la barre d'état
    lBarreEtat -> setText(" Mode Manuel");

    // Arret du timer pour stopper le défilement des images
    timer->stop();
}

void LecteurVue::lancerDiapo()
{
   // Modifie la barre d'état
    lBarreEtat -> setText(" Mode Automatique");

   // Lancement du timer avec 2 secondes d'intervalles
   timer->start(vitesseDiapo);

   // Fait défiler les images
   demandeAvancerDiapo();
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
    QMessageBox::information(nullptr, "A propos de ...", "Version : V4 \n \n Date de Création : ... \n \n Créateurs : Nathan PIEL // Léo FERME // Mathieu CHOURREAU");
}

void LecteurVue::quitter()
{
    // Ferme la fenêtre principale
    close();
}

void LecteurVue::demandeChargerDiaporama()
{
    // Appel de la méthode chargerDiaporama de Lecteur
    int _numDiaporamaCourant = 1;
    getLecteur()->Lecteur::changerDiaporama(_numDiaporamaCourant);

    // Met à jour LecteurVue
    mettreAJourVue();

    // Activation des boutons
    ui -> bReculerDiapo -> setEnabled(true);
    ui -> bAvancerDiapo -> setEnabled(true);
    ui -> bLancerDiapo -> setEnabled(true);
    ui -> bArreterDiapo -> setEnabled(true);

    // Initialisation de la vitesse de défilement du diapo à 2 secondes
    vitesseDiapo = 2000;
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
    maDlg  = new DialogVitesse(this);

    // Stockage dans reponse la validation du dialog de l'utilisateur
    int reponse = maDlg -> exec();

    // Si l'utilisateur a validé son dialog
    if (reponse == QDialog::Accepted)
    {
        // Alors on récupère la nouvelle vitesse de défilement du diaporama
        vitesseDiapo = maDlg -> vitesseDiapo();
    }
}

void LecteurVue::changerCategorie()
{
    // Vérifie si le bouton fonctionne
    qDebug()<< "Je change de catégorie"<< Qt::endl;
}

