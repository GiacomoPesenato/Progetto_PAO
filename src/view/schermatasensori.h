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

#include "../model/sensore.h"
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
    void ricerca(const QString &value);
private:
    std::vector<Sensore*> sensori;
    int flgRicerca = 0;
    QVBoxLayout *mainLayout;
    QGridLayout *sensorLayout;
    QMap<QString, QGroupBox*> groupWidgets;
};

#endif // SCHERMATASENSORI_H
