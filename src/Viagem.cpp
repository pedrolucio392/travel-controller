#include "Viagem.hpp"
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Transporte.hpp"
#include <stdexcept>

Viagem::Viagem(Transporte *transporte, std::vector<Passageiro *> passageiros, Cidade *origem, Cidade *destino)
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino), proxima(nullptr), horasEmTransito(0), emAndamento(false), distanciaDesdeUltimoDescanso(0), distanciaDoTrecho(0), distanciaPercorrida(0)
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

    if (this->transporte->getLocalAtual() != this->origem && this->transporte->getLocalAtual() != nullptr)
    {
        throw std::logic_error("O transporte não se encontra na cidade de origem nem em trânsito.");
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
        this->distanciaPercorrida += velocidade; // Como anda de hoa em hora e a velocidade é km/h, então é v*1.
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
                // Gim da viagem, então muda o local dos passageiros e destino
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
    return;
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