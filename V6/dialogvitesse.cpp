#include "dialogvitesse.h"
#include "ui_dialogvitesse.h"

DialogVitesse::DialogVitesse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVitesse)
{
    ui->setupUi(this);

    // connexion des slots et signals
    connect(ui->btnAnnuler, SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->btnOk, SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(ui->radioB0_5, SIGNAL(clicked()), this, SLOT(changerVitesseDiapoX0_5()));
    QObject::connect(ui->radioB1, SIGNAL(clicked()), this, SLOT(changerVitesseDiapoX1()));
    QObject::connect(ui->radioB2, SIGNAL(clicked()), this, SLOT(changerVitesseDiapoX2()));
}

DialogVitesse::~DialogVitesse()
{
    delete ui;
}

// Retourne la vitesse de défilemenent voulue par l'utilisateur
double DialogVitesse::vitesseDiapo()
{
    return valVitesseDiapo;
}

// Modifie la vitesse de défilement du diapo à 4 secondes pour défiler en X0.5
void DialogVitesse::changerVitesseDiapoX0_5()
{
    valVitesseDiapo = 3000;
}

// Modifie la vitesse de défilement du diapo à 2 secondes pour défiler en X1
void DialogVitesse::changerVitesseDiapoX1()
{
    valVitesseDiapo = 2000;
}

// Modifie la vitesse de défilement du diapo à 1 secondes pour défiler en X2
void DialogVitesse::changerVitesseDiapoX2()
{
    valVitesseDiapo = 1000;
}
