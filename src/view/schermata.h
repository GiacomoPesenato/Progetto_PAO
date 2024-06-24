#ifndef SCHERMATA_H
#define SCHERMATA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Schermata;
}
QT_END_NAMESPACE

class Schermata : public QMainWindow
{
    Q_OBJECT

public:
    Schermata(QWidget *parent = nullptr);
    ~Schermata();

private:
    Ui::Schermata *ui;
};
#endif // SCHERMATA_H
