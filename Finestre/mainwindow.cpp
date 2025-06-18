#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <Modelli/audiolibro.h>
#include <Modelli/film.h>
#include <Modelli/manga.h>
#include <Modelli/mediawidgetfactory.h>
#include <Widgets/mediawidget.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    menu = menuBar();
    menu->addMenu("File");

    QWidget* primoWidget = new QWidget;
    QHBoxLayout*  primoLayout = new QHBoxLayout;
    cercaEdit = new QLineEdit;
    cercaBtn = new QPushButton("Cerca");

    primoLayout->addWidget(cercaEdit);
    primoLayout->addWidget(cercaBtn);
    primoWidget->setLayout(primoLayout);

    listaMedia = new QListWidget;
    aggiungiBtn = new QPushButton("Aggiungi");
    QVBoxLayout* destraLayout = new QVBoxLayout;
    destraLayout->addWidget(listaMedia);
    destraLayout->addWidget(aggiungiBtn);

    QWidget* destraWidget = new QWidget;
    destraWidget->setLayout(destraLayout);

    QWidget* sinistraWidget = new QWidget;
    QVBoxLayout* sinistraLayout = new QVBoxLayout;
    stacked = new QStackedWidget;
    sinistraLayout->addWidget(stacked);
    sinistraWidget->setLayout(sinistraLayout);

    QWidget* centraleWidget = new QWidget;
    QHBoxLayout* layoutCentrale = new QHBoxLayout;
    layoutCentrale->addWidget(sinistraWidget);
    layoutCentrale->addWidget(destraWidget);
    centraleWidget->setLayout(layoutCentrale);

    QWidget* mainWidget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(primoWidget);
    mainLayout->addWidget(centraleWidget);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    formAggiunta = nullptr;

    connect(cercaBtn, &QPushButton::clicked, this, &MainWindow::filtraMedia);
    connect(aggiungiBtn, &QPushButton::clicked, this, &MainWindow::aggiungiMedia);
    connect(listaMedia, &QListWidget::currentRowChanged, this, &MainWindow::mostraDettagliMedia);

    aggiornaLista();
}

MainWindow::~MainWindow() {}

void MainWindow::aggiornaLista() {
    listaMedia->clear();
    for (const auto& media : db) {
        listaMedia->addItem(QString::fromStdString(media->getNome()));
    }
}

void MainWindow::caricaMedia()
{

}

void MainWindow::salvaMedia()
{

}

void MainWindow::aggiungiMedia() {
    if (!formAggiunta) {
        formAggiunta = new FormAWidget;
        stacked->addWidget(formAggiunta);

        connect(formAggiunta, &FormAWidget::confermato, this, [=](
            const QString& tipo, const QString& nome, const QString& descrizione,
            double prezzo, const QString& campo1, const QString& campo2) {

            Media* nuovo = nullptr;
            if (tipo == "Film") {
                nuovo = new Film(nome.toStdString(), prezzo, descrizione.toStdString(),
                                    campo1.toStdString(), campo2.toStdString());

            } else if (tipo == "Manga") {
                nuovo = new Manga(nome.toStdString(), prezzo,descrizione.toStdString(),
                                  campo1.toStdString(), campo2.toStdString());
            } else if (tipo == "AudioLibro") {
                nuovo = new AudioLibro(nome.toStdString(), prezzo, descrizione.toStdString(),
                                       campo1.toStdString(), campo2.toStdString());
            }

            if (nuovo) {
                db.push_back(nuovo);
                aggiornaLista();
                listaMedia->setCurrentRow(static_cast<int>(db.size()) - 1);
            }

            stacked->setCurrentWidget(new QWidget);
        });

        connect(formAggiunta, &FormAWidget::annulato, this, [=]() {
            stacked->setCurrentWidget(new QWidget);
        });
    }

    stacked->setCurrentWidget(formAggiunta);
}

void MainWindow::rimuoviMedia()
{

}

void MainWindow::modificaMedia() {

}

void MainWindow::gestisciFile()
{

}

void MainWindow::filtraMedia() {
    QString filtro = cercaEdit->text();
    listaMedia->clear();
    for (const auto& media : db) {
        if (QString::fromStdString(media->getNome()).contains(filtro, Qt::CaseInsensitive)) {
            listaMedia->addItem(QString::fromStdString(media->getNome()));
        }
    }
}

void MainWindow::mostraDettagliMedia() {
    int index = listaMedia->currentRow();
    if (index < 0 || index >= static_cast<int>(db.size())) return;

    const Media* media = db[index];

    MediaWidgetFactory factory(this);
    media->accept(factory);
    MediaWidget* nuovoWidget = dynamic_cast<MediaWidget*>(factory.getWidget());

    if (!nuovoWidget) return;

    connect(nuovoWidget, &MediaWidget::modificaRichiesta, this, &MainWindow::modificaMedia);
    connect(nuovoWidget, &MediaWidget::eliminaRichiesta, this, &MainWindow::rimuoviMedia);

    QWidget* vecchio = stacked->currentWidget();
    if (vecchio)
        stacked->removeWidget(vecchio);

    stacked->addWidget(nuovoWidget);
    stacked->setCurrentWidget(nuovoWidget);
}
