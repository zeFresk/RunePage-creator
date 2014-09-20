#ifndef RUNE_H
#define RUNE_H

#include <string>
#include <utility>

typename std::pair<string,int> Effet;

enum class RuneType {Marque, Sceau, Glyphe, Quint};

class Rune
{
public:
    Rune(std::string nom,Effet effet,RuneType type);
    std::string getName() const;
    RuneType getType() const;
private:
    std::string name_;
    Effet effet_;
    RuneType type_;
};

#endif // RUNE_H
