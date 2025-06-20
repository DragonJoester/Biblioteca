#include "mainwindow.h"
#include <QFile>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QVBoxLayout>
#include <Modelli/audiolibro.h>
#include <Modelli/film.h>
#include <Modelli/manga.h>
#include <Modelli/mediawidgetfactory.h>
#include <Widgets/mediawidget.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setFixedSize(800, 600);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    menu = menuBar();
    menu->addAction(tr("Salva"));
    menu->addAction(tr("Importa"));

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
    placeholderVuoto = new QWidget;
    stacked->addWidget(placeholderVuoto);
    stacked->setCurrentWidget(placeholderVuoto);

    connect(cercaBtn, &QPushButton::clicked, this, &MainWindow::filtraMedia);
    connect(aggiungiBtn, &QPushButton::clicked, this, &MainWindow::aggiungiMedia);
    connect(listaMedia, &QListWidget::currentRowChanged, this, &MainWindow::mostraDettagliMedia);
    connect(menu, &QMenuBar::triggered, this, &MainWindow::apriFile);

    caricaMedia();
}

MainWindow::~MainWindow() {
    salvaMedia();
}

void MainWindow::aggiornaLista() {
    listaMedia->clear();
    for (const auto& media : db) {
        listaMedia->addItem(QString::fromStdString(media->getNome()));
    }
}

void MainWindow::caricaMedia()
{
    db.clear();
    listaMedia->clear();

    QFile file("db.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
        QJsonArray jsonArray = jsonDocument.array();

        for (const auto& jsonValue : std::as_const(jsonArray)) {
            QJsonObject jsonObject = jsonValue.toObject();
            if (jsonObject.contains("durata")) {
                AudioLibro* audio = new AudioLibro();
                audio->fromJson(jsonObject);
                db.push_back(audio);
            } else if (jsonObject.contains("genere")) {
                Manga* manga = new Manga();
                manga->fromJson(jsonObject);
                db.push_back(manga);
            } else if (jsonObject.contains("regista")) {
                Film* film = new Film();
                film->fromJson(jsonObject);
                db.push_back(film);
            }
        }
    }

    aggiornaLista();
}

void MainWindow::salvaMedia() {
    QJsonArray jsonArray;

    for (const auto& m : db) {
        jsonArray.append(m->toJson());
    }

    QJsonDocument jsonDocument(jsonArray);

    QFile file("db.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(jsonDocument.toJson());
        file.close();
    }
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
            formAggiunta = nullptr;
        });

        connect(formAggiunta, &FormAWidget::annulato, this, [=]() {
            stacked->setCurrentWidget(placeholderVuoto);
            formAggiunta = nullptr;
        });
    }

    stacked->setCurrentWidget(formAggiunta);
}

void MainWindow::rimuoviMedia() {
    int index = listaMedia->currentRow();
    if (index < 0 || index >= static_cast<int>(db.size())) return;

    auto risposta = QMessageBox::question(this, "Conferma eliminazione",
                                          "Sei sicuro di voler eliminare questo media?",
                                          QMessageBox::Yes | QMessageBox::No);

    if (risposta == QMessageBox::Yes) {
        delete db[index];
        db.erase(db.begin() + index);

        QWidget* widgetAttuale = stacked->currentWidget();

        // Elimina il widget se è ancora nello stack e non è il placeholder
        if (widgetAttuale && stacked->indexOf(widgetAttuale) != -1 &&
            widgetAttuale != placeholderVuoto && widgetAttuale != formAggiunta) {
            stacked->removeWidget(widgetAttuale);
            widgetAttuale->deleteLater();
        }

        aggiornaLista();
        stacked->setCurrentWidget(placeholderVuoto);
    }
}


