#ifndef CONTROLE_DE_TRANSITO_HPP
#define CONTROLE_DE_TRANSITO_HPP

#include <string>
#include <vector>

class Cidade;
class Trajeto;
class Transporte;
class Passageiro;
class Viagem;

class ControladorDeTransito
{
private:
    std::vector<Cidade *> cidades;
    std::vector<Trajeto *> trajetos;
    std::vector<Transporte *> transportes;
    std::vector<Passageiro *> passageiros;
    std::vector<Viagem *> viagens;

public:
    void cadastrarCidade(const std::string &nome);
    void cadastrarTrajeto(const std::string &nomeOrigem, const std::string &nomeDestino, char tipo, int distancia);
    void cadastrarTransporte(const std::string &nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, const std::string &localAtual);
    void cadastrarPassageiro(const std::string &nome, const std::string &localAtual);
    void iniciarViagem(const std::string &nomeTransporte, const std::vector<std::string> &nomesPassageiros, const std::string &nomeOrigem, const std::string &nomeDestino);
    void avancarHoras(int horas);
    void relatarEstado() const;

    Cidade *buscarCidade(const std::string &nome) const;
    Transporte *buscarTransporte(const std::string &nome) const;
    Passageiro *buscarPassageiro(const std::string &nome) const;

    // Retorna um vetor com os ponteiros das cidades que formam o caminho mais curto
    std::vector<Cidade *> calcularMelhorCaminho(const std::string &nomeOrigem, const std::string &nomeDestino) const;
};

#endif