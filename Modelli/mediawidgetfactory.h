#ifndef MEDIAWIDGETFACTORY_H
#define MEDIAWIDGETFACTORY_H
#include <QWidget>
#include "mediavisitor.h"

class MediaWidgetFactory : public MediaVisitor
{
public:
    explicit MediaWidgetFactory(QWidget* parent = nullptr);
    void visit(const Film&) override;
    void visit(const Manga&) override;
    void visit(const AudioLibro&) override;
    QWidget* getWidget() const;
private:
    QWidget* result = nullptr;
    QWidget* parent;
};

#endif // MEDIAWIDGETFACTORY_H
