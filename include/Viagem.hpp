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

public:
    Viagem(Transporte *transporte, std::vector<Passageiro *> passageiros, Cidade *origem, Cidade *destino);
    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado() const;
    bool isEmAndamento() const;
};

#endif