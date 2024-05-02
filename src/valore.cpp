#include "../headers/valore.h"

Valore::Valore(double valore, const QDateTime &dataOra)
    : valore(valore)
    , dataOra(dataOra)
{}

double Valore::getValore() const
{
    return valore;
}

const QDateTime &Valore::getDataOra() const
{
    return dataOra;
}

void Valore::setValore(const double &valore)
{
    this->valore = valore;
}
