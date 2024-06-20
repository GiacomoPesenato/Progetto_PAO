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
public:
    explicit SideBar(QWidget* parent = 0);
public slots:
    void openNuovoSensore();
private:
    void setDataOra() const;
    QVBoxLayout* mainLayout;
    QLabel *orario;
    QLabel *data;
};

#endif // SIDEBAR_H
