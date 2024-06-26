#ifndef SENSOREELETTRODOMESTICO_H
#define SENSOREELETTRODOMESTICO_H

#include <QtWidgets>
#include "sensoreelettricita.h"

class SensoreElettrodomestico : public SensoreElettricita
{
private:
    QString classeEnergetica;
    QString tipoElettrodomestico;
public:
    SensoreElettrodomestico();
    SensoreElettrodomestico(const unsigned int id,
                            const QString &name,
                            const QString &unitaMisura,
                            const QString &icona,
                            const QString gruppo,
                            QString classeEnergetica,
                            double potenzaMax,
                            double valore,
                            QString tipoElettrodomestico);

    QString getClasseEnergetica() const;
    void setClasseEnergetica(const QString &value);

    QString getTipoElettrodomestico() const;
    void setTipoElettrodomestico(const QString &value);

    virtual Sensore *clone() const override;
    Valore getRandom(const QDateTime &dataOra) override;
    virtual void accetta(sensoreVisitor& visitor) const override;
    ~SensoreElettrodomestico() override = default;
};
#endif // SENSOREELETTRODOMESTICO_H
