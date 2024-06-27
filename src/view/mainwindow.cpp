#include "mainwindow.h"
#include "schermatasensori.h"
#include <iostream>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Domotica");

    mainLayout = new QHBoxLayout;
    leftWidget = new QWidget;
    leftLayout = new QVBoxLayout;
    leftWidget->setLayout(leftLayout);

    // Set up the scroll area
    scrollArea = new QScrollArea;
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet("QScrollArea { background: transparent; border: 0; }");

    // Create a container widget for the scroll area content
    QWidget *scrollContent = new QWidget;
    rightLayout = new QVBoxLayout(scrollContent);
    scrollContent->setLayout(rightLayout);
    scrollContent->setStyleSheet("background: transparent; border: 0;");

    // Set the container widget as the scroll area's widget
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);

    scrollArea->setStyle(new QCommonStyle);
    scrollArea->setStyleSheet("QScrollArea { border: 0; background: transparent; } "
                              "QScrollBar:vertical {"
                              "    border: 1px transparent;"
                              "    background-color: transparent;"
                              "    width: 8px;"
                              "    margin: 10px 0 10px 0;"
                              "} "
                              "QScrollBar::handle:vertical {"
                              "    background-color: white;"
                              "    border-radius: 4px;"
                              "} "
                              "QScrollBar::add-line:vertical {"
                              "    border: 2px solid transparent;"
                              "    background-color: transparent;"
                              "} "
                              "QScrollBar::sub-line:vertical {"
                              "    border: 2px solid transparent;"
                              "    background-color: transparent;"
                              "}");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);

    mainLayout->addWidget(leftWidget);
    mainLayout->addWidget(scrollArea);

    // Apply gradient background to central widget
    QString hexColorStart = "#3C3F41"; // Light grey
    QString hexColorEnd = "#1B1E21";   // Dark grey

    QColor colorStart(hexColorStart);
    QColor colorEnd(hexColorEnd);

    QLinearGradient gradiente(0, 0, 0, 1000);
    gradiente.setColorAt(0, colorStart);
    gradiente.setColorAt(1, colorEnd);

    centralWidget->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(gradiente));
    centralWidget->setPalette(palette);

    sidebar = new SideBar();
    leftLayout->addWidget(sidebar, Qt::AlignTop | Qt::AlignLeft);
    leftLayout->setAlignment(Qt::AlignTop);

    schermatasensori = new SchermataSensori(sensori, this);
    rightLayout->addWidget(schermatasensori, Qt::AlignTop | Qt::AlignLeft);
    rightLayout->setAlignment(Qt::AlignTop);

    schermatanuovosensore = new SchermataNuovoSensore();



    connect(sidebar, &SideBar::openNuovoSensoreSignal, this, &MainWindow::openNuovoSensore);
    connect(sidebar, &SideBar::openSalvaSignal, this, &MainWindow::openSalva);
    connect(sidebar, &SideBar::openSalvaConNomeSignal, this, &MainWindow::openSalvaConNome);
    connect(sidebar, &SideBar::openCaricaSignal, this, &MainWindow::openCarica);


    schermatasensore = new SchermataSensore();
    connect(schermatasensori, &SchermataSensori::sensoreSelezionatoSignal, this, &MainWindow::showSensoreDetails);

    connect(schermatasensore, &SchermataSensore::chiudiSchermataSensoreSignal, this, &MainWindow::closeSchermataSensore);
    connect(schermatanuovosensore, &SchermataNuovoSensore::nuovoSensoreCreato, this, &MainWindow::aggiungiNuovoSensore);
    connect(schermatanuovosensore, &SchermataNuovoSensore::chiudiSchermataNuovoSensoreSignal, this, &MainWindow::closeSchermataNuovoSensore);
    connect(schermatasensore, &SchermataSensore::eliminaSensoreSignal, this, &MainWindow::eliminaSensore);
    connect(schermatasensore, &SchermataSensore::modificaSensoreSignal, this, &MainWindow::modificaSensore);

    schermatamodificasensore = new SchermataModificaSensore();

    connect(schermatamodificasensore, &SchermataModificaSensore::chiudiSchermataModificaSensoreSignal, this, &MainWindow::chiudiSchermataModificaSensore);
    connect(schermatamodificasensore, &SchermataModificaSensore::modificaSensoreSignal, this, &MainWindow::salvaModificheSensore);
}

