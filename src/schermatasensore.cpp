#include "../headers/schermatasensore.h"

SchermataSensore::SchermataSensore(QWidget *parent)
    : QWidget(parent){

    mainLayout = new QHBoxLayout;
    setLayout(mainLayout);

    QPushButton *nuovosensore = new QPushButton("Indietro");
    connect(nuovosensore, &QPushButton::clicked, this, &SchermataSensore::chiudiSchermataSensore);
    mainLayout->addWidget(nuovosensore);

    QWidget *widgetIconaSensore = new QWidget;
    QVBoxLayout *layoutIconaSensore = new QVBoxLayout(widgetIconaSensore);
    widgetIconaSensore->setLayout(layoutIconaSensore);

    QWidget *widgetInfoSensore = new QWidget;
    QVBoxLayout *layoutInfoSensore = new QVBoxLayout(widgetInfoSensore);
    widgetInfoSensore->setLayout(layoutInfoSensore);

    mainLayout->addWidget(widgetIconaSensore);
    mainLayout->addWidget(widgetInfoSensore);

    int idSensore = 0;
    QString nomeSensore = "";
    QString gruppoSensore = "";
    QString iconaSensore = "";
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

    layoutIconaSensore->addWidget(labelIcona, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelId, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelNome, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelGruppo, Qt::AlignTop | Qt::AlignLeft);
    layoutInfoSensore->addWidget(labelValore, Qt::AlignTop | Qt::AlignLeft);

}

void SchermataSensore::setSensore(Sensore *sensore) {
    labelId->setText("ID: "+QString::number(sensore->getId()));
    labelNome->setText("Nome Sensore: " + sensore->getNome());
    labelGruppo->setText("GRUPPO: "+sensore->getGruppo());
    labelValore->setText("Valore Sensore: " + QString::number(sensore->getValore()) + " " + sensore->getUnitaMisura());
}

void SchermataSensore::chiudiSchermataSensore(){
    emit chiudiSchermataSensoreSignal();
}
