#include "Paciente.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>

// Construtor
Paciente::Paciente(const std::string& id, bool alta, int ano, int mes, int dia, int hora, 
                   int grau, int mh, int tl, int ei, int im) 
    : id(id), alta(alta), grauUrgencia(grau), medidasHospitalares(mh), testesLaboratorio(tl), 
      examesImagem(ei), instrumentosMedicamentos(im), estadoAtual(0), tempoEspera(0), tempoPermanencia(0) {

    tempoAdmissao[0] = ano;
    tempoAdmissao[1] = mes;
    tempoAdmissao[2] = dia;
    tempoAdmissao[3] = hora;

    estadoAtual = 2;

    // Validar grau de urgência
    if (grauUrgencia < 0 || grauUrgencia > 2) {
        throw std::invalid_argument("Grau de urgência deve ser entre 0 e 2.");
    }

    // Validar data
    if (ano < 0 || mes < 1 || mes > 12 || dia < 1 || dia > 31 || hora < 0 || hora > 23) {
        throw std::invalid_argument("Data ou hora inválida.");
    }

    // Array com o número de dias em cada mês (não considerando anos bissextos)
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Ajusta para anos bissextos
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasPorMes[1] = 29;
    }

    if (dia > diasPorMes[mes - 1]) {
        throw std::invalid_argument("Dia inválido para o mês especificado.");
    }

    // Validar atividades
    if (mh < 0 || tl < 0 || ei < 0 || im < 0) {
        throw std::invalid_argument("Valores de atividades não podem ser negativos.");
    }
}

// Calcula os tempos com base nos parâmetros fornecidos
void Paciente::calcularTempos(double tempoTriagem, double tempoAtendimento, double tempoMH,
                              double tempoTL, double tempoEI, double tempoIM) {
    // Calcula o tempo total de permanência
    tempoPermanencia = tempoTriagem + tempoAtendimento + 
                       (medidasHospitalares * tempoMH) + 
                       (testesLaboratorio * tempoTL) + 
                       (examesImagem * tempoEI) + 
                       (instrumentosMedicamentos * tempoIM);

    tempoTotal = tempoPermanencia + tempoEspera;

    // Converte tempo total de horas para minutos
    int totalMinutos = static_cast<int>(tempoTotal * 60);
    int minutosExtras = totalMinutos % 60;  // Minutos restantes
    int totalHoras = totalMinutos / 60;
    int horasExtras = totalHoras % 24;      // Horas restantes
    int diasExtras = totalHoras / 24;       // Dias inteiros adicionais

    // Ajusta a data e hora de saída
    int dia = tempoAdmissao[2] + diasExtras;
    int mes = tempoAdmissao[1];
    int ano = tempoAdmissao[0];

    // Array com número de dias por mês
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Ajusta para anos bissextos
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasPorMes[1] = 29;
    }

    // Calcula a transição de dias, meses e anos
    while (dia > diasPorMes[mes - 1]) {
        dia -= diasPorMes[mes - 1];
        mes++;
        if (mes > 12) {
            mes = 1;
            ano++;
            // Reajusta para anos bissextos
            if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
                diasPorMes[1] = 29;
            } else {
                diasPorMes[1] = 28;
            }
        }
    }

    // Calcula hora e minuto de saída
    int hora = tempoAdmissao[4] + horasExtras;
    int minuto = minutosExtras;

    if (hora >= 24) {
        hora -= 24;
        dia++;
        if (dia > diasPorMes[mes - 1]) {
            dia -= diasPorMes[mes - 1];
            mes++;
            if (mes > 12) {
                mes = 1;
                ano++;
            }
        }
    }

    // Atualiza os atributos de saída
    tempoSaida[0] = ano;
    tempoSaida[1] = mes;
    tempoSaida[2] = dia;
    tempoSaida[3] = hora;
    tempoSaida[4] = minuto;
}

