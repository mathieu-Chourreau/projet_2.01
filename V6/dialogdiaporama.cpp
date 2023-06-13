#include "dialogdiaporama.h"
#include "ui_dialogdiaporama.h"

DialogDiaporama::DialogDiaporama(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDiaporama)
{
    ui->setupUi(this);

    connect(ui->btnAnnuler, SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->btnOk, SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(ui->rbDiapoPantxika, SIGNAL(clicked()), this, SLOT(chargerDiapoPantxika()));
    QObject::connect(ui->rbDiapoManu, SIGNAL(clicked()), this, SLOT(chargerDiapoManu()));
    QObject::connect(ui->rbDiapoThierry, SIGNAL(clicked()), this, SLOT(chargerDiapoThierry()));
    QObject::connect(ui->rbDiapoYann, SIGNAL(clicked()), this, SLOT(chargerDiapoYann()));
}

DialogDiaporama::~DialogDiaporama()
{
    delete ui;
}

int DialogDiaporama::chargerLeDiapo()
{
    return leDiapo;
}

void DialogDiaporama::chargerDiapoPantxika()
{
    leDiapo = 1;
}

void DialogDiaporama::chargerDiapoManu()
{
    leDiapo = 4;
}

void DialogDiaporama::chargerDiapoYann()
{
    leDiapo = 3;
}

void DialogDiaporama::chargerDiapoThierry()
{
    leDiapo = 2;
}

