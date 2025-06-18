#include "audiolibrowidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

AudioLibroWidget::AudioLibroWidget(const AudioLibro* audio, QWidget* parent)
    : MediaWidget(parent) {

    QVBoxLayout* layout = new QVBoxLayout(this);

    nomeLabel = new QLabel(QString::fromStdString("<h2>" + audio->getNome() + "</h2>"));
    descrizioneLabel = new QLabel(QString::fromStdString(audio->getDescrizione()));
    prezzoLabel = new QLabel(QString("Prezzo: €%1").arg(audio->getPrezzo()));
    argomentoLabel = new QLabel(QString::fromStdString("Argomento: " + audio->getArgomento()));
    durataLabel = new QLabel(QString::fromStdString("Durata: " + audio->getDurata()));

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
