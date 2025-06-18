#ifndef MANGA_H
#define MANGA_H
#include <string>
#include <QJsonObject>
#include "media.h"

class Manga : public Media
{
public:
    Manga();
    Manga(const std::string, double, const std::string, const std::string, const std::string);

    std::string getAutore() const;
    std::string getGenere() const;

    void setAutore(const std::string);
    void setGenere(const std::string);

    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject&) override;

    void accept(MediaVisitor&) const override;
private:
    std::string autore;
    std::string genere;
};

#endif // MANGA_H
