#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <string>

class Paciente {
private:
    int id;                 // Identificador único do paciente
    int alta;               // Indicador de alta (0 = não, 1 = sim)
    int grauUrgencia;       // Grau de urgência (0 = verde, 1 = amarelo, 2 = vermelho)
    int medidasHospitalares; // Número de medidas hospitalares
    int testesLaboratorio;   // Número de testes de laboratório
    int examesImagem;        // Número de exames de imagem
    int instrumentosMedicamentos; // Número de instrumentos/medicamentos
    double tempoEspera;      // Tempo total em filas
    double tempoAtendimento; // Tempo total sendo atendido
    int estadoAtual;         // Estado atual do paciente (0 a 14)

public:
    // Construtor padrão
    Paciente();

    // Construtor parametrizado
    Paciente(int id, int alta, int grauUrgencia, int medidas, int testes, int exames, int instrumentos);

    // Métodos de acesso (getters)
    int getId() const;
    int getAlta() const;
    int getGrauUrgencia() const;
    int getEstadoAtual() const;
    double getTempoEspera() const;
    double getTempoAtendimento() const;

    // Métodos de modificação (setters)
    void setEstadoAtual(int novoEstado);
    void adicionarTempoEspera(double tempo);
    void adicionarTempoAtendimento(double tempo);

    // Método para exibir informações do paciente (para debug)
    void exibirInformacoes() const;
};

#endif // PACIENTE_HPP
