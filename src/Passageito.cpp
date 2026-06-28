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

    // Se o seu sistema permitir que o passageiro fique sem cidade
    // durante uma viagem, você remove esse if abaixo:
    if (local == nullptr)
    {
        throw std::invalid_argument("Local invalido.");
    }

    this->localAtual = local;
}