int* Paciente::calcularProximoEvento(int tempoInicio[5], double tempoMedio) {

    // Converte tempoMedio de horas para minutos
    int minutosAdicionar = static_cast<int>(tempoMedio * 60);
    int minutosExtras = minutosAdicionar % 60;
    int totalHoras = minutosAdicionar / 60;
    int horasExtras = totalHoras % 24;
    int diasExtras = totalHoras / 24;

    // Ajusta a data e hora de início
    int minuto = tempoInicio[4] + minutosExtras;
    int hora = tempoInicio[3] + horasExtras;
    int dia = tempoInicio[2] + diasExtras;
    int mes = tempoInicio[1];
    int ano = tempoInicio[0];

    // Ajusta minutos e horas
    if (minuto >= 60) {
        minuto -= 60;
        hora++;
    }
    if (hora >= 24) {
        hora -= 24;
        dia++;
    }

    // Array com número de dias por mês
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Ajusta para anos bissextos
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasPorMes[1] = 29;
    }

    // Calcula a transição de dias, meses e anos
    while (dia > diasPorMes[mes - 1]) {
        dia -= diasPorMes[mes - 1];
        mes++;
        if (mes > 12) {
            mes = 1;
            ano++;
            // Reajusta para anos bissextos
            if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
                diasPorMes[1] = 29;
            } else {
                diasPorMes[1] = 28;
            }
        }
    }

    // Atualiza o novo tempo
    proximoTempo[0] = ano;
    proximoTempo[1] = mes;
    proximoTempo[2] = dia;
    proximoTempo[3] = hora;
    proximoTempo[4] = minuto;

    tempoEspera += tempoDiff(tempoInicio, proximoTempo);

    return proximoTempo;
}

// Avança o estado do paciente para o próximo
void Paciente::avancarEstado() {
    if (estadoAtual < 14) { // Máximo de estados definidos
        estadoAtual++;
    } else {
        throw std::runtime_error("Estado inválido: não pode avançar além do último estado.");
    }
}


//----------------#Funções secundárias#----------------


// Define o estado atual do paciente
void Paciente::setEstado(int estado) {
    if (estado < 0 || estado > 14) {
        throw std::invalid_argument("Estado inválido: deve estar entre 0 e 14.");
    }
    estadoAtual = estado;
}

// Retorna o estado atual do paciente
int Paciente::getEstado() const {
    return estadoAtual;
}

// Setter para tempo de espera  
void Paciente::setTempoEspera(double tempo) {
    tempoEspera = tempo;
}

// Retorna tempo total em espera
double Paciente::getTempoEspera() const {
    return tempoEspera;
}

// Retorna tempo total no hospital (permanência)
double Paciente::getTempoPermanencia() const {
    return tempoPermanencia;
}

// Retorna tempo total no hospital (permanência + espera)
double Paciente::getTempoTotal() const {
    return tempoTotal;
}

std::string Paciente::getId() const {
    return id;
}

bool Paciente::getAlta() const {
    return alta;
}

int Paciente::getGrauUrgencia() const {
    return grauUrgencia;
}

int Paciente::getMedidasHospitalares() const {
    return medidasHospitalares;
}

int Paciente::getTestesLaboratorio() const {
    return testesLaboratorio;
}

int Paciente::getExamesImagem() const {
    return examesImagem;
}

int Paciente::getInstrumentosMedicamentos() const {
    return instrumentosMedicamentos;
}

int* Paciente::getTempoAdmissao() const {
    return tempoAdmissao;
}

// Função para escrever o output do paciente (usando funções simplificadas)
void Paciente::escreverOutput() const {
    std::ostringstream oss;
    oss << id << " " 
        << formatarDataHora(tempoAdmissao) << " "
        << formatarDataHora(tempoSaida) << " "
        << std::fixed << std::setprecision(2) 
        << tempoTotal << " " << tempoPermanencia << " " << tempoEspera;
    std::cout << oss.str() << std::endl;
}
