/**
 * @file Cidade.cpp
 * @brief Implementação dos métodos da classe Cidade.
 */

#include "Cidade.hpp"

Cidade::Cidade(const std::string &nome)
    : nome(nome) {}

std::string Cidade::getNome() const
{
    return this->nome;
}