// schermatasensore.h
#ifndef SCHERMATASENSORE_H
#define SCHERMATASENSORE_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QCommonStyle>
#include <QPushButton>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include "../model/sensore.h"

class SchermataSensore : public QWidget {
    Q_OBJECT
private slots:
    void chiudiSchermataSensore();
    void simula();
    void eliminaSensore();
    void modificaSensore();
    void setGraficoAnno();
    void setGraficoMese();
    void setGraficoSettimana();
    void setGraficoGiorno();
signals:
    void chiudiSchermataSensoreSignal();
    void eliminaSensoreSignal(Sensore *sensore);
    void modificaSensoreSignal(Sensore *sensore);
public:
    explicit SchermataSensore(QWidget *parent = nullptr);
    void setSensore(Sensore *sensore);
private:
    Sensore *sensore;
    QHBoxLayout* mainLayout;
    QLabel* labelId;
    QLabel* labelNome;
    QLabel* labelGruppo;
    QLabel* labelValore;
    QLabel *labelIcona;
    QLabel *labelTemperaturaTarget;
    QLabel *labelUmiditaTarget;
    QLabel *labelPotenzaMassima;
    QLabel *labelDimmerabile;
    QLabel *labelNumeroPannelli;
    QLabel *labelPotenzaPannello;
    QLabel *labelClasseEnergetica;

    QVBoxLayout *chartLayout;

    QPushButton *buttonAnno;
    QPushButton *buttonMese;
    QPushButton *buttonSettimana;
    QPushButton *buttonGiorno;
};

#endif // SCHERMATASENSORE_H
