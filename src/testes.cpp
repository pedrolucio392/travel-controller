#include <iostream>
#include <cassert>
#include "Cidade.hpp"
#include "Passageiro.hpp"

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

int main()
{
    std::cout << "Iniciando bateria de testes...\n"
              << std::endl;

    test_cidade();
    test_passageiro();

    std::cout << "\nTodos os testes passaram com sucesso!" << std::endl;
    return 0;
}