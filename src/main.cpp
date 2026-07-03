/**
 * @file main.cpp
 * @brief Ponto de entrada do Sistema de Gestão de Trânsito.
 *
 * Este arquivo contém o loop principal da Interface de Linha de Comando (CLI).
 * Ele lida com a interação direta do usuário, recebendo os inputs,
 * tratando o buffer do teclado e repassando os comandos para o ControladorDeTransito.
 */

#include <iostream>
#include <string>
#include <limits>
#include "ControladorDeTransito.hpp"

/**
 * @brief Exibe o menu principal de opções no terminal.
 */
void exibirMenu()
{
    std::cout << "\n===================================" << std::endl;
    std::cout << "    SISTEMA DE GESTAO DE TRANSITO  " << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "1. Cadastrar Cidade" << std::endl;
    std::cout << "2. Cadastrar Trajeto" << std::endl;
    std::cout << "3. Cadastrar Transporte" << std::endl;
    std::cout << "4. Cadastrar Passageiro" << std::endl;
    std::cout << "5. Iniciar Nova Viagem" << std::endl;
    std::cout << "6. Avancar Tempo (Horas)" << std::endl;
    std::cout << "7. Relatar Estado do Sistema" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Escolha uma opcao: ";
}

/**
 * @brief Lê uma linha inteira de texto do terminal, lidando corretamente com espaços.
 *
 * Utiliza std::ws para limpar buffers residuais (como "Enters" perdidos)
 * antes de invocar o std::getline, evitando que o programa pule a leitura.
 *
 * @return std::string A string completa digitada pelo usuário.
 */
std::string lerTexto()
{
    std::string texto;
    std::cin >> std::ws; // Descarta espaços em branco ou enters sobrando no buffer
    std::getline(std::cin, texto);
    return texto;
}

/**
 * @brief Função principal do programa.
 *
 * Inicializa o Controlador de Trânsito, carrega os dados persistidos
 * e mantém o loop do menu ativo até que o usuário decida sair.
 *
 * @return int Retorna 0 ao finalizar com sucesso.
 */
