#include <iostream>
#include <cassert>
#include <vector>
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Trajeto.hpp"
#include "Transporte.hpp"
#include "Viagem.hpp"
#include "ControladorDeTransito.hpp"

// Esqueci o danado dos comentários, vou começar da parte de viagem e o resto faço dps

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

void test_viagem()
{
    Cidade c1("Natal");
    Cidade c2("Parelhas");

    // Capacidade de 2 pessoas
    Transporte onibus("Jardinense", 'T', 2, 80, 200, 2, &c1);

    Passageiro p1("Roberto", &c1);
    Passageiro p2("Carlos", &c1);
    Passageiro p3("Lady Laura", &c1);

    std::vector<Passageiro *> passageiros_validos = {&p1, &p2};
    std::vector<Passageiro *> passageiros_excedentes = {&p1, &p2, &p3};

    // Teste de Sucesso
    Viagem v_valida(&onibus, passageiros_validos, &c1, &c2);
    assert(v_valida.isEmAndamento() == false);

    v_valida.iniciarViagem();
    assert(v_valida.isEmAndamento() == true);

    // Se avançar horas não gerar erro, tá massa
    v_valida.avancarHoras(5);

    // Teste de Falha: Construtor com ponteiros nulos
    bool erro_nulo = false;
    try
    {
        Viagem v_nula(nullptr, passageiros_validos, &c1, &c2);
    }
    catch (const std::invalid_argument &e)
    {
        erro_nulo = true;
    }
    assert(erro_nulo == true);

    // Teste de Falha: Transporte no local errado
    Transporte aviao("Jato", 'A', 50, 800, 1000, 1, &c2);
    Viagem v_local_errado(&aviao, passageiros_validos, &c1, &c2);
    bool erro_local = false;
    try
    {
        v_local_errado.iniciarViagem();
    }
    catch (const std::logic_error &e)
    {
        erro_local = true;
    }
    assert(erro_local == true);

    // Teste de Falha: Superlotação
    Viagem v_lotada(&onibus, passageiros_excedentes, &c1, &c2);
    bool erro_lotacao = false;
    try
    {
        v_lotada.iniciarViagem();
    }
    catch (const std::logic_error &e)
    {
        erro_lotacao = true;
    }
    assert(erro_lotacao == true);

    // Avançar tempo antes de iniciar
    Viagem v_nao_iniciada(&onibus, passageiros_validos, &c1, &c2);
    bool erro_avanco_estado = false;
    try
    {
        v_nao_iniciada.avancarHoras(2);
    }
    catch (const std::logic_error &e)
    {
        erro_avanco_estado = true;
    }
    assert(erro_avanco_estado == true);

    // Teste de Falha: Avançar zero ou horas negativas
    bool erro_avanco_tempo = false;
    try
    {
        v_valida.avancarHoras(-3);
    }
    catch (const std::invalid_argument &e)
    {
        erro_avanco_tempo = true;
    }
    assert(erro_avanco_tempo == true);

    std::cout << "[OK] Classe Viagem" << std::endl;
}

