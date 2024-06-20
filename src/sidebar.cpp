#include "../headers/sidebar.h"

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
    connect(nuovosensore, &QPushButton::clicked, this, &SideBar::openNuovoSensore);
    mainLayout->addWidget(nuovosensore);
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
