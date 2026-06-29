#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

#include <string>

class Cidade;

class Transporte
{
private:
    std::string nome;
    char tipo;                     // 'A' para Aquático, 'T' para Terrestre
    int capacidade;                // número de passageiros
    int velocidade;                // km/h
    int distancia_entre_descansos; // em km
    int tempo_de_descanso;         // em horas
    int tempo_de_descanso_atual;   // em horas
    Cidade *localAtual;

public:
    Transporte(const std::string& nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade *localAtual);
    std::string getNome() const;
    char getTipo() const;
    int getCapacidade() const;
    int getVelocidade() const;
    int getDistanciaEntreDescansos() const;
    int getTempoDescanso() const;
    int getTempoDescansoAtual() const;
    Cidade *getLocalAtual() const;
    void setLocalAtual(Cidade *local);
};

#endif