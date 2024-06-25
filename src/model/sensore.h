#ifndef SENSORE_H
#define SENSORE_H

#include <QWidget>
#include "sensorevisitor.h"
#include "valore.h"
#include <QVector>

using namespace std;

class Sensore
{
private:
    unsigned int id;
    QString nome;
    QString unitaMisura;
    QVector<Valore> valori;
    QString icona;
    QString gruppo;
    double valore;
public:
    Sensore(const unsigned int &id, const QString &name, const QString &unitaMisura, const QString &icona, const QString &gruppo, double &valore);
    Sensore();

    void addValore(Valore valore);

    double getValore() const;
    void setValore(const double &valore);

    unsigned int getId() const;
    void setId(const unsigned int &id);

    QString getNome() const;
    void setNome(QString &nome);

    QString getUnitaMisura() const;
    void setUnitaMisura(QString &unitaMisura);

    QString getIcona() const;
    void setIcona(QString &icona);

    QString getGruppo() const;

    QVector<Valore> getValori() const;
    void setValori(QVector<Valore> &valori);

    void rimuoviDati();

    virtual ~Sensore() = default;
    virtual Sensore *clone() const = 0;
    virtual Valore getRandom(const QDateTime &dataOra);
    virtual void generaDati();
    virtual void accept(sensoreVisitor& visitor) const = 0;

};
#endif // SENSORE_H