int main()
{
    ControladorDeTransito ctrl;

    // Carregar dados ao abrir
    ctrl.carregarDados();

    int opcao = -1;

    do
    {
        exibirMenu();

        // Evitar letras no lugar de números causando loop infinito
        if (!(std::cin >> opcao))
        {
            std::cin.clear();                                                   // Limpa a flag de erro
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta a entrada ruim
            opcao = -1;                                                         // Força cair no default do switch
        }

        switch (opcao)
        {
        case 1:
        {
            std::cout << "\n--- CADASTRAR CIDADE ---" << std::endl;
            std::cout << "Nome da Cidade: ";
            std::string nome = lerTexto();

            try
            {
                ctrl.cadastrarCidade(nome);
                std::cout << "[OK] Cidade '" << nome << "' cadastrada com sucesso!\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "[ERRO] " << e.what() << std::endl;
            }
            break;
        }
        case 2:
        {
            std::cout << "\n--- CADASTRAR TRAJETO ---" << std::endl;
            std::cout << "Cidade de Origem: ";
            std::string origem = lerTexto();

            std::cout << "Cidade de Destino: ";
            std::string destino = lerTexto();

            std::cout << "Tipo (A para Aquático, T para Terrestre): ";
            char tipo;
            std::cin >> tipo;

            std::cout << "Distancia (em km): ";
            int distancia;
            std::cin >> distancia;

            try
            {
                ctrl.cadastrarTrajeto(origem, destino, tipo, distancia);
                std::cout << "[OK] Trajeto de " << origem << " para " << destino << " cadastrado com sucesso!\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "[ERRO] " << e.what() << std::endl;
            }
            break;
        }
        case 3:
        {
            std::cout << "\n--- CADASTRAR TRANSPORTE ---" << std::endl;
            std::cout << "Nome do Veiculo (ex: Jumento): ";
            std::string nome = lerTexto();

            std::cout << "Tipo (A para aquático, T para Terrestre): ";
            char tipo;
            std::cin >> tipo;

            std::cout << "Capacidade maxima de Passageiros: ";
            int cap;
            std::cin >> cap;

            std::cout << "Velocidade media (km/h): ";
            int vel;
            std::cin >> vel;

            std::cout << "Distancia maxima sem descanso (km): ";
            int distDescanso;
            std::cin >> distDescanso;

            std::cout << "Tempo de descanso (horas): ";
            int tempoDescanso;
            std::cin >> tempoDescanso;

            std::cout << "Local Atual (Nome da Cidade onde esta estacionado): ";
            std::string local = lerTexto();

            try
            {
                ctrl.cadastrarTransporte(nome, tipo, cap, vel, distDescanso, tempoDescanso, local);
                std::cout << "[OK] Transporte '" << nome << "' cadastrado e estacionado em " << local << "!\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "[ERRO] " << e.what() << std::endl;
            }
            break;
        }
        case 4:
        {
            std::cout << "\n--- CADASTRAR PASSAGEIRO ---" << std::endl;
            std::cout << "Nome do Passageiro: ";
            std::string nome = lerTexto();

            std::cout << "Local Atual (Nome da Cidade onde esta aguardando): ";
            std::string local = lerTexto();

            try
            {
                ctrl.cadastrarPassageiro(nome, local);
                std::cout << "[OK] Passageiro '" << nome << "' cadastrado com sucesso em " << local << "!\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "[ERRO] " << e.what() << std::endl;
            }
            break;
        }
        case 5:
        {
            std::cout << "\n--- INICIAR NOVA VIAGEM ---" << std::endl;

            std::cout << "Nome do Transporte: ";
            std::string nomeTransporte = lerTexto();

            std::cout << "Cidade de Origem: ";
            std::string origem = lerTexto();

            std::cout << "Cidade de Destino: ";
            std::string destino = lerTexto();

            std::vector<std::string> nomesPassageiros;
            std::cout << "Digite os nomes dos passageiros (pressione 0 para finalizar):" << std::endl;

            while (true)
            {
                std::cout << "Passageiro " << (nomesPassageiros.size() + 1) << ": ";
                std::string nomePassageiro = lerTexto();

                if (nomePassageiro == "0")
                {
                    break; // Sai do laço se o usuário apertar 0
                }
                nomesPassageiros.push_back(nomePassageiro);
            }

            if (nomesPassageiros.empty())
            {
                std::cout << "[AVISO] Viagem cancelada: pelo menos um passageiro eh obrigatorio." << std::endl;
                break;
            }

            try
            {
                std::cout << "\nCalculando rota com Dijkstra e montando escalas..." << std::endl;
                ctrl.iniciarViagem(nomeTransporte, nomesPassageiros, origem, destino);
                std::cout << "[OK] Viagem iniciada com sucesso! O veiculo '" << nomeTransporte << "' ja esta a caminho." << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cout << "\n[ERRO] Nao foi possivel iniciar a viagem: " << e.what() << std::endl;
            }
            break;
        }
        case 6:
        {
            std::cout << "\n--- AVANÇAR TEMPO ---" << std::endl;
            std::cout << "Quantas horas deseja avancar? ";
            int horas;
            std::cin >> horas;

            try
            {
                ctrl.avancarHoras(horas);
                std::cout << "[OK] O tempo avancou " << horas << " horas!\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "[ERRO] " << e.what() << std::endl;
            }
            break;
        }
        case 7:
        {
            // Mostra o relatório construido na classe Viagem
            ctrl.relatarEstado();
            break;
        }
        case 0:
            std::cout << "Encerrando o sistema..." << std::endl;
            // Salvar dados ao fechar
            ctrl.salvarDados();
            break;
        default:
            std::cout << "[AVISO] Opcao invalida! Tente novamente." << std::endl;
        }

    } while (opcao != 0);

    return 0;
}