#ifndef MEDIA_H
#define MEDIA_H
#include <string>
#include <QJsonObject>
#include "mediavisitor.h"

class Media
{
public:
    Media();
    Media(const std::string, double, const std::string);

    std::string getNome() const;
    double getPrezzo() const;
    std::string getDescrizione() const;

    void setNome(const std::string);
    void setPrezzo(double);
    void setDescrizione(const std::string);

    virtual QJsonObject toJson() const = 0;
    virtual void fromJson(const QJsonObject&) = 0;

    virtual void accept(MediaVisitor&) const = 0;
    virtual ~Media() = default;
private:
    std::string nome;
    double prezzo;
    std::string descrizione;
};


#endif // MEDIA_H
