#include "fenetre.h"
#include "ui_fenetre.h"
#include "fileManagement.h"
#include <QFileDialog>
#include <QMessageBox>

template <typename T>
T abs(T a)
{
    return (a >= 0) ? a : -1*a;
}

Fenetre::Fenetre(QWidget *parent) : QMainWindow(parent), ui(new Ui::Fenetre)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    QLabel* hidden = new QLabel("<html><head/><body><p><span style=\" font-size:12pt; font-style:italic;\">Ta gueule </span><span style=\" font-size:12pt;\">, Canis</span></p></body></html>");
    hidden->setVisible(false); //cache toi ! :D

    //on connecte les Qapplication
    connect(ui->actionNouveau,SIGNAL(triggered()),this,SLOT(nouveauFichier()));
    connect(ui->actionOuvrir,SIGNAL(triggered()),this,SLOT(ouvrirFichier()));
    connect(ui->actionSauvegarder,SIGNAL(triggered()),this,SLOT(sauvegarderFichier()));
    connect(ui->actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));

    index = loadIndexFromFile("res/runes.index"); //on charge les runes

    //on charge les icones des runes;
    vectorPixRune.push_back(new QPixmap("res/marque_ico.png"));
    vectorPixRune.push_back(new QPixmap("res/sceau_ico.png"));
    vectorPixRune.push_back(new QPixmap("res/glyphe_ico.png"));
    vectorPixRune.push_back(new QPixmap("res/quint_ico.png"));

    for (auto &a : index)
    {
        QHBoxLayout* layout = new QHBoxLayout; //layout de l'élément

        QLabel* ico = new QLabel; //icone de rune
        ico->setPixmap(vectorPixRune[static_cast<unsigned>(a.getType())]->scaledToHeight(50,Qt::SmoothTransformation)); //on resize

        QLabel* nom = new QLabel(a.getColoredName()); //on met le nom coloré de la rune
        nom->setWordWrap(true);
        nom->setMaximumWidth(200);

        QLabel* intEffet = new QLabel(a.getColoredEffect()); //on récupère l'effet déjà mis en forme

        //on ajoute au layout principal
        layout->addWidget(ico);
        layout->addWidget(nom);
        layout->addWidget(intEffet);

        QListWidgetItem* item = new QListWidgetItem();

        ui->DRunelist->addItem(item); //temporaire

        QWidget* wi = new QWidget;
        wi->setLayout(layout);
        item->setSizeHint(wi->sizeHint());

        ui->DRunelist->setItemWidget(item,wi); //on fait en sorte que ce soit le layout qui soit présent dans la liste
    }

    connect(ui->DRunelist,SIGNAL(pressed(QModelIndex)),this,SLOT(ajouteBonneList(QModelIndex))); //on connecte pour que quand on clique on ajoute la rune.

    //on connecte pour qu'on pouisse supprimer les runes des petites listes
    connect(ui->MarquesList,SIGNAL(pressed(QModelIndex)),this,SLOT(supprimerMarque(QModelIndex)));
    connect(ui->SceauxList,SIGNAL(pressed(QModelIndex)),this,SLOT(supprimerSceau(QModelIndex)));
    connect(ui->GlyphesList,SIGNAL(pressed(QModelIndex)),this,SLOT(supprimerGlyphe(QModelIndex)));
    connect(ui->QuintList,SIGNAL(pressed(QModelIndex)),this,SLOT(supprimerQuint(QModelIndex)));
}

Fenetre::~Fenetre() //useless ? Je ne crois pas !
{
    delete ui;
}

void Fenetre::supprimerMarque(QModelIndex ind)
{
    page.remove(RuneType::Marque, ind.row()); //on supprime la bonne rune
    ui->MarquesList->removeItemWidget(ui->MarquesList->currentItem()); //on delete l'item
    ui->MarquesList->takeItem(ind.row()); //on enlève les espaces
    updateStats();
}

void Fenetre::supprimerSceau(QModelIndex ind)
{
    page.remove(RuneType::Sceau, ind.row()); //on supprime la bonne rune
    ui->SceauxList->removeItemWidget(ui->SceauxList->currentItem()); //on delete l'item
    ui->SceauxList->takeItem(ind.row()); //on enlève les espaces
    updateStats();
}

