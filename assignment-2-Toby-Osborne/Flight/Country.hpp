#ifndef COUNTRY_HPP
#define COUNTRY_HPP

#include <string>

using namespace std;

class Country {
public:
    enum Language {
        CHINESE,
        SPANISH,
        ENGLISH,
        HINDI,
        ARABIC
    };
    Country(const std::string &name, Language language);
    Language getLanguage() const;
    std::string getName() const;
private:
    Country(const Country &other);
    Country& operator=(const Country &other);
   std::string Name;
    Language language;
};

#endif
