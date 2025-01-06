#include "Suporte.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>

// Função para obter o nome do dia da semana
std::string getDiaSemana(int tempoInfos[5]) {
    static const char* diasSemana[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    std::tm time_in = { 0, 0, 0, tempoInfos[2], tempoInfos[1] - 1, tempoInfos[0] - 1900 };
    std::mktime(&time_in);  // Converte para estrutura de tempo válida
    return diasSemana[time_in.tm_wday];
}

// Função para obter o nome do mês
std::string getMesNome(int tempoInfos[5]) {
    static const char* meses[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    return meses[tempoInfos[1] - 1];  // Assume que mes está entre 1 e 12
}

// Função para formatar a data e hora (já valida que os valores estão consistentes)
std::string formatarDataHora(int tempoInfos[5]) {
    std::ostringstream oss;
    oss << getDiaSemana(tempoInfos) << " " 
        << getMesNome(tempoInfos) << " " 
        << std::setw(2) << std::setfill('0') << tempoInfos[2] << " " 
        << std::setw(2) << std::setfill('0') << tempoInfos[3] << ":" 
        << std::setw(2) << std::setfill('0') << tempoInfos[4] << ":00 " 
        << tempoInfos[1];
    return oss.str();
}

// Função para calcular a diferença de tempo entre dois instantes
double tempoDiff(int tempoInicio[5], int tempoFim[5]) {
    std::tm tInicio = { 0, tempoInicio[4], tempoInicio[3], tempoInicio[2], tempoInicio[1] - 1, tempoInicio[0] - 1900 };
    std::tm tFim = { 0, tempoFim[4], tempoFim[3], tempoFim[2], tempoFim[1] - 1, tempoFim[0] - 1900 };

    std::time_t timeInicio = std::mktime(&tInicio);
    std::time_t timeFim = std::mktime(&tFim);

    double diffSeconds = std::difftime(timeFim, timeInicio);
    return diffSeconds / 3600.0; // Convert seconds to hours
}

// Outras funções membro da classe Suporte