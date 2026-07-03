/**
 * @file Viagem.cpp
 * @brief Implementação dos métodos da classe Viagem.
 *
 * Contém a lógica de execução da viagem, incluindo o controle de tempo,
 * deslocamento físico, paradas obrigatórias para descanso do motorista e
 * a transição automática entre os trechos da rota (Lista Encadeada).
 */

#include "Viagem.hpp"
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Transporte.hpp"
#include <stdexcept>
#include <iostream>

Viagem::Viagem(Transporte *transporte, std::vector<Passageiro *> passageiros, Cidade *origem, Cidade *destino)
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino), proxima(nullptr), horasEmTransito(0), emAndamento(false), distanciaDesdeUltimoDescanso(0), distanciaDoTrecho(0), distanciaPercorrida(0)
{
    if (transporte == nullptr || origem == nullptr || destino == nullptr)
    {
        throw std::invalid_argument("Transporte, origem ou destino nao podem ser nulos.");
    }
}

/**
 * @details Verifica a validade da partida (se o veículo está na origem correta e
 * se há capacidade suficiente). Após a validação, retira o transporte e os passageiros
 * da cidade atual (setando seus locais para nullptr) para representar o estado "em trânsito".
 */
void Viagem::iniciarViagem()
{
    if (this->emAndamento)
    {
        return;
    }

    if (this->transporte->getLocalAtual() != this->origem && this->transporte->getLocalAtual() != nullptr)
    {
        throw std::logic_error("O transporte nao se encontra na cidade de origem nem em transito.");
    }

    if (this->passageiros.size() > static_cast<size_t>(this->transporte->getCapacidade()))
    {
        throw std::logic_error("A quantidade de passageiros excede a capacidade do transporte.");
    }

    this->emAndamento = true;
    this->horasEmTransito = 0;
    this->distanciaPercorrida = 0;

    // Tira o transporte e os passageiros da cidade
    this->transporte->setLocalAtual(nullptr);

    for (Passageiro *p : this->passageiros)
    {
        p->setLocalAtual(nullptr);
    }
}

/**
 * @details O avanço do tempo é processado de hora em hora (passo a passo) para
 * garantir que as validações de descanso (fadiga) e chegada ao destino sejam
 * verificadas no momento exato. Se o destino do trecho for alcançado e ainda
 * sobrarem horas a avançar, o próximo trecho da lista encadeada é acionado.
 */
void Viagem::avancarHoras(int horas)
{
    if (!this->emAndamento)
    {
        throw std::logic_error("Nao eh possivel avancar o tempo de uma viagem que nao esta em andamento.");
    }

    if (horas <= 0)
    {
        throw std::invalid_argument("O numero de horas a avancar deve ser maior que zero.");
    }

    // Roda o tempo de hora em hora e faz as veriricações
    for (int h = 0; h < horas; h++)
    {
        // Verifica se está descansando
        if (this->transporte->getTempoDescansoAtual() > 0)
        {
            this->transporte->decrementarDescanso();
            this->horasEmTransito++;
            continue; // Pula para a próxima hora sem sair do lugar
        }

        // Se não está descansando, o transporte anda
        int velocidade = this->transporte->getVelocidade();
        this->distanciaPercorrida += velocidade; // Como anda de hora em hora e a velocidade é km/h, então é v*1.
        this->distanciaDesdeUltimoDescanso += velocidade;

        // Verificação de tempo para descanso
        if (this->distanciaDesdeUltimoDescanso >= this->transporte->getDistanciaEntreDescansos())
        {
            this->transporte->iniciarDescanso();
            this->distanciaDesdeUltimoDescanso = 0;
        }

        // Verificação de Chegada no destino desse trecho
        if (this->distanciaPercorrida >= this->distanciaDoTrecho)
        {
            // O trecho atual acabou
            this->emAndamento = false;
            this->horasEmTransito++; // Contabiliza a hora da chegada

            // Descobre quantas horas sobram nesse salto de tempo
            int horasSobrando = horas - (h + 1);

            // Verifica se há conexão
            if (this->proxima != nullptr)
            {
                // Dá a partida no próximo trecho
                this->proxima->iniciarViagem();

                // Se sobrou horas, o próximo trecho já começa a andar
                if (horasSobrando > 0)
                {
                    this->proxima->avancarHoras(horasSobrando);
                }
            }
            else
            {
                // Fim da viagem, então muda o local dos passageiros e destino
                this->transporte->setLocalAtual(this->destino);

                for (Passageiro *p : this->passageiros)
                {
                    p->setLocalAtual(this->destino);
                }
            }
            break;
        }

        // O relógio geral avança 1 hora normal
        this->horasEmTransito++;
    }
}

void Viagem::relatarEstado() const
{
    // Usa os getters básicos nas classes de modelo
    std::cout << "  -> Trecho: [" << this->origem->getNome() << " -> " << this->destino->getNome() << "] ";

    if (this->emAndamento)
    {
        std::cout << ">> EM ANDAMENTO <<" << std::endl;
        std::cout << "     Progresso do Trecho: " << this->distanciaPercorrida << " km / " << this->distanciaDoTrecho << " km" << std::endl;

        if (this->transporte->getTempoDescansoAtual() > 0)
        {
            std::cout << "     Status: MOTORISTA DESCANSANDO (" << this->transporte->getTempoDescansoAtual() << "h restantes)" << std::endl;
        }
        else
        {
            std::cout << "     Status: EM MOVIMENTO (Fadiga Acumulada: " << this->distanciaDesdeUltimoDescanso << " km / " << this->transporte->getDistanciaEntreDescansos() << " km)" << std::endl;
        }
    }
    else if (this->distanciaPercorrida >= this->distanciaDoTrecho && this->distanciaDoTrecho > 0)
    {
        std::cout << "[CONCLUIDO]" << std::endl;
    }
    else
    {
        std::cout << "[AGUARDANDO CONEXAO]" << std::endl;
    }
}

bool Viagem::isEmAndamento() const
{
    return this->emAndamento;
}

Viagem *Viagem::getProxima() const
{
    return this->proxima;
}

void Viagem::setProxima(Viagem *proximaViagem)
{
    this->proxima = proximaViagem;
}

void Viagem::setDistanciaDoTrecho(int distancia)
{
    this->distanciaDoTrecho = distancia;
}