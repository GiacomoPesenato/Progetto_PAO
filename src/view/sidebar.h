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
