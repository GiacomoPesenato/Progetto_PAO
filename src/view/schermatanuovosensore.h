#ifndef SCHERMATANUOVSENSORE_H
#define SCHERMATANUOVSENSORE_H

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
public slots:
    void chiudiSchermataNuovoSensore();
signals:
    void nuovoSensoreCreato(Sensore *sensore);
    void chiudiSchermataNuovoSensoreSignal();
private:
    QVBoxLayout* mainLayout;
};

#endif // SCHERMATANUOVSENSORE_H
