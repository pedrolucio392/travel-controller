/**
 * @file Cidade.hpp
 * @brief Declaração da classe Cidade.
 */

#ifndef CIDADE_HPP
#define CIDADE_HPP

#include <string>

/**
 * @class Cidade
 * @brief Representa um nó (cidade) no sistema de controle de trânsito.
 *
 * A classe Cidade é fundamental para a estrutura do grafo do sistema,
 * servindo como ponto de origem e destino para Trajetos e Viagens,
 * além de ser o local onde Transportes e Passageiros podem estar fisicamente presentes ou aguardando.
 */
class Cidade
{
private:
    std::string nome; ///< Armazena o nome da cidade.

public:
    /**
     * @brief Construtor da classe Cidade.
     *
     * Inicializa um objeto Cidade definindo o seu nome.
     *
     * @param nome Uma string constante (passada por referência) contendo o nome da cidade.
     */
    Cidade(const std::string &nome);

    /**
     * @brief Obtém o nome da cidade.
     *
     * @return std::string Retorna o nome da cidade.
     */
    std::string getNome() const;
};

#endif