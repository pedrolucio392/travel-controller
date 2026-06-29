#include <iostream>
#include <cassert>
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Trajeto.hpp"
#include "Transporte.hpp"

void test_cidade()
{
    Cidade c("Metropolis");

    assert(c.getNome() == "Metropolis");

    std::cout << "[OK] Classe Cidade" << std::endl;
}

void test_passageiro()
{
    Cidade origem("Metropolis");
    Cidade destino("Gotham");

    Passageiro p("Arthur", &origem);

    assert(p.getNome() == "Arthur");
    assert(p.getLocalAtual() == &origem);

    assert(p.getLocalAtual()->getNome() == "Metropolis");

    p.setLocalAtual(&destino);
    assert(p.getLocalAtual() == &destino);
    assert(p.getLocalAtual()->getNome() == "Gotham");

    std::cout << "[OK] Classe Passageiro" << std::endl;
}

void test_trajeto()
{
    Cidade c1("Natal");
    Cidade c2("Parelhas");

    Trajeto t_valido(&c1, &c2, 'T', 250);
    assert(t_valido.getOrigem() == &c1);
    assert(t_valido.getDestino() == &c2);
    assert(t_valido.getTipo() == 'T');
    assert(t_valido.getDistancia() == 250);

    bool erro_nulo = false;
    try
    {
        Trajeto t_nulo(nullptr, &c2, 'T', 250);
    }
    catch (const std::invalid_argument &e)
    {
        erro_nulo = true;
    }
    assert(erro_nulo == true);

    bool erro_circular = false;
    try
    {
        Trajeto t_circ(&c1, &c1, 'T', 250);
    }
    catch (const std::invalid_argument &e)
    {
        erro_circular = true;
    }
    assert(erro_circular == true);

    bool erro_dist = false;
    try
    {
        Trajeto t_dist(&c1, &c2, 'A', 0);
    }
    catch (const std::invalid_argument &e)
    {
        erro_dist = true;
    }
    assert(erro_dist == true);

    bool erro_tipo = false;
    try
    {
        Trajeto t_tipo(&c1, &c2, 'X', 250);
    }
    catch (const std::invalid_argument &e)
    {
        erro_tipo = true;
    }
    assert(erro_tipo == true);

    std::cout << "[OK] Classe Trajeto" << std::endl;
}

void test_transporte()
{
    Cidade c1("Natal");
    Cidade c2("Parelhas");

    Transporte onibus("Jardinense", 'T', 40, 80, 200, 2, &c1);

    assert(onibus.getNome() == "Jardinense");
    assert(onibus.getTipo() == 'T');
    assert(onibus.getCapacidade() == 40);
    assert(onibus.getVelocidade() == 80);
    assert(onibus.getDistanciaEntreDescansos() == 200);
    assert(onibus.getTempoDescanso() == 2);
    assert(onibus.getTempoDescansoAtual() == 0);
    assert(onibus.getLocalAtual() == &c1);

    onibus.setLocalAtual(&c2);
    assert(onibus.getLocalAtual() == &c2);

    bool erro_tipo = false;
    try
    {
        Transporte erro1("Opcional", 'X', 1, 20, 10, 1, &c1);
    }
    catch (const std::invalid_argument &e)
    {
        erro_tipo = true;
    }
    assert(erro_tipo == true);

    bool erro_cap = false;
    try
    {
        Transporte erro2("Carona", 'T', 0, 80, 100, 1, &c1);
    }
    catch (const std::invalid_argument &e)
    {
        erro_cap = true;
    }
    assert(erro_cap == true);

    bool erro_vel = false;
    try
    {
        Transporte erro3("Carroça", 'T', 4, 0, 100, 1, &c1);
    }
    catch (const std::invalid_argument &e)
    {
        erro_vel = true;
    }
    assert(erro_vel == true);

    bool erro_nulo = false;
    try
    {
        Transporte erro4("Jegue véi", 'T', 100, 50, 100, 1, nullptr);
    }
    catch (const std::invalid_argument &e)
    {
        erro_nulo = true;
    }
    assert(erro_nulo == true);

    std::cout << "[OK] Classe Transporte" << std::endl;
}

int main()
{
    std::cout << "Iniciando bateria de testes...\n"
              << std::endl;

    test_cidade();
    test_passageiro();
    test_trajeto();
    test_transporte();

    std::cout << "\nTodos os testes passaram com sucesso!" << std::endl;
    return 0;
}