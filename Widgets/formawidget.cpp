#include "formawidget.h"
#include <QDoubleValidator>
#include <QMessageBox>

FormAWidget::FormAWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    tipoCombo = new QComboBox;
    tipoCombo->addItems({"Film", "Manga", "AudioLibro"});

    nomeEdit = new QLineEdit;
    descrizioneEdit = new QLineEdit;
    prezzoEdit = new QLineEdit;
    QDoubleValidator* validator = new QDoubleValidator(0, 9999, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    validator->setLocale(QLocale::C);
    prezzoEdit->setValidator(validator);


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
    connect(annullaBtn, &QPushButton::clicked, this, [=]() {
        emit annulato();
    });

    aggiornaCampiSpecifici();
}

void FormAWidget::setDati(const QString& tipo, const QString& nome, const QString& descrizione, double prezzo,
                          const QString& campo1, const QString& campo2) {
    tipoCombo->setCurrentText(tipo);
    nomeEdit->setText(nome);
    descrizioneEdit->setText(descrizione);
    prezzoEdit->setText(QString::number(prezzo));

    aggiornaCampiSpecifici();

    if (tipo == "Film") {
        registaEdit->setText(campo1);
        rilascioEdit->setText(campo2);
    } else if (tipo == "Manga") {
        autoreEdit->setText(campo1);
        genereEdit->setText(campo2);
    } else if (tipo == "AudioLibro") {
        argomentoEdit->setText(campo1);
        durataEdit->setText(campo2);
    }

}

void FormAWidget::aggiornaCampiSpecifici() {
    specificiStack->setCurrentIndex(tipoCombo->currentIndex());
}

void FormAWidget::inviaDati() {
    QString tipo = tipoCombo->currentText();
    QString nome = nomeEdit->text().trimmed();
    QString descrizione = descrizioneEdit->text().trimmed();
    double prezzo = QLocale::c().toDouble(prezzoEdit->text());
    QString campo1, campo2;

    if (tipo == "Film") {
        campo1 = registaEdit->text().trimmed();
        campo2 = rilascioEdit->text().trimmed();
    } else if (tipo == "Manga") {
        campo1 = autoreEdit->text().trimmed();
        campo2 = genereEdit->text().trimmed();
    } else if (tipo == "AudioLibro") {
        campo1 = argomentoEdit->text().trimmed();
        campo2 = durataEdit->text().trimmed();
    }

    if (nome.isEmpty() || descrizione.isEmpty() || prezzo <= 0.0 || campo1.isEmpty() || campo2.isEmpty()) {
        QMessageBox::warning(this, "Campi mancanti", "Compila tutti i campi correttamente");
        return;
    }

    emit confermato(
        tipo,
        nome,
        descrizione,
        prezzo,
        campo1,
        campo2
        );
}
