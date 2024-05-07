#include "../headers/sensorearia.h"
#include "../headers/sensore.h"
#include "../headers/chart.h"

#include <QDateTime>
#include <QtCharts>

using namespace std;

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

    double maxVariation = 5.0;
    double min = std::max(30.0, this->getValore() - maxVariation);
    double max = std::min(180.0, this->getValore() + maxVariation);

    //distribuzione tra min e max della variazione es getValore = 50 min = 45 max= 55
    std::uniform_real_distribution<double> distribution(min, max);
    double randomNumber = distribution(gen);

    //calcolo la variazione rispetto al valore precedente
    double variationFromPrev = randomNumber - this->getValore();
    if (variationFromPrev > maxVariation || variationFromPrev < -maxVariation) {
        randomNumber = this->getValore() + std::uniform_real_distribution<double>(-maxVariation, maxVariation)(gen); // se è troppo distante dal valore precedente, lo rendo più vicino
    }

    //sistemo il numero compreso tra 30 e 180
    randomNumber = std::max(30.0, std::min(180.0, randomNumber));

    //aggiungo la probabilistica variazione del 20% tra 50 e 75
    if (std::uniform_real_distribution<double>(0.0, 1.0)(gen) < 0.20) {
        double biasedNumber = std::uniform_real_distribution<double>(50.0, 75.0)(gen);
        if (biasedNumber >= this->getValore() - maxVariation && biasedNumber <= this->getValore() + maxVariation) {
            randomNumber = biasedNumber;
        }
    }

    return Valore(randomNumber, dataOra);
}

void SensoreAria::modificaData(QDateTime &data){
    data = data.addDays(1);
    int currentMonth = data.date().month();
    if (data.date().daysInMonth() < data.date().day()) {
        // Se il giorno supera i giorni totali del mese, aumenta il mese
        data = data.addMonths(1);
        // Se era l'ultimo giorno di dicembre, aumenta anche l'anno
        if (currentMonth == 12) {
            data = data.addYears(1);
        }
        // Imposta il giorno a 1 per il nuovo mese
        data.setDate(QDate(data.date().year(), data.date().month(), 1));
    }
}

Sensore *SensoreAria::clone() const {
    return new SensoreAria(*this);
}


int main(int argc, char *argv[])
{
    QDateTime data = QDateTime::currentDateTime();
    SensoreAria s = SensoreAria(0,"Sensore1", "IQA", "prova","cucina",180,50);
    for (int i = 0; i < 366; ++i) {
        Valore val = s.getRandom(data);
        s.setValore(val.getValore());
        s.modificaData(data);
        s.addValore(val);
    }
    QApplication a(argc, argv);
    QMainWindow window;
    QString abc = "mese";
    window.setCentralWidget(Chart::getChart(s, abc));
    window.resize(1000,1000);
    window.show();
    return a.exec();
}
