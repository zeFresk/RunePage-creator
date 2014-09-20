#include "rune.h"

Rune::Rune(std::string nom, Effet effet, RuneType type) : name_(nom), effet_(effet), type_(type)
{

}

std::string Rune::getName() const
{
    return name_;
}

RuneType Rune::getType() const
{
    return type_;
}

Effet Rune::getEffet() const
{
    return effet_;
}
