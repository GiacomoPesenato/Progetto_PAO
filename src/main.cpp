#include <QDateTime>
#include <QTimer>
#include <QtWidgets>
#include "view/mainwindow.h"

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
    app.setWindowIcon(QIcon("C:/Users/samsung/Desktop/PAO grafica/untitled/img/logo.png"));
    MainWindow window;
    window.resize(1300, 700);
    window.show();

    return app.exec();

}
