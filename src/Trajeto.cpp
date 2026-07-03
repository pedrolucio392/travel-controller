/**
 * @file Trajeto.cpp
 * @brief Implementação dos métodos da classe Trajeto.
 */

#include "Trajeto.hpp"
#include "Cidade.hpp"
#include <stdexcept>

Trajeto::Trajeto(Cidade *origem, Cidade *destino, char tipo, int distancia)
    : origem(origem), destino(destino), tipo(tipo), distancia(distancia)
{
    if (origem == nullptr || destino == nullptr)
{
        throw std::invalid_argument("Origem e destino não podem ser nulos.");
    }

    if (origem == destino)
    {
        throw std::invalid_argument("A cidade de origem não pode ser igual à de destino.");
    }

    if (distancia <= 0)
    {
        throw std::invalid_argument("A distância do trajeto deve ser maior que zero.");
    }

    if (tipo != 'A' && tipo != 'T')
    {
        throw std::invalid_argument("O tipo de trajeto deve ser 'A' (Aquático) ou 'T' (Terrestre).");
    }
}

Cidade *Trajeto::getOrigem() const
{
    return this->origem;
}

Cidade *Trajeto::getDestino() const
{
    return this->destino;
}

char Trajeto::getTipo() const
{
    return this->tipo;
}

int Trajeto::getDistancia() const
{
    return this->distancia;
}