#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <string>
#include "Suporte.hpp"

class Paciente {
private:
    std::string id; // Identificador único do paciente
    bool alta; // Indica se teve alta após o atendimento
    int* tempoAdmissao; // Data e hora de admissão
    int grauUrgencia; // Grau de urgência: 0 - Verde, 1 - Amarelo, 2 - Vermelho
    int medidasHospitalares, testesLaboratorio, examesImagem, instrumentosMedicamentos; // Quantidades de procedimentos
    
    // Estado
    std::string estadoAtual; 
    int* proximoTempo;

    // Estatística
    double tempoEspera; // Tempo total em espera
    double tempoAtendido; // Tempo total no hospital (triagem + atendimento + procedimentos)
    double tempoTotal; // Tempo total no hospital (permanência + espera)

    // Hora de saída
    int* tempoSaida;

public:
    // Construtor
    Paciente(const std::string& id, bool alta, int ano, int mes, int dia, int hora, 
             int grau, int mh, int tl, int ei, int im);

    // Métodos para calcular tempos de saída do paciente
    void calcularTempos(double tempoTriagem, double tempoAtendimento, double tempoMH,
                        double tempoTL, double tempoEI, double tempoIM);
    int* calcularProximoEvento(int tempoInicio[5], double tempoMedio);

    // Setter
    void setTempoEspera(double tempo);


    // Estado 
    void avancarEstado();        // Avança para o próximo estado
    void setEstado(int estado);  // Define diretamente um estado
    int getEstado() const;       // Retorna o estado atual
    

    // Getters
    double getTempoEspera() const;
    double getTempoAtendido() const;
    double getTempoTotal() const;
    std::string getId() const;
    bool getAlta() const;
    int* getTempoAdmissao() const;
    int getGrauUrgencia() const;
    int getMedidasHospitalares() const;
    int getTestesLaboratorio() const;
    int getExamesImagem() const;
    int getInstrumentosMedicamentos() const;
    
    // Função para escrever o output do paciente
    void escreverOutput() const;
};

#endif

/*
Os estados aceitos são:
fila_triagem
em_triagem
fim_triagem
fila_atendimento
em_atendimento
fim_atendimento
fila_procedimentos
em_procedimentos
alta
*/