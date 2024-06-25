#include "mainwindow.h"
#include "schermatasensori.h"
#include <iostream>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    /*sensori.push_back(new SensoreAria(1, "Aria1", "IQA", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/aria.png", "camera", 180, 170));
    sensori.push_back(new SensoreAria(2, "Aria2", "IQA", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/aria.png", "cucina", 180, 170));
    sensori.push_back(new SensoreAria(3, "Aria3", "IQA", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/aria.png", "cucina", 180, 170));
    sensori.push_back(new SensoreAria(4, "Aria4", "IQA", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/aria.png", "bagno", 180, 170));
    sensori.push_back(new SensoreAria(5, "Aria5", "IQA", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/aria.png", "camera", 180, 170));
    sensori.push_back(new SensoreTemperatura(6, "Temp1", "°", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/termometro.png", "camera", 22, 18, 28, 23));
    sensori.push_back(new SensoreTemperatura(7, "Temperatura1", "°", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/termometro.png", "camera", 21, 10, 40, 20));
    sensori.push_back(new SensoreElettricita(8, "Consumo", "W", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/elettrecita.png", "generale", 3000, 1425));
    sensori.push_back(new SensoreElettrodomestico(9, "TV", "W", "C:/Users/samsung/Desktop/PAO grafica/untitled/img/tv.png", "salotto", "A", 450, 89));*/

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
    QString hexColorStart = "#323a3d"; // Light grey
    QString hexColorEnd = "#0d1114";   // Dark grey

    QColor colorStart(hexColorStart);
    QColor colorEnd(hexColorEnd);

    QLinearGradient gradient(0, 0, 0, 1000);
    gradient.setColorAt(0, colorStart);
    gradient.setColorAt(1, colorEnd);

    centralWidget->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(gradient));
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
    connect(schermatasensori, &SchermataSensori::widgetSensoreClicked, this, &MainWindow::showSensoreDetails);

    connect(schermatasensore, &SchermataSensore::chiudiSchermataSensoreSignal, this, &MainWindow::closeSchermataSensore);
    connect(schermatanuovosensore, &SchermataNuovoSensore::nuovoSensoreCreato, this, &MainWindow::aggiungiNuovoSensore);
    connect(schermatanuovosensore, &SchermataNuovoSensore::chiudiSchermataNuovoSensoreSignal, this, &MainWindow::closeSchermataNuovoSensore);
    connect(schermatasensore, &SchermataSensore::eliminaSensoreSignal, this, &MainWindow::eliminaSensore);
}

void MainWindow::openNuovoSensore() {
    switchWidgets(rightLayout, schermatasensori, schermatanuovosensore);
}

void MainWindow::openSalva(){
    sidebar->salvaJsonFile(sensori, repository);
}

void MainWindow::openSalvaConNome() {
    sidebar->salvaJsonFileConNome(sensori, repository);
}

void MainWindow::openCarica(){

}

void MainWindow::openSchermataSensore(Sensore* sensore) {
    // schermatasensore = new SchermataSensore(sensore);
}

void MainWindow::closeSchermataSensore() {
    switchWidgets(rightLayout, schermatasensore, schermatasensori);
}

void MainWindow::closeSchermataNuovoSensore() {
    switchWidgets(rightLayout, schermatanuovosensore, schermatasensori);
    std::cout << "chiudi" << std::endl;
}

void MainWindow::switchWidgets(QLayout *layout, QWidget *currentWidget, QWidget *newWidget) {
    if (layout->indexOf(currentWidget) != -1) {
        layout->replaceWidget(currentWidget, newWidget);
        currentWidget->hide();
        newWidget->show();
    }
}

void MainWindow::showSensoreDetails(Sensore *sensore) {
    schermatasensore->setSensore(sensore);
    switchWidgets(rightLayout, schermatasensori, schermatasensore);
}

void MainWindow::aggiungiNuovoSensore(Sensore *sensore) {
    sensore->setId(sensori.size());
    sensori.push_back(sensore);
    schermatasensori->clearSensori();
    schermatasensori->insertSensori(sensori);
    switchWidgets(rightLayout, schermatanuovosensore, schermatasensori);
}

void MainWindow::eliminaSensore(Sensore *sensore){
    for (std::vector<Sensore*>::iterator it = sensori.begin(); it != sensori.end(); it++)
        if (*it == sensore) {
            sensori.erase(it);
            break;
        };
    schermatasensori->clearSensori();
    schermatasensori->insertSensori(sensori);
    switchWidgets(rightLayout, schermatasensore, schermatasensori);
}

void MainWindow::modificaSensore(Sensore *widget){

}
