#ifndef FILMWIDGET_H
#define FILMWIDGET_H

#include <QString>
#include "mediawidget.h"
#include "../Modelli/film.h"
#include <QLabel>
#include <QPushButton>

class FilmWidget : public MediaWidget {
public:
    FilmWidget(const Film* film, QWidget* parent = nullptr);
private:
    QLabel* nomeLabel;
    QLabel* descrizioneLabel;
    QLabel* prezzoLabel;
    QLabel* registaLabel;
    QLabel* rilascioLabel;

    QPushButton* modificaBtn;
    QPushButton* eliminaBtn;
};

#endif // FILMWIDGET_H
