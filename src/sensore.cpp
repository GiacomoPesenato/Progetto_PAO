#include "../headers/sensore.h"
#include "../headers/valore.h"

#include <QDateTime>
#include <vector>

using namespace std;

Sensore::Sensore(const QString &nome, const QString &unitaMisura, const QString &icona, double valore)
    : nome(nome)
    , unitaMisura(unitaMisura)
    , valori()
    , icona(icona)
    , valore(valore)
{}

Sensore::Sensore()
    : nome("sensore")
    , unitaMisura("um")
    , valori()
    , icona("resources/icon.png")
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

vector<Valore> Sensore::getValori() const{
    return this->valori;
}
double Sensore::getValore() const{
    return valore;
}
void Sensore::setValore(double valore){
    this->valore = valore;
}
