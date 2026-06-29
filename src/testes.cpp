#include <iostream>
#include <cassert>
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Trajeto.hpp"

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

void test_trajeto() {
    Cidade c1("Natal");
    Cidade c2("Parelhas");

    Trajeto t_valido(&c1, &c2, 'T', 250);
    assert(t_valido.getOrigem() == &c1);
    assert(t_valido.getDestino() == &c2);
    assert(t_valido.getTipo() == 'T');
    assert(t_valido.getDistancia() == 250);

    bool erro_nulo = false;
    try {
        Trajeto t_nulo(nullptr, &c2, 'T', 250);
    } catch (const std::invalid_argument& e) {
        erro_nulo = true;
    }
    assert(erro_nulo == true);

    bool erro_circular = false;
    try {
        Trajeto t_circ(&c1, &c1, 'T', 250);
    } catch (const std::invalid_argument& e) {
        erro_circular = true;
    }
    assert(erro_circular == true);

    bool erro_dist = false;
    try {
        Trajeto t_dist(&c1, &c2, 'A', 0);
    } catch (const std::invalid_argument& e) {
        erro_dist = true;
    }
    assert(erro_dist == true);

    bool erro_tipo = false;
    try {
        Trajeto t_tipo(&c1, &c2, 'X', 250);
    } catch (const std::invalid_argument& e) {
        erro_tipo = true;
    }
    assert(erro_tipo == true);

    std::cout << "[OK] Classe Trajeto" << std::endl;
}

int main()
{
    std::cout << "Iniciando bateria de testes...\n"
              << std::endl;

    test_cidade();
    test_passageiro();
    test_trajeto();

    std::cout << "\nTodos os testes passaram com sucesso!" << std::endl;
    return 0;
}