void test_controlador()
{
    ControladorDeTransito ctrl;

    // Teste sucesso
    ctrl.cadastrarCidade("Natal");
    ctrl.cadastrarCidade("Parelhas");
    ctrl.cadastrarTrajeto("Natal", "Parelhas", 'T', 300);
    ctrl.cadastrarTransporte("Jardinense véi de guerra", 'T', 40, 80, 200, 2, "Natal");
    ctrl.cadastrarPassageiro("Gandalf", "Natal");
    ctrl.cadastrarPassageiro("Aragorn", "Natal");

    // Teste de Falha: Cadastro com referência inexistente
    bool erro_trajeto = false;
    try
    {
        // Tenta criar trajeto para Fortaleza, que não foi cadastrada
        ctrl.cadastrarTrajeto("Natal", "Fortaleza", 'T', 500);
    }
    catch (const std::invalid_argument &e)
    {
        erro_trajeto = true;
    }
    assert(erro_trajeto == true);

    // Teste de Sucesso: Iniciar Viagem Válida
    std::vector<std::string> passageiros_validos = {"Gandalf", "Aragorn"};
    bool erro_viagem_valida = false;
    try
    {
        ctrl.iniciarViagem("Jardinense véi de guerra", passageiros_validos, "Natal", "Parelhas");
    }
    catch (const std::exception &e)
    {
        erro_viagem_valida = true;
    }
    assert(erro_viagem_valida == false); // Não deve dar erro

    // Teste de Falha: Iniciar viagem com passageiro inexistente
    std::vector<std::string> passageiros_invalidos = {"Bolsonaro", "Xandão"};
    bool erro_passageiro_fantasma = false;
    try
    {
        ctrl.iniciarViagem("Camburão da federal", passageiros_invalidos, "Natal", "Recife");
    }
    catch (const std::invalid_argument &e)
    {
        erro_passageiro_fantasma = true;
    }
    assert(erro_passageiro_fantasma == true);

    // Teste de Sucesso: Avançar Tempo
    bool erro_avancar_tempo_valido = false;
    try
    {
        ctrl.avancarHoras(3); // Deve passar silenciosamente
    }
    catch (const std::exception &e)
    {
        erro_avancar_tempo_valido = true;
    }
    assert(erro_avancar_tempo_valido == false);

    // Teste de Falha: Tempo Negativo
    bool erro_tempo_invalido = false;
    try
    {
        ctrl.avancarHoras(-5);
    }
    catch (const std::invalid_argument &e)
    {
        erro_tempo_invalido = true;
    }
    assert(erro_tempo_invalido == true);

    std::cout << "[OK] Classe ControladorDeTransito" << std::endl;
}

void test_dijkstra()
{
    ControladorDeTransito ctrl;

    // Montando o mapa de teste
    ctrl.cadastrarCidade("Natal");
    ctrl.cadastrarCidade("Santa Cruz");
    ctrl.cadastrarCidade("Currais Novos");
    ctrl.cadastrarCidade("Parelhas");
    ctrl.cadastrarCidade("Caico"); // Cidade sem estradas

    // Cadastro de trajetos
    ctrl.cadastrarTrajeto("Natal", "Santa Cruz", 'T', 100);
    ctrl.cadastrarTrajeto("Natal", "Currais Novos", 'T', 150);
    ctrl.cadastrarTrajeto("Santa Cruz", "Parelhas", 'T', 200);
    ctrl.cadastrarTrajeto("Currais Novos", "Parelhas", 'T', 50);

    // tesde de sucessop
    // O algoritmo deve escolher ir por Currais Novos e ignorar Santa cruz

    std::vector<Cidade *> rota = ctrl.calcularMelhorCaminho("Natal", "Parelhas");

    // O vetor deve ter exatamente 3 cidades: Natal -> Currais Novos -> Parelhas
    assert(rota.size() == 3);
    assert(rota[0]->getNome() == "Natal");
    assert(rota[1]->getNome() == "Currais Novos");
    assert(rota[2]->getNome() == "Parelhas");

    // Teste rota Impossível (Destino Isolado)
    std::vector<Cidade *> rota_isolada = ctrl.calcularMelhorCaminho("Natal", "Caico");
    assert(rota_isolada.size() == 0); // Como não há estrada, deve retornar vetor vazio

    // Teste viagem para o mesmo lugar
    std::vector<Cidade *> rota_mesma = ctrl.calcularMelhorCaminho("Natal", "Natal");
    assert(rota_mesma.size() == 1); // A rota é apenas a própria cidade de origem
    assert(rota_mesma[0]->getNome() == "Natal");

    // Teste cidades Inexistentes
    bool erro_cidade_falsa = false;
    try
    {
        ctrl.calcularMelhorCaminho("Natal", "Gotham");
    }
    catch (const std::invalid_argument &e)
    {
        erro_cidade_falsa = true;
    }
    assert(erro_cidade_falsa == true);

    std::cout << "[OK] Algoritmo de Dijkstra (calcularMelhorCaminho)" << std::endl;
}

int main()
{
    std::cout << "Iniciando bateria de testes...\n"
              << std::endl;

    test_cidade();
    test_passageiro();
    test_trajeto();
    test_transporte();
    test_viagem();
    test_controlador();
    test_dijkstra();

    std::cout << "\nTodos os testes passaram com sucesso!" << std::endl;
    return 0;
}