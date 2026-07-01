#include <ControladorDeTransito.hpp>
#include "Viagem.hpp"
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Transporte.hpp"
#include "Trajeto.hpp"
#include <stdexcept>

void ControladorDeTransito::cadastrarCidade(const std::string &nome)
{
    Cidade *novaCidade = new Cidade(nome);
    this->cidades.push_back(novaCidade);
}

void ControladorDeTransito::cadastrarTrajeto(const std::string &nomeOrigem, const std::string &nomeDestino, char tipo, int distancia)
{
    Cidade *ptrOrigem = this->buscarCidade(nomeOrigem);
    Cidade *ptrDestino = this->buscarCidade(nomeDestino);

    if (ptrOrigem == nullptr || ptrDestino == nullptr)
    {
        throw std::invalid_argument("Erro: Cidade de origem ou destino não cadastrada no sistema.");
    }

    Trajeto *novoTrajeto = new Trajeto(ptrOrigem, ptrDestino, tipo, distancia);
    this->trajetos.push_back(novoTrajeto);
}

void ControladorDeTransito::cadastrarTransporte(const std::string &nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, const std::string &localAtual)
{
    Cidade *ptrLocalAtual = this->buscarCidade(localAtual);

    if (ptrLocalAtual == nullptr)
    {
        throw std::invalid_argument("Erro: Cidade atual não cadastrada no sistema.");
    }

    Transporte *novoTransporte = new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, ptrLocalAtual);
    this->transportes.push_back(novoTransporte);
}

void ControladorDeTransito::cadastrarPassageiro(const std::string &nome, const std::string &localAtual)
{
    Cidade *ptrLocalAtual = this->buscarCidade(localAtual);

    if (ptrLocalAtual == nullptr)
    {
        throw std::invalid_argument("Erro: Cidade atual não cadastrada no sistema.");
    }

    Passageiro *novoPassageiro = new Passageiro(nome, ptrLocalAtual);
    this->passageiros.push_back(novoPassageiro);
}

void ControladorDeTransito::iniciarViagem(const std::string &nomeTransporte, const std::vector<std::string> &nomesPassageiros, const std::string &nomeOrigem, const std::string &nomeDestino)
{
    Transporte *ptrTransporte = buscarTransporte(nomeTransporte);
    Cidade *ptrOrigem = this->buscarCidade(nomeOrigem);
    Cidade *ptrDestino = this->buscarCidade(nomeDestino);

    if (ptrTransporte == nullptr)
    {
        throw std::invalid_argument("Erro: transporte não cadastrado no sistema.");
    }

    if (ptrOrigem == nullptr || ptrDestino == nullptr)
    {
        throw std::invalid_argument("Erro: Cidade de origem ou destino não cadastrada no sistema.");
    }

    std::vector<Passageiro *> ptrsPassageiros;

    for (const std::string &nome : nomesPassageiros)
    {
        Passageiro *ptrPassageiro = this->buscarPassageiro(nome);

        if (ptrPassageiro == nullptr)
        {
            throw std::invalid_argument("Erro: Passageiro não cadastrado no sistema.");
        }

        ptrsPassageiros.push_back(ptrPassageiro);
    }

    Viagem *novaViagem = new Viagem(ptrTransporte, ptrsPassageiros, ptrOrigem, ptrDestino);
    novaViagem->iniciarViagem();
    this->viagens.push_back(novaViagem);
}

void ControladorDeTransito::avancarHoras(int horas)
{
    if (horas <= 0)
    {
        throw std::invalid_argument("O número de horas a avançar deve ser maior que zero.");
    }

    for (Viagem *viagem : this->viagens)
    {
        if (viagem->isEmAndamento())
        {
            viagem->avancarHoras(horas);
        }
    }
}

void ControladorDeTransito::relatarEstado() const
{
    return;
}

// Métodos auxiliares para retornar o objeto se eexistir
Cidade *ControladorDeTransito::buscarCidade(const std::string &nome) const
{
    for (Cidade *c : this->cidades)
    {
        if (c->getNome() == nome)
        {
            return c;
        }
    }
    return nullptr;
}

Transporte *ControladorDeTransito::buscarTransporte(const std::string &nome) const
{
    for (Transporte *t : this->transportes)
    {
        if (t->getNome() == nome)
        {
            return t;
        }
    }
    return nullptr;
}

Passageiro *ControladorDeTransito::buscarPassageiro(const std::string &nome) const
{
    for (Passageiro *p : this->passageiros)
    {
        if (p->getNome() == nome)
        {
            return p;
        }
    }
    return nullptr;
}