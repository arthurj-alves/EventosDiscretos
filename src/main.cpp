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
        
        // Remove o próximo evento do escalonador
        Evento eventoAtual = escalonador.retiraProximoEvento();

        // Avança o relógio para o instante do próximo evento
        relogioAtual = eventoAtual.tempoIncio[3]; // Supondo que tempoIncio[3] é a hora do evento

        // Verifica o próximo estado do paciente
        Paciente* paciente = eventoAtual.paciente;
        paciente->avancarEstado();

        switch (paciente->getEstado()) {
            case 1:
            triagem.alocarUnidade(paciente);
            break;
            case 2:
            atendimento.enfileira(paciente);
            break;
            case 3:
            medidas.enfileira(paciente);
            break;
            case 4:
            testes.enfileira(paciente);
            break;
            case 5:
            imagem.enfileira(paciente);
            break;
            case 6:
            instrumentos.enfileira(paciente);
            break;
            case 7:
            triagem.enfileira(paciente);
            break;
            case 8:
            atendimento.enfileira(paciente);
            break;
            case 9:
            medidas.enfileira(paciente);
            break;
            case 10:
            testes.enfileira(paciente);
            break;
            case 11:
            imagem.enfileira(paciente);
            break;
            case 12:
            instrumentos.enfileira(paciente);
            break;
            case 13:
            triagem.enfileira(paciente);
            break;
            case 14:
            std::cout << "Paciente " << paciente->getId() << " recebeu alta." << std::endl;
            break;
            default:
            std::cerr << "Erro: Estado inválido do paciente " << paciente->getId() << std::endl;
            break;
        }

        // Para cada fila de espera que tenha pacientes
        Procedimento* procedimentos[] = { &triagem, &atendimento, &medidas, &testes, &imagem, &instrumentos };
        for (Procedimento* procedimento : procedimentos) {
            // Se há unidade disponível para execução
            if (!procedimento->filaVazia() && procedimento->temUnidadesLivres()) {
                // Escalonar o evento de execução do serviço
                Paciente* proxPaciente = procedimento->desenfileira();
                escalonador.insereEvento(proxPaciente);
                procedimento->alocarUnidade(proxPaciente);
            }
        }

        // Atualizar as estatísticas
        // (Implementar a lógica de atualização de estatísticas conforme necessário)
    }

    // Gerar relatórios de estatísticas
    escalonador.geraRelatorios();

    return 0;
}
