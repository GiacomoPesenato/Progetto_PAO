#include "widgetsensore.h"
#include "../model/sensore.h"

WidgetSensore::WidgetSensore(Sensore *sensore, QWidget *parent)
    : QWidget(parent), sensore(sensore)
{
    QWidget *mainWidget = new QWidget();
    QString nomeSensore = sensore->getNome();
    QString iconaSensore = sensore->getIcona();
    QString unitaMisuraSensore = sensore->getUnitaMisura();
    double valoreSensore = sensore->getValore();

    //etichetta nome
    QLabel *labelNome = new QLabel;
    labelNome->setText(nomeSensore);
    labelNome->setStyleSheet("color: black; font-size: 16px;");

    //etichetta valore (valore + unità di misura)
    QLabel *labelValore = new QLabel(QString::number(valoreSensore)+unitaMisuraSensore);
    labelValore->setStyleSheet("color: black; font-size: 16px;");

    //etichetta icona sensore
    QPixmap icona(iconaSensore);
    QLabel *labelIcona = new QLabel;
    labelIcona->setPixmap(icona.scaled(70, 70, Qt::KeepAspectRatio));

    mainLayout = new QGridLayout();
    mainLayout->addWidget(labelNome, 0, 0, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(labelValore, 0, 1, Qt::AlignTop | Qt::AlignRight);
    mainLayout->addWidget(labelIcona, 1, 0, 1, 2, Qt::AlignTop | Qt::AlignCenter);


    mainWidget->setLayout(mainLayout);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(mainWidget);
    mainWidget->setStyleSheet("background: #ffffff; color: black; font-size: 16px; border-radius: 10px;");
    this->setLayout(layout);
}

void WidgetSensore::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        emit selezionatoSignal(this);
    }
    QWidget::mousePressEvent(event);
}

Sensore* WidgetSensore::getSensore() const{
    return sensore;
}
