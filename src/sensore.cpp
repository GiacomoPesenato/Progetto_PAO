#include "../headers/sensore.h"
#include "../headers/valore.h"

#include <QDateTime>
#include <QVector>>

using namespace std;

Sensore::Sensore(const unsigned int &id, const QString &nome, const QString &unitaMisura, const QString &icona, const QString &gruppo,  double &valore)
    : id(id)
    , nome(nome)
    , unitaMisura(unitaMisura)
    , valori()
    , icona(icona)
    , gruppo(gruppo)
    , valore(valore)
{}

Sensore::Sensore()
    : id(-1)
    , nome("sensore")
    , unitaMisura("um")
    , valori()
    , icona("resources/icon.png")
    , gruppo("")
    , valore(10)
{}

void Sensore::addValore(Valore valore)
{
    valori.push_back(valore);
}

Valore Sensore::getRandom(const QDateTime &dataOra)
{
    srand(time(0));
    int intRandom = rand();
    double doubleRandom = static_cast<double>(intRandom) / 100;
    double random = doubleRandom * 100;

    Valore valore = Valore(random, dataOra);
    return valore;
}

QVector<Valore> Sensore::getValori() const{
    return this->valori;
}
double Sensore::getValore() const{
    return valore;
}
void Sensore::setValore(const double &valore){
    this->valore = valore;
}
