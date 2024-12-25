#include "Paciente.hpp"
#include <iostream>

// Construtor padrão
Paciente::Paciente() 
    : id(0), alta(0), grauUrgencia(0), medidasHospitalares(0), testesLaboratorio(0),
      examesImagem(0), instrumentosMedicamentos(0), tempoEspera(0.0), tempoAtendimento(0.0), estadoAtual(0) {}

// Construtor parametrizado
Paciente::Paciente(int id, int alta, int grauUrgencia, int medidas, int testes, int exames, int instrumentos) 
    : id(id), alta(alta), grauUrgencia(grauUrgencia), medidasHospitalares(medidas),
      testesLaboratorio(testes), examesImagem(exames), instrumentosMedicamentos(instrumentos), 
      tempoEspera(0.0), tempoAtendimento(0.0), estadoAtual(0) {}

// Getters
int Paciente::getId() const {
    return id;
}

int Paciente::getAlta() const {
    return alta;
}

int Paciente::getGrauUrgencia() const {
    return grauUrgencia;
}

int Paciente::getEstadoAtual() const {
    return estadoAtual;
}

double Paciente::getTempoEspera() const {
    return tempoEspera;
}

double Paciente::getTempoAtendimento() const {
    return tempoAtendimento;
}

// Setters
void Paciente::setEstadoAtual(int novoEstado) {
    estadoAtual = novoEstado;
}

void Paciente::adicionarTempoEspera(double tempo) {
    tempoEspera += tempo;
}

void Paciente::adicionarTempoAtendimento(double tempo) {
    tempoAtendimento += tempo;
}

// Método para exibir informações do paciente
void Paciente::exibirInformacoes() const {
    std::cout << "ID: " << id
              << ", Alta: " << alta
              << ", Grau de Urgência: " << grauUrgencia
              << ", Estado Atual: " << estadoAtual
              << ", Tempo de Espera: " << tempoEspera
              << ", Tempo de Atendimento: " << tempoAtendimento
              << std::endl;
}
