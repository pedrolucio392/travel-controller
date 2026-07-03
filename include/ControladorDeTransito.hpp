/**
 * @file ControleDeTransito.hpp
 * @brief Declaração da classe ControladorDeTransito.
 */

#ifndef CONTROLE_DE_TRANSITO_HPP
#define CONTROLE_DE_TRANSITO_HPP

#include <string>
#include <vector>

// Forward declarations para evitar dependências circulares
class Cidade;
class Trajeto;
class Transporte;
class Passageiro;
class Viagem;

/**
 * @class ControladorDeTransito
 * @brief Classe principal que atua como o motor do sistema de simulação.
 *
 * O ControladorDeTransito é responsável por gerenciar e armazenar todas as entidades
 * do sistema (Cidades, Trajetos, Transportes, Passageiros e Viagens). Ele também executa
 * as lógicas principais, como o cálculo de rotas usando o algoritmo de Dijkstra,
 * o avanço do tempo e a persistência dos dados.
 */
class ControladorDeTransito
{
private:
    std::vector<Cidade *> cidades;         ///< Vetor contendo os ponteiros para todas as cidades cadastradas.
    std::vector<Trajeto *> trajetos;       ///< Vetor contendo os ponteiros para todos os trajetos (arestas) cadastrados.
    std::vector<Transporte *> transportes; ///< Vetor contendo os ponteiros para todos os transportes da frota.
    std::vector<Passageiro *> passageiros; ///< Vetor contendo os ponteiros para todos os passageiros registrados.
    std::vector<Viagem *> viagens;         ///< Vetor contendo os ponteiros para as listas encadeadas de viagens (cabeças das listas).

public:
    /**
     * @brief Cadastra uma nova cidade no sistema.
     *
     * @param nome O nome da cidade a ser cadastrada.
     */
    void cadastrarCidade(const std::string &nome);

    /**
     * @brief Cadastra um novo trajeto conectando duas cidades.
     *
     * @param nomeOrigem Nome da cidade de origem.
     * @param nomeDestino Nome da cidade de destino.
     * @param tipo Tipo do trajeto (ex: 'A' para asfalto, 'T' para terra).
     * @param distancia A distância em quilômetros entre as duas cidades.
     */
    void cadastrarTrajeto(const std::string &nomeOrigem, const std::string &nomeDestino, char tipo, int distancia);

    /**
     * @brief Cadastra um novo veículo de transporte no sistema.
     *
     * @param nome O nome do veículo (ex: "Viacao Serido").
     * @param tipo O tipo do veículo (ex: 'O' para ônibus, 'V' para van).
     * @param capacidade A quantidade máxima de passageiros suportada.
     * @param velocidade A velocidade média de cruzeiro do veículo em km/h.
     * @param distancia_entre_descansos Distância máxima em km que o veículo pode percorrer antes do motorista descansar.
     * @param tempo_de_descanso O tempo em horas que o veículo precisa ficar parado para descanso.
     * @param localAtual O nome da cidade onde o veículo está estacionado inicialmente.
     */
    void cadastrarTransporte(const std::string &nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, const std::string &localAtual);

    /**
     * @brief Cadastra um novo passageiro no sistema.
     *
     * @param nome O nome do passageiro.
     * @param localAtual O nome da cidade onde o passageiro está aguardando inicialmente.
     */
    void cadastrarPassageiro(const std::string &nome, const std::string &localAtual);

    /**
     * @brief Inicia uma nova viagem, calculando a rota e gerenciando as escalas.
     *
     * @param nomeTransporte O nome do transporte que fará a rota.
     * @param nomesPassageiros Um vetor com os nomes dos passageiros que embarcarão.
     * @param nomeOrigem O nome da cidade de partida.
     * @param nomeDestino O nome da cidade final da viagem.
     */
    void iniciarViagem(const std::string &nomeTransporte, const std::vector<std::string> &nomesPassageiros, const std::string &nomeOrigem, const std::string &nomeDestino);

    /**
     * @brief Avança o relógio geral do sistema de trânsito.
     *
     * @param horas A quantidade de horas para avançar no tempo, afetando todas as viagens em andamento.
     */
    void avancarHoras(int horas);

    /**
     * @brief Imprime no terminal o painel de estado completo do sistema.
     *
     * Exibe o resumo de cadastros, a localização de todos os passageiros e transportes,
     * além do progresso de cada trecho das viagens ativas.
     */
    void relatarEstado() const;

    /**
     * @brief Busca uma cidade pelo nome.
     *
     * @param nome O nome da cidade desejada.
     * @return Cidade* Retorna o ponteiro para a cidade se encontrada, ou nullptr se não existir.
     */
    Cidade *buscarCidade(const std::string &nome) const;

    /**
     * @brief Busca um transporte pelo nome.
     *
     * @param nome O nome do transporte desejado.
     * @return Transporte* Retorna o ponteiro para o transporte se encontrado, ou nullptr se não existir.
     */
    Transporte *buscarTransporte(const std::string &nome) const;

    /**
     * @brief Busca um passageiro pelo nome.
     *
     * @param nome O nome do passageiro desejado.
     * @return Passageiro* Retorna o ponteiro para o passageiro se encontrado, ou nullptr se não existir.
     */
    Passageiro *buscarPassageiro(const std::string &nome) const;

    /**
     * @brief Calcula a rota mais curta entre duas cidades utilizando o Algoritmo de Dijkstra.
     *
     * @param nomeOrigem Nome da cidade de partida.
     * @param nomeDestino Nome da cidade de destino.
     * @return std::vector<Cidade*> Retorna um vetor contendo a sequência de cidades da melhor rota,
     *         ou um vetor vazio se não houver caminho possível.
     */
    std::vector<Cidade *> calcularMelhorCaminho(const std::string &nomeOrigem, const std::string &nomeDestino) const;

    /**
     * @brief Retorna a distância de um trajeto direto entre duas cidades adjacentes.
     *
     * @param origem Ponteiro para a cidade de origem.
     * @param destino Ponteiro para a cidade de destino.
     * @return int A distância em quilômetros do trajeto que liga as duas cidades.
     */
    int getDistanciaEntre(Cidade *origem, Cidade *destino);

    /**
     * @brief Salva os dados de cadastros (Cidades, Trajetos, Transportes e Passageiros) em um arquivo de texto.
     */
    void salvarDados() const;

    /**
     * @brief Carrega os dados de cadastros do sistema a partir de um arquivo de texto.
     */
    void carregarDados();
};

#endif