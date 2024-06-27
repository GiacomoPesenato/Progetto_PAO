#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif

#include "schermatamodificasensore.h"
#include "../model/sensorearia.h"
#include "../model/sensoreelettrodomestico.h"
#include "../model/sensorelampadina.h"
#include "../model/sensorepannelli.h"
#include "../model/sensoretemperatura.h"
#include "../model/sensoreumidita.h"
#include <iostream>
#include <QMessageBox>

SchermataModificaSensore::SchermataModificaSensore(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *centerWidget = new QWidget(this);
    QVBoxLayout *centerLayout = new QVBoxLayout(centerWidget);
    centerLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(centerWidget);

    //Button indietro
    QPushButton *buttonIndietro = new QPushButton;
    QIcon iconIndietro("C:/Users/samsung/Desktop/PAO grafica/untitled/img/indietro.png"); // Sostituisci con il percorso dell'immagine della freccia
    buttonIndietro->setIcon(iconIndietro);
    buttonIndietro->setIconSize(QSize(24, 24));
    buttonIndietro->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    centerLayout->addWidget(buttonIndietro);

    // Tipo sensore (generale)
    labelTipo1 = new QLabel("Tipo sensore:");
    labelTipo1->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelTipo1);
    inputTipo1 = new QComboBox(this);
    inputTipo1->addItem("Qualità aria");
    inputTipo1->addItem("Temperatura");
    inputTipo1->addItem("Umidità");
    inputTipo1->addItem("Lampadina");
    inputTipo1->addItem("Pannelli fotovoltaici");
    inputTipo1->addItem("Elettrodomestico");
    inputTipo1->setDisabled(true);
    inputTipo1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    centerLayout->addWidget(inputTipo1);

    // Nome sensore (generale)
    labelNome = new QLabel("Nome sensore:");
    labelNome->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelNome);
    inputNome = new QLineEdit(this);
    inputNome->setPlaceholderText("Es: luce tavolo");
    inputNome->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    centerLayout->addWidget(inputNome);

    // Gruppo sensore (generale)
    labelGruppo = new QLabel("Gruppo sensore:");
    labelGruppo->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelGruppo);
    inputGruppo = new QLineEdit();
    inputGruppo->setPlaceholderText("Es: cucina");
    inputGruppo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    centerLayout->addWidget(inputGruppo);

    // Tipo elettrodomestico (SensoreElettrodomestico)
    labelTipo2 = new QLabel("Tipo elettrodomestico:");
    labelTipo2->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelTipo2);
    labelTipo2->setVisible(false);
    inputTipo2 = new QComboBox();
    inputTipo2->addItem("TV");
    inputTipo2->addItem("Frigorifero");
    inputTipo2->addItem("Lavatrice");
    inputTipo2->addItem("Forno");
    inputTipo2->setVisible(false);
    inputTipo2->setDisabled(true);
    inputTipo2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    centerLayout->addWidget(inputTipo2);

    // Classe energetica (SensoreElettrodomestico)
    labelClasseEnergetica = new QLabel("Classe energetica:");
    labelClasseEnergetica->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelClasseEnergetica);
    labelClasseEnergetica->setVisible(false);
    inputClasseEnergetica = new QComboBox();
    inputClasseEnergetica->addItem("A");
    inputClasseEnergetica->addItem("B");
    inputClasseEnergetica->addItem("C");
    inputClasseEnergetica->addItem("D");
    inputClasseEnergetica->addItem("E");
    inputClasseEnergetica->setVisible(false);
    inputClasseEnergetica->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    centerLayout->addWidget(inputClasseEnergetica);

    // Target temperatura (SensoreTemperatura)
    labelTemperaturaTarget = new QLabel("Temperatura target:");
    labelTemperaturaTarget->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelTemperaturaTarget);
    labelTemperaturaTarget->setVisible(false);
    inputTemperaturaTarget = new QDoubleSpinBox();
    inputTemperaturaTarget->setRange(10.0, 40.0);
    inputTemperaturaTarget->setDecimals(1);
    inputTemperaturaTarget->setSuffix(" °");
    inputTemperaturaTarget->setVisible(false);
    centerLayout->addWidget(inputTemperaturaTarget);

    // Target umidità (SensoreUmidita)
    labelUmiditaTarget = new QLabel("Umidità target:");
    labelUmiditaTarget->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelUmiditaTarget);
    labelUmiditaTarget->setVisible(false);
    inputUmiditaTarget = new QDoubleSpinBox();
    inputUmiditaTarget->setRange(0.0, 100.0);
    inputUmiditaTarget->setDecimals(1);
    inputUmiditaTarget->setSuffix(" %");
    inputUmiditaTarget->setVisible(false);
    centerLayout->addWidget(inputUmiditaTarget);

    // Potenza massima (SensoreElettrodomestico, SensoreLampadina, SensorePannelli)
    labelPotenzaMassima = new QLabel("Potenza massima:");
    labelPotenzaMassima->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelPotenzaMassima);
    labelPotenzaMassima->setVisible(false);
    inputPotenzaMassima = new QSpinBox();
    inputPotenzaMassima->setRange(1, 10000);
    inputPotenzaMassima->setSuffix(" W");
    inputPotenzaMassima->setVisible(false);
    centerLayout->addWidget(inputPotenzaMassima);

    // Dimmerabile (SensoreLampadina)
    labelDimmerabile = new QLabel("Dimmerabile:");
    labelDimmerabile->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelDimmerabile);
    labelDimmerabile->setVisible(false);
    inputDimmerabile = new QCheckBox();
    inputDimmerabile->setVisible(false);
    QHBoxLayout *checkBoxLayout = new QHBoxLayout();
    checkBoxLayout->addStretch();
    checkBoxLayout->addWidget(inputDimmerabile);
    checkBoxLayout->addStretch();
    centerLayout->addLayout(checkBoxLayout);

    // Numero pannelli (SensorePannelli)
    labelNumeroPannelli = new QLabel("Numero pannelli:");
    labelNumeroPannelli->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelNumeroPannelli);
    labelNumeroPannelli->setVisible(false);
    inputNumeroPannelli = new QSpinBox();
    inputNumeroPannelli->setRange(1, 100);
    inputNumeroPannelli->setVisible(false);
    centerLayout->addWidget(inputNumeroPannelli);

    // Potenza pannello (SensorePannelli)
    labelPotenzaPannello = new QLabel("Potenza singolo pannello:");
    labelPotenzaPannello->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelPotenzaPannello);
    labelPotenzaPannello->setVisible(false);
    inputPotenzaPannello = new QSpinBox();
    inputPotenzaPannello->setRange(1, 1000);
    inputPotenzaPannello->setSuffix(" W");
    inputPotenzaPannello->setVisible(false);
    centerLayout->addWidget(inputPotenzaPannello);

    // Button aggiungi sensore
    QPushButton *modificaSensore = new QPushButton("Salva Modifiche");
    centerLayout->addWidget(modificaSensore);
    modificaSensore->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Stile
    QString style = "QComboBox, QLineEdit, QDoubleSpinBox, QSpinBox {"
                    "    background-color: white;"
                    "    color: black;"
                    "    font-size: 24px;"
                    "    border-radius: 10px;"
                    "    margin: 10px;"
                    "    padding: 5px;"
                    "}"
                    "QCheckBox {"
                    "    width: 30px;"
                    "    height: 30px;"
                    "    color: white;"
                    "    font-size: 24px;"
                    "}"
                    "QLabel {"
                    "    color: white;"
                    "    font-size: 24px;"
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
                    "}";

    centerWidget->setStyleSheet(style);

    connect(buttonIndietro, &QPushButton::clicked, this, &SchermataModificaSensore::chiudiSchermataModificaSensore);

    connect(modificaSensore, &QPushButton::clicked, this, [=]() {
        // Verifica che i campi non siano vuoti
        if (inputNome->text().isEmpty() || inputGruppo->text().isEmpty() ||
            (inputTipo1->currentText() == "Elettrodomestico" && (inputTipo2->currentText().isEmpty() || inputClasseEnergetica->currentText().isEmpty() || inputPotenzaMassima->value() == 0)) ||
            (inputTipo1->currentText() == "Temperatura" && inputTemperaturaTarget->value() == 0) ||
            (inputTipo1->currentText() == "Umidità" && inputUmiditaTarget->value() == 0) ||
            (inputTipo1->currentText() == "Lampadina" && inputPotenzaMassima->value() == 0) ||
            (inputTipo1->currentText() == "Pannelli fotovoltaici" && (inputNumeroPannelli->value() == 0 || inputPotenzaPannello->value() == 0))) {

            QMessageBox msgBox;
            msgBox.setWindowTitle("Errore");
            msgBox.setText("Per favore, riempi tutti i campi richiesti.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
            return;
        }

        sensore->setNome(inputNome->text());
        sensore->setGruppo(inputGruppo->text());
        sensore->rimuoviDati();

        if (dynamic_cast<SensoreAria*>(sensore)) {
            SensoreAria* sensorearia = dynamic_cast<SensoreAria*>(sensore);
            emit modificaSensoreSignal(sensorearia);
        } else if (dynamic_cast<SensoreTemperatura*>(sensore)) {
            SensoreTemperatura* sensoretemperatura = dynamic_cast<SensoreTemperatura*>(sensore);
            sensoretemperatura->setValoreTarget(inputTemperaturaTarget->value());
            emit modificaSensoreSignal(sensoretemperatura);
        } else if (dynamic_cast<SensoreUmidita*>(sensore)) {
            SensoreUmidita* sensoreumidita = dynamic_cast<SensoreUmidita*>(sensore);
            sensoreumidita->setValoreTarget(inputUmiditaTarget->value());
            emit modificaSensoreSignal(sensoreumidita);
        } else if (dynamic_cast<SensoreLampadina*>(sensore)) {
            SensoreLampadina* sensorelampadina = dynamic_cast<SensoreLampadina*>(sensore);
            sensorelampadina->setPotenzaMax(inputPotenzaMassima->value());
            sensorelampadina->setDimmer(inputDimmerabile->isChecked());
            emit modificaSensoreSignal(sensorelampadina);
        } else if (dynamic_cast<SensorePannelli*>(sensore)) {
            SensorePannelli* sensorepannelli = dynamic_cast<SensorePannelli*>(sensore);
            sensorepannelli->setNPannelli(inputNumeroPannelli->value());
            sensorepannelli->setPotenzaPannello(inputPotenzaPannello->value());
            sensorepannelli->setPotenzaMax(inputNumeroPannelli->value() * inputPotenzaPannello->value());
            emit modificaSensoreSignal(sensorepannelli);
        } else if (dynamic_cast<SensoreElettrodomestico*>(sensore)) {
            SensoreElettrodomestico* sensoreelettrodomestico = dynamic_cast<SensoreElettrodomestico*>(sensore);
            sensoreelettrodomestico->setClasseEnergetica(inputClasseEnergetica->currentText());
            sensoreelettrodomestico->setPotenzaMax(inputPotenzaMassima->value());
            emit modificaSensoreSignal(sensoreelettrodomestico);
        }
        pulisciInput();
    });
}

