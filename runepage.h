#ifndef RUNEPAGE_H
#define RUNEPAGE_H

#include <array>
#include <vector>
#include "rune.h"

void addEffet(std::vector<Effet> &vect, Effet const& effet);

class RunePage
{
public:
    RunePage();
    RunePage& operator=(RunePage const& r)=delete; //d'où tu crois qu'une page ça se copie alors qu'on manipule des pointeurs ?!
    RunePage(RunePage& r)=delete; //Tu me cherches ???!!!
    bool ajouterRune(Rune &rune);
    void clear();
    std::vector<Effet> getAllEffect() const;
    std::vector<Rune> getAllRune() const;
    void remove(RuneType const& type, int pos);
private:
    std::array<Rune*,9> Marques_;
    std::array<Rune*,9> Sceaux_;
    std::array<Rune*,9> Glyphes_;
    std::array<Rune*,3> Quints_;
};

#endif // RUNEPAGE_H
