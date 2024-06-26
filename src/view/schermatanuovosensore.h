#ifndef SCHERMATANUOVOSENSORE_H
#define SCHERMATANUOVOSENSORE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include "../model/sensore.h"

class SchermataNuovoSensore : public QWidget
{
    Q_OBJECT
public:
    explicit SchermataNuovoSensore(QWidget *parent = nullptr);
    static QWidget* createWidget(QWidget *parent = nullptr); // Metodo statico per creare il widget
    void clearInput();
public slots:
    void chiudiSchermataNuovoSensore();
signals:
    void nuovoSensoreCreato(Sensore *sensore);
    void chiudiSchermataNuovoSensoreSignal();
private:
    QVBoxLayout* mainLayout;

    //input
    QComboBox *inputTipo1;
    QLineEdit *inputNome;
    QLineEdit *inputGruppo;
    QComboBox *inputTipo2;
    QComboBox *inputClasseEnergetica;
    QDoubleSpinBox *inputTemperaturaTarget;
    QDoubleSpinBox *inputUmiditaTarget;
    QSpinBox *inputPotenzaMassima;
    QCheckBox *inputDimmerabile;
    QSpinBox *inputNumeroPannelli;
    QSpinBox *inputPotenzaPannello;

    //label
    QLabel *labelTipo1;
    QLabel *labelNome;
    QLabel *labelGruppo;
    QLabel *labelTipo2;
    QLabel *labelClasseEnergetica;
    QLabel *labelTemperaturaTarget;
    QLabel *labelUmiditaTarget;
    QLabel *labelPotenzaMassima;
    QLabel *labelDimmerabile;
    QLabel *labelNumeroPannelli;
    QLabel *labelPotenzaPannello;
};

#endif // SCHERMATANUOVOSENSORE_H
