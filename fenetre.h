#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include <QModelIndex>
#include <QPixmap>
#include <QListWidget>
#include <vector>
#include "rune.h"
#include "runepage.h"

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

    void ajouteBonneList(QModelIndex ind);

    void supprimerMarque(QModelIndex ind);
    void supprimerSceau(QModelIndex ind);
    void supprimerGlyphe(QModelIndex ind);
    void supprimerQuint(QModelIndex ind);

private:
    Ui::Fenetre *ui;
    std::vector<QPixmap*> vectorPixRune;

    void updateStats();
    void addToList(QListWidget* list, Rune const& rune);
    void ajouteBonneList(int ind);

    std::vector<Rune> index;
    RunePage page;
};

#endif // FENETRE_H