void Fenetre::supprimerGlyphe(QModelIndex ind)
{
    page.remove(RuneType::Glyphe, ind.row()); //on supprime la bonne rune
    ui->GlyphesList->removeItemWidget(ui->GlyphesList->currentItem()); //on delete l'item
    ui->GlyphesList->takeItem(ind.row()); //on enlève les espaces
    updateStats();
}

void Fenetre::supprimerQuint(QModelIndex ind)
{
    page.remove(RuneType::Quint, ind.row()); //on supprime la bonne rune
    ui->QuintList->removeItemWidget(ui->QuintList->currentItem()); //on delete l'item
    ui->QuintList->takeItem(ind.row()); //on enlève les espaces
    updateStats();
}

void Fenetre::ajouteBonneList(QModelIndex ind)
{
    ajouteBonneList(ind.row()); //Parce qu'il est impossible de créer un QModelIndex manuellement et que j'avais besoin que la fonction demande un int pour quand on ouvre un .runepage
}

void Fenetre::ajouteBonneList(int ind)
{
    bool success = page.ajouterRune(index[ind]); //On ajoute le bon index à la runepage. théoriquement c'est bon.
    if (success) //on a jouté la rune
    {
        if (index[ind].getType() == RuneType::Marque) //on a cliqué sur une marque
        {
            addToList(ui->MarquesList, index[ind]); //on ajoute à la liste des marques
        }
        else if (index[ind].getType() == RuneType::Sceau) //on a cliqué sur un sceau
        {
            addToList(ui->SceauxList, index[ind]); //on ajoute à la liste des sceaux
        }
        else if (index[ind].getType() == RuneType::Glyphe) //on a cliqué sur un glyphe
        {
            addToList(ui->GlyphesList, index[ind]); //on ajoute à la liste des glyphes
        }
        else if (index[ind].getType() == RuneType::Quint) //on a cliqué sur une quintessence
        {
            addToList(ui->QuintList, index[ind]); //on ajoute à la liste des quints
        }
    }
    updateStats();
}

void Fenetre::addToList(QListWidget* list, Rune const& rune) //ça ressemble à la première liste mais on ne peut pas copier car les tailles sont différentes
{
    QHBoxLayout* layout = new QHBoxLayout; //layout de l'élément

    QLabel* nom = new QLabel(rune.getColoredName(7)); //on met le nom coloré de la rune
    nom->setWordWrap(true);
    nom->setMaximumWidth(125);

    QLabel* intEffet = new QLabel(rune.getColoredEffect(8)); //on met l'effet coloré de la rune

    layout->addWidget(nom);
    layout->addWidget(intEffet);

    QListWidgetItem* item = new QListWidgetItem();

    list->addItem(item); //temporaire

    QWidget* wi = new QWidget;
    wi->setLayout(layout);
    item->setSizeHint(wi->sizeHint());

    list->setItemWidget(item,wi);
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
    nouveauFichier();
    auto path = QFileDialog::getOpenFileName(this,"Charger une page de rune",QString(),"Page de rune (*.runepage)"); //on demande où ouvrir à l'user
    if (path != "") //si il n'a pas cliqué sur cancel
    {
        std::vector<unsigned> indexList = getIndexListFromFile(path); //on récupère les numéro dans l'index des runes stockées dans le fichier
        for (auto &a : indexList)
        {
            ajouteBonneList(a); // on les ajoute une par une
        }
    }
}

void Fenetre::sauvegarderFichier()
{
    if (ui->MarquesList->count() == 0 && ui->SceauxList->count() == 0 && ui->GlyphesList->count() == 0 && ui->QuintList->count() == 0) //si la page est vide les listes ne sont pas remplies, un RunePage::isEmpty() aurait été pas mal aussi mais bon
    {
        QMessageBox::warning(this,"Opération impossible","Vous ne pouvez pas enregistrer une page de rune vide !");
    }
    else //la page contient au moins une rune
    {
        auto pathToSave = QFileDialog::getSaveFileName(this,"Enregister la page de rune",QString(),"Page de rune (*.runepage)"); //on récupère l'endroit choisi par l'user
        if (pathToSave != "") saveRunePageToFile(index, page, pathToSave); // s'il n'a pas cliqué sur "cancel" on sauvegarde la page à l'endroit indiqué
    }
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
