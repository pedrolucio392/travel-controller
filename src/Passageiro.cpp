/**
 * @file Passageiro.cpp
 * @brief Implementação dos métodos da classe Passageiro.
 */

#include "Passageiro.hpp"
#include "Cidade.hpp"
#include <stdexcept>

Passageiro::Passageiro(const std::string &nome, Cidade *localAtual)
    : nome(nome), localAtual(localAtual) {}

std::string Passageiro::getNome() const
{
    return this->nome;
}

Cidade *Passageiro::getLocalAtual() const
{
    return this->localAtual;
}

void Passageiro::setLocalAtual(Cidade *local)
{
    if (this->localAtual == local)
    {
        return;
    }

    this->localAtual = local;
}