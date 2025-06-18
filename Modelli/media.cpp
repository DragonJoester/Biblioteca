#include "media.h"

Media::Media() {
    nome = "";
    prezzo = 0;
    descrizione = "";
}

Media::Media(const std::string nome, double prezzo, const std::string descrizione)
    : nome(nome), prezzo(prezzo), descrizione(descrizione){

}

std::string Media::getNome() const{
    return nome;
}

double Media::getPrezzo() const
{
    return prezzo;
}

std::string Media::getDescrizione() const
{
    return descrizione;
}

void Media::setNome(const std::string nome)
{
    this->nome = nome;
}

void Media::setPrezzo(double prezzo)
{
    this->prezzo = prezzo;
}

void Media::setDescrizione(const std::string descrizione)
{
    this->descrizione = descrizione;
}
