#include "sensorearia.h"
#include "../view/chart.h"

#include <QDateTime>
#include <QtCharts>

SensoreAria::SensoreAria():Sensore(), sogliaMassima(180){}

SensoreAria::SensoreAria(const unsigned int id,
                         const QString &nome,
                         const QString &unitaMisura,
                         const QString &icona,
                         const QString gruppo,
                         int sogliaMassima,
                         double valore
                         )
    : Sensore(id, nome, unitaMisura, icona, gruppo, valore)
    , sogliaMassima(sogliaMassima){}

Valore SensoreAria::getRandom(const QDateTime &dataOra)  {
    std::random_device rd;
    std::mt19937 gen(rd());

    double maxVariazione = 5.0;
    double min = std::max(30.0, this->getValore() - maxVariazione);
    double max = std::min(180.0, this->getValore() + maxVariazione);

    //distribuzione tra min e max della variazione es getValore = 50 min = 45 max= 55
    std::uniform_real_distribution<double> distribution(min, max);
    double valoreRandom = distribution(gen);

    //calcolo la variazione rispetto al valore precedente
    double variazioneDalPrecedente = valoreRandom - this->getValore();
    if (variazioneDalPrecedente > maxVariazione || variazioneDalPrecedente < -maxVariazione) {
        valoreRandom = this->getValore() + std::uniform_real_distribution<double>(-maxVariazione, maxVariazione)(gen); // se è troppo distante dal valore precedente, lo rendo più vicino
    }

    //sistemo il numero compreso tra 30 e 180
    valoreRandom = std::max(30.0, std::min(180.0, valoreRandom));

    //aggiungo la probabilistica variazione del 20% tra 50 e 75
    if (std::uniform_real_distribution<double>(0.0, 1.0)(gen) < 0.20) {
        double numeroProbabilistico = std::uniform_real_distribution<double>(50.0, 75.0)(gen);
        if (numeroProbabilistico >= this->getValore() - maxVariazione && numeroProbabilistico <= this->getValore() + maxVariazione) {
            valoreRandom = numeroProbabilistico;
        }
    }
    valoreRandom = std::round(valoreRandom * 100.0) / 100.0;
    return Valore(valoreRandom, dataOra);
}

Sensore *SensoreAria::clone() const {
    return new SensoreAria(*this);
}

int SensoreAria::getSogliaMassima() const {
    return sogliaMassima;
}

void SensoreAria::setSogliaMassima(const int &value) {
    sogliaMassima = value;
}

void SensoreAria::accetta(sensoreVisitor& visitor) const {
    visitor.visita(*this);
}


int hmain(int argc, char *argv[])
{
    SensoreAria s = SensoreAria(0,"Sensore1", "IQA", "prova","cucina",180,50);
    s.generaDati();
    QString abc = "anno";
    QApplication a(argc, argv);
    QMainWindow window;
    Chart palle;
    window.setCentralWidget(palle.getChart(s, abc));
    window.resize(1000,1000);
    window.show();
    return a.exec();
}
