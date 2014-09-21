#include "runepage.h"

RunePage::RunePage()
{
    clear();
}

bool RunePage::ajouterRune(Rune & rune)
{
    if (rune.getType() == RuneType::Marque && Marques_[8] == nullptr) //on veut ajouter une marque ET les marques ne sont pas encore remplies.
    {
        for (auto &a : Marques_) //on parcourt
        {
            if (a == nullptr) //emplacement inutilisé
            {
                a = &rune; //on fait pointer l'élément sur la rune.
                break;
            }
        }
        return true;
    }
    else if(rune.getType() == RuneType::Sceau && Sceaux_[8] == nullptr)
    {
        for (auto &a : Sceaux_) //on parcourt
        {
            if (a == nullptr) //emplacement inutilisé
            {
                a = &rune; //on fait pointer l'élément sur la rune.
                break;
            }
        }
        return true;
    }
    else if(rune.getType() == RuneType::Glyphe && Glyphes_[8] == nullptr)
    {
        for (auto &a : Glyphes_) //on parcourt
        {
            if (a == nullptr) //emplacement inutilisé
            {
                a = &rune; //on fait pointer l'élément sur la rune.
                break;
            }
        }
        return true;
    }
    else if (rune.getType() == RuneType::Quint && Quints_[2] == nullptr) //seulement 3 quints
    {
        for (auto &a : Quints_) //on parcourt
        {
            if (a == nullptr) //emplacement inutilisé
            {
                a = &rune; //on fait pointer l'élément sur la rune.
                break;
            }
        }
        return true;
    }
    else //on a pas ajouté la rune
    {
        return false;
    }
}

void RunePage::clear() //RAZ des pointeurs
{
    for (auto& a: Marques_) {a = nullptr;}
    for (auto& a: Sceaux_) {a = nullptr;}
    for (auto& a: Glyphes_) {a = nullptr;}
    for (auto& a: Quints_) {a = nullptr;}
}

std::vector<Effet> RunePage::getAllEffect() const
{
    std::vector<Effet> ret;

    //on ajoute tous les effets rune par rune
    for (auto &a : Marques_) {addEffet(ret,a->getEffet());}
    for (auto &a : Sceaux_) {addEffet(ret,a->getEffet());}
    for (auto &a : Glyphes_) {addEffet(ret,a->getEffet());}
    for (auto &a : Quints_) {addEffet(ret,a->getEffet());}

    return ret;
}

void addEffet(std::vector<Effet> &vect, Effet const& effet)
{
    int pos = -1;
    for (unsigned i{0}; i < vect.size(); i++) //on cherche si l'effet est déjà présent dans le vector
    {
        if (vect[i].first == effet.first) //existe déjà
            pos = i; //l'effet existe déjà donc on donne la pos
    }

    if (pos != -1) //l'effet existe
    {
        vect[pos].second += effet.second; //on cumule les effets
    }
    else //l'effet n'existe pas
    {
        vect.push_back(effet); //on l'ajoute
    }
}
