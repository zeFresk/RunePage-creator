#include "fenetre.h"
#include "ui_fenetre.h"
#include "fileManagement.h"
#include <QMessageBox>

Fenetre::Fenetre(QWidget *parent) : QMainWindow(parent), ui(new Ui::Fenetre)
{
    ui->setupUi(this);

    //on connecte les Qapplication
    connect(ui->actionNouveau,SIGNAL(triggered()),this,SLOT(nouveauFichier()));
    connect(ui->actionOuvrir,SIGNAL(triggered()),this,SLOT(ouvrirFichier()));
    connect(ui->actionSauvegarder,SIGNAL(triggered()),this,SLOT(sauvegarderFichier()));
    connect(ui->actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));

    index = loadIndexFromFile("runes.index"); //on charge les runes
    for (auto &a : index)
    {
        ui->DRunelist->addItem(a.getQPres()); //temporaire
    }

    connect(ui->DRunelist,SIGNAL(clicked(QModelIndex)),this,SLOT(ajouteBonneList(QModelIndex))); //on connecte pour que quand on clique on ajoute la rune.
}

Fenetre::~Fenetre()
{
    delete ui;
}

void Fenetre::ajouteBonneList(QModelIndex ind)
{
    bool success = page.ajouterRune(index[ind.row()]); //On ajoute le bon index à la runepage. théoriquement c'est bon.
    if (success) //on a jouté la rune
    {
        if (index[ind.row()].getType() == RuneType::Marque) //on a cliqué sur une marque
        {
            ui->MarquesList->addItem(ui->DRunelist->currentItem()->clone()); //on ajoute l'item à la bonne liste
        }
        else if (index[ind.row()].getType() == RuneType::Sceau) //on a cliqué sur un sceau
        {
            ui->SceauxList->addItem(ui->DRunelist->currentItem()->clone());
        }
        else if (index[ind.row()].getType() == RuneType::Glyphe) //on a cliqué sur un glyphe
        {
            ui->GlyphesList->addItem(ui->DRunelist->currentItem()->clone());
        }
        else if (index[ind.row()].getType() == RuneType::Quint) //on a cliqué sur une quintessence
        {
            ui->QuintList->addItem(ui->DRunelist->currentItem()->clone());
        }
    }
    updateStats();
}

void Fenetre::nouveauFichier()
{
    //on vide les listes
    ui->MarquesList->clear();
    ui->SceauxList->clear();
    ui->GlyphesList->clear();
    ui->QuintList->clear();

    //on vide la page
    page.clear();

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
            tmp = (a.second > 0) ? "<span style=\" color:#d00000; font-size:20pt; font-weight:400\">+ " : "<span style=\" color:#0267b5; font-size:20pt; font-weight:400\">- "; //on prend le signe du bonus
            //+/- XX STAT (avec de la coloration et STAT en italique)
            newLabel += "<p align=\"center\">" + tmp + QString::number(abs(a.second)) + " </span><span style=\" font-style:italic; color:#000000; font-size:20pt; font-weight:600\">" + a.first.c_str() + "</span></p>";
        }
        newLabel += "</body></html>"; //on finit la mise en page
        ui->StatLabel->setText(newLabel);
    }
}
