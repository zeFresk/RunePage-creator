#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>

namespace Ui {
class Fenetre;
}

class Fenetre : public QMainWindow
{
    Q_OBJECT

public:
    explicit Fenetre(QWidget *parent = 0);
    ~Fenetre();

public slots:
    void nouveauFichier();
    void ouvrirFichier();
    void sauvegarderFichier();

private:
    Ui::Fenetre *ui;
};

#endif // FENETRE_H
