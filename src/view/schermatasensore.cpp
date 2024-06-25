#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif


#include "schermatasensore.h"
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

    topLeftLayout->addWidget(widgetIconaSensore);
    topLeftLayout->addWidget(widgetInfoSensore);
    topLeftLayout->addStretch();
    topLeftLayout->addWidget(widgetFunzioniSensore);

    int idSensore = 0;
    QString nomeSensore = "";
    QString gruppoSensore = "";
    QString iconaSensore = "C:/Users/samsung/Desktop/PAO grafica/untitled/img/aria.png";
    QString unitaMisuraSensore = "";
    double valoreSensore = NULL;

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

    buttonSimula->setStyleSheet("    background-color: white;"
                                "    color: black;"
                                "    font-size: 16px;"
                                "    border-radius: 10px;"
                                "    margin: 5px;"
                                "    padding: 5px;");
    buttonModifica->setStyleSheet("    background-color: white;"
                                "    color: black;"
                                "    font-size: 16px;"
                                "    border-radius: 10px;"
                                "    margin: 5px;"
                                "    padding: 5px;");
    buttonElimina->setStyleSheet("    background-color: white;"
                                "    color: black;"
                                "    font-size: 16px;"
                                "    border-radius: 10px;"
                                "    margin: 5px;"
                                "    padding: 5px;");

    layoutIconaSensore->addWidget(buttonIndietro, Qt::AlignTop | Qt::AlignLeft);
    layoutIconaSensore->addWidget(labelIcona, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelId, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelNome, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelGruppo, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelValore, Qt::AlignTop | Qt::AlignLeft);
    layoutFunzioniSensore->addWidget(buttonSimula, Qt::AlignTop | Qt::AlignRight);
    layoutFunzioniSensore->addWidget(buttonModifica, Qt::AlignTop | Qt::AlignRight);
    layoutFunzioniSensore->addWidget(buttonElimina, Qt::AlignTop | Qt::AlignRight);

    connect(buttonIndietro, &QPushButton::clicked, this, &SchermataSensore::chiudiSchermataSensore);
    connect(buttonSimula, &QPushButton::clicked, this, &SchermataSensore::simula);

    // Creazione e aggiunta del QChart in basso al centro
    QWidget *chartWidget = new QWidget;
    chartLayout = new QVBoxLayout(chartWidget);
    chartLayout->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    mainLayout->addWidget(chartWidget, 1); // Espande per occupare lo spazio rimanente
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
    if(sensore->getValori().size()>0){
        Chart grafico;
        chartLayout->addWidget(grafico.getChart(*sensore, "settimana"));
    }
}

void SchermataSensore::chiudiSchermataSensore() {
    emit chiudiSchermataSensoreSignal();
}

void SchermataSensore::simula() {
    sensore->rimuoviDati();
    sensore->generaDati();
    Chart grafico;

    // Rimuovi il vecchio grafico se esiste
    if (chartLayout->count() > 0) {
        QWidget *oldChart = chartLayout->itemAt(0)->widget();
        if (oldChart) {
            chartLayout->removeWidget(oldChart);
            oldChart->deleteLater();
        }
    }

    // Aggiungi il nuovo grafico
    chartLayout->addWidget(grafico.getChart(*sensore, "settimana"));
}
