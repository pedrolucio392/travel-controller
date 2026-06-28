#ifndef CIDADE_HPP
#define CIDADE_HPP

#include <string>

class Cidade
{
private:
    std::string nome;

public:
    Cidade(const std::string &nome);
    std::string getNome() const;
};

#endif