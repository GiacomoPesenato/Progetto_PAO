#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QtCharts>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../model/Repository/jsonRepo.h"

class SideBar: public QWidget
{
    Q_OBJECT
signals:
    void openNuovoSensoreSignal();
    void openSalvaSignal();
    void openSalvaConNomeSignal();
    void openCaricaSignal();
public:
    explicit SideBar(QWidget* parent = 0);
    void caricaJsonFile(Repository::JsonRepository*& repository);
    void salvaJsonFile(const std::vector<Sensore*>& sensori, Repository::JsonRepository*& repository);
    void salvaJsonFileConNome(const std::vector<Sensore*>& sensori, Repository::JsonRepository*& repository);
public slots:
    void openNuovoSensore();
    void openSalva();
    void openSalvaConNome();
    void openCarica();
private:
    void setDataOra() const;
    QVBoxLayout* mainLayout;
    QLabel *orario;
    QLabel *data;
};

#endif // SIDEBAR_H
