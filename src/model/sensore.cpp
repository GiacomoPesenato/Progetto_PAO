#include "sensore.h"
#include "valore.h"

#include <QDateTime>
#include <QVector>
#include <iostream>

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
    , unitaMisura("N/A")
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

void Sensore::generaDati() {
    QDate dataCorrente = QDate::currentDate();
    QDate primoDelMese = QDate(dataCorrente.year(), dataCorrente.month(), 1);
    QTime orarioInizio(0, 0, 0);
    QDateTime data(primoDelMese, orarioInizio);
    for (int i = 0; i < 365; ++i) {
        Valore val = this->getRandom(data);
        this->setValore(val.getValore());
        this->addValore(val);
        data = data.addDays(1);
    }
}

unsigned int Sensore::getId() const{
    return id;
}

void Sensore::setId(const unsigned int &id){
    this->id = id;
}

double Sensore::getValore() const{
    return valore;
}

void Sensore::setValore(const double &valore){
    this->valore = valore;
}

QString Sensore::getNome() const{
    return nome;
}
void Sensore::setNome(const QString &nome){
    this->nome = nome;
}

QString Sensore::getUnitaMisura() const{
    return unitaMisura;
}

QString Sensore::getGruppo() const{
    return gruppo;
}
void Sensore::setGruppo(const QString &gruppo){
    this->gruppo = gruppo;
}

void Sensore::setUnitaMisura(const QString &unitaMisura){
    this->unitaMisura = unitaMisura;
}

QString Sensore::getIcona() const{
    return icona;
}
void Sensore::setIcona(QString &icona){
    this->icona = icona;
}

QVector<Valore> Sensore::getValori() const{
    return this->valori;
}
void Sensore::setValori(QVector<Valore> &valori){
    this->valori = valori;
}
void Sensore::rimuoviDati(){
    valori.clear();
}

