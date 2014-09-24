#include "fileManagement.h"

#include <fstream>
#include <QFile>
#include <QTextStream>
#include <stdexcept>

using namespace std;

QString runeIndex(const std::vector<Rune> &ind, const Rune &r);

vector<Rune> loadIndexFromFile(string const& path)
{
    ifstream file{path}; //on charge le fichier
    if (!file) throw runtime_error("Unable to load index file."); //impossible d'ouvrir le fichier

    string tmp;
    vector<Rune> ret;
    while (getline(file,tmp)) //on parcourt ligne par ligne
    {
        ret.push_back(tmp); //on ajoute la rune via un constructeur surchargé
    }

    return ret; //on retourne notre vector
}

void saveRunePageToFile(std::vector<Rune> const& index,RunePage const& page, QString const& path)
{
    auto vect = page.getAllRune(); //on récupère toutes les runes
    QFile file(path); //caractères spéciaux non gérés par ofstream T.T
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) throw runtime_error("Unable to save runepage.");
    QTextStream out(&file); //pour écrire !

    for (auto &a : vect) //on parcourt
    {
        out << runeIndex(index, a) << '\n'; //on récupère le numéro d'index correspondant en on l'enregistre
    }
}

vector<unsigned> getIndexListFromFile(QString const& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) throw runtime_error("Unable to load runepage."); //on ouvre le fichier en lecture
    QTextStream in(&file);

    vector<unsigned> ret;
    while (!in.atEnd()) //tant qu'on est pas à la fin du fichier
    {
        QString line = in.readLine(); //on lit la ligne
        ret.push_back(static_cast<unsigned>(stoi(line.toStdString()))); //on ajoute au vector de retour
    }
    return ret;
}

QString runeIndex(std::vector<Rune> const& ind, Rune const& r) //retourne l'index de la rune dans le vector (ind[i] == r)
{
    for (unsigned i{0};i<ind.size();i++)
    {
        if (ind[i] == r) return QString::number(i); //si c'est égal on retourne l'index
    }
    throw runtime_error("Rune isn't in index file !");
}
