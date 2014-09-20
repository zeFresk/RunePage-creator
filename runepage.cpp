#include "runepage.h"

RunePage::RunePage()
{
    clear();
}

void RunePage::ajouterRune(Rune const& rune)
{
    if (rune.getType == RuneType::Marque && Marques_[8] != nullptr) //on veut ajouter une marque ET les marques ne sont pas encore remplies.
    {
        for (auto &a : Marques_) //on parcourt
        {
            if (a != nullptr) //emplacement inutilisé
            {
                a = *rune; //on fait pointer l'élément sur la rune.
            }
        }
    }
    else if(rune.getType == RuneType::Sceau && Sceaux_[8] != nullptr)
    {
        for (auto &a : Sceaux_) //on parcourt
        {
            if (a != nullptr) //emplacement inutilisé
            {
                a = *rune; //on fait pointer l'élément sur la rune.
            }
        }
    }
    else if(rune.getType == RuneType::Glyphe && Glyphes_[8] != nullptr)
    {
        for (auto &a : Glyphes_) //on parcourt
        {
            if (a != nullptr) //emplacement inutilisé
            {
                a = *rune; //on fait pointer l'élément sur la rune.
            }
        }
    }
    else if (rune.getType == RuneType::Quint && Quints_[2] != nullptr) //seulement 3 quints
    {
        for (auto &a : Quints_) //on parcourt
        {
            if (a != nullptr) //emplacement inutilisé
            {
                a = *rune; //on fait pointer l'élément sur la rune.
            }
        }
    }
}

void RunePage::clear() //RAZ des pointeurs
{
    for (auto& a: Marques_) {a = nullptr;}
    for (auto& a: Sceaux_) {a = nullptr;}
    for (auto& a: Glyphes_) {a = nullptr;}
    for (auto& a: Quints_) {a = nullptr;}
}
