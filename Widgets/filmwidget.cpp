#include "filmwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

FilmWidget::FilmWidget(const Film* film, QWidget* parent)
    : MediaWidget(parent) {
    auto layout = new QVBoxLayout(this);

    nomeLabel = new QLabel(QString::fromStdString("<h1>🍿" + film->getNome() + "</h1>"));
    descrizioneLabel = new QLabel(QString::fromStdString("<h3>Descrizione:</h3>\n" + film->getDescrizione()));
    descrizioneLabel->setWordWrap(true);
    descrizioneLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    prezzoLabel = new QLabel(QString("<h3>Prezzo:</h3> <h1>€%1</h1>").arg(film->getPrezzo()));
    registaLabel = new QLabel(QString::fromStdString("<h3>Regista:</h3> " + film->getRegista()));
    rilascioLabel = new QLabel(QString::fromStdString("<h3>Rilascio:</h3> " + film->getRilascio()));

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
