#ifndef RUNEPAGE_H
#define RUNEPAGE_H

#include <array>
#include "rune.h"

class RunePage
{
public:
    RunePage();
    RunePage& operator=(RunePage const& r)=delete;
    RunePage(RunePage& r)=delete;
    void ajouterRune(Rune const& rune);
    void clear();
private:
    std::array<Rune*,9> Marques_;
    std::array<Rune*,9> Sceaux_;
    std::array<Rune*,9> Glyphes_;
    std::array<Rune*,3> Quints_;
};

#endif // RUNEPAGE_H
