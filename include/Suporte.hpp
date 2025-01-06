#ifndef SUPORTE_HPP
#define SUPORTE_HPP

// Inclua aqui as bibliotecas necessárias
#include <sstream>
#include <iostream>
#include <iomanip>

// Declaração das funções de suporte

double tempoDiff(int tempoInicio[5], int tempoFim[5]);
std::string getDiaSemana(int tempoInfos[5]);
std::string getMesNome(int tempoInfos[5]);
std::string formatarDataHora(int tempoInfos[5]);

#endif // SUPORTE_HPP