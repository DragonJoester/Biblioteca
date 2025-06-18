#ifndef AUDIOLIBROWIDGET_H
#define AUDIOLIBROWIDGET_H
#include "mediawidget.h"
#include "../Modelli/audiolibro.h"
#include <QLabel>
#include <QPushButton>

class AudioLibroWidget : public MediaWidget {
public:
    AudioLibroWidget(const AudioLibro*, QWidget* parent = nullptr);
private:
    QLabel* nomeLabel;
    QLabel* descrizioneLabel;
    QLabel* prezzoLabel;
    QLabel* argomentoLabel;
    QLabel* durataLabel;

    QPushButton* modificaBtn;
    QPushButton* eliminaBtn;
};

#endif // AUDIOLIBROWIDGET_H
