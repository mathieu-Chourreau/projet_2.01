#ifndef DIALOGDIAPORAMA_H
#define DIALOGDIAPORAMA_H

#include <QDialog>

namespace Ui {
class DialogDiaporama;
}

class DialogDiaporama : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDiaporama(QWidget *parent = nullptr);
    ~DialogDiaporama();

public slots:
    int chargerLeDiapo();
    void chargerDiapoPantxika();
    void chargerDiapoManu();
    void chargerDiapoYann();
    void chargerDiapoThierry();

private:
    Ui::DialogDiaporama *ui;
    int leDiapo;
};

#endif // DIALOGDIAPORAMA_H
