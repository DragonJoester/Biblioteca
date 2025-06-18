#include "mangawidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MangaWidget::MangaWidget(const Manga* manga, QWidget* parent)
    : MediaWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    nomeLabel = new QLabel(QString::fromStdString("<h2>" + manga->getNome() + "</h2>"));
    descrizioneLabel = new QLabel(QString::fromStdString("<h3>Descrizione:</h3>\n" + manga->getDescrizione()));
    descrizioneLabel->setWordWrap(true);
    descrizioneLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    prezzoLabel = new QLabel(QString("<h3>Prezzo:</h3> <h1>€%1</h1>").arg(manga->getPrezzo()));
    autoreLabel = new QLabel(QString::fromStdString("<h3>Autore:</h3> " + manga->getAutore()));
    genereLabel = new QLabel(QString::fromStdString("<h3>Genere:</h3> " + manga->getGenere()));

    modificaBtn = new QPushButton("Modifica");
    eliminaBtn = new QPushButton("Elimina");

    layout->addWidget(nomeLabel);
    layout->addWidget(descrizioneLabel);
    layout->addWidget(prezzoLabel);
    layout->addWidget(autoreLabel);
    layout->addWidget(genereLabel);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(modificaBtn);
    btnLayout->addWidget(eliminaBtn);
    layout->addLayout(btnLayout);

    connect(modificaBtn, &QPushButton::clicked, this, &MediaWidget::modificaRichiesta);
    connect(eliminaBtn, &QPushButton::clicked, this, &MediaWidget::eliminaRichiesta);
}
