// Includi gli header di Windows e Qt
#include <windows.h>
#undef byte // Rimuove la definizione di `byte` dopo aver incluso windows.h
#include "../headers/schermatanuovosensore.h"
#include "../headers/sensorearia.h"
#include "../headers/sensoreelettricita.h"
#include "../headers/sensoreelettrodomestico.h"
#include "../headers/sensorelampadina.h"
#include "../headers/sensorepannelli.h"
#include "../headers/sensoretemperatura.h"
#include "../headers/sensoreumidita.h"

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

    // Tipo sensore (generale)
    QLabel *labelTipo1 = new QLabel("Tipo sensore:");
    labelTipo1->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelTipo1);
    QComboBox *inputTipo1 = new QComboBox(this);
    inputTipo1->addItem("Qualità aria");
    inputTipo1->addItem("Temperatura");
    inputTipo1->addItem("Umidità");
    inputTipo1->addItem("Lampadina");
    inputTipo1->addItem("Pannelli fotovoltaici");
    inputTipo1->addItem("Elettrodomestico");
    inputTipo1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    centerLayout->addWidget(inputTipo1);

    //Nome sensore (generale)
    QLabel *labelNome = new QLabel("Nome sensore:");
    labelNome->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelNome);
    QLineEdit *inputNome = new QLineEdit(this);
    inputNome->setPlaceholderText("Es: luce tavolo");
    inputNome->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    centerLayout->addWidget(inputNome);

    //Gruppo sensore (generale)
    QLabel *labelGruppo = new QLabel("Gruppo sensore:");
    labelGruppo->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelGruppo);
    QLineEdit *inputGruppo = new QLineEdit();
    inputGruppo->setPlaceholderText("Es: cucina");
    inputGruppo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    centerLayout->addWidget(inputGruppo);

    //Tipo elettrodomestico (SensoreElettrodomestico)
    QLabel *labelTipo2 = new QLabel("Tipo elettrodomestico:");
    labelTipo2->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelTipo2);
    labelTipo2->setVisible(false);
    QComboBox *inputTipo2 = new QComboBox();
    inputTipo2->addItem("TV");
    inputTipo2->addItem("Frigorifero");
    inputTipo2->addItem("Lavatrice");
    inputTipo2->addItem("Forno");
    inputTipo2->setVisible(false);
    inputTipo2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    centerLayout->addWidget(inputTipo2);

    //Classe energetica (SensoreElettrodomestico)
    QLabel *labelClasseEnergetica = new QLabel("Classe energetica:");
    labelClasseEnergetica->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelClasseEnergetica);
    labelClasseEnergetica->setVisible(false);
    QComboBox *inputClasseEnergetica = new QComboBox();
    inputClasseEnergetica->addItem("A");
    inputClasseEnergetica->addItem("B");
    inputClasseEnergetica->addItem("C");
    inputClasseEnergetica->addItem("D");
    inputClasseEnergetica->addItem("E");
    inputClasseEnergetica->setVisible(false);
    inputClasseEnergetica->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    centerLayout->addWidget(inputClasseEnergetica);

    //Target temperatura (SensoreTemperatura)
    QLabel *labelTemperaturaTarget = new QLabel("Temperatura target:");
    labelTemperaturaTarget->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelTemperaturaTarget);
    labelTemperaturaTarget->setVisible(false);
    QDoubleSpinBox *inputTemperaturaTarget = new QDoubleSpinBox();
    inputTemperaturaTarget->setRange(10.0, 40.0);
    inputTemperaturaTarget->setDecimals(1);
    inputTemperaturaTarget->setSuffix(" °");
    inputTemperaturaTarget->setVisible(false);
    centerLayout->addWidget(inputTemperaturaTarget);

    //Target umidità (SensoreUmidita)
    QLabel *labelUmiditaTarget = new QLabel("Umidità target:");
    labelUmiditaTarget->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelUmiditaTarget);
    labelUmiditaTarget->setVisible(false);
    QDoubleSpinBox *inputUmiditaTarget = new QDoubleSpinBox();
    inputUmiditaTarget->setRange(0.0, 100.0);
    inputUmiditaTarget->setDecimals(1);
    inputUmiditaTarget->setSuffix(" %");
    inputUmiditaTarget->setVisible(false);
    centerLayout->addWidget(inputUmiditaTarget);

    //Potenza massima (SensoreElettrecita, SensoreElettrodomestico, SensoreLampadina, SensorePannelli)
    QLabel *labelPotenzaMassima = new QLabel("Potenza massima:");
    labelPotenzaMassima->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelPotenzaMassima);
    labelPotenzaMassima->setVisible(false);
    QSpinBox *inputPotenzaMassima = new QSpinBox();
    inputPotenzaMassima->setRange(1, 10000);
    inputPotenzaMassima->setSuffix(" W");
    inputPotenzaMassima->setVisible(false);
    centerLayout->addWidget(inputPotenzaMassima);

    // Dimmerabile (SensoreLampadina)
    QLabel *labelDimmerabile = new QLabel("Dimmerabile:");
    labelDimmerabile->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelDimmerabile);
    labelDimmerabile->setVisible(false);
    QCheckBox *inputDimmerabile = new QCheckBox();
    inputDimmerabile->setVisible(false);
    inputDimmerabile->setFixedSize(50, 50); // Imposta la dimensione desiderata
    QHBoxLayout *checkBoxLayout = new QHBoxLayout();
    checkBoxLayout->addStretch();
    checkBoxLayout->addWidget(inputDimmerabile);
    checkBoxLayout->addStretch();
    centerLayout->addLayout(checkBoxLayout);

    //Numero pannelli (SensorePannelli)
    QLabel *labelNumeroPannelli = new QLabel("Numero pannelli:");
    labelNumeroPannelli->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelNumeroPannelli);
    labelNumeroPannelli->setVisible(false);
    QSpinBox *inputNumeroPannelli = new QSpinBox();
    inputNumeroPannelli->setRange(1, 100);
    inputNumeroPannelli->setVisible(false);
    centerLayout->addWidget(inputNumeroPannelli);

    //Potenza pannello (SensorePannelli)
    QLabel *labelPotenzaPannello = new QLabel("Potenza singolo pannello:");
    labelPotenzaPannello->setAlignment(Qt::AlignCenter);
    centerLayout->addWidget(labelPotenzaPannello);
    labelPotenzaPannello->setVisible(false);
    QSpinBox *inputPotenzaPannello = new QSpinBox();
    inputPotenzaPannello->setRange(1, 1000);
    inputPotenzaMassima->setSuffix(" W");
    inputPotenzaPannello->setVisible(false);
    centerLayout->addWidget(inputPotenzaPannello);

    //Button aggiungi sensore
    QPushButton *nuovoSensore = new QPushButton("Aggiungi Sensore");
    centerLayout->addWidget(nuovoSensore);
    nuovoSensore->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);


    connect(inputTipo1, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](){
        if(inputTipo1->currentText() == "Elettrodomestico"){
            inputTipo2->setVisible(true);
            labelTipo2->setVisible(true);
            labelPotenzaMassima->setVisible(true);
            inputPotenzaMassima->setVisible(true);
            labelClasseEnergetica->setVisible(true);
            inputClasseEnergetica->setVisible(true);
        }else {
            inputTipo2->setVisible(false);
            labelTipo2->setVisible(false);
            labelPotenzaMassima->setVisible(false);
            inputPotenzaMassima->setVisible(false);
            labelClasseEnergetica->setVisible(false);
            inputClasseEnergetica->setVisible(false);
        }
        if(inputTipo1->currentText() == "Temperatura"){
            labelTemperaturaTarget->setVisible(true);
            inputTemperaturaTarget->setVisible(true);
        }else{
            labelTemperaturaTarget->setVisible(false);
            inputTemperaturaTarget->setVisible(false);
        }
        if(inputTipo1->currentText() == "Umidità"){
            labelUmiditaTarget->setVisible(true);
            inputUmiditaTarget->setVisible(true);
        }else{
            labelUmiditaTarget->setVisible(false);
            inputUmiditaTarget->setVisible(false);
        }
        if(inputTipo1->currentText() == "Lampadina"){
            labelPotenzaMassima->setVisible(true);
            inputPotenzaMassima->setVisible(true);
            labelDimmerabile->setVisible(true);
            inputDimmerabile->setVisible(true);
        }else{
            labelPotenzaMassima->setVisible(false);
            inputPotenzaMassima->setVisible(false);
            labelDimmerabile->setVisible(false);
            inputDimmerabile->setVisible(false);
        }
        if(inputTipo1->currentText() == "Pannelli fotovoltaici"){
            labelNumeroPannelli->setVisible(true);
            inputNumeroPannelli->setVisible(true);
            labelPotenzaPannello->setVisible(true);
            labelPotenzaPannello->setVisible(true);
        }else {
            labelNumeroPannelli->setVisible(false);
            labelNumeroPannelli->setVisible(false);
            labelPotenzaPannello->setVisible(false);
            labelPotenzaPannello->setVisible(false);
        }
    });


    //Stile
    QString style = "QComboBox, QLineEdit, QDoubleSpinBox, QSpinBox, QPushButton {"
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
                    "}";


    centerWidget->setStyleSheet(style);

    connect(nuovoSensore, &QPushButton::clicked, this, [=]() {
        if(inputTipo1->currentText() == "Qualità aria"){
            SensoreAria *sensorearia = new SensoreAria(0, inputNome->text(), "IQA", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/aria.png", inputGruppo->text(), 180, 170);
            emit nuovoSensoreCreato(sensorearia);
        }
        if(inputTipo1->currentText() == "Elettrodomestico"){
            QString icona = "";
            if(inputTipo2->currentText() == "TV"){
                icona = "C:/Users/samsung/Desktop/PAO grafica/untitled/img/tv.png";
            }else if(inputTipo2->currentText() == "Frigorifero"){
                icona = "C:/Users/samsung/Desktop/PAO grafica/untitled/img/frigo.png";
            }else if(inputTipo2->currentText() == "Lavatrice"){
                icona = "C:/Users/samsung/Desktop/PAO grafica/untitled/img/lavatrice.png";
            }else if(inputTipo2->currentText() == "Forno"){
                icona = "C:/Users/samsung/Desktop/PAO grafica/untitled/img/forno.png";
            }
            SensoreElettrodomestico *sensoreelettrodomestico = new SensoreElettrodomestico(0, inputNome->text(), "W", icona, inputGruppo->text(), inputClasseEnergetica->currentText(), inputPotenzaMassima->value(), 0);
            emit nuovoSensoreCreato(sensoreelettrodomestico);
        }
        if(inputTipo1->currentText() == "Temperatura"){
            SensoreTemperatura *sensoretemperatura = new SensoreTemperatura(0, inputNome->text(), "°", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/termometro.png", inputGruppo->text(), inputTemperaturaTarget->value(), 10, 40, 20);
            emit nuovoSensoreCreato(sensoretemperatura);
        }
        if(inputTipo1->currentText() == "Umidità"){
            SensoreUmidita *sensoreumidita = new SensoreUmidita(0, inputNome->text(), "%", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/goccia.png", inputGruppo->text(), inputUmiditaTarget->value(), 10);
            emit nuovoSensoreCreato(sensoreumidita);
        }
        if(inputTipo1->currentText() == "Pannelli fotovoltaici"){
            SensorePannelli *sensorepannelli = new SensorePannelli(0, inputNome->text(), "W", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/pannelli.png", inputGruppo->text(), inputNumeroPannelli->value(), inputPotenzaPannello->value(), inputNumeroPannelli->value()*inputPotenzaPannello->value(), 3400);
            emit nuovoSensoreCreato(sensorepannelli);
        }
        if(inputTipo1->currentText() == "Lampadina"){
            SensoreLampadina *sensorelampadina = new SensoreLampadina(0, inputNome->text(), "W", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/lampadina.png", inputGruppo->text(), inputDimmerabile->isChecked(), inputPotenzaMassima->value(), 10);
            emit nuovoSensoreCreato(sensorelampadina);
        }
    });
}

QWidget* SchermataNuovoSensore::createWidget(QWidget *parent) {
    return new SchermataNuovoSensore(parent);
}
