#include "mediawidgetfactory.h"
#include "../Widgets/audiolibrowidget.h"
#include "../Widgets/filmwidget.h"
#include "../Widgets/mangawidget.h"

MediaWidgetFactory::MediaWidgetFactory(QWidget* parent)
    : parent(parent) {}

void MediaWidgetFactory::visit(const Film& film) {
    result = new FilmWidget(&film, parent);
}

void MediaWidgetFactory::visit(const Manga& manga) {
    result = new MangaWidget(&manga, parent);
}


void MediaWidgetFactory::visit(const AudioLibro& audioLibro) {
    result = new AudioLibroWidget(&audioLibro, parent);
}

QWidget* MediaWidgetFactory::getWidget() const {
    return result;
}


