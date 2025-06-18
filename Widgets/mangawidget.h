#ifndef MANGAWIDGET_H
#define MANGAWIDGET_H
#include <QPushButton>
#include <QLabel>
#include "mediawidget.h"
#include "../Modelli/manga.h"

class MangaWidget : public MediaWidget {
public:
    MangaWidget(const Manga* manga, QWidget* parent = nullptr);
private:
    QLabel* nomeLabel;
    QLabel* descrizioneLabel;
    QLabel* prezzoLabel;
    QLabel* autoreLabel;
    QLabel* genereLabel;

    QPushButton* modificaBtn;
    QPushButton* eliminaBtn;
};

#endif // MANGAWIDGET_H
