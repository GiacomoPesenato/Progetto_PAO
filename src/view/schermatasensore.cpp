#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif


#include "schermatasensore.h"
#include "../model/sensorelampadina.h"
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
    QIcon iconIndietro("C:/Users/samsung/Desktop/PAO grafica/untitled/img/indietro.png"); // Sostituisci con il percorso dell'immagine della freccia
    buttonIndietro->setIcon(iconIndietro);
    buttonIndietro->setIconSize(QSize(24, 24));

    QWidget *widgetIconaSensore = new QWidget;
    QVBoxLayout *layoutIconaSensore = new QVBoxLayout(widgetIconaSensore);
    widgetIconaSensore->setLayout(layoutIconaSensore);

    QWidget *widgetInfoSensore = new QWidget;
    QVBoxLayout *layoutInfoSensore = new QVBoxLayout(widgetInfoSensore);
    widgetInfoSensore->setLayout(layoutInfoSensore);

    QWidget *widgetFunzioniSensore = new QWidget;
    QVBoxLayout *layoutFunzioniSensore = new QVBoxLayout(widgetFunzioniSensore);
    widgetFunzioniSensore->setLayout(layoutFunzioniSensore);

    QWidget *widgetFiltriGrafico = new QWidget;
    QHBoxLayout *layoutFiltriGrafico = new QHBoxLayout(widgetFiltriGrafico);
    widgetFiltriGrafico->setLayout(layoutFiltriGrafico);
    mainLayout->addWidget(widgetFiltriGrafico);

    topLeftLayout->addWidget(widgetIconaSensore);
    topLeftLayout->addWidget(widgetInfoSensore);
    topLeftLayout->addStretch();
    topLeftLayout->addWidget(widgetFunzioniSensore);

    int idSensore = 0;
    QString nomeSensore = "";
    QString gruppoSensore = "";
    QString iconaSensore = "C:/Users/samsung/Desktop/PAO grafica/untitled/img/aria.png";
    QString unitaMisuraSensore = "";
    double valoreSensore = 0.0;

    labelId = new QLabel("ID: "+QString::number(idSensore));
    labelNome = new QLabel("NOME: "+nomeSensore);
    labelGruppo = new QLabel("GRUPPO: "+gruppoSensore);
    labelValore = new QLabel("VALORE: "+QString::number(valoreSensore)+unitaMisuraSensore);

    QPixmap icona(iconaSensore);
    labelIcona = new QLabel;
    labelIcona->setPixmap(icona.scaled(70, 70, Qt::KeepAspectRatio));

    labelId->setStyleSheet("color: white; font-size: 16px;");
    labelNome->setStyleSheet("color: white; font-size: 16px;");
    labelGruppo->setStyleSheet("color: white; font-size: 16px;");
    labelValore->setStyleSheet("color: white; font-size: 16px;");

    QPushButton *buttonSimula = new QPushButton("Simula");
    QPushButton *buttonModifica = new QPushButton("Modifica");
    QPushButton *buttonElimina = new QPushButton("Elimina");

    buttonAnno = new QPushButton("Anno");
    buttonMese = new QPushButton("Mese");
    buttonSettimana = new QPushButton("Settimana");
    buttonGiorno = new QPushButton("Giorno");

    layoutIconaSensore->addWidget(buttonIndietro, Qt::AlignTop | Qt::AlignLeft);
    layoutIconaSensore->addWidget(labelIcona, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelId, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelNome, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelGruppo, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelValore, Qt::AlignTop | Qt::AlignLeft);
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
    labelId->setText("ID: " + QString::number(sensore->getId()));
    labelNome->setText("Nome Sensore: " + sensore->getNome());
    labelGruppo->setText("GRUPPO: " + sensore->getGruppo());
    labelValore->setText("Valore Sensore: " + QString::number(sensore->getValore()) + " " + sensore->getUnitaMisura());
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
