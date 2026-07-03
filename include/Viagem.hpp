#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include <string>
#include <vector>

class Cidade;
class Transporte;
class Passageiro;

class Viagem
{
private:
    Transporte *transporte;
    std::vector<Passageiro *> passageiros;
    Cidade *origem;
    Cidade *destino;
    Viagem *proxima;
    int horasEmTransito;
    bool emAndamento;
    int distanciaDoTrecho;   // A distância apenas entre a origem e o destino DESTA viagem específica
    int distanciaPercorrida; // Quanto já andamos neste trecho
    int distanciaDesdeUltimoDescanso;

public:
    Viagem(Transporte *transporte, std::vector<Passageiro *> passageiros, Cidade *origem, Cidade *destino);
    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado() const;
    bool isEmAndamento() const;
    Viagem* getProxima() const;

    void setProxima(Viagem *proximaViagem);
    void setDistanciaDoTrecho(int distancia);
};

#endif