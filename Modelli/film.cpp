#include "film.h"

Film::Film() {
    regista = "";
    rilascio = "";
}

Film::Film(const std::string nome, double prezzo, const std::string descrizione, const std::string regista, const std::string rilascio)
    : Media(nome, prezzo, descrizione), regista(regista), rilascio(rilascio){

}

std::string Film::getRegista() const{
    return regista;
}

std::string Film::getRilascio() const{
    return rilascio;
}

void Film::setRegista(const std::string regista){
    this->regista = regista;
}


void Film::setRilascio(const std::string rilascio){
    this->rilascio = rilascio;
}

QJsonObject Film::toJson() const{
    QJsonObject json;

    json["nome"] = QString::fromStdString(getNome());
    json["prezzo"] = getPrezzo();
    json["descrizione"] = QString::fromStdString(getDescrizione());

    json["regista"] = QString::fromStdString(regista);
    json["rilascio"] = QString::fromStdString(rilascio);

    return json;
};

void Film::fromJson(const QJsonObject& json){
    setNome(json["nome"].toString().toStdString());
    setPrezzo(json["prezzo"].toDouble());
    setDescrizione(json["descrizione"].toString().toStdString());

    regista = json["regista"].toString().toStdString();
    rilascio = json["rilascio"].toString().toStdString();
}

void Film::accept(MediaVisitor&  visitor) const {
    visitor.visit(*this);
}