void SchermataModificaSensore::setSensore(Sensore* sensore){
    this->sensore = sensore;

    inputNome->setText(sensore->getNome());
    inputGruppo->setText(sensore->getGruppo());

    if (dynamic_cast<SensoreAria*>(sensore)) {
        inputTipo1->setCurrentIndex(0);
    } else if (dynamic_cast<SensoreTemperatura*>(sensore)) {
        SensoreTemperatura* sensoretemperatura = dynamic_cast<SensoreTemperatura*>(sensore);
        inputTipo1->setCurrentIndex(1);
        labelTemperaturaTarget->setVisible(true);
        inputTemperaturaTarget->setVisible(true);
        inputTemperaturaTarget->setValue(sensoretemperatura->getValoreTarget());
    } else if (dynamic_cast<SensoreUmidita*>(sensore)) {
        SensoreUmidita* sensoreumidita = dynamic_cast<SensoreUmidita*>(sensore);
        inputTipo1->setCurrentIndex(2);
        labelUmiditaTarget->setVisible(true);
        inputUmiditaTarget->setVisible(true);
        inputUmiditaTarget->setValue(sensoreumidita->getValoreTarget());
    } else if (dynamic_cast<SensoreLampadina*>(sensore)) {
        SensoreLampadina* sensorelampadina = dynamic_cast<SensoreLampadina*>(sensore);
        inputTipo1->setCurrentIndex(3);
        labelPotenzaMassima->setVisible(true);
        inputPotenzaMassima->setVisible(true);
        inputPotenzaMassima->setValue(sensorelampadina->getPotenzaMax());
        labelDimmerabile->setVisible(true);
        inputDimmerabile->setVisible(true);
        inputDimmerabile->setChecked(sensorelampadina->getDimmer());
    } else if (dynamic_cast<SensorePannelli*>(sensore)) {
        SensorePannelli* sensorepannelli = dynamic_cast<SensorePannelli*>(sensore);
        inputTipo1->setCurrentIndex(4);
        labelNumeroPannelli->setVisible(true);
        inputNumeroPannelli->setVisible(true);
        inputNumeroPannelli->setValue(sensorepannelli->getNPannelli());
        inputTipo1->setCurrentIndex(3);
        labelPotenzaPannello->setVisible(true);
        inputPotenzaPannello->setVisible(true);
        inputPotenzaPannello->setValue(sensorepannelli->getPotenzaPannello());
    } else if (dynamic_cast<SensoreElettrodomestico*>(sensore)) {
        SensoreElettrodomestico* sensoreelettrodomestico = dynamic_cast<SensoreElettrodomestico*>(sensore);
        inputTipo1->setCurrentIndex(5);
        labelTipo2->setVisible(true);
        inputTipo2->setVisible(true);
        int index = inputTipo2->findText(sensoreelettrodomestico->getTipoElettrodomestico(), Qt::MatchFixedString);
        inputTipo2->setCurrentIndex(index);
        labelClasseEnergetica->setVisible(true);
        inputClasseEnergetica->setVisible(true);
        inputClasseEnergetica->setCurrentIndex(0);
        labelPotenzaMassima->setVisible(true);
        inputPotenzaMassima->setVisible(true);
        inputPotenzaMassima->setValue(sensoreelettrodomestico->getPotenzaMax());
    }
}

