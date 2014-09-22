#include "rune.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

template <typename T>
T abs(T a)
{
    return (a >= 0) ? a : -1*a;
}

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
        replace(sub.begin(), sub.end(), '_', ' ');
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
        effet_.second = stod(sub); //on tente la conversion !
    }
    catch (...) //un problème est survenu...
    {
        throw runtime_error("Index corrupted.");
    }
}

std::string Rune::toString() const //FORMAT : NOM_LONG M/S/G/Q EFETNOM EFFETVALEUR
{
    string nameCopy = name_;
    replace(nameCopy.begin(), nameCopy.end(), ' ', '_'); //on remplace ' ' par '_'
    string ret = nameCopy;
    if (type_ == RuneType::Marque) ret += " M";
    if (type_ == RuneType::Sceau) ret += " S";
    if (type_ == RuneType::Glyphe) ret += " G";
    if (type_ == RuneType::Quint) ret += " Q";
    ret += " " + effet_.first;
    ret += " " + to_string(effet_.second);
    return ret;
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

QString Rune::getColoredName(unsigned size) const
{
    QString color;
    if (type_ == RuneType::Marque)
    {
        color = "#c24000";
    }
    else if (type_ == RuneType::Sceau)
    {
        color = "#f1c900";
    }
    else if (type_ == RuneType::Glyphe)
    {
        color = "#0183da";
    }
    else if (type_ == RuneType::Quint)
    {
        color = "#ffac05";
    }
    return QString("<html><head/><body><p><span style=\" font-size:" + QString::number(size) + "pt; font-weight:500; color:" + color + ";\">" + name_.c_str() + "</span></p></body></html>");
}

QString Rune::getColoredEffect(unsigned size) const
{
    QString signe = (effet_.second > 0) ? "#4dc515;\">+ " : "#0267b5;\">- ";
    //<html><head/><body><p align="center"><span style=" font-size:10pt; font-weight:600; color:#4dc515;">+ XX</span><span style=" font-size:10pt;"/><span style=" font-size:10pt; font-weight:600; font-style:italic;">YYY</span></p></body></html>
    return QString("<html><head/><body><p><span style=\" font-size:" + QString::number(size) +"pt; font-weight:400; color:" + signe + QString::number(abs(effet_.second)) + "</span><span style=\" font-size:" + QString::number(size) + "pt;\"/><span style=\" font-size:" + QString::number(size) + "pt; font-weight:600; font-style:italic;\"> " + effet_.first.c_str() + "</span></p></body></html>");
}
