#include "Paciente.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>

// Construtor
Paciente::Paciente(const std::string& id, bool alta, int ano, int mes, int dia, int hora, 
                   int grau, int mh, int tl, int ei, int im) 
    : id(id), alta(alta), anoAdmissao(ano), mesAdmissao(mes), diaAdmissao(dia), 
      horaAdmissao(hora), grauUrgencia(grau), medidasHospitalares(mh), testesLaboratorio(tl), 
      examesImagem(ei), instrumentosMedicamentos(im), tempoEspera(0), tempoPermanencia(0), 
      anoSaida(ano), mesSaida(mes), diaSaida(dia), horaSaida(hora), minutoSaida(0) {}

// Calcula os tempos com base nos parâmetros fornecidos
void Paciente::calcularTempos(double tempoTriagem, double tempoAtendimento, double tempoMH,
                              double tempoTL, double tempoEI, double tempoIM) {
    tempoPermanencia = tempoTriagem + tempoAtendimento + 
                       (medidasHospitalares * tempoMH) + 
                       (testesLaboratorio * tempoTL) + 
                       (examesImagem * tempoEI) + 
                       (instrumentosMedicamentos * tempoIM);
    tempoTotal = tempoPermanencia + tempoEspera;

    // Calcula a data e hora de saída com base no tempo total
    int totalMinutos = static_cast<int>(tempoTotal * 60);
    int minutosSaida = totalMinutos % 60;
    int totalHoras = totalMinutos / 60;
    int horasSaida = totalHoras % 24;
    int totalDias = totalHoras / 24;

    // Ajusta a data de saída
    int dia = diaAdmissao + totalDias;
    int mes = mesAdmissao;
    int ano = anoAdmissao;

    // Array com o número de dias em cada mês (não considerando anos bissextos)
    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Ajusta para anos bissextos
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasPorMes[1] = 29;
    }

    // Ajusta o dia, mês e ano de saída
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

    // Atualiza os atributos de saída
    diaSaida = dia;
    mesSaida = mes;
    anoSaida = ano;
    horaSaida = (horaAdmissao + horasSaida) % 24;
    minutoSaida = minutosSaida;

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

// Função para obter o nome do dia da semana
std::string getDiaSemana(int ano, int mes, int dia) {
    static const char* diasSemana[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    std::tm time_in = { 0, 0, 0, dia, mes - 1, ano - 1900 };
    std::mktime(&time_in);
    return diasSemana[time_in.tm_wday];
}

// Função para obter o nome do mês
std::string getMesNome(int mes) {
    static const char* meses[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    return meses[mes - 1];
}

// Função para formatar a data e hora
std::string formatarDataHora(int ano, int mes, int dia, int hora, int minuto) {
    std::ostringstream oss;
    oss << getDiaSemana(ano, mes, dia) << " " << getMesNome(mes) << " " << std::setw(2) << std::setfill('0') << dia
        << " " << std::setw(2) << std::setfill('0') << hora << ":" << std::setw(2) << std::setfill('0') << minuto
        << ":00 " << ano;
    return oss.str();
}

// Função para escrever o output do paciente
void Paciente::escreverOutput() const {
    std::ostringstream oss;
    oss << id << " " << formatarDataHora(anoAdmissao, mesAdmissao, diaAdmissao, horaAdmissao, 0) << " "
        << formatarDataHora(anoSaida, mesSaida, diaSaida, horaSaida, minutoSaida) << " "
        << std::fixed << std::setprecision(2) << tempoTotal << " " << tempoPermanencia << " " << tempoEspera;
    std::cout << oss.str() << std::endl;
}


