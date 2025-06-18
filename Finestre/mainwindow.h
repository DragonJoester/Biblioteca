#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QListWidget>
#include <QLabel>
#include <QTextEdit>
#include <vector>
#include <Widgets/formawidget.h>
#include "../Modelli/media.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenuBar* menu;
    QLineEdit* cercaEdit;
    QPushButton* cercaBtn;
    QListWidget* listaMedia;
    QStackedWidget* stacked;

    QPushButton* modificaBtn;
    QPushButton* eliminaBtn;
    QPushButton* aggiungiBtn;
    std::vector<Media*> db;
    FormAWidget* formAggiunta;
    QWidget* placeholderVuoto;

    void aggiornaLista();


private slots:
    void caricaMedia();
    void salvaMedia();
    void aggiungiMedia();
    void rimuoviMedia();
    void modificaMedia();
    void gestisciFile();
    void filtraMedia();
    void mostraDettagliMedia();
    void apriFile(QAction*);

};
#endif // MAINWINDOW_H
