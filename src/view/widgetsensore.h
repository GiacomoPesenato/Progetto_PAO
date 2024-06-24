#ifndef WIDGETSENSORE_H
#define WIDGETSENSORE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QMouseEvent>

#include "../model/sensore.h"

class WidgetSensore:  public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSensore(Sensore *sensore = nullptr, QWidget *parent = nullptr);
    Sensore* getSensore() const;
private:
    Sensore *sensore;
    QGridLayout *mainLayout;
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void selected(WidgetSensore *widget);
};

#endif // WIDGETSENSORE_H
