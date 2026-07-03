/**
 * @file Passageiro.hpp
 * @brief Declaração da classe Passageiro.
 */

#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <string>

// Forward declaration para evitar dependência circular
class Cidade;

/**
 * @class Passageiro
 * @brief Representa um passageiro dentro do sistema de simulação de trânsito.
 *
 * A classe Passageiro gerencia as informações de um indivíduo que viaja
 * pelo sistema, mantendo o controle exato de onde ele está fisicamente
 * (em uma rodoviária/cidade ou viajando nas rodovias).
 */
class Passageiro
{
private:
    std::string nome;   ///< Armazena o nome do passageiro.
    Cidade *localAtual; ///< Ponteiro para a cidade onde o passageiro está. É configurado como nullptr quando o passageiro está em trânsito.

public:
    /**
     * @brief Construtor da classe Passageiro.
     *
     * Inicializa um novo passageiro definindo seu nome e o local onde ele
     * entra no sistema.
     *
     * @param nome O nome completo ou identificação do passageiro.
     * @param localAtual Ponteiro para a cidade onde o passageiro se encontra inicialmente.
     */
    Passageiro(const std::string &nome, Cidade *localAtual);

    /**
     * @brief Obtém o nome do passageiro.
     *
     * @return std::string Retorna a string contendo o nome do passageiro.
     */
    std::string getNome() const;

    /**
     * @brief Obtém a localização atual do passageiro no mapa.
     *
     * @return Cidade* Retorna o ponteiro para a cidade atual do passageiro.
     *         Retorna nullptr caso o passageiro esteja viajando em um transporte.
     */
    Cidade *getLocalAtual() const;

    /**
     * @brief Atualiza a localização física do passageiro.
     *
     * Usado para mover o passageiro entre cidades ou para indicar que ele
     * entrou em um veículo.
     *
     * @param local Ponteiro para a nova cidade, ou nullptr para colocar o passageiro com o status de "em trânsito".
     */
    void setLocalAtual(Cidade *local);
};

#endif