void SchermataModificaSensore::pulisciInput(){
    //tutti i label vengono resi invisibili
    labelTipo2->setVisible(false);
    labelClasseEnergetica->setVisible(false);
    labelTemperaturaTarget->setVisible(false);
    labelUmiditaTarget->setVisible(false);
    labelPotenzaMassima->setVisible(false);
    labelDimmerabile->setVisible(false);
    labelNumeroPannelli->setVisible(false);
    labelPotenzaPannello->setVisible(false);

    //tutti gli input vengono puliti
    inputTipo1->setCurrentIndex(0);
    inputNome->clear();
    inputGruppo->clear();
    inputTipo2->setCurrentIndex(0);
    inputClasseEnergetica->setCurrentIndex(0);
    inputTemperaturaTarget->setValue(0.0);
    inputUmiditaTarget->setValue(0.0);
    inputPotenzaMassima->setValue(0);
    inputDimmerabile->setChecked(false);
    inputNumeroPannelli->setValue(0);
    inputPotenzaPannello->setValue(0);

    //tutti gli input vengono resi invisibili
    inputTipo2->setVisible(false);
    inputClasseEnergetica->setVisible(false);
    inputTemperaturaTarget->setVisible(false);
    inputUmiditaTarget->setVisible(false);
    inputPotenzaMassima->setVisible(false);
    inputDimmerabile->setVisible(false);
    inputNumeroPannelli->setVisible(false);
    inputPotenzaPannello->setVisible(false);
}

void SchermataModificaSensore::chiudiSchermataModificaSensore() {
    pulisciInput();
    emit chiudiSchermataModificaSensoreSignal(sensore);
}


/*QWidget* SchermataNuovoSensore::createWidget(QWidget *parent) {
    return new SchermataNuovoSensore(parent);
}

void SchermataNuovoSensore::chiudiSchermataNuovoSensore() {
    emit chiudiSchermataNuovoSensoreSignal();
}*/
