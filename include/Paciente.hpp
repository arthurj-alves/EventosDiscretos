#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <string>

class Paciente {
private:
    std::string id; // Identificador único do paciente
    bool alta; // Indica se teve alta após o atendimento
    int anoAdmissao, mesAdmissao, diaAdmissao, horaAdmissao; // Data e hora de admissão
    int grauUrgencia; // Grau de urgência: 0 - Verde, 1 - Amarelo, 2 - Vermelho
    int medidasHospitalares, testesLaboratorio, examesImagem, instrumentosMedicamentos; // Quantidades de procedimentos
    
    
    // Estatística
    double tempoEspera; // Tempo total em espera
    double tempoPermanencia; // Tempo total no hospital (triagem + atendimento + procedimentos)
    double tempoTotal; // Tempo total no hospital (permanência + espera)

    // Hora de saída
    int anoSaida, mesSaida, diaSaida, horaSaida, minutoSaida;

public:
    // Construtor
    Paciente(const std::string& id, bool alta, int ano, int mes, int dia, int hora, 
             int grau, int mh, int tl, int ei, int im);

    // Métodos para calcular tempos
    void calcularTempos(double tempoTriagem, double tempoAtendimento, double tempoMH,
                        double tempoTL, double tempoEI, double tempoIM);

    // Getters
    double getTempoEspera() const;
    double getTempoPermanencia() const;
    double getTempoTotal() const;
    
    // Função para escrever o output do paciente
    void escreverOutput() const;
};

#endif
