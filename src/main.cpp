#include "Paciente.hpp"
#include "Procedimento.hpp"
#include "Fila.hpp"
#include "Escalonador.hpp"
#include <iostream>

int main() {
    // Inicializa Condição de Término para FALSO
    bool condicaoTermino = false;

    // Inicializa as variáveis de estado do sistema
    Escalonador escalonador;
    Procedimento triagem(0.2, 3);
    Procedimento atendimento(0.5, 5);
    Procedimento medidas(0.1, 10);
    Procedimento testes(0.05, 5);
    Procedimento imagem(0.5, 20);
    Procedimento instrumentos(0.05, 5);
    Procedimento* procedimentos[] = { &triagem, &atendimento, &medidas, &testes, &imagem, &instrumentos };
    escalonador.inicializaProcedimentos(procedimentos);

    // Inicializa o Relógio
    double relogioAtual = 0.0;

    // Escalona a chegada de pacientes
    Paciente paciente1("0009600008", false, 2017, 3, 21, 2, 1, 5, 43, 2, 110);
    Paciente paciente2("0009600009", false, 2017, 3, 21, 2, 0, 3, 1, 5, 21);
    Paciente* pacientes[] = { &paciente1, &paciente2 };
    escalonador.inserePaciente(pacientes, 2);

    // Enquanto houver eventos ou filas não vazias
    while (!escalonador.vazio()) {
        
      
    }

    // Gerar relatórios de estatísticas
    escalonador.geraRelatorios();

    return 0;
}
