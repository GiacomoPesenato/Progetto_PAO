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
signals:
    void chiudiSchermataSensoreSignal();
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
    QVBoxLayout *chartLayout;
};

#endif // SCHERMATASENSORE_H
