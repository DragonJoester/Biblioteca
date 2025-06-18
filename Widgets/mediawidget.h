#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H

#include <QWidget>

class MediaWidget : public QWidget {
    Q_OBJECT
public:
    explicit MediaWidget(QWidget *parent = nullptr);
    virtual ~MediaWidget() = default;
signals:
    void modificaRichiesta();
    void eliminaRichiesta();
};

#endif // MEDIAWIDGET_H
