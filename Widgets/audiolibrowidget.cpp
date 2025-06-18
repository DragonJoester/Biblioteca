#include "audiolibrowidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

AudioLibroWidget::AudioLibroWidget(const AudioLibro* audio, QWidget* parent)
    : MediaWidget(parent) {

    QVBoxLayout* layout = new QVBoxLayout(this);

    nomeLabel = new QLabel(QString::fromStdString("<h2>" + audio->getNome() + "</h2>"));
    descrizioneLabel = new QLabel(QString::fromStdString("<h3>Descrizione:</h3>\n" + audio->getDescrizione()));
    descrizioneLabel->setWordWrap(true);
    descrizioneLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    prezzoLabel = new QLabel(QString("<h3>Prezzo:</h3> <h1>€%1</h1>").arg(audio->getPrezzo()));
    argomentoLabel = new QLabel(QString::fromStdString("<h3>Argomento:</h3> " + audio->getArgomento()));
    durataLabel = new QLabel(QString::fromStdString("<h3>Durata:</h3> " + audio->getDurata()));

    modificaBtn = new QPushButton("Modifica");
    eliminaBtn = new QPushButton("Elimina");

    layout->addWidget(nomeLabel);
    layout->addWidget(descrizioneLabel);
    layout->addWidget(prezzoLabel);
    layout->addWidget(argomentoLabel);
    layout->addWidget(durataLabel);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(modificaBtn);
    btnLayout->addWidget(eliminaBtn);
    layout->addLayout(btnLayout);

    connect(modificaBtn, &QPushButton::clicked, this, &MediaWidget::modificaRichiesta);
    connect(eliminaBtn, &QPushButton::clicked, this, &MediaWidget::eliminaRichiesta);
}
