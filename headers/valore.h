#ifndef VALORE_H
#define VALORE_H

#include <QDateTime>

class Valore
{
private:
    double valore;
    QDateTime dataOra;

public:
    Valore(double valore, const QDateTime &dataOra);

    double getValore() const;

    const QDateTime &getDataOra() const;
};

#endif // VALORE_H
