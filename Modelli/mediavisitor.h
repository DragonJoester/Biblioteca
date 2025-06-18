#ifndef MEDIAVISITOR_H
#define MEDIAVISITOR_H

class Film;
class Manga;
class AudioLibro;

class MediaVisitor {
public:
    virtual void visit(const Film&) = 0;
    virtual void visit(const Manga&) = 0;
    virtual void visit(const AudioLibro&) = 0;
    virtual ~MediaVisitor() = default;
};

#endif // MEDIAVISITOR_H
