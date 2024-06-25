#include "sidebar.h"
#include <iostream>

SideBar::SideBar(QWidget* parent)
    : QWidget(parent)
{
    // Creazione di un QLabel per la data attuale
    data = new QLabel("Lunedì, 00/00/0000");
    data->setAlignment(Qt::AlignHCenter);
    data->setStyleSheet("color: white; font-size: 24px;");

    // Creazione di un QLabel per l'ora attuale
    orario = new QLabel("00:00:00");
    orario->setAlignment(Qt::AlignHCenter);
    orario->setStyleSheet("color: white; font-size: 24px;");

    mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    mainLayout->addWidget(data, Qt::AlignTop | Qt::AlignLeft);
    mainLayout->addWidget(orario, Qt::AlignTop | Qt::AlignLeft);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    // Aggiorna l'orario e la data ogni secondo
    QTimer *timer = new QTimer(this);
    setDataOra();
    connect(timer, &QTimer::timeout, [=]() {
        setDataOra();
    });
    timer->start(1000); // Avvia il timer per aggiornare ogni secondo

    // Creazione del bottone per il cambio di widget
    QPushButton *nuovosensore = new QPushButton("Nuovo Sensore");
    QPushButton *salva = new QPushButton("Salva");
    QPushButton *salvaConNome = new QPushButton("Salva con nome");
    QPushButton *carica = new QPushButton("Carica");
    connect(nuovosensore, &QPushButton::clicked, this, &SideBar::openNuovoSensore);
    connect(salva, &QPushButton::clicked, this, &SideBar::openSalva);
    connect(salvaConNome, &QPushButton::clicked, this, &SideBar::openSalvaConNome);
    connect(carica, &QPushButton::clicked, this, &SideBar::openCarica);
    mainLayout->addWidget(nuovosensore);
    mainLayout->addWidget(salva);
    mainLayout->addWidget(salvaConNome);
    mainLayout->addWidget(carica);
}

void SideBar::setDataOra() const{
    QDateTime currentDateTime = QDateTime::currentDateTime(); // Ottieni la data e l'ora corrente
    orario->setText(currentDateTime.toString("hh:mm:ss")); // Imposta l'orario nel formato desiderato

    QString italianDate = currentDateTime.toString("dddd, d MMMM yyyy"); // Formatta la data nel formato desiderato in italiano
    italianDate.replace("Monday", "Lunedì").replace("Tuesday", "Martedì").replace("Wednesday", "Mercoledì")
        .replace("Thursday", "Giovedì").replace("Friday", "Venerdì").replace("Saturday", "Sabato")
        .replace("Sunday", "Domenica")
        .replace("January", "Gennaio").replace("February", "Febbraio").replace("March", "Marzo")
        .replace("April", "Aprile").replace("May", "Maggio").replace("June", "Giugno")
        .replace("July", "Luglio").replace("August", "Agosto").replace("September", "Settembre")
        .replace("October", "Ottobre").replace("November", "Novembre").replace("December", "Dicembre");

    data->setText(italianDate); // Imposta la data nel formato desiderato
}

void SideBar::openNuovoSensore(){
    emit openNuovoSensoreSignal();
}

void SideBar::openSalva(){
    emit openSalvaSignal();
}

void SideBar::openSalvaConNome(){
    emit openSalvaConNomeSignal();
}

void SideBar::openCarica(){
    emit openCaricaSignal();
}

void SideBar::caricaJsonFile(Repository::JsonRepository*& repository)
{
    QString defaultFolder = "JsonDocuments";
    QFileDialog dialog(this);
    dialog.setDirectory(defaultFolder);
    QString fileName = dialog.getOpenFileName(this, "Apri file JSON", defaultFolder,
                                              "JSON Files (*.json);;All Files (*)");

    if (!fileName.isEmpty()) {
        delete repository;
        repository = new Repository::JsonRepository(Repository::JsonRepository::fromPath(fileName.toStdString())); // Static factory method

        /* Questa era la precedente implementazione, ma c'era un bug, in certe situazioni non riusciva più a entrare in else, allora sono andato a forza
           bruta eliminando e ricreando ogni volta repository */
        /*if(repository==nullptr)
            repository = new Sensor::Repository::JsonRepository(Sensor::Repository::JsonRepository::fromPath(fileName.toStdString())); // Static factory method
        else{
            repository->setPath(fileName.toStdString());
            qDebug()<<"Sono entrato qui";
        }*/

        // Load del file Json nel repository, che poi viene salvato nel sensors di MainWindow
        repository->load();
    }
}

void SideBar::salvaJsonFile(const std::vector<Sensore*>& sensori, Repository::JsonRepository*& repository)
{
    if (repository == nullptr) {
        salvaJsonFileConNome(sensori, repository);
    } else {
        // Sovrascrizione della std::map di repository, che poi archivia nel Json
        repository->overwrite(sensori);
        repository->store();
    }
}

void SideBar::salvaJsonFileConNome(const std::vector<Sensore*>& sensori, Repository::JsonRepository*& repository)
{
    QString defaultFolder = "JsonDocuments";
    QFileDialog dialog(this);
    dialog.setDirectory(defaultFolder);

    QString fileName = dialog.getSaveFileName(this, "Salva file JSON", defaultFolder, "JSON Files (*.json)");

    if (!fileName.isEmpty()) {
        // Aggiungi l'estensione .json se non è già presente
        if (!fileName.endsWith(".json", Qt::CaseSensitive)) {
            fileName += ".json";
        }
        if(repository==nullptr){
            repository = new Repository::JsonRepository(Repository::JsonRepository::fromPath(fileName.toStdString())); // Static factory method
        }else{
            repository->setPath(fileName.toStdString());
        }
        // Sovrascrizione della std::map di repository, che poi archivia nel Json
        repository->overwrite(sensori);
        repository->store();
    }
}

