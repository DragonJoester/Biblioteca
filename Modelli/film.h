#ifndef FILM_H
#define FILM_H
#include <string>
#include <QJsonObject>
#include "media.h"

class Film : public Media
{
public:
    Film();
    Film(const std::string, double, const std::string, const std::string, const std::string);

    std::string getRegista() const;
    std::string getRilascio() const;

    void setRegista(const std::string);
    void setRilascio(const std::string);

    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject&);
private:
    std::string regista;
    std::string rilascio;
};

#endif // FILM_H
