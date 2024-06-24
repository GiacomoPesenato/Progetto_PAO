#include "../view/schermatasensori.h"
#include "../view/widgetsensore.h"
#include <iostream>


SchermataSensori::SchermataSensori(const std::vector<Sensore*>& sensori, QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QGridLayout;
    setLayout(mainLayout);

    //inserisce i sensori nel layout
    insertSensori(sensori);
}

void SchermataSensori::insertSensori(const std::vector<Sensore*>& sensori){
    for (Sensore* sensore : sensori) {
        QString gruppoSensore = sensore->getGruppo();

        //crea il gruppo del sensore se non esiste
        if (!groupWidgets.contains(gruppoSensore)) {
            int elementi = groupWidgets.count();
            int nrow = elementi / 2;
            int ncol = (elementi) % 2;

            QGroupBox *groupBox = new QGroupBox(gruppoSensore);
            QGridLayout *groupLayout = new QGridLayout(groupBox);
            groupBox->setLayout(groupLayout);

            QString groupStyle = "QGroupBox { border: 20px solid rgba(255, 255, 255, 0) } QGroupBox::title { font-size: 15px; color: rgb(255, 255, 255); }";
            groupBox->setStyleSheet(groupStyle);

            groupWidgets[gruppoSensore] = groupBox;
            mainLayout->addWidget(groupBox, nrow, ncol);
        }

        //crea e definisce il widget del sensore
        WidgetSensore *widgetSensore = new WidgetSensore(sensore);
        widgetSensore->setFixedSize(150, 150);

        //inserisce il sensore all'interno del relativo gruppo di appartenenza
        int numeroElementi = groupWidgets[gruppoSensore]->layout()->count();
        int row = numeroElementi/2;
        int column = numeroElementi%2;
        QGridLayout *groupLayout = qobject_cast<QGridLayout*>(groupWidgets[gruppoSensore]->layout());
        if (groupLayout) {
            groupLayout->addWidget(widgetSensore, row, column, Qt::AlignTop | Qt::AlignLeft);
        }

        connect(widgetSensore, &WidgetSensore::selected, this, &SchermataSensori::handleWidgetSensoreClicked);
    }
}

void SchermataSensori::clearSensori() {
    for (auto& groupBox : groupWidgets) {
        QLayout* layout = groupBox->layout();
        while (QLayoutItem* item = layout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                widget->deleteLater();
            }
            delete item;
        }
    }
}

void SchermataSensori::handleWidgetSensoreClicked(WidgetSensore *widget){
    Sensore *sensore = widget->getSensore();
    QString nome = sensore->getNome();
    std::string nomeStd = nome.toStdString(); // Converti QString in std::string
    std::cout << "Il nome del sensore è: " << nomeStd << std::endl;
    emit widgetSensoreClicked(sensore);
}
