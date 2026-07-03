/**
 * @file Transporte.hpp
 * @brief Declaração da classe Transporte.
 */

#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

#include <string>

// Forward declaration para evitar dependência circular
class Cidade;

/**
 * @class Transporte
 * @brief Representa um veículo no sistema de simulação de trânsito.
 *
 * A classe Transporte gerencia as propriedades de um veículo (como capacidade
 * e velocidade) e controla a mecânica de fadiga do motorista, garantindo que
 * o veículo pare para descansar após percorrer uma determinada distância.
 */
class Transporte
{
private:
    std::string nome;              ///< Nome de identificação do transporte (ex: "Viacao Serido").
    char tipo;                     ///< Caractere indicando o tipo de transporte ('A' para Aquático, 'T' para Terrestre).
    int capacidade;                ///< Número máximo de passageiros que o veículo suporta.
    int velocidade;                ///< Velocidade média do transporte em km/h.
    int distancia_entre_descansos; ///< Distância máxima em km que o veículo roda antes de precisar descansar.
    int tempo_de_descanso;         ///< Tempo padrão, em horas, exigido para cada parada de descanso.
    int tempo_de_descanso_atual;   ///< Contador regressivo em horas do descanso em andamento (0 se estiver rodando).
    Cidade *localAtual;            ///< Ponteiro para a cidade atual do transporte, ou nullptr se estiver em viagem.

public:
    /**
     * @brief Construtor da classe Transporte.
     *
     * @param nome O nome do veículo.
     * @param tipo Caractere identificador do tipo ('A' ou 'T').
     * @param capacidade Lotação máxima de passageiros.
     * @param velocidade Velocidade média de deslocamento em km/h.
     * @param distancia_entre_descansos Distância em km até o motorista sofrer fadiga.
     * @param tempo_de_descanso Duração em horas da parada obrigatória.
     * @param localAtual Ponteiro para a cidade inicial onde o veículo está estacionado.
     */
    Transporte(const std::string &nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade *localAtual);

    /**
     * @brief Obtém o nome do transporte.
     *
     * @return std::string Retorna o nome registrado.
     */
    std::string getNome() const;

    /**
     * @brief Obtém o tipo do transporte.
     *
     * @return char Retorna a categoria do veículo ('A' ou 'T').
     */
    char getTipo() const;

    /**
     * @brief Obtém a capacidade máxima de passageiros.
     *
     * @return int Retorna o limite de lotação.
     */
    int getCapacidade() const;

    /**
     * @brief Obtém a velocidade de deslocamento.
     *
     * @return int Retorna a velocidade em km/h.
     */
    int getVelocidade() const;

    /**
     * @brief Obtém a tolerância de distância antes do descanso.
     *
     * @return int Retorna a distância máxima sem paradas em km.
     */
    int getDistanciaEntreDescansos() const;

    /**
     * @brief Obtém o tempo padrão de duração de uma parada de descanso.
     *
     * @return int Retorna as horas necessárias para o descanso.
     */
    int getTempoDescanso() const;

    /**
     * @brief Obtém as horas restantes do descanso atual.
     *
     * @return int Retorna o contador regressivo de descanso. Se for 0, o veículo está pronto para rodar.
     */
    int getTempoDescansoAtual() const;

    /**
     * @brief Obtém a localização atual do veículo.
     *
     * @return Cidade* Retorna o ponteiro para a cidade, ou nullptr se estiver na rodovia.
     */
    Cidade *getLocalAtual() const;

    /**
     * @brief Atualiza o local físico onde o transporte está.
     *
     * @param local Ponteiro para a nova cidade, ou nullptr para colocar o veículo em trânsito.
     */
    void setLocalAtual(Cidade *local);

    /**
     * @brief Aciona o estado de descanso do veículo.
     *
     * Copia o valor de `tempo_de_descanso` para o contador `tempo_de_descanso_atual`,
     * indicando que o veículo não pode se mover até zerar as horas.
     */
    void iniciarDescanso();

    /**
     * @brief Decrementa o contador de descanso em andamento.
     *
     * Chamado pelo avanço do tempo no relógio do sistema. Reduz o `tempo_de_descanso_atual`
     * em 1 hora, limitando-o a zero (onde o veículo volta a ficar disponível).
     */
    void decrementarDescanso();
};

#endif