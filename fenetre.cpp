#include "fenetre.h"
#include "ui_fenetre.h"
#include "fileManagement.h"

Fenetre::Fenetre(QWidget *parent) : QMainWindow(parent), ui(new Ui::Fenetre)
{
    ui->setupUi(this);

    //on connecte les Qapplication
    connect(ui->actionNouveau,SIGNAL(triggered()),this,SLOT(nouveauFichier()));
    connect(ui->actionOuvrir,SIGNAL(triggered()),this,SLOT(ouvrirFichier()));
    connect(ui->actionSauvegarder,SIGNAL(triggered()),this,SLOT(sauvegarderFichier()));
    connect(ui->actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));

    index = loadIndexFromFile("runes.index"); //on charge les runes
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

void Fenetre::ouvrirFichier()
{
    //rien pour le moment
}

void Fenetre::sauvegarderFichier()
{
    //rien non plus
}

void Fenetre::updateStats()
{
    if (ui->MarquesList->count() == 0 && ui->SceauxList->count() == 0 && ui->GlyphesList->count() == 0 && ui->QuintList->count() == 0) //les listes sont toutes vides
    {
        ui->StatLabel->setText(""); //on vide le texte
    }
    else
    {
        QString newLabel{"<html><head/><body>"};
        QString tmp{""};
        std::vector<Effet> allEffect = page.getAllEffect(); //on récupère tous les effets de la page !
        for (auto &a : allEffect) //on parcoure tous les effets
        {
            tmp = (a.second > 0) ? "<span style=\" color:#d00000;\">+ " : "<span style=\" color:#0267b5;\">- "; //on prend le signe du bonus
            //+/- XX STAT (avec de la coloration et STAT en italique)
            newLabel += "<p align=\"center\">" + tmp + QString{a.second} + " </span><span style=\" font-style:italic; color:#000000;\">" + std::string(a.first).c_str() + "</span></p>";
        }
        newLabel += "</body></html>"; //on finit la mise en page
        ui->StatLabel->setText(newLabel);
    }
}
