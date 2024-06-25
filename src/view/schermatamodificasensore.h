#ifndef SCHERMATAMODIFICASENSORE_H
#define SCHERMATAMODIFICASENSORE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include "../model/sensore.h"

class SchermataModificaSensore : public QWidget
{
    Q_OBJECT
public:
    explicit SchermataModificaSensore(QWidget *parent = nullptr);
    static QWidget* createWidget(QWidget *parent = nullptr); // Metodo statico per creare il widget
public slots:
signals:
private:
    QVBoxLayout* mainLayout;
};

#endif // SCHERMATAMODIFICASENSORE_H
