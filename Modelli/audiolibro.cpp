#include "audiolibro.h"

AudioLibro::AudioLibro() {
    durata = "";
    argomento = "";
}

AudioLibro::AudioLibro(const std::string nome, double prezzo, const std::string descrizione, const std::string durata, const std::string argomento)
    : Media(nome, prezzo, descrizione),durata(durata), argomento(argomento){
}

std::string AudioLibro::getDurata() const{
    return durata;
}

std::string AudioLibro::getArgomento() const{
    return argomento;
}

void AudioLibro::setDurata(const std::string durata){
    this->durata = durata;
}


void AudioLibro::setArgomento(const std::string argomento){
    this->argomento = argomento;
}

QJsonObject AudioLibro::toJson() const{
    QJsonObject json;

    json["nome"] = QString::fromStdString(getNome());
    json["prezzo"] = QString::fromStdString(std::to_string(getPrezzo()));
    json["descrizione"] = QString::fromStdString(getDescrizione());

    json["durata"] = QString::fromStdString(durata);
    json["argomento"] = QString::fromStdString(argomento);

    return json;
};

void AudioLibro::fromJson(const QJsonObject& json){
    setNome(json["nome"].toString().toStdString());
    setPrezzo(json["prezzo"].toString().toDouble());
    setDescrizione(json["descrizione"].toString().toStdString());

    durata = json["durata"].toString().toStdString();
    argomento = json["argomento"].toString().toStdString();
}

void AudioLibro::accept(MediaVisitor& visitor) const{
    visitor.visit(*this);
}
