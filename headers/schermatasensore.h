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
#include "sensore.h"

class SchermataSensore : public QWidget {
    Q_OBJECT
private slots:
    void chiudiSchermataSensore();
signals:
    void chiudiSchermataSensoreSignal();
public:
    explicit SchermataSensore(QWidget *parent = nullptr);
    void setSensore(Sensore *sensore);
private:
    QHBoxLayout* mainLayout;
    QLabel* labelId;
    QLabel* labelNome;
    QLabel* labelGruppo;
    QLabel* labelValore;
    QLabel *labelIcona;
};

#endif // SCHERMATASENSORE_H
