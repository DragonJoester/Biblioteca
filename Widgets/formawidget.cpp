#include "formawidget.h"
#include <QDoubleValidator>

FormAWidget::FormAWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    tipoCombo = new QComboBox;
    tipoCombo->addItems({"Film", "Manga", "AudioLibro"});

    nomeEdit = new QLineEdit;
    descrizioneEdit = new QLineEdit;
    prezzoEdit = new QLineEdit;
    prezzoEdit->setValidator(new QDoubleValidator(0, 9999, 2, this));

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Tipo:", tipoCombo);
    formLayout->addRow("Nome:", nomeEdit);
    formLayout->addRow("Descrizione", descrizioneEdit);
    formLayout->addRow("Prezzo:", prezzoEdit);

    filmWidget = new QWidget;
    QFormLayout* filmLayout = new QFormLayout;
    registaEdit = new QLineEdit;
    rilascioEdit = new QLineEdit;
    filmLayout->addRow("Regista:", registaEdit);
    filmLayout->addRow("Rilascio:", rilascioEdit);
    filmWidget->setLayout(filmLayout);

    mangaWidget = new QWidget;
    QFormLayout* mangaLayout = new QFormLayout;
    autoreEdit = new QLineEdit;
    genereEdit = new QLineEdit;
    mangaLayout->addRow("Autore:", autoreEdit);
    mangaLayout->addRow("Genere:", genereEdit);
    mangaWidget->setLayout(mangaLayout);

    audioWidget = new QWidget;
    QFormLayout* audioLayout = new QFormLayout;
    argomentoEdit = new QLineEdit;
    durataEdit = new QLineEdit;
    audioLayout->addRow("Argomento:", argomentoEdit);
    audioLayout->addRow("Durata:", durataEdit);
    audioWidget->setLayout(audioLayout);

    specificiStack = new QStackedWidget;
    specificiStack->addWidget(filmWidget);
    specificiStack->addWidget(mangaWidget);
    specificiStack->addWidget(audioWidget);

    confermaBtn = new QPushButton("Conferma");
    annullaBtn = new QPushButton("Annulla");

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(confermaBtn);
    btnLayout->addWidget(annullaBtn);

    layout->addLayout(formLayout);
    layout->addWidget(specificiStack);
    layout->addLayout(btnLayout);

    connect(tipoCombo, &QComboBox::currentIndexChanged, this, &FormAWidget::aggiornaCampiSpecifici);
    connect(confermaBtn, &QPushButton::clicked, this, &FormAWidget::inviaDati);
    connect(annullaBtn, &QPushButton::clicked, this, &FormAWidget::annulato);

    aggiornaCampiSpecifici();
}

void FormAWidget::aggiornaCampiSpecifici() {
    specificiStack->setCurrentIndex(tipoCombo->currentIndex());
}

void FormAWidget::inviaDati() {
    QString tipo = tipoCombo->currentText();
    QString campo1, campo2;

    if (tipo == "Film") {
        campo1 = registaEdit->text();
        campo2 = rilascioEdit->text();
    } else if (tipo == "Manga") {
        campo1 = autoreEdit->text();
        campo2 = genereEdit->text();
    } else if (tipo == "AudioLibro") {
        campo1 = argomentoEdit->text();
        campo2 = durataEdit->text();
    }

    emit confermato(
        tipo,
        nomeEdit->text(),
        descrizioneEdit->text(),
        prezzoEdit->text().toDouble(),
        campo1,
        campo2
        );
}
