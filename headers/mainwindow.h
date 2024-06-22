#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QtCharts>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "sensore.h"
#include "sidebar.h"
#include "schermatasensori.h"
#include "schermatasensore.h"
#include "schermatanuovosensore.h"

class MainWindow: public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = 0);
    void openNuovoSensore();
    void openSchermataSensore(Sensore* sensore = nullptr);
    void closeSchermataSensore();
private slots:
    void showSensoreDetails(Sensore *widget);
    void aggiungiNuovoSensore(Sensore *sensore);
private:
    std::vector<Sensore*> sensori;

    QWidget* centralWidget;
    QHBoxLayout* mainLayout;
    QWidget* leftWidget;
    QVBoxLayout* leftLayout;
    QWidget* rightWidget;
    QVBoxLayout* rightLayout;
    QScrollArea *scrollArea;

    SideBar* sidebar;
    SchermataSensori* schermatasensori;
    SchermataNuovoSensore* schermatanuovosensore;
    SchermataSensore* schermatasensore;
    void switchWidgets(QLayout *layout, QWidget *currentWidget, QWidget *newWidget);
};

#endif // MAINWINDOW_H
