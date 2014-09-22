#include "runepage.h"
#include <stdexcept>

// Bon là il faut vraiment que j'explique parce que c'est pas simple !
// Cette fonction permet de supprimer les trous de nullptr dans le tableau de rune après suppression d'une rune
// Prenons le tableau suivant : plein plein nullptr plein
// après un passage de for il deviendra : plein plein plein nullptr
//
// La boucle do while est là dans le cas (que je n'appelle théoriquement jamais) où on a trou de plus d'une case !
// Exemple : plein nullptr nullptr plein
// Après un for : plein nullptr plein nullptr
//  > Vu qu'on a eu un changement on refait un tour !
// Deuxième for : plein plein nullptr nullptr
// Et voilà c'est tout beau !
template <std::size_t a>
void ordonne(std::array<Rune*,a> & arr)
{
    bool changement;
    do
    {
        changement = false;
        for (unsigned i{0};i<arr.size();i++) // on parcourt
        {
            if (arr[i] == nullptr && i < (arr.size()-1)) //le pointeur à la case est vide et on n'est pas à la dernière case
            {
                if (arr[i+1] != nullptr) //d'ou la condition précédente sinon overflow !!!
                {
                    arr[i] = arr[i+1];
                    arr[i+1] = nullptr;
                    changement = true;
                }
            }
        }
    } while (changement == true); //tant qu'on a eu un changement
}

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
    for (auto &a : Marques_)
    {
        if (a != nullptr)
            addEffet(ret,a->getEffet());
    }
    for (auto &a : Sceaux_)
    {
        if (a != nullptr)
            addEffet(ret,a->getEffet());
    }
    for (auto &a : Glyphes_)
    {
        if (a != nullptr)
            addEffet(ret,a->getEffet());
    }
    for (auto &a : Quints_)
    {
        if (a != nullptr)
            addEffet(ret,a->getEffet());
    }

    return ret;
}

void RunePage::remove(RuneType const& type, int pos)
{
    if (pos < 0) throw std::runtime_error("Unable to remove the rune ! (pos < 0)"); //Qt qui peut renvoyer un index négatif...
    if (type == RuneType::Marque && pos < 9)
    {
        Marques_[pos] = nullptr;
        ordonne(Marques_); //pour ne pas avoir de trous
    }
    else if (type == RuneType::Sceau && pos < 9)
    {
        Sceaux_[pos] = nullptr;
        ordonne(Sceaux_);
    }
    else if (type == RuneType::Glyphe && pos < 9)
    {
        Glyphes_[pos] = nullptr;
        ordonne(Glyphes_);
    }
    else if (type == RuneType::Quint && pos < 3)
    {
        Quints_[pos] = nullptr;
        ordonne(Quints_);
    }
    else // l'index est trop grand, en théorie ça n'arrivera jamais !
    {
        throw std::runtime_error("Unable to remove the rune ! (pos > maxPos)");
    }
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
