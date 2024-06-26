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

#include "../model/Repository/jsonRepo.h"
#include "../model/sensore.h"
#include "sidebar.h"
#include "schermatasensori.h"
#include "schermatasensore.h"
#include "schermatanuovosensore.h"

class MainWindow: public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = 0);
    void openNuovoSensore();
    void openSalva();
    void openSalvaConNome();
    void openCarica();
    void openSchermataSensore(Sensore* sensore = nullptr);
    void closeSchermataSensore();
    void closeSchermataNuovoSensore();
    void aggiornaSensori();
    void vuoiSalvare();
private slots:
    void showSensoreDetails(Sensore *widget);
    void aggiungiNuovoSensore(Sensore *sensore);
    void eliminaSensore(Sensore *widget);
    void modificaSensore(Sensore *widget);
private:
    std::vector<Sensore*> sensori;
    Repository::JsonRepository* repository = nullptr;
    bool isSaved = true;

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
