#include "rune.h"
#include <sstream>
#include <stdexcept>

using namespace std;

Rune::Rune(string const& nom, Effet const& effet, RuneType const& type) : name_(nom), effet_(effet), type_(type)
{

}

Rune::Rune(string str) //pour pouvoir load à partir d'une chaîne de type "NOM TYPE EFFET_NOM EFFET_VALEUR"
{
    istringstream iss(str); //d'où la copie
    try // on est pas sûrs que le fichier soit valide
    {
        string sub{""};

        iss >> sub; //premier "mot"
        name_ = sub;

        iss >> sub; //deuxième
        if (sub == "M") //marque
        {
            type_ = RuneType::Marque;
        }
        else if (sub == "S") //sceau
        {
            type_ = RuneType::Sceau;
        }
        else if (sub == "G") //glyphe
        {
            type_ = RuneType::Glyphe;
        }
        else if (sub == "Q") //quintessence
        {
            type_ = RuneType::Quint;
        }
        else //oulah problème
        {
            throw runtime_error("Unable to find type.");
        }

        iss >> sub; //nom de l'effet
        effet_.first = sub;

        iss >> sub; //valeur
        effet_.second = stoi(sub); //on tente la conversion !
    }
    catch (...) //un problème est survenu...
    {
        throw runtime_error("Index corrupted.");
    }
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

QString Rune::getQPres() const
{
    return QString(QString::number(static_cast<int>(type_)) + " " + name_.c_str() + " " + effet_.first.c_str() + " " + QString::number(effet_.second));
}
