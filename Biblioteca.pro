QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Modelli/audiolibro.cpp \
    Modelli/film.cpp \
    Modelli/manga.cpp \
    Modelli/media.cpp \
    Modelli/mediawidgetfactory.cpp \
    Widgets/audiolibrowidget.cpp \
    Widgets/filmwidget.cpp \
    Widgets/formawidget.cpp \
    Widgets/mangawidget.cpp \
    Widgets/mediawidget.cpp \
    Finestre/mainwindow.cpp \
    main.cpp \


HEADERS += \
    Modelli/audiolibro.h \
    Modelli/film.h \
    Modelli/manga.h \
    Modelli/media.h \
    Modelli/mediavisitor.h \
    Modelli/mediawidgetfactory.h \
    Widgets/audiolibrowidget.h \
    Widgets/filmwidget.h \
    Widgets/formawidget.h \
    Widgets/mangawidget.h \
    Widgets/mediawidget.h \
    Finestre/mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore
