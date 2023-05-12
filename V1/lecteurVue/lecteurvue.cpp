#include "lecteurvue.h"
#include "ui_lecteurvue.h"


LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    connect(ui->bArreterDiapo,SIGNAL(clicked()),this,SLOT(ArreterDiapo()));
    connect(ui->bLancerDiapo,SIGNAL(clicked()),this,SLOT(LancerDiapo()));
    connect(ui->bAvancerDiapo,SIGNAL(clicked()),this,SLOT(AvancerDiapo()));
    connect(ui->bReculerDiapo,SIGNAL(clicked()),this,SLOT(ReculerDiapo()));

    connect(ui->actionA_propos_de,SIGNAL(clicked()),this,SLOT(AProposDe()));
    connect(ui->actionquitter,SIGNAL(clicked()),this,SLOT(Quitter()));
    connect(ui->actionCharger_diaporama,SIGNAL(clicked()),this,SLOT(ChargerDiaporama()));
    connect(ui->actionEnlever_diaporama,SIGNAL(clicked()),this,SLOT(EnleverDiaporama()));
    connect(ui->actionvitesse_de_defilement,SIGNAL(clicked()),this,SLOT(VitesseDefilement()));
    connect(ui->bChangerCategorie,SIGNAL(clicked()),this,SLOT(ChangerCategorie()));



}

LecteurVue::~LecteurVue()
{
    delete ui;
}

void LecteurVue::ArreterDiapo()
{

}

void LecteurVue::LancerDiapo()
{

}

void LecteurVue::AvancerDiapo()
{

}

void LecteurVue::ReculerDiapo()
{

}

void LecteurVue::AProposDe()
{

}

void LecteurVue::Quitter()
{

}

void LecteurVue::ChargerDiaporama()
{

}

void LecteurVue::EnleverDiaporama()
{

}

void LecteurVue::VitesseDefilement()
{

}

void LecteurVue::ChangerCategorie()
{

}

