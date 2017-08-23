/*
Classe base MultimediaItem (Renderla Astratta magari?)
*/
#ifndef MULTIMEDIAITEM_H
#define MULTIMEDIAITEM_H

#include<iostream>
#include<map>
#include<string>

class MultimediaItem{
  private:
    std::string nome;
    std::string link;
    std::string descrizione;
    int nHits;
    static std::map<std::string, bool (*)(const MultimediaItem&, const std::string&)> searchMap;
    // ISO C++ non mi consente di creare puntatori a funzioni di istanza, quindi queste le devo rendere statiche
    static bool has_name(const MultimediaItem&, const std::string&);
    // Ricerca per link e descrizione non sono interessanti
  public:
    std::string getNome() const;
    std::string getLink() const;
    std::string getDesc() const;
    std::string getHits() const;
    MultimediaItem();
    MultimediaItem(const std::string&, const std::string&, const std::string&, int);
    virtual const std::map<std::string, std::string> readInfo() const;
    virtual void get();
    virtual MultimediaItem* search(const std::string&, const std::string&);
    // Distruttore virtuale puro mi evita di istanziare oggetti MultimediaItem e mi permetterà una corretta gestione della memoria in futuro
    virtual ~MultimediaItem() = 0;
    // Operatore di uguaglianza virtuale per confronti
    virtual bool operator==(const MultimediaItem&);
};

#endif
