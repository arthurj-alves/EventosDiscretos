// Arquivo: SistemaEscalonamento.hpp
#ifndef SISTEMA_ESCALONAMENTO_HPP
#define SISTEMA_ESCALONAMENTO_HPP

#include "Paciente.hpp"
#include "Fila.hpp"
#include "Procedimento.hpp"
#include <iostream>

class SistemaEscalonamento {
private:
    Procedimento triagem;
    Procedimento atendimento;
    Procedimento medidasHospitalares;
    Procedimento testesLaboratorio;
    Procedimento examesImagem;
    Procedimento instrumentosMedicamentos;

    Fila filaTriagem;
    Fila filaAtendimento;
    Fila filaMedidas;
    Fila filaTestes;
    Fila filaExames;
    Fila filaInstrumentos;

    double relogioSimulacao; // Tempo atual da simulação

public:
    // Construtor
    SistemaEscalonamento(double tempoTriagem, int unidadesTriagem,
                         double tempoAtendimento, int unidadesAtendimento,
                         double tempoMH, int unidadesMH,
                         double tempoTL, int unidadesTL,
                         double tempoEI, int unidadesEI,
                         double tempoIM, int unidadesIM);

    // Métodos principais
    void adicionarPaciente(const Paciente& paciente);
    void simular();

private:
    void processarFila(Fila& fila, Procedimento& procedimento, const std::string& nomeProcedimento);
};

#endif // SISTEMA_ESCALONAMENTO_HPP