void MainWindow::modificaMedia() {
    int index = listaMedia->currentRow();
    if (index < 0 || index >= static_cast<int>(db.size())) {
        stacked->setCurrentWidget(placeholderVuoto);
        return;
    }

    Media* media = db[index];

    if (!media) return;

    if (formAggiunta) {
        stacked->removeWidget(formAggiunta);
        delete formAggiunta;
        formAggiunta = nullptr;
    }

    formAggiunta = new FormAWidget;
    stacked->addWidget(formAggiunta);

    QString tipo;
    QString campo1, campo2;
    if (auto f = dynamic_cast<Film*>(media)) {
        tipo = "Film";
        campo1 = QString::fromStdString(f->getRegista());
        campo2 = QString::fromStdString(f->getRilascio());
    } else if (auto m = dynamic_cast<Manga*>(media)) {
        tipo = "Manga";
        campo1 = QString::fromStdString(m->getAutore());
        campo2 = QString::fromStdString(m->getGenere());
    } else if (auto a = dynamic_cast<AudioLibro*>(media)) {
        tipo = "AudioLibro";
        campo1 = QString::fromStdString(a->getArgomento());
        campo2 = QString::fromStdString(a->getDurata());
    }

    formAggiunta->setDati(
        tipo,
        QString::fromStdString(media->getNome()),
        QString::fromStdString(media->getDescrizione()),
        media->getPrezzo(),
        campo1,
        campo2);

    connect(formAggiunta, &FormAWidget::confermato, this,
            [=](const QString& tipo, const QString& nome, const QString& descrizione,
                                                              double prezzo, const QString& campo1, const QString& campo2) {
        qDebug() << tipo;

        media->setNome(nome.toStdString());
        media->setDescrizione(descrizione.toStdString());
        media->setPrezzo(prezzo);

        if (auto f = dynamic_cast<Film*>(media)) {
            f->setRegista(campo1.toStdString());
            f->setRilascio(campo2.toStdString());
        } else if (auto m = dynamic_cast<Manga*>(media)) {
            m->setAutore(campo1.toStdString());
            m->setGenere(campo2.toStdString());
        } else if (auto a = dynamic_cast<AudioLibro*>(media)) {
            a->setArgomento(campo1.toStdString());
            a->setDurata(campo2.toStdString());
        }

        aggiornaLista();
        listaMedia->setCurrentRow(index);
        stacked->setCurrentWidget(placeholderVuoto);
        formAggiunta = nullptr;
    });

    connect(formAggiunta, &FormAWidget::annulato, this, [=]() {
        stacked->setCurrentWidget(placeholderVuoto);
        formAggiunta = nullptr;
    });

    stacked->setCurrentWidget(formAggiunta);
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
    if (index < 0 || index >= static_cast<int>(db.size())) {
        stacked->setCurrentWidget(placeholderVuoto);
        return;
    }

    const Media* media = db[index];
    if (!media) return;

    MediaWidgetFactory factory(this);
    media->accept(factory);
    MediaWidget* nuovoWidget = dynamic_cast<MediaWidget*>(factory.getWidget());
    if (!nuovoWidget) return;

    connect(nuovoWidget, &MediaWidget::modificaRichiesta, this, &MainWindow::modificaMedia);
    connect(nuovoWidget, &MediaWidget::eliminaRichiesta, this, &MainWindow::rimuoviMedia);

    QWidget* vecchio = stacked->currentWidget();

    // Evita di rimuovere il placeholder o il form
    if (vecchio && vecchio != placeholderVuoto && vecchio != formAggiunta) {
        stacked->removeWidget(vecchio);
        vecchio->deleteLater();
    }

    stacked->addWidget(nuovoWidget);
    stacked->setCurrentWidget(nuovoWidget);
}


void MainWindow::apriFile(QAction* action) {
    if (action->text() == "Salva") {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        "Salva JSON", "", "JSON file (*.json)");
        if (fileName.isEmpty()) return;

        if (!fileName.endsWith(".json", Qt::CaseInsensitive)) {
            fileName += ".json";
        }

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Errore", "Impossibile aprire il file");
            return;
        }

        QJsonArray jsonArray;
        for (const auto& m : db) {
            jsonArray.append(m->toJson());
        }

        QJsonDocument jsonDocument(jsonArray);
        file.write(jsonDocument.toJson());
        file.close();
    } else {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        "Apri JSON", "", "JSON (*.json)");
        if (fileName.isEmpty()) return;
        db.clear();
        db.clear();
        listaMedia->clear();

        QFile file("db.json");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray jsonData = file.readAll();
            file.close();

            QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
            QJsonArray jsonArray = jsonDocument.array();

            for (const auto& jsonValue : std::as_const(jsonArray)) {
                QJsonObject jsonObject = jsonValue.toObject();
                if (jsonObject.contains("durata")) {
                    AudioLibro* audio = new AudioLibro();
                    audio->fromJson(jsonObject);
                    db.push_back(audio);
                } else if (jsonObject.contains("genere")) {
                    Manga* manga = new Manga();
                    manga->fromJson(jsonObject);
                    db.push_back(manga);
                } else if (jsonObject.contains("regista")) {
                    Film* film = new Film();
                    film->fromJson(jsonObject);
                    db.push_back(film);
                }
            }
        }

        aggiornaLista();
    }
}
