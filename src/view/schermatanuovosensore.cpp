#ifdef _WIN32
#define NOMINMAX // Avoid conflicts with min/max macros
#include <windows.h>
#undef byte // Undefine byte to avoid conflicts with std::byte
#include <cstddef> // For std::byte
#endif

#include "schermatanuovosensore.h"
#include "../model/sensorearia.h"
#include "../model/sensoreelettrodomestico.h"
#include "../model/sensorelampadina.h"
#include "../model/sensorepannelli.h"
#include "../model/sensoretemperatura.h"
#include "../model/sensoreumidita.h"
#include <iostream>
#include <QMessageBox>

SchermataNuovoSensore::SchermataNuovoSensore(QWidget *parent)
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
    QPushButton *nuovoSensore = new QPushButton("Aggiungi Sensore");
    centerLayout->addWidget(nuovoSensore);
    nuovoSensore->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    centerLayout->addStretch();

    // Ad ogni cambiamento di tipo di sensore aggiorna la visibilità dei campi
    connect(inputTipo1, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](){
        std::cout << "Tipo selezionato: " << inputTipo1->currentText().toStdString() << std::endl;

        if(inputTipo1->currentText() == "Elettrodomestico"){
            std::cout << "Rendere visibile per Elettrodomestico" << std::endl;
            inputTipo2->setVisible(true);
            labelTipo2->setVisible(true);
            labelPotenzaMassima->setVisible(true);
            inputPotenzaMassima->setVisible(true);
            labelClasseEnergetica->setVisible(true);
            inputClasseEnergetica->setVisible(true);

            labelTemperaturaTarget->setVisible(false);
            inputTemperaturaTarget->setVisible(false);
            labelUmiditaTarget->setVisible(false);
            inputUmiditaTarget->setVisible(false);
            labelDimmerabile->setVisible(false);
            inputDimmerabile->setVisible(false);
            labelNumeroPannelli->setVisible(false);
            inputNumeroPannelli->setVisible(false);
            labelPotenzaPannello->setVisible(false);
            inputPotenzaPannello->setVisible(false);
        }
        else if(inputTipo1->currentText() == "Temperatura"){
            std::cout << "Rendere visibile per Temperatura" << std::endl;
            labelTemperaturaTarget->setVisible(true);
            inputTemperaturaTarget->setVisible(true);

            inputTipo2->setVisible(false);
            labelTipo2->setVisible(false);
            labelPotenzaMassima->setVisible(false);
            inputPotenzaMassima->setVisible(false);
            labelClasseEnergetica->setVisible(false);
            inputClasseEnergetica->setVisible(false);
            labelUmiditaTarget->setVisible(false);
            inputUmiditaTarget->setVisible(false);
            labelDimmerabile->setVisible(false);
            inputDimmerabile->setVisible(false);
            labelNumeroPannelli->setVisible(false);
            inputNumeroPannelli->setVisible(false);
            labelPotenzaPannello->setVisible(false);
            inputPotenzaPannello->setVisible(false);
        }
        else if(inputTipo1->currentText() == "Umidità"){
            std::cout << "Rendere visibile per Umidità" << std::endl;
            labelUmiditaTarget->setVisible(true);
            inputUmiditaTarget->setVisible(true);

            inputTipo2->setVisible(false);
            labelTipo2->setVisible(false);
            labelPotenzaMassima->setVisible(false);
            inputPotenzaMassima->setVisible(false);
            labelClasseEnergetica->setVisible(false);
            inputClasseEnergetica->setVisible(false);
            labelTemperaturaTarget->setVisible(false);
            inputTemperaturaTarget->setVisible(false);
            labelDimmerabile->setVisible(false);
            inputDimmerabile->setVisible(false);
            labelNumeroPannelli->setVisible(false);
            inputNumeroPannelli->setVisible(false);
            labelPotenzaPannello->setVisible(false);
            inputPotenzaPannello->setVisible(false);
        }
        else if(inputTipo1->currentText() == "Lampadina"){
            std::cout << "Rendere visibile per Lampadina" << std::endl;
            labelPotenzaMassima->setVisible(true);
            inputPotenzaMassima->setVisible(true);
            labelDimmerabile->setVisible(true);
            inputDimmerabile->setVisible(true);

            inputTipo2->setVisible(false);
            labelTipo2->setVisible(false);
            labelClasseEnergetica->setVisible(false);
            inputClasseEnergetica->setVisible(false);
            labelTemperaturaTarget->setVisible(false);
            inputTemperaturaTarget->setVisible(false);
            labelUmiditaTarget->setVisible(false);
            inputUmiditaTarget->setVisible(false);
            labelNumeroPannelli->setVisible(false);
            inputNumeroPannelli->setVisible(false);
            labelPotenzaPannello->setVisible(false);
            inputPotenzaPannello->setVisible(false);
        }
        else if(inputTipo1->currentText() == "Pannelli fotovoltaici"){
            std::cout << "Rendere visibile per Pannelli fotovoltaici" << std::endl;
            labelNumeroPannelli->setVisible(true);
            inputNumeroPannelli->setVisible(true);
            labelPotenzaPannello->setVisible(true);
            inputPotenzaPannello->setVisible(true);

            inputTipo2->setVisible(false);
            labelTipo2->setVisible(false);
            labelPotenzaMassima->setVisible(false);
            inputPotenzaMassima->setVisible(false);
            labelClasseEnergetica->setVisible(false);
            inputClasseEnergetica->setVisible(false);
            labelTemperaturaTarget->setVisible(false);
            inputTemperaturaTarget->setVisible(false);
            labelUmiditaTarget->setVisible(false);
            inputUmiditaTarget->setVisible(false);
            labelDimmerabile->setVisible(false);
            inputDimmerabile->setVisible(false);
        }
        else {
            std::cout << "Nascondere tutti gli altri campi" << std::endl;
            inputTipo2->setVisible(false);
            labelTipo2->setVisible(false);
            labelPotenzaMassima->setVisible(false);
            inputPotenzaMassima->setVisible(false);
            labelClasseEnergetica->setVisible(false);
            inputClasseEnergetica->setVisible(false);
            labelTemperaturaTarget->setVisible(false);
            inputTemperaturaTarget->setVisible(false);
            labelUmiditaTarget->setVisible(false);
            inputUmiditaTarget->setVisible(false);
            labelDimmerabile->setVisible(false);
            inputDimmerabile->setVisible(false);
            labelNumeroPannelli->setVisible(false);
            inputNumeroPannelli->setVisible(false);
            labelPotenzaPannello->setVisible(false);
            inputPotenzaPannello->setVisible(false);
        }
    });

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

    connect(buttonIndietro, &QPushButton::clicked, this, &SchermataNuovoSensore::chiudiSchermataNuovoSensore);

    connect(nuovoSensore, &QPushButton::clicked, this, [=]() {
        // Verifica che i campi non siano vuoti
        if (inputNome->text().isEmpty() || inputGruppo->text().isEmpty() ||
            (inputTipo1->currentText() == "Elettrodomestico" && (inputTipo2->currentText().isEmpty() || inputClasseEnergetica->currentText().isEmpty() || inputPotenzaMassima->value() <= 0)) ||
            (inputTipo1->currentText() == "Temperatura" && inputTemperaturaTarget->value() <= 10) ||
            (inputTipo1->currentText() == "Umidità" && inputUmiditaTarget->value() <= 0) ||
            (inputTipo1->currentText() == "Lampadina" && inputPotenzaMassima->value() <= 0) ||
            (inputTipo1->currentText() == "Pannelli fotovoltaici" && (inputNumeroPannelli->value() <= 0 || inputPotenzaPannello->value() <= 0))) {

            QMessageBox msgBox;
            msgBox.setWindowTitle("Errore");
            msgBox.setText("Per favore, riempi tutti i campi richiesti.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
            return;
        }
        std::random_device dev;
        std::mt19937 rng(dev());

        if(inputTipo1->currentText() == "Qualità aria"){
            std::uniform_int_distribution<std::mt19937::result_type> dist(30,180);
            SensoreAria *sensorearia = new SensoreAria(0, inputNome->text(), "IQA", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/aria.png", inputGruppo->text(), 180, dist(rng));
            emit nuovoSensoreCreato(sensorearia);
        }
        if(inputTipo1->currentText() == "Elettrodomestico"){
            QString icona = "";
            if(inputTipo2->currentText() == "TV"){
                icona = "C:/Users/samsung/Desktop/PAO grafica/untitled/img/tv.png";
            } else if(inputTipo2->currentText() == "Frigorifero"){
                icona = "C:/Users/samsung/Desktop/PAO grafica/untitled/img/frigo.png";
            } else if(inputTipo2->currentText() == "Lavatrice"){
                icona = "C:/Users/samsung/Desktop/PAO grafica/untitled/img/lavatrice.png";
            } else if(inputTipo2->currentText() == "Forno"){
                icona = "C:/Users/samsung/Desktop/PAO grafica/untitled/img/forno.png";
            }
            SensoreElettrodomestico *sensoreelettrodomestico = new SensoreElettrodomestico(0, inputNome->text(), "W", icona, inputGruppo->text(), inputClasseEnergetica->currentText(), inputPotenzaMassima->value(), 100, inputTipo2->currentText());
            emit nuovoSensoreCreato(sensoreelettrodomestico);
        }
        if(inputTipo1->currentText() == "Temperatura"){
            std::uniform_int_distribution<std::mt19937::result_type> dist(10,40);
            SensoreTemperatura *sensoretemperatura = new SensoreTemperatura(0, inputNome->text(), "°", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/termometro.png", inputGruppo->text(), inputTemperaturaTarget->value(), 10, 40, dist(rng));
            emit nuovoSensoreCreato(sensoretemperatura);
        }
        if(inputTipo1->currentText() == "Umidità"){
            std::uniform_int_distribution<std::mt19937::result_type> dist(inputUmiditaTarget->value()-10, inputUmiditaTarget->value()+10);
            SensoreUmidita *sensoreumidita = new SensoreUmidita(0, inputNome->text(), "%", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/goccia.png", inputGruppo->text(), inputUmiditaTarget->value(), dist(rng));
            emit nuovoSensoreCreato(sensoreumidita);
        }
        if(inputTipo1->currentText() == "Pannelli fotovoltaici"){
            std::uniform_int_distribution<std::mt19937::result_type> dist(0,inputNumeroPannelli->value()*inputPotenzaPannello->value());
            SensorePannelli *sensorepannelli = new SensorePannelli(0, inputNome->text(), "W", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/pannello.png", inputGruppo->text(), inputNumeroPannelli->value(), inputPotenzaPannello->value(), inputNumeroPannelli->value()*inputPotenzaPannello->value(), dist(rng));
            emit nuovoSensoreCreato(sensorepannelli);
        }
        if(inputTipo1->currentText() == "Lampadina"){
            //default lampadina potenza massima, altrimenti dovrei controllare se dimmerabile o meno, visto che è una simulazione setto io  al max
            SensoreLampadina *sensorelampadina = new SensoreLampadina(0, inputNome->text(), "W", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/lampadina.png", inputGruppo->text(), inputDimmerabile->isChecked(), inputPotenzaMassima->value(), inputPotenzaMassima->value());
            emit nuovoSensoreCreato(sensorelampadina);
        }
        pulisciInput();
    });
}

void SchermataNuovoSensore::pulisciInput(){
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

QWidget* SchermataNuovoSensore::creaWidget(QWidget *parent) {
    return new SchermataNuovoSensore(parent);
}

void SchermataNuovoSensore::chiudiSchermataNuovoSensore() {
    pulisciInput();
    emit chiudiSchermataNuovoSensoreSignal();
}
