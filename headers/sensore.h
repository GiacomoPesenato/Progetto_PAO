#ifndef SENSORE_H
#define SENSORE_H

#include <QWidget>
#include "valore.h"
#include <vector>

using namespace std;

class Sensore
{
private:
    QString nome;
    QString unitaMisura;
    vector<Valore> valori;
    QString icona;
    double valore;
public:
    Sensore();
    Sensore(const QString &name, const QString &unitaMisura, const QString &icona, double valore);
    void addValore(Valore valore);
    virtual Valore getRandom(const QDateTime &dataOra);
    vector<Valore> getValori() const;
    double getValore() const;
    void setValore(double valore);
};

#endif // SENSORE_H
