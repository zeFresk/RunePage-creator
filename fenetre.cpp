#include "fenetre.h"
#include "ui_fenetre.h"

Fenetre::Fenetre(QWidget *parent) : QMainWindow(parent), Sui(new Ui::Fenetre)
{
    ui->setupUi(this);

    //on connecte les Qapplication
    connect(ui->actionNouveau,SIGNAL(triggered()),this,SLOT(nouveauFichier()));
    connect(ui->actionOuvrir,SIGNAL(triggered()),this,SLOT(ouvrirFichier()));
    connect(ui->actionSauvegarder,SIGNAL(triggered()),this,SLOT(sauvegarderFichier()));
    connect(ui->actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));
    //connect(ui->)
}

Fenetre::~Fenetre()
{
    delete ui;
}

void Fenetre::nouveauFichier()
{
    //on vide les listes
    ui->MarquesList->clear();
    ui->SceauxList->clear();
    ui->GlyphesList->clear();
    ui->QuintList->clear();

    updateStats();
}

void Fenetre::updateStats()
{
    if (ui->MarquesList->count() == 0 && ui->SceauxList->count() == 0 && ui->GlyphesList->count() == 0 && ui->QuintList->count() == 0) //les listes sont toutes vides
    {
        ui->StatLabel->setText(""); //on vide le texte
    }
    else
    {
        std::vector<
    }
}
