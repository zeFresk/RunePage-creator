#include "fileManagement.h"

#include <fstream>
#include <stdexcept>

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
