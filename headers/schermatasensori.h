#ifndef SCHERMATASENSORI_H
#define SCHERMATASENSORI_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QtCharts>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "sensore.h"
#include "widgetsensore.h"

class SchermataSensori: public QWidget
{
    Q_OBJECT
public:
    explicit SchermataSensori(const std::vector<Sensore*>& sensori, QWidget* parent = nullptr);
    void insertSensori(const std::vector<Sensore*>& sensori);
    void clearSensori();
signals:
    void widgetSensoreClicked(Sensore *sensore);
private slots:
    void handleWidgetSensoreClicked(WidgetSensore *widget);
private:
    QMap<QString, QGroupBox*> groupWidgets;
    QGridLayout *mainLayout;
};

#endif // SCHERMATASENSORI_H
