#include "manga.h"

Manga::Manga() {
    autore = "";
    genere = "";
}
Manga::Manga(const std::string nome, double prezzo, const std::string descrizione, const std::string autore, const std::string genere)
    :  Media(nome, prezzo, descrizione), autore(autore), genere(genere){

    }
std::string Manga::getAutore()const{
    return autore;
}

std::string Manga::getGenere()const{
    return genere;
}

void Manga::setAutore(const std::string autore){
    this->autore = autore;
}

void Manga::setGenere(const std::string genere){
    this->genere = genere;
}

QJsonObject Manga::toJson() const{
    QJsonObject json;

    json["nome"] = QString::fromStdString(getNome());
    json["prezzo"] = QString::fromStdString(std::to_string(getPrezzo()));
    json["descrizione"] = QString::fromStdString(getDescrizione());

    json["autore"] = QString::fromStdString(autore);
    json["genere"] = QString::fromStdString(genere);

    return json;
};

void Manga::fromJson(const QJsonObject& json){
    setNome(json["nome"].toString().toStdString());
    setPrezzo(json["prezzo"].toString().toDouble());
    setDescrizione(json["descrizione"].toString().toStdString());

    autore = json["autore"].toString().toStdString();
    genere = json["genere"].toString().toStdString();
}

void Manga::accept(MediaVisitor& visitor) const {
    visitor.visit(*this);
}
