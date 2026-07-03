#include "Transporte.hpp"
#include "Cidade.hpp"
#include <stdexcept>

Transporte::Transporte(const std::string &nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade *localAtual)
    : nome(nome), tipo(tipo), capacidade(capacidade), velocidade(velocidade), distancia_entre_descansos(distancia_entre_descansos), tempo_de_descanso(tempo_de_descanso), localAtual(localAtual), tempo_de_descanso_atual(0)
{
    if (tipo != 'A' && tipo != 'T')
    {
        throw std::invalid_argument("O tipo de transporte deve ser 'A' (Aquático) ou 'T' (Terrestre).");
    }
    if (capacidade <= 0)
    {
        throw std::invalid_argument("A capacidade deve ser maior que zero.");
    }
    if (velocidade <= 0)
    {
        throw std::invalid_argument("A velocidade deve ser maior que zero.");
    }
    if (localAtual == nullptr)
    {
        throw std::invalid_argument("O transporte precisa ser instanciado em uma cidade válida (ponteiro não-nulo).");
    }
}

std::string Transporte::getNome() const
{
    return this->nome;
}

char Transporte::getTipo() const
{
    return this->tipo;
}

int Transporte::getCapacidade() const
{
    return this->capacidade;
}

int Transporte::getVelocidade() const
{
    return this->velocidade;
}

int Transporte::getDistanciaEntreDescansos() const
{
    return this->distancia_entre_descansos;
}

int Transporte::getTempoDescanso() const
{
    return this->tempo_de_descanso;
}

int Transporte::getTempoDescansoAtual() const
{
    return this->tempo_de_descanso_atual;
}

Cidade *Transporte::getLocalAtual() const
{
    return this->localAtual;
}

void Transporte::setLocalAtual(Cidade *local)
{
    if (this->localAtual == local)
    {
        return;
    }

    this->localAtual = local;
}

void Transporte::iniciarDescanso()
{
    // O despertador é configurado para a quantidade de horas padrão de descanso deste veículo
    this->tempo_de_descanso_atual = this->tempo_de_descanso;
}

void Transporte::decrementarDescanso()
{
    // Reduz 1 hora do tempo de descanso para que não fique negativo
    if (this->tempo_de_descanso_atual > 0)
    {
        this->tempo_de_descanso_atual--;
    }
}