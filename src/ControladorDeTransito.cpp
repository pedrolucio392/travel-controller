#include <ControladorDeTransito.hpp>
#include "Viagem.hpp"
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Transporte.hpp"
#include "Trajeto.hpp"
#include <stdexcept>

// bibliotecas do algoritmo de Dijkstra
#include <queue>
#include <map>
#include <limits>
#include <algorithm>

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

    // Traçar a rota
    std::vector<Cidade *> rotaCalculada = this->calcularMelhorCaminho(nomeOrigem, nomeDestino);

    // Se o vetor voltou vazio não tem estrada
    if (rotaCalculada.size() < 2)
    {
        throw std::invalid_argument("Erro: Nenhuma rota viavel encontrada entre a origem e o destino.");
    }

    // Montar a Lista Encadeada de Viagens
    Viagem *viagemInicial = nullptr;
    Viagem *viagemAnterior = nullptr;

    for (size_t i = 0; i < rotaCalculada.size() - 1; i++)
    {
        Cidade *cOrigem = rotaCalculada[i];
        Cidade *cDestino = rotaCalculada[i + 1];

        // Cria o trecho específico
        Viagem *novoTrecho = new Viagem(ptrTransporte, ptrsPassageiros, cOrigem, cDestino);

        // Busca a quilometragem deste trecho e salva na viagem
        int distanciaDoTrecho = this->getDistanciaEntre(cOrigem, cDestino);
        novoTrecho->setDistanciaDoTrecho(distanciaDoTrecho);

        if (viagemAnterior != nullptr)
        {
            // Liga o trecho anterior a este novo trecho
            viagemAnterior->setProxima(novoTrecho);
        }
        else
        {
            // Guarda quem é a primeira viagem
            viagemInicial = novoTrecho;
        }

        viagemAnterior = novoTrecho;
    }

    // Dá partida na primeira viagem
    viagemInicial->iniciarViagem();

    // 4. Salva a cabeça da lista no Controlador
    this->viagens.push_back(viagemInicial);
}

void ControladorDeTransito::avancarHoras(int horas)
{
    if (horas <= 0)
    {
        throw std::invalid_argument("O numero de horas a avancar deve ser maior que zero.");
    }

    // Passa o tempo para todas as rotas ativas no sistema
    for (Viagem *viagemCabeca : this->viagens)
    {
        Viagem *trechoAtual = viagemCabeca;

        // Pula os trechos que já terminaram até achar o trecho atual da escala
        while (trechoAtual != nullptr && !trechoAtual->isEmAndamento())
        {
            trechoAtual = trechoAtual->getProxima();
        }

        // Se achou um trecho em andamento, passa as horas para ele
        if (trechoAtual != nullptr)
        {
            trechoAtual->avancarHoras(horas);
        }
    }
}

void ControladorDeTransito::relatarEstado() const
{
    return;
}

// Método que usa o algoritmo

std::vector<Cidade *> ControladorDeTransito::calcularMelhorCaminho(const std::string &nomeOrigem, const std::string &nomeDestino) const
{
    Cidade *origem = this->buscarCidade(nomeOrigem);
    Cidade *destino = this->buscarCidade(nomeDestino);

    if (origem == nullptr || destino == nullptr)
    {
        throw std::invalid_argument("Erro: Cidade de origem ou destino não encontrada para calcular rota.");
    }

    // Cria um mapa onde a chave é uma Cidade, e o valor é uma lista dos Trajetos que saem dela
    std::map<Cidade *, std::vector<Trajeto *>> adjacencias;
    for (Trajeto *t : this->trajetos)
    {
        // Ida e volta
        adjacencias[t->getOrigem()].push_back(t);
        adjacencias[t->getDestino()].push_back(t);
    }

    // Configuração do Dijkstra
    std::map<Cidade *, int> distancias;
    std::map<Cidade *, Cidade *> antecessores;

    // Inicializa todas as distâncias com infinito
    for (Cidade *c : this->cidades)
    {
        distancias[c] = std::numeric_limits<int>::max();
        antecessores[c] = nullptr;
    }

    // A distância da origem para ela mesma é zero
    distancias[origem] = 0;

    // Fila de prioridade que guarda pares de <Distancia, Cidade*>
    // A estrutura std::greater garante que a cidade com menor distância fique sempre no topo
    std::priority_queue<std::pair<int, Cidade *>,
                        std::vector<std::pair<int, Cidade *>>,
                        std::greater<std::pair<int, Cidade *>>>
        fila;

    fila.push({0, origem});

    // Encontrar o menor caminho usando o algoritmo
    while (!fila.empty())
    {
        int distAtual = fila.top().first;
        Cidade *cidadeAtual = fila.top().second;
        fila.pop();

        // Se chegarno destino, não precisa calcular o resto do mapa
        if (cidadeAtual == destino)
            break;

        // Se encontrar um caminho antigo na fila que já foi superado, ignora
        if (distAtual > distancias[cidadeAtual])
            continue;

        // Analisa todos os vizinhos da cidade atual
        for (Trajeto *t : adjacencias[cidadeAtual])
        {
            Cidade *vizinho = t->getDestino();
            int pesoDaAresta = t->getDistancia();

            // Se a distância passando por 'cidadeAtual' for menor que a conhecida
            if (distancias[cidadeAtual] + pesoDaAresta < distancias[vizinho])
            {
                distancias[vizinho] = distancias[cidadeAtual] + pesoDaAresta;
                antecessores[vizinho] = cidadeAtual; // Gravamos o rastro para voltar depois
                fila.push({distancias[vizinho], vizinho});
            }
        }
    }

    // Reconstrução do Caminho
    std::vector<Cidade *> caminhoFinal;

    // Se a distância do destino continua "Infinita", significa que não existe rota possível
    if (distancias[destino] == std::numeric_limits<int>::max())
    {
        return caminhoFinal; // Retorna vetor vazio
    }

    // Faz o caminho reverso, do destino até a origem, usando o mapa de antecessores
    for (Cidade *atual = destino; atual != nullptr; atual = antecessores[atual])
    {
        caminhoFinal.push_back(atual);
    }

    // Como rastrea de trás pra frente, precisa inverter o vetor para ficar Origem -> Destino
    std::reverse(caminhoFinal.begin(), caminhoFinal.end());

    return caminhoFinal;
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

// retorna a distância entre duas cidades
int ControladorDeTransito::getDistanciaEntre(Cidade *origem, Cidade *destino)
{
    for (Trajeto *t : this->trajetos)
    {
        // Verifica se o trajeto liga as duas cidades (ida ou volta)
        if ((t->getOrigem() == origem && t->getDestino() == destino) ||
            (t->getOrigem() == destino && t->getDestino() == origem))
        {
            return t->getDistancia();
        }
    }

    // Se chegou aqui, as cidades não estão conectadas
    throw std::invalid_argument("Erro: Nao existe trajeto direto entre as cidades.");
}