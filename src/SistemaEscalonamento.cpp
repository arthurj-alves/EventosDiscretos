// Arquivo: SistemaEscalonamento.cpp
#include "SistemaEscalonamento.hpp"

// Construtor
SistemaEscalonamento::SistemaEscalonamento(double tempoTriagem, int unidadesTriagem,
                                           double tempoAtendimento, int unidadesAtendimento,
                                           double tempoMH, int unidadesMH,
                                           double tempoTL, int unidadesTL,
                                           double tempoEI, int unidadesEI,
                                           double tempoIM, int unidadesIM)
    : triagem(tempoTriagem, unidadesTriagem),
      atendimento(tempoAtendimento, unidadesAtendimento),
      medidasHospitalares(tempoMH, unidadesMH),
      testesLaboratorio(tempoTL, unidadesTL),
      examesImagem(tempoEI, unidadesEI),
      instrumentosMedicamentos(tempoIM, unidadesIM),
      relogioSimulacao(0) {}

// Adiciona um paciente à fila inicial (triagem)
void SistemaEscalonamento::adicionarPaciente(const Paciente& paciente) {
    filaTriagem.enfileirar(paciente);
}

// Processa uma fila e avança a simulação
void SistemaEscalonamento::processarFila(Fila& fila, Procedimento& procedimento, const std::string& nomeProcedimento) {
    if (!fila.estaVazia() && procedimento.temUnidadesLivres()) {
        Paciente paciente = fila.desenfileirar();
        procedimento.alocarUnidade();
        std::cout << "Processando " << nomeProcedimento << " para paciente." << std::endl;
        procedimento.desalocarUnidade();
    }
}

// Simula o funcionamento do sistema
void SistemaEscalonamento::simular() {
    while (!filaTriagem.estaVazia() || !filaAtendimento.estaVazia() ||
           !filaMedidas.estaVazia() || !filaTestes.estaVazia() ||
           !filaExames.estaVazia() || !filaInstrumentos.estaVazia()) {

        processarFila(filaTriagem, triagem, "Triagem");
        processarFila(filaAtendimento, atendimento, "Atendimento");
        processarFila(filaMedidas, medidasHospitalares, "Medidas Hospitalares");
        processarFila(filaTestes, testesLaboratorio, "Testes Laboratório");
        processarFila(filaExames, examesImagem, "Exames de Imagem");
        processarFila(filaInstrumentos, instrumentosMedicamentos, "Instrumentos e Medicamentos");

        relogioSimulacao += 0.1; // Incrementa o relógio da simulação (em unidades arbitrárias)
    }
}
