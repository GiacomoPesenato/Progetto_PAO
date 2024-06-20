#include "../headers/schermatanuovosensore.h"
#include <QDebug>

SchermataNuovoSensore::SchermataNuovoSensore(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    // Aggiungi il campo di input per il nome del sensore
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("Nome sensore");
    mainLayout->addWidget(lineEdit);

    // Aggiungi il menu a tendina per il tipo di sensore
    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItem("Sensore qualità aria");
    comboBox->addItem("Sensore temperatura");
    comboBox->addItem("Sensore umidità");
    comboBox->addItem("elettrodomestico");

    // Collega il segnale currentIndexChanged del comboBox alla tua funzione slot
    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){
        if(comboBox->currentText() == "elettrodomestico"){
            secondComboBox->setVisible(true);
        }else {
            secondComboBox->setVisible(false);
        }
        /*if(index == 0) { // Se viene selezionato "elettrodomestico"
            // Mostra la seconda lista per i tipi di elettrodomestico
            secondComboBox->setVisible(true);
        } else {
            // Nascondi la seconda lista per i tipi di elettrodomestico
            secondComboBox->setVisible(false);
        }*/
    });

    mainLayout->addWidget(comboBox);

    // Aggiungi la seconda lista per i tipi di elettrodomestico
    secondComboBox = new QComboBox(this);
    secondComboBox->addItem("Frigorifero");
    secondComboBox->addItem("Lavatrice");
    secondComboBox->addItem("Forno");

    // Nascondi la seconda lista all'inizio
    secondComboBox->setVisible(false);

    mainLayout->addWidget(secondComboBox);

    // Imposta la dimensione fissa del layout
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    // Stile per i campi di input testo
    QString lineEditStyle = "QLineEdit {"
                            "    background-color: white;"
                            "    color: black;"
                            "    font-size: 24px;"
                            "    border-radius: 10px;"
                            "    margin: 10px;"
                            "}";

    // Applica lo stile al campo di input testo
    lineEdit->setStyleSheet(lineEditStyle);

    // Stile per i menu a tendina
    QString comboBoxStyle = "QComboBox {"
                            "    background-color: white;"
                            "    color: black;"
                            "    font-size: 24px;"
                            "    border-radius: 10px;"
                            "    margin: 10px;"
                            "}";

    // Applica lo stile al menu a tendina
    comboBox->setStyleSheet(comboBoxStyle);
    secondComboBox->setStyleSheet(comboBoxStyle);
}

QWidget* SchermataNuovoSensore::createWidget(QWidget *parent) {
    return new SchermataNuovoSensore(parent);
}
