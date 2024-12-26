#include <iostream>
#include <fstream>
#include <sstream>
#include "SistemaEscalonamento.hpp"
#include "Paciente.hpp"

int main() {
    // Arquivo de entrada (pode ser substituído por std::cin para leitura direta)
    std::ifstream entrada("../entrada.csv");
    if (!entrada) {
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
        return 1;
    }

    double tempoTriagem, tempoAtendimento, tempoMH, tempoTL, tempoEI, tempoIM;
    int unidadesTriagem, unidadesAtendimento, unidadesMH, unidadesTL, unidadesEI, unidadesIM;
    int numeroPacientes;

    // Lendo tempos e unidades dos procedimentos
    entrada >> tempoTriagem >> unidadesTriagem;
    entrada >> tempoAtendimento >> unidadesAtendimento;
    entrada >> tempoMH >> unidadesMH;
    entrada >> tempoTL >> unidadesTL;
    entrada >> tempoEI >> unidadesEI;
    entrada >> tempoIM >> unidadesIM;

    // Criando o sistema de escalonamento
    SistemaEscalonamento sistema(tempoTriagem, unidadesTriagem,
                                  tempoAtendimento, unidadesAtendimento,
                                  tempoMH, unidadesMH,
                                  tempoTL, unidadesTL,
                                  tempoEI, unidadesEI,
                                  tempoIM, unidadesIM);

    // Lendo o número de pacientes
    entrada >> numeroPacientes;

    // Lendo informações de cada paciente e adicionando ao sistema
    for (int i = 0; i < numeroPacientes; ++i) {
        std::string id;
        bool alta;
        int ano, mes, dia, hora, grauUrgencia;
        int medidasHospitalares, testesLaboratorio, examesImagem, instrumentosMedicamentos;

        entrada >> id >> alta >> ano >> mes >> dia >> hora >> grauUrgencia
                >> medidasHospitalares >> testesLaboratorio >> examesImagem >> instrumentosMedicamentos;

        Paciente paciente(id, alta, ano, mes, dia, hora, grauUrgencia,
                          medidasHospitalares, testesLaboratorio, examesImagem, instrumentosMedicamentos);

        sistema.adicionarPaciente(paciente);
    }

    // Iniciando a simulação
    sistema.simular();

    return 0;
}
