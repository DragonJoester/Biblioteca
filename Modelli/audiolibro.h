#ifndef AUDIOLIBRO_H
#define AUDIOLIBRO_H
#include <string>
#include <QJsonObject>
#include "media.h"

class AudioLibro : public Media
{
public:
    AudioLibro();
    AudioLibro(const std::string, double, const std::string, const std::string, const std::string);

    std::string getDurata() const;
    std::string getArgomento() const;

    void setDurata(const std::string);
    void setArgomento(const std::string);

    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject&) override;

    void accept(MediaVisitor&) const override;

private:
    std::string durata;
    std::string argomento;
};

#endif // AUDIOLIBRO_H
