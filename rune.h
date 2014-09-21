#ifndef RUNE_H
#define RUNE_H

#include <string>
#include <utility>
#include <QString>

typedef std::pair<std::string,int> Effet;

enum class RuneType {Marque, Sceau, Glyphe, Quint};

class Rune
{
public:
    Rune(const std::string &nom, const Effet &effet, const RuneType &type);
    Rune(std::string str); //pour pouvoir load à partir d'une chaîne de type "NOM TYPE EFFET_NOM EFFET_VALEUR"
    std::string getName() const;
    RuneType getType() const;
    Effet getEffet() const;
    QString getQPres() const;
private:
    std::string name_;
    Effet effet_;
    RuneType type_;
};

#endif // RUNE_H
