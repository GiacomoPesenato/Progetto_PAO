#include <QDateTime>
#include <QTimer>
#include <QtWidgets>

class SectionWidget : public QWidget
{
public:
    SectionWidget(const QString &title, const QStringList &panelData, QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Titolo della sezione
        QLabel *titleLabel = new QLabel(title);
        titleLabel->setStyleSheet(
            "color: white; font-size: 16px; font-weight: bold;"); // Stile del testo
        layout->addWidget(titleLabel);

        // Griglia di pannelli con scritta, valore e icona
        QGridLayout *panelGrid = new QGridLayout;

        int row = 0;
        for (int i = 0; i < panelData.size(); i += 2) {
            QStringList panelInfo1 = panelData[i].split(',');
            QStringList panelInfo2 = (i + 1 < panelData.size()) ? panelData[i + 1].split(',')
                                                                : QStringList{"", "", ""};

            QLabel *panelLabel1 = new QLabel(panelInfo1[0]);
            QLabel *valueLabel1 = new QLabel(panelInfo1[1]);
            QLabel *iconLabel1 = new QLabel;
            iconLabel1->setPixmap(QPixmap(panelInfo1[2]));

            QWidget *panelWidget1 = createPanelWidget(panelLabel1, valueLabel1, iconLabel1);

            panelGrid->addWidget(panelWidget1, row, 0, Qt::AlignTop | Qt::AlignLeft);

            if (i + 1 < panelData.size()) {
                QLabel *panelLabel2 = new QLabel(panelInfo2[0]);
                QLabel *valueLabel2 = new QLabel(panelInfo2[1]);
                QLabel *iconLabel2 = new QLabel;
                iconLabel2->setPixmap(QPixmap(panelInfo2[2]));

                QWidget *panelWidget2 = createPanelWidget(panelLabel2, valueLabel2, iconLabel2);

                panelGrid->addWidget(panelWidget2, row, 1, Qt::AlignTop | Qt::AlignLeft);
                panelLabel2->setStyleSheet("color: black; font-size: 11px;");
                valueLabel2->setStyleSheet("color: black; font-size: 11px;");
            }

            panelLabel1->setStyleSheet("color: black; font-size: 11px;");
            valueLabel1->setStyleSheet("color: black; font-size: 11px;");
            row++;
        }

        layout->addLayout(panelGrid);
    }

private:
    QWidget *createPanelWidget(QLabel *panelLabel, QLabel *valueLabel, QLabel *iconLabel)
    {
        QWidget *panelWidget = new QWidget;
        panelWidget->setStyleSheet("background-color: white; border-radius: 10px;");
        panelWidget->setFixedSize(80, 80);

        QVBoxLayout *panelLayout = new QVBoxLayout(panelWidget);
        panelLayout->addWidget(panelLabel);
        panelLayout->addWidget(valueLabel);
        panelLayout->addWidget(iconLabel);

        return panelWidget;
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Creazione della finestra principale
    QWidget mainWindow;
    mainWindow.setWindowTitle("Schermata Qt");

    // Creazione di un layout a griglia
    QGridLayout *mainLayout = new QGridLayout(&mainWindow);
    mainWindow.setLayout(mainLayout);

    // Creazione del widget per la colonna a sinistra (1/4 dello spazio)
    QWidget *leftColumnWidget = new QWidget;
    QVBoxLayout *leftColumnLayout = new QVBoxLayout(leftColumnWidget);

    // Creazione di un QLabel per l'ora attuale
    QLabel *labelTime = new QLabel;
    labelTime->setAlignment(Qt::AlignHCenter);
    labelTime->setStyleSheet("color: white; font-size: 24px;"); // Stile del testo
    leftColumnLayout->addWidget(labelTime, 0, Qt::AlignTop | Qt::AlignCenter);

    // Creazione di un QLabel per la data attuale
    QLabel *labelDate = new QLabel;
    labelDate->setAlignment(Qt::AlignHCenter);
    labelDate->setStyleSheet("color: white; font-size: 16px;"); // Stile del testo
    leftColumnLayout->addWidget(labelDate,
                                0,
                                Qt::AlignTop
                                    | Qt::AlignCenter); // Aggiunto dopo l'etichetta dell'ora

    leftColumnWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    mainLayout->addWidget(leftColumnWidget, 0, 0, 1, 1); // (riga, colonna, rowspan, colspan)

    // Creazione del widget per la colonna a destra (3/4 dello spazio)
    QWidget *rightColumnWidget = new QWidget;
    QGridLayout *rightColumnLayout = new QGridLayout(rightColumnWidget);

    // Aggiungi tre colonne alla colonna destra, ognuna con una sezione
    QStringList panelData1 = {"Label1,Value1,icon1.png",
                              "Label2,Value2,icon2.png",
                              "Label3,Value3,icon3.png"};
    QStringList panelData2 = {"Label4,Value4,icon4.png",
                              "Label5,Value5,icon5.png",
                              "Label6,Value6,icon6.png"};
    QStringList panelData3 = {"Label7,Value7,icon7.png",
                              "Label8,Value8,icon8.png",
                              "Label9,Value9,icon9.png"};
    QStringList panelData4 = {"Label1,Value1,icon1.png",
                              "Label2,Value2,icon2.png",
                              "Label3,Value3,icon3.png"};
    QStringList panelData5 = {"Label4,Value4,icon4.png",
                              "Label5,Value5,icon5.png",
                              "Label6,Value6,icon6.png"};
    QStringList panelData6 = {"Label7,Value7,icon7.png",
                              "Label8,Value8,icon8.png",
                              "Label9,Value9,icon9.png"};

    SectionWidget *section1 = new SectionWidget("Sezione 1", panelData1);
    SectionWidget *section2 = new SectionWidget("Sezione 2", panelData2);
    SectionWidget *section3 = new SectionWidget("Sezione 3", panelData3);
    SectionWidget *section4 = new SectionWidget("Sezione 4", panelData4);
    SectionWidget *section5 = new SectionWidget("Sezione 5", panelData5);
    SectionWidget *section6 = new SectionWidget("Sezione 6", panelData6);

    rightColumnLayout->addWidget(section1, 0, 0, Qt::AlignTop | Qt::AlignLeft);
    rightColumnLayout->addWidget(section2, 0, 1, Qt::AlignTop | Qt::AlignLeft);
    rightColumnLayout->addWidget(section3, 0, 2, Qt::AlignTop | Qt::AlignLeft);
    rightColumnLayout->addWidget(section4, 1, 0, Qt::AlignTop | Qt::AlignLeft);
    rightColumnLayout->addWidget(section5, 1, 1, Qt::AlignTop | Qt::AlignLeft);
    rightColumnLayout->addWidget(section6, 1, 2, Qt::AlignTop | Qt::AlignLeft);

    mainLayout->addWidget(rightColumnWidget, 0, 1, 1, 3); // (riga, colonna, rowspan, colspan)

    // Applica uno sfondo sfumato tra grigio chiaro e grigio scuro usando il codice esadecimale
    QString hexColorStart = "#323a3d"; // Grigio chiaro
    QString hexColorEnd = "#0d1114";   // Grigio scuro

    QColor colorStart(hexColorStart);
    QColor colorEnd(hexColorEnd);

    QLinearGradient gradient(0, 0, 0, mainWindow.height());
    gradient.setColorAt(0, colorStart);
    gradient.setColorAt(1, colorEnd);

    mainWindow.setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(gradient));
    mainWindow.setPalette(palette);

    // Aggiorna l'orario e la data ogni secondo
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        labelTime->setText(currentDateTime.toString("hh:mm:ss"));
        labelDate->setText(currentDateTime.toString("dddd, MMMM d, yyyy"));
    });
    timer.start(1000); // Ogni secondo

    mainWindow.show();
    return app.exec();
}
