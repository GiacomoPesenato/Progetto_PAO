#include "../headers/schermata.h"
#include "./ui_schermata.h"
Schermata::Schermata(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Schermata)
{
    ui->setupUi(this);
}

Schermata::~Schermata()
{
    delete ui;
}
