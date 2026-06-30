#include "Viagem.hpp"
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Transporte.hpp"
#include <stdexcept>

Viagem::Viagem(Transporte *transporte, std::vector<Passageiro *> passageiros, Cidade *origem, Cidade *destino)
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino), proxima(nullptr), horasEmTransito(0), emAndamento(false)
{
    if (transporte == nullptr || origem == nullptr || destino == nullptr)
    {
        throw std::invalid_argument("Transporte, origem ou destino não podem ser nulos.");
    }
}

void Viagem::iniciarViagem()
{
    if (this->emAndamento)
    {
        return;
    }

    if (this->transporte->getLocalAtual() != this->origem)
    {
        throw std::logic_error("O transporte não se encontra na cidade de origem.");
    }

    if (this->passageiros.size() > static_cast<size_t>(this->transporte->getCapacidade()))
    {
        throw std::logic_error("A quantidade de passageiros excede a capacidade do transporte.");
    }

    this->emAndamento = true;
    this->horasEmTransito = 0;
}

void Viagem::avancarHoras(int horas)
{
    if (!this->emAndamento)
    {
        throw std::logic_error("Não é possível avançar o tempo de uma viagem que não está em andamento.");
    }

    if (horas <= 0)
    {
        throw std::invalid_argument("O número de horas a avançar deve ser maior que zero.");
    }

    this->horasEmTransito += horas;
}

void Viagem::relatarEstado() const
{
    return;
}

bool Viagem::isEmAndamento() const
{
    return this->emAndamento;
}