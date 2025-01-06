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
    int estadoAtual; // 0 - 14;
    int* proximoTempo;

    // Estatística
    double tempoEspera; // Tempo total em espera
    double tempoPermanencia; // Tempo total no hospital (triagem + atendimento + procedimentos)
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
    double getTempoPermanencia() const;
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

Crie um .hpp e um .cpp de um tad de paciente, ele deve conter seu construtor da seguinte maneira:

Paciente(const std::string& id, bool alta, int ano, int mes, int dia, int hora, int grau, int mh, int tl, int ei, int im);

e seu private deve ser assim:

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

outras funções necessárias: bool de calcular estatísticas, get de tempo de espera, get tempo de atendimento, get tempo total, escrever o output conforme o output almejado para um paciênte unico */