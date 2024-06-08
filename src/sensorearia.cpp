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

void SensoreAria::modificaData(QDateTime &data)
{
    //cout << "Sensore::modificaData" << endl;
    data = data.addDays(1);
    int currentMonth = data.date().month();
    if (data.date().daysInMonth() < data.date().day()) {
        data = data.addMonths(1);
        data.setDate(QDate(data.date().year(), currentMonth, data.date().day()));
    }
    //cout << "Data modificata: " << data.toString().toStdString() << endl;
}

Sensore *SensoreAria::clone() const {
    return new SensoreAria(*this);
}

int SensoreAria::getSogliaMassima() const {
    return sogliaMassima;
}

void SensoreAria::setSogliaMassima(int value) {
    sogliaMassima = value;
}

void SensoreAria::generaDati() {
    QDate dataCorrente = QDate::currentDate();
    QDate primoDelMese = QDate(dataCorrente.year(), dataCorrente.month(), 1);
    QTime startTime(0, 0, 0);
    QDateTime data(primoDelMese, startTime);
    for (int i = 0; i < 366; ++i) {
        Valore val = this->getRandom(data);
        this->setValore(val.getValore());
        this->modificaData(data);
        this->addValore(val);
    }
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
