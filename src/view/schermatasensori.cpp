#include "../view/schermatasensori.h"
#include "../view/widgetsensore.h"
#include <iostream>


SchermataSensori::SchermataSensori(const std::vector<Sensore*>& sensori, QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    // Layout superiore
    QHBoxLayout *searchLayout = new QHBoxLayout;
    QLabel *labelRicerca = new QLabel("Cerca:");
    labelRicerca->setAlignment(Qt::AlignCenter);
    searchLayout->addWidget(labelRicerca, 0);

    QLineEdit *inputRicerca = new QLineEdit(this);
    inputRicerca->setPlaceholderText("");
    searchLayout->addWidget(inputRicerca, 0);

    connect(inputRicerca, &QLineEdit::textChanged, this, &SchermataSensori::ricerca);

    // Aggiungi il layout di ricerca al layout principale
    mainLayout->addLayout(searchLayout, 0);

    // Layout per i sensori
    sensorLayout = new QGridLayout;
    mainLayout->addLayout(sensorLayout);
    mainLayout->addStretch();

    // Stile
    QString style = "QLineEdit{"
                    "    background-color: white;"
                    "    color: black;"
                    "    font-size: 24px;"
                    "    border-radius: 10px;"
                    "    margin: 10px;"
                    "    padding: 5px;"
                    "}"
                    "QLabel {"
                    "    color: white;"
                    "    font-size: 24px;"
                    "}";

    this->setStyleSheet(style);

    // Inserisci i sensori nel layout
    inserimentoSensori(sensori);
}

void SchermataSensori::inserimentoSensori(const std::vector<Sensore*>& sensori) {
    if (flgRicerca == 0) {
        this->sensori = sensori;
    } else {
        flgRicerca = 0;
    }
    for (Sensore* sensore : sensori) {
        QString gruppoSensore = sensore->getGruppo();

        // Crea il gruppo del sensore se non esiste
        if (!groupWidgets.contains(gruppoSensore)) {
            int elementi = groupWidgets.count();
            int nrow = elementi / 2;
            int ncol = elementi % 2;

            QGroupBox *groupBox = new QGroupBox(gruppoSensore);
            QGridLayout *groupLayout = new QGridLayout(groupBox);
            groupBox->setLayout(groupLayout);

            QString groupStyle = "QGroupBox { border: 20px solid rgba(255, 255, 255, 0) } QGroupBox::title { font-size: 15px; color: rgb(255, 255, 255); }";
            groupBox->setStyleSheet(groupStyle);

            groupWidgets[gruppoSensore] = groupBox;
            sensorLayout->addWidget(groupBox, nrow, ncol);
        }

        // Crea e definisce il widget del sensore
        WidgetSensore *widgetSensore = new WidgetSensore(sensore);
        //widgetSensore->setFixedSize(150, 150);
        widgetSensore->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // Imposta dimensioni minime e massime per uniformare le dimensioni dei widget
        /*widgetSensore->setMinimumSize(150, 150);
        widgetSensore->setMaximumSize(250, 250);*/

        // Inserisce il sensore all'interno del relativo gruppo di appartenenza
        int numeroElementi = groupWidgets[gruppoSensore]->layout()->count();
        int row = numeroElementi / 2;
        int column = numeroElementi % 2;
        QGridLayout *groupLayout = qobject_cast<QGridLayout*>(groupWidgets[gruppoSensore]->layout());
        if (groupLayout) {
            groupLayout->addWidget(widgetSensore, row, column);
        }
        connect(widgetSensore, &WidgetSensore::selezionatoSignal, this, &SchermataSensori::sensoreSelezionato);
    }
    if(groupWidgets.size()<=1){
        int elementi = groupWidgets.count();
        int nrow = elementi / 2;
        int ncol = elementi % 2;

        QGroupBox *groupBox = new QGroupBox();
        QGridLayout *groupLayout = new QGridLayout(groupBox);
        groupBox->setLayout(groupLayout);

        QString groupStyle = "QGroupBox { border: 20px solid rgba(255, 255, 255, 0) } QGroupBox::title { font-size: 15px; color: rgb(255, 255, 255); }";
        groupBox->setStyleSheet(groupStyle);
        sensorLayout->addWidget(groupBox, nrow, ncol);

        QLabel *space = new QLabel;
        space->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        groupLayout->addWidget(space, 0, 0);

    }
}

void SchermataSensori::pulisciSensori() {
    for (auto& groupBox : groupWidgets) {
        QLayout* layout = groupBox->layout();
        while (QLayoutItem* item = layout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                widget->deleteLater();
            }
            delete item;
        }
    }
    for (auto it = groupWidgets.begin(); it != groupWidgets.end(); ++it) {
        delete it.value(); // Elimina il QGroupBox
    }
    groupWidgets.clear(); // Svuota il QMap
}

void SchermataSensori::sensoreSelezionato(WidgetSensore *widget){
    Sensore *sensore = widget->getSensore();
    QString nome = sensore->getNome();
    std::string nomeStd = nome.toStdString(); // Converti QString in std::string
    std::cout << "Il nome del sensore è: " << nomeStd << std::endl;
    emit sensoreSelezionatoSignal(sensore);
}

void SchermataSensori::ricerca(const QString &value){
    std::vector<Sensore*> sensoriFiltrati;
    std::cout << sensori.size() << std::endl;
    for (Sensore* sensore : sensori) {
        if (sensore) {
            QString gruppo = sensore->getGruppo();
            QString nome = sensore->getNome();

            if (gruppo.contains(value, Qt::CaseInsensitive) || nome.contains(value, Qt::CaseInsensitive)) {
                sensoriFiltrati.push_back(sensore);
            }
        }
    }
    flgRicerca = 1;
    pulisciSensori();
    inserimentoSensori(sensoriFiltrati);
}
