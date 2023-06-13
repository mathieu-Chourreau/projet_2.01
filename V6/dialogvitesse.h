#ifndef DIALOGVITESSE_H
#define DIALOGVITESSE_H
#include <QRadioButton>
#include <QDialog>

namespace Ui {
class DialogVitesse;
}

class DialogVitesse : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVitesse(QWidget *parent = nullptr);
    ~DialogVitesse();
    double vitesseDiapo();                  // Retourne la vitesse de défilemenent voulue par l'utilisateur

private slots:
    void changerVitesseDiapoX0_5();         // Modifie la vitesse de défilement du diapo à 4 secondes pour défiler en X0.5
    void changerVitesseDiapoX1();           // Modifie la vitesse de défilement du diapo à 2 secondes pour défiler en X1
    void changerVitesseDiapoX2();           // Modifie la vitesse de défilement du diapo à 1 secondes pour défiler en X2

private:
    double valVitesseDiapo;                 // Initialisation de la vitesse de défilemenent voulue par l'utilisateur
    Ui::DialogVitesse *ui;
};

#endif // DIALOGVITESSE_H