void MainWindow::openNuovoSensore() {
    if(rightLayout->indexOf(schermatasensori) != -1){
        spostaWidget(rightLayout, schermatasensori, schermatanuovosensore);
    }else if(rightLayout->indexOf(schermatasensore) != -1){
        spostaWidget(rightLayout, schermatasensore, schermatanuovosensore);
    }else if(rightLayout->indexOf(schermatamodificasensore) != -1){
        spostaWidget(rightLayout, schermatamodificasensore, schermatanuovosensore);
    }
}

void MainWindow::openSalva(){
    sidebar->salvaJsonFile(sensori, repository);

}

void MainWindow::openSalvaConNome() {
    sidebar->salvaJsonFileConNome(sensori, repository);
}

void MainWindow::openCarica(){
    if(!flgSalvato){
        vuoiSalvare();
    }
    if(flgSalvato){
        sidebar->caricaJsonFile(repository);
        if(repository != nullptr) aggiornaSensori();
    }
}

void MainWindow::aggiornaSensori() {
    sensori.clear();
    schermatasensori->pulisciSensori();
    for (const auto& pair : repository->getRepository()) {
        aggiungiNuovoSensore(pair.second);
    }
    flgSalvato = true; // richiamo aggiornaSensori() solo quando carico quindi sono per forza aggiornati

}

void MainWindow::openSchermataSensore(Sensore* sensore) {
    // schermatasensore = new SchermataSensore(sensore);
}

void MainWindow::closeSchermataSensore() {
    schermatasensori->pulisciSensori();
    schermatasensori->inserimentoSensori(sensori);
    spostaWidget(rightLayout, schermatasensore, schermatasensori);
}

void MainWindow::closeSchermataNuovoSensore() {
    spostaWidget(rightLayout, schermatanuovosensore, schermatasensori);
    std::cout << "chiudi" << std::endl;
}

void MainWindow::spostaWidget(QLayout *layout, QWidget *currentWidget, QWidget *newWidget) {
    if (layout->indexOf(currentWidget) != -1) {
        layout->replaceWidget(currentWidget, newWidget);
        currentWidget->hide();
        newWidget->show();
    }
}

void MainWindow::showSensoreDetails(Sensore *sensore) {
    schermatasensore->setSensore(sensore);
    spostaWidget(rightLayout, schermatasensori, schermatasensore);
}

void MainWindow::aggiungiNuovoSensore(Sensore *sensore) {
    sensore->setId(sensori.size());
    sensori.push_back(sensore);
    schermatasensori->pulisciSensori();
    schermatasensori->inserimentoSensori(sensori);
    spostaWidget(rightLayout, schermatanuovosensore, schermatasensori);
    flgSalvato = false;
}

void MainWindow::eliminaSensore(Sensore *sensore){
    for (std::vector<Sensore*>::iterator it = sensori.begin(); it != sensori.end(); it++)
        if (*it == sensore) {
            delete sensore;
            sensori.erase(it);
            break;
        };
    schermatasensori->pulisciSensori();
    schermatasensori->inserimentoSensori(sensori);
    spostaWidget(rightLayout, schermatasensore, schermatasensori);
    flgSalvato = false;
}

void MainWindow::vuoiSalvare(){
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Conferma",
                                                                   "Ci sono modifiche non salvate. Vuoi salvare il lavoro svolto?",
                                                                   QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (resBtn == QMessageBox::Yes) {
        emit sidebar->openSalvaSignal();
        flgSalvato = true;
    }else if(resBtn == QMessageBox::No){
        flgSalvato = true;
    }
}

void MainWindow::modificaSensore(Sensore *sensore){
    schermatamodificasensore->setSensore(sensore);

    spostaWidget(rightLayout, schermatasensore, schermatamodificasensore);
}

void MainWindow::chiudiSchermataModificaSensore(Sensore* sensore){
    schermatasensore->setSensore(sensore);
    spostaWidget(rightLayout, schermatamodificasensore, schermatasensore);
}
void MainWindow::salvaModificheSensore(Sensore* sensore){
    flgSalvato = false;
    schermatasensore->setSensore(sensore);
    schermatasensori->pulisciSensori();
    schermatasensori->inserimentoSensori(sensori);
    spostaWidget(rightLayout, schermatamodificasensore, schermatasensore);
}
