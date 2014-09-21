#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include <QModelIndex>
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

private:
    Ui::Fenetre *ui;
    void updateStats();
    std::vector<Rune> index;
    RunePage page;
};

#endif // FENETRE_H
