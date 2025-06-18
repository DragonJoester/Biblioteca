#ifndef FORMAWIDGET_H
#define FORMAWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QFormLayout>
#include <QVBoxLayout>

class FormAWidget : public QWidget {
    Q_OBJECT
public:
    explicit FormAWidget(QWidget* parent = nullptr);
    void setDati(const QString&, const QString&, const QString&, double, const QString&, const QString&);
signals:
    void confermato(const QString& tipo, const QString& nome, const QString& descrizione,
                    double prezzo, const QString& campo1, const QString& campo2);
    void annulato();
private:
    QComboBox* tipoCombo;
    QLineEdit* nomeEdit;
    QLineEdit* descrizioneEdit;
    QLineEdit* prezzoEdit;

    QStackedWidget* specificiStack;
    QWidget* filmWidget;
    QLineEdit*  registaEdit;
    QLineEdit* rilascioEdit;

    QWidget* mangaWidget;
    QLineEdit* autoreEdit;
    QLineEdit* genereEdit;

    QWidget* audioWidget;
    QLineEdit* argomentoEdit;
    QLineEdit* durataEdit;

    QPushButton* confermaBtn;
    QPushButton* annullaBtn;

private slots:
    void aggiornaCampiSpecifici();
    void inviaDati();
};

#endif // FORMAWIDGET_H
