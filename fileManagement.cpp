#include "fileManagement.h"

#include <fstream>
#include <QFile>
#include <QTextStream>
//#include <algorithm>
#include <stdexcept>
#include <QMessageBox>

using namespace std;

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

void saveRunePageToFile(RunePage const& page, std::string path)
{
    auto vect = page.getAllRune(); //on récupère toutes les runes
    QFile file(path.c_str()); //caractères spéciaux non gérés par ofstream T.T
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) throw runtime_error("Unable to save runepage.");
    QTextStream out(&file); //pour écrire !

    for (auto &a : vect) //on parcourt
    {
        out << a.toString().c_str() << '\n'; //on save la rune
    }
}
