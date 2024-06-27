#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif


#include "schermatasensore.h"
#include "../model/sensorearia.h"
#include "../model/sensoreelettrodomestico.h"
#include "../model/sensorelampadina.h"
#include "../model/sensorepannelli.h"
#include "../model/sensoretemperatura.h"
#include "../model/sensoreumidita.h"
#include "chart.h"

SchermataSensore::SchermataSensore(QWidget *parent)
    : QWidget(parent){

    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    // Sotto-layout per posizionare i widget in alto a sinistra
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    QWidget *topLeftWidget = new QWidget;
    topLeftWidget->setLayout(topLeftLayout);
    topLeftLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(topLeftWidget, 0, Qt::AlignTop);

    QPushButton *buttonIndietro = new QPushButton;
    QIcon iconIndietro(":/indietro.png");
    buttonIndietro->setIcon(iconIndietro);
    buttonIndietro->setIconSize(QSize(24, 24));

    QWidget *widgetIconaSensore = new QWidget;
    QVBoxLayout *layoutIconaSensore = new QVBoxLayout(widgetIconaSensore);
    widgetIconaSensore->setLayout(layoutIconaSensore);

    QWidget *widgetInfoSensore = new QWidget;
    QVBoxLayout *layoutInfoSensore = new QVBoxLayout(widgetInfoSensore);
    widgetInfoSensore->setLayout(layoutInfoSensore);

    QWidget *widgetInfoSecondarieSensore = new QWidget;
    QVBoxLayout *layoutInfoSecondarieSensore = new QVBoxLayout(widgetInfoSecondarieSensore);
    widgetInfoSecondarieSensore->setLayout(layoutInfoSecondarieSensore);

    QWidget *widgetFunzioniSensore = new QWidget;
    QVBoxLayout *layoutFunzioniSensore = new QVBoxLayout(widgetFunzioniSensore);
    widgetFunzioniSensore->setLayout(layoutFunzioniSensore);

    QWidget *widgetFiltriGrafico = new QWidget;
    QHBoxLayout *layoutFiltriGrafico = new QHBoxLayout(widgetFiltriGrafico);
    widgetFiltriGrafico->setLayout(layoutFiltriGrafico);
    mainLayout->addWidget(widgetFiltriGrafico);

    topLeftLayout->addWidget(widgetIconaSensore);
    topLeftLayout->addWidget(widgetInfoSensore);
    topLeftLayout->addWidget(widgetInfoSecondarieSensore);
    topLeftLayout->addStretch();
    topLeftLayout->addWidget(widgetFunzioniSensore);

    int idSensore = 0;
    QString nomeSensore = "";
    QString gruppoSensore = "";
    QString iconaSensore = "";
    QString unitaMisuraSensore = "";
    double valoreSensore = 0.0;

    labelId = new QLabel("Id: "+QString::number(idSensore));
    labelNome = new QLabel("Nome: "+nomeSensore);
    labelGruppo = new QLabel("Gruppo: "+gruppoSensore);
    labelValore = new QLabel("Valore: "+QString::number(valoreSensore)+unitaMisuraSensore);
    labelTemperaturaTarget = new QLabel("Target: ");
    labelUmiditaTarget = new QLabel("Target: ");
    labelPotenzaMassima = new QLabel("Potenza Massima: ");
    labelDimmerabile = new QLabel("Dimmerabile: ");
    labelNumeroPannelli = new QLabel("Numero Pannelli: ");
    labelPotenzaPannello = new QLabel("Potenza Pannello: ");
    labelClasseEnergetica = new QLabel("Classe Energetica: ");

    QPixmap icona(iconaSensore);
    labelIcona = new QLabel;
    labelIcona->setPixmap(icona.scaled(70, 70, Qt::KeepAspectRatio));

    QPushButton *buttonSimula = new QPushButton("Simula");
    QPushButton *buttonModifica = new QPushButton("Modifica");
    QPushButton *buttonElimina = new QPushButton("Elimina");

    buttonAnno = new QPushButton("Anno");
    buttonMese = new QPushButton("Mese");
    buttonSettimana = new QPushButton("Settimana");
    buttonGiorno = new QPushButton("Giorno");

    layoutIconaSensore->addWidget(buttonIndietro, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutIconaSensore->addWidget(labelIcona, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutIconaSensore->addStretch();
    layoutInfoSensore->addWidget(labelId, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelNome, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelGruppo, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelValore, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addStretch();
    layoutInfoSecondarieSensore->addWidget(labelTemperaturaTarget, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSecondarieSensore->addWidget(labelUmiditaTarget, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSecondarieSensore->addWidget(labelPotenzaMassima, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSecondarieSensore->addWidget(labelDimmerabile, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSecondarieSensore->addWidget(labelNumeroPannelli, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSecondarieSensore->addWidget(labelPotenzaPannello, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSecondarieSensore->addWidget(labelClasseEnergetica, 0, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSecondarieSensore->addStretch();
    layoutFunzioniSensore->addWidget(buttonSimula, Qt::AlignTop | Qt::AlignRight);
    layoutFunzioniSensore->addWidget(buttonModifica, Qt::AlignTop | Qt::AlignRight);
    layoutFunzioniSensore->addWidget(buttonElimina, Qt::AlignTop | Qt::AlignRight);
    layoutFiltriGrafico->addWidget(buttonAnno, Qt::AlignTop | Qt::AlignRight);
    layoutFiltriGrafico->addWidget(buttonMese, Qt::AlignTop | Qt::AlignRight);
    layoutFiltriGrafico->addWidget(buttonSettimana, Qt::AlignTop | Qt::AlignRight);
    layoutFiltriGrafico->addWidget(buttonGiorno, Qt::AlignTop | Qt::AlignRight);
    layoutFiltriGrafico->addStretch();

    // Connect dei button indietro, simula, modifica ed elimina
    connect(buttonIndietro, &QPushButton::clicked, this, &SchermataSensore::chiudiSchermataSensore);
    connect(buttonSimula, &QPushButton::clicked, this, &SchermataSensore::simula);
    connect(buttonModifica, &QPushButton::clicked, this, &SchermataSensore::modificaSensore);
    connect(buttonElimina, &QPushButton::clicked, this, &SchermataSensore::eliminaSensore);

    connect(buttonAnno, &QPushButton::clicked, this, &SchermataSensore::setGraficoAnno);
    connect(buttonMese, &QPushButton::clicked, this, &SchermataSensore::setGraficoMese);
    connect(buttonSettimana, &QPushButton::clicked, this, &SchermataSensore::setGraficoSettimana);
    connect(buttonGiorno, &QPushButton::clicked, this, &SchermataSensore::setGraficoGiorno);


    // Creazione e aggiunta del QChart in basso al centro
    QWidget *chartWidget = new QWidget;
    chartLayout = new QVBoxLayout(chartWidget);
    chartLayout->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    mainLayout->addWidget(chartWidget, 1); // Espande per occupare lo spazio rimanente

    this->setStyleSheet(
        "QLabel {"
        "   color: white;"
        "   font-size: 16px;"
        "}"
        "QPushButton {"
        "    background-color: #5DADE2;"
        "    color: white;"
        "    font-size: 16px;"
        "    border-radius: 10px;"
        "    padding: 10px 20px;"
        "    text-align: center;"
        "}"
        "QPushButton:hover {"
        "    background-color: #4885af;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #335e7c;"
        "    color: #B2EBF2;"
        "}"
        );
}

void SchermataSensore::setSensore(Sensore *sensore) {
    this->sensore = sensore;
    //informazioni sensore
    labelId->setText("Id: " + QString::number(sensore->getId()));
    labelNome->setText("Nome: " + sensore->getNome());
    labelGruppo->setText("Gruppo: " + sensore->getGruppo());
    labelValore->setText("Valore: " + QString::number(sensore->getValore()) + " " + sensore->getUnitaMisura());
    //informazioni secondarie sensore
    labelTemperaturaTarget->setVisible(false);
    labelUmiditaTarget->setVisible(false);
    labelPotenzaMassima->setVisible(false);
    labelDimmerabile->setVisible(false);
    labelNumeroPannelli->setVisible(false);
    labelPotenzaPannello->setVisible(false);
    labelClasseEnergetica->setVisible(false);
    if (dynamic_cast<SensoreAria*>(sensore)) {
    } else if (dynamic_cast<SensoreTemperatura*>(sensore)) {
        SensoreTemperatura* sensoretemperatura = dynamic_cast<SensoreTemperatura*>(sensore);
        labelTemperaturaTarget->setText("Target: " + QString::number(sensoretemperatura->getValoreTarget()));
        labelTemperaturaTarget->setVisible(true);
    } else if (dynamic_cast<SensoreUmidita*>(sensore)) {
        SensoreUmidita* sensoreumidita = dynamic_cast<SensoreUmidita*>(sensore);
        labelUmiditaTarget->setText("Target: " + QString::number(sensoreumidita->getValoreTarget()));
        labelUmiditaTarget->setVisible(true);
    } else if (dynamic_cast<SensoreLampadina*>(sensore)) {
        SensoreLampadina* sensorelampadina = dynamic_cast<SensoreLampadina*>(sensore);
        labelPotenzaMassima->setText("Potenza Massima: " + QString::number(sensorelampadina->getPotenzaMax()) + " W");
        labelPotenzaMassima->setVisible(true);
        if(sensorelampadina->getDimmer()){
            labelDimmerabile->setText("Dimmerabile: Sì");
        }else{
            labelDimmerabile->setText("Dimmerabile: No");
        }
        labelDimmerabile->setVisible(true);
    } else if (dynamic_cast<SensorePannelli*>(sensore)) {
        SensorePannelli* sensorepannelli = dynamic_cast<SensorePannelli*>(sensore);
        labelPotenzaMassima->setText("Potenza Massima: " + QString::number(sensorepannelli->getPotenzaMax()) + " W");
        labelPotenzaMassima->setVisible(true);
        labelNumeroPannelli->setText("Numero Pannelli: " + QString::number(sensorepannelli->getNPannelli()));
        labelNumeroPannelli->setVisible(true);
        labelPotenzaPannello->setText("Potenza Pannello: " + QString::number(sensorepannelli->getPotenzaPannello()) + " W");
        labelPotenzaPannello->setVisible(true);
    } else if (dynamic_cast<SensoreElettrodomestico*>(sensore)) {
        SensoreElettrodomestico* sensoreelettrodomestico = dynamic_cast<SensoreElettrodomestico*>(sensore);
        labelPotenzaMassima->setText("Potenza Massima: " + QString::number(sensoreelettrodomestico->getPotenzaMax()) + " W");
        labelPotenzaMassima->setVisible(true);
        labelClasseEnergetica->setText("Classe Energetica: " + sensoreelettrodomestico->getClasseEnergetica());
        labelClasseEnergetica->setVisible(true);
    }

    QPixmap icona(sensore->getIcona());
    labelIcona->setPixmap(icona.scaled(70, 70, Qt::KeepAspectRatio));
    if (chartLayout->count() > 0) {
        QWidget *oldChart = chartLayout->itemAt(0)->widget();
        if (oldChart) {
            chartLayout->removeWidget(oldChart);
            oldChart->deleteLater();
        }
    }
    buttonAnno->setVisible(false);
    buttonMese->setVisible(false);
    buttonSettimana->setVisible(false);
    buttonGiorno->setVisible(false);
    if(sensore->getValori().size()>0){
        Chart grafico;
        if (dynamic_cast<SensoreLampadina*>(sensore)) {
            buttonAnno->setVisible(false);
            buttonMese->setVisible(true);
            buttonSettimana->setVisible(true);
            buttonGiorno->setVisible(true);
            buttonAnno->setStyleSheet("background-color: #5DADE2;");
            buttonMese->setStyleSheet("background-color: #4885af;");
            buttonSettimana->setStyleSheet("background-color: #5DADE2;");
            buttonGiorno->setStyleSheet("background-color: #5DADE2;");
            chartLayout->addWidget(grafico.getChart(*sensore, "mese"));
        }else{
            buttonAnno->setVisible(true);
            buttonMese->setVisible(true);
            buttonSettimana->setVisible(true);
            buttonGiorno->setVisible(false);
            buttonAnno->setStyleSheet("background-color: #4885af;");
            buttonMese->setStyleSheet("background-color: #5DADE2;");
            buttonSettimana->setStyleSheet("background-color: #5DADE2;");
            buttonGiorno->setStyleSheet("background-color: #5DADE2;");
            chartLayout->addWidget(grafico.getChart(*sensore, "anno"));
        }
    }
}

void SchermataSensore::chiudiSchermataSensore() {
    emit chiudiSchermataSensoreSignal();
}

void SchermataSensore::simula() {
    sensore->rimuoviDati();
    sensore->generaDati();
    Chart nuovoGrafico;
    labelValore->setText("Valore: " + QString::number(sensore->getValore()) + " " + sensore->getUnitaMisura());
    Chart grafico;

    if (chartLayout->count() > 0) {
        QWidget *vecchioGrafico = chartLayout->itemAt(0)->widget();
        if (vecchioGrafico) {
            chartLayout->removeWidget(vecchioGrafico);
            vecchioGrafico->deleteLater();
        }
    }

    if (dynamic_cast<SensoreLampadina*>(sensore)) {
        buttonAnno->setVisible(false);
        buttonMese->setVisible(true);
        buttonSettimana->setVisible(true);
        buttonGiorno->setVisible(true);
        buttonAnno->setStyleSheet("background-color: #5DADE2;");
        buttonMese->setStyleSheet("background-color: #4885af;");
        buttonSettimana->setStyleSheet("background-color: #5DADE2;");
        buttonGiorno->setStyleSheet("background-color: #5DADE2;");
        chartLayout->addWidget(nuovoGrafico.getChart(*sensore, "mese"));
    }else{
        buttonAnno->setVisible(true);
        buttonMese->setVisible(true);
        buttonSettimana->setVisible(true);
        buttonGiorno->setVisible(false);
        buttonAnno->setStyleSheet("background-color: #4885af;");
        buttonMese->setStyleSheet("background-color: #5DADE2;");
        buttonSettimana->setStyleSheet("background-color: #5DADE2;");
        buttonGiorno->setStyleSheet("background-color: #5DADE2;");
        chartLayout->addWidget(nuovoGrafico.getChart(*sensore, "anno"));
    }
}

void SchermataSensore::modificaSensore(){
    emit modificaSensoreSignal(sensore);
}

void SchermataSensore::eliminaSensore(){
    emit eliminaSensoreSignal(sensore);
}

void SchermataSensore::setGraficoAnno(){
    if (chartLayout->count() > 0) {
        QWidget *vecchioGrafico = chartLayout->itemAt(0)->widget();
        if (vecchioGrafico) {
            chartLayout->removeWidget(vecchioGrafico);
            vecchioGrafico->deleteLater();
            Chart nuovoGrafico;
            chartLayout->addWidget(nuovoGrafico.getChart(*sensore, "anno"));
            buttonAnno->setStyleSheet("background-color: #4885af;");
            buttonMese->setStyleSheet("background-color: #5DADE2;");
            buttonSettimana->setStyleSheet("background-color: #5DADE2;");
            buttonGiorno->setStyleSheet("background-color: #5DADE2;");
        }
    }
}

void SchermataSensore::setGraficoMese(){
    if (chartLayout->count() > 0) {
        QWidget *vecchioGrafico = chartLayout->itemAt(0)->widget();
        if (vecchioGrafico) {
            chartLayout->removeWidget(vecchioGrafico);
            vecchioGrafico->deleteLater();
            Chart nuovoGrafico;
            chartLayout->addWidget(nuovoGrafico.getChart(*sensore, "mese"));
            buttonAnno->setStyleSheet("background-color: #5DADE2;");
            buttonMese->setStyleSheet("background-color: #4885af;");
            buttonSettimana->setStyleSheet("background-color: #5DADE2;");
            buttonGiorno->setStyleSheet("background-color: #5DADE2;");
        }
    }
}

void SchermataSensore::setGraficoSettimana(){
    if (chartLayout->count() > 0) {
        QWidget *vecchioGrafico = chartLayout->itemAt(0)->widget();
        if (vecchioGrafico) {
            chartLayout->removeWidget(vecchioGrafico);
            vecchioGrafico->deleteLater();
            Chart nuovoGrafico;
            chartLayout->addWidget(nuovoGrafico.getChart(*sensore, "settimana"));
            buttonAnno->setStyleSheet("background-color: #5DADE2;");
            buttonMese->setStyleSheet("background-color: #5DADE2;");
            buttonSettimana->setStyleSheet("background-color: #4885af;");
            buttonGiorno->setStyleSheet("background-color: #5DADE2;");
        }
    }
}

void SchermataSensore::setGraficoGiorno(){
    if (chartLayout->count() > 0) {
        QWidget *vecchioGrafico = chartLayout->itemAt(0)->widget();
        if (vecchioGrafico) {
            chartLayout->removeWidget(vecchioGrafico);
            vecchioGrafico->deleteLater();
            Chart nuovoGrafico;
            chartLayout->addWidget(nuovoGrafico.getChart(*sensore, "giorno"));
            buttonAnno->setStyleSheet("background-color: #5DADE2;");
            buttonMese->setStyleSheet("background-color: #5DADE2;");
            buttonSettimana->setStyleSheet("background-color: #5DADE2;");
            buttonGiorno->setStyleSheet("background-color: #4885af;");
        }
    }
}
