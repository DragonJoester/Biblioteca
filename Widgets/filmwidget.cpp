#include "filmwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

FilmWidget::FilmWidget(const Film* film, QWidget* parent)
    : MediaWidget(parent) {
    auto layout = new QVBoxLayout(this);

    nomeLabel = new QLabel(QString::fromStdString("<h2>" + film->getNome() + "</h2>"));
    descrizioneLabel = new QLabel(QString::fromStdString(film->getDescrizione()));
    prezzoLabel = new QLabel(QString("Prezzo: €%1").arg(film->getPrezzo()));
    registaLabel = new QLabel(QString::fromStdString("Regista: " + film->getRegista()));
    rilascioLabel = new QLabel(QString::fromStdString("Rilascio: " + film->getRilascio()));

    modificaBtn = new QPushButton("Modifica");
    eliminaBtn = new QPushButton("Elimina");

    layout->addWidget(nomeLabel);
    layout->addWidget(descrizioneLabel);
    layout->addWidget(prezzoLabel);
    layout->addWidget(registaLabel);
    layout->addWidget(rilascioLabel);

    auto btnLayout = new QHBoxLayout;
    btnLayout->addWidget(modificaBtn);
    btnLayout->addWidget(eliminaBtn);
    layout->addLayout(btnLayout);

    connect(modificaBtn, &QPushButton::clicked, this, &MediaWidget::modificaRichiesta);
    connect(eliminaBtn, &QPushButton::clicked, this, &MediaWidget::eliminaRichiesta);
}
