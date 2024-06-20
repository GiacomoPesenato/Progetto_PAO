#ifndef SCHERMATANUOVSENSORE_H
#define SCHERMATANUOVSENSORE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>

class SchermataNuovoSensore : public QWidget
{
    Q_OBJECT
public:
    explicit SchermataNuovoSensore(QWidget *parent = nullptr);
    static QWidget* createWidget(QWidget *parent = nullptr); // Metodo statico per creare il widget
private:
    QVBoxLayout* mainLayout;
    QComboBox *secondComboBox;
};

#endif // SCHERMATANUOVSENSORE_H
