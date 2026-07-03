/**
 * @file Viagem.hpp
 * @brief Declaração da classe Viagem.
 */

#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include <string>
#include <vector>

// Forward declarations para evitar dependências circulares
class Cidade;
class Transporte;
class Passageiro;

/**
 * @class Viagem
 * @brief Representa um trecho específico de uma rota no sistema.
 *
 * A classe Viagem gerencia a simulação do deslocamento entre duas cidades conectadas.
 * Ela atua como um nó em uma Lista Encadeada, onde uma viagem completa calculada pelo
 * ControladorDeTransito pode ser composta por múltiplas instâncias de `Viagem` encadeadas
 * através do ponteiro `proxima`.
 */
class Viagem
{
private:
    Transporte *transporte;                ///< Ponteiro para o veículo realizando este trecho.
    std::vector<Passageiro *> passageiros; ///< Lista de ponteiros dos passageiros a bordo.
    Cidade *origem;                        ///< Ponteiro para a cidade de partida deste trecho.
    Cidade *destino;                       ///< Ponteiro para a cidade de chegada deste trecho.
    Viagem *proxima;                       ///< Ponteiro para o próximo trecho da rota (Lista Encadeada).
    int horasEmTransito;                   ///< Contador de horas que o transporte já passou em movimento neste trecho.
    bool emAndamento;                      ///< Flag que indica se este trecho está ativamente sendo percorrido.
    int distanciaDoTrecho;                 ///< A distância total em km entre a origem e o destino específicos desta viagem.
    int distanciaPercorrida;               ///< Odômetro do trecho: quantos km já foram avançados.
    int distanciaDesdeUltimoDescanso;      ///< Acumulador de km para calcular a fadiga do motorista.

public:
    /**
     * @brief Construtor da classe Viagem.
     *
     * @param transporte O veículo alocado para o trajeto.
     * @param passageiros A lista de passageiros que farão a viagem.
     * @param origem A cidade de início deste trecho específico.
     * @param destino A cidade final deste trecho específico.
     */
    Viagem(Transporte *transporte, std::vector<Passageiro *> passageiros, Cidade *origem, Cidade *destino);

    /**
     * @brief Dá a partida neste trecho da viagem.
     *
     * Muda o status para em andamento, verifica validações de lotação e localidade,
     * e tira o veículo e os passageiros de suas cidades (setando o local para nullptr).
     */
    void iniciarViagem();

    /**
     * @brief Avança o tempo da simulação para esta viagem.
     *
     * Calcula o deslocamento com base na velocidade do transporte, lida com a mecânica
     * de descanso (fadiga) e finaliza o trecho caso o destino seja alcançado.
     *
     * @param horas A quantidade de horas a avançar.
     */
    void avancarHoras(int horas);

    /**
     * @brief Imprime no terminal o status detalhado deste trecho.
     *
     * Exibe se está em andamento, aguardando conexão, concluído, a quilometragem
     * e se o motorista está descansando.
     */
    void relatarEstado() const;

    /**
     * @brief Verifica o status atual da viagem.
     *
     * @return true Se o veículo está ativamente na rodovia ou descansando neste trecho.
     * @return false Se a viagem ainda não começou ou se já foi concluída.
     */
    bool isEmAndamento() const;

    /**
     * @brief Obtém o próximo trecho da rota.
     *
     * @return Viagem* Retorna o ponteiro para a próxima viagem da lista encadeada,
     *         ou nullptr se este for o trecho final.
     */
    Viagem *getProxima() const;

    /**
     * @brief Define a próxima conexão desta rota.
     *
     * Conecta este nó ao próximo trecho na Lista Encadeada de viagens.
     *
     * @param proximaViagem Ponteiro para a viagem subsequente.
     */
    void setProxima(Viagem *proximaViagem);

    /**
     * @brief Configura a distância física deste trecho.
     *
     * Injetado pelo Controlador após ler os dados da aresta correspondente no grafo.
     *
     * @param distancia O valor em quilômetros do trecho.
     */
    void setDistanciaDoTrecho(int distancia);
};

#endif