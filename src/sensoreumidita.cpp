#include "../headers/sensoreumidita.h"
#include "../headers/sensore.h"
#include <random>

using namespace std;

SensoreUmidita::SensoreUmidita()
    : Sensore()
    , valoreTarget(80)
{}

SensoreUmidita::SensoreUmidita(const unsigned int id,
                               const QString &nome,
                               const QString &unitaMisura,
                               const QString &icona,
                               const QString gruppo,
                               double valoreTarget,
                               double valore)
    : Sensore(id, nome, unitaMisura, icona, gruppo, valore)
    , valoreTarget(valoreTarget)
{}

double SensoreUmidita::getValoreTarget() const
{
    return valoreTarget;
}

Valore SensoreUmidita::getRandom(const QDateTime &dataOra){
    // Inizializza il generatore di numeri casuali con il tempo corrente
    random_device rd;
    mt19937 gen(rd());

    // Definisci la distribuzione normale con media = valoreTarget e deviazione standard = 3
    // La deviazione standard controlla la dispersione dei valori generati
    normal_distribution<double> distribution(valoreTarget, 3.0);

    // Genera il valore casuale
    double valoreCasuale = distribution(gen);

    // Limita il valoreCasuale tra valoreTarget-10 e valoreTarget+5
    valoreCasuale = max(valoreTarget - 10.0, min(valoreCasuale, valoreTarget + 3.0));

    double random = valoreCasuale;

    Valore valore = Valore(random, dataOra);
    return valore;
}
