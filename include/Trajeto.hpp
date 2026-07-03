/**
 * @file Trajeto.hpp
 * @brief Declaração da classe Trajeto.
 */

#ifndef TRAJETO_HPP
#define TRAJETO_HPP

#include <string>

// Forward declaration para evitar dependência circular
class Cidade;

/**
 * @class Trajeto
 * @brief Representa uma conexão (aresta) entre duas cidades no sistema de trânsito.
 *
 * A classe Trajeto armazena as informações de uma rota direta entre uma
 * cidade de origem e uma cidade de destino. Ela é essencial para a
 * construção do mapa (grafo) e para o cálculo de rotas do Controlador.
 */
class Trajeto
{
private:
    Cidade *origem;  ///< Ponteiro para a cidade onde o trajeto se inicia.
    Cidade *destino; ///< Ponteiro para a cidade onde o trajeto termina.
    char tipo;       ///< Caractere que define o tipo do trajeto ('A' para Aquático, 'T' para Terrestre).
    int distancia;   ///< Distância física do trajeto em quilômetros.

public:
    /**
     * @brief Construtor da classe Trajeto.
     *
     * Cria uma ligação direta entre duas cidades, especificando o tipo
     * da via e a sua extensão física.
     *
     * @param origem Ponteiro para a cidade de partida.
     * @param destino Ponteiro para a cidade de chegada.
     * @param tipo Caractere indicando o tipo de terreno ou via (ex: 'A' ou 'T').
     * @param distancia A extensão do trecho em quilômetros.
     */
    Trajeto(Cidade *origem, Cidade *destino, char tipo, int distancia);

    /**
     * @brief Obtém a cidade de origem do trajeto.
     *
     * @return Cidade* Retorna o ponteiro para a cidade inicial desta rota.
     */
    Cidade *getOrigem() const;

    /**
     * @brief Obtém a cidade de destino do trajeto.
     *
     * @return Cidade* Retorna o ponteiro para a cidade final desta rota.
     */
    Cidade *getDestino() const;

    /**
     * @brief Obtém o tipo de via do trajeto.
     *
     * @return char Retorna o caractere que classifica a via ('A', 'T').
     */
    char getTipo() const;

    /**
     * @brief Obtém a extensão em quilômetros do trajeto.
     *
     * @return int Retorna a distância total do trecho.
     */
    int getDistancia() const;
};

#endif