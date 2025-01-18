#include "Paciente.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>


std::string parseDataString(long long int seconds) {
    std::time_t timeVal = static_cast<std::time_t>(seconds);
    std::tm* tmPtr = std::localtime(&timeVal);

    char buffer[100];

    // Use %e instead of %d to pad a single digit day with a space.
    std::strftime(buffer, sizeof(buffer), "%a %b %e %H:%M:%S %Y", tmPtr);

    return std::string(buffer);
}

double parseDataSegundos(int year, int month, int day, int hour) {
    std::tm tempoStruct = {};
    tempoStruct.tm_year = year - 1900;
    tempoStruct.tm_mon = month - 1;
    tempoStruct.tm_mday = day;
    tempoStruct.tm_hour = hour;
    tempoStruct.tm_min = 0;
    tempoStruct.tm_sec = 0;
    std::time_t tempoSegundos = std::mktime(&tempoStruct);
    return static_cast<double>(tempoSegundos);
}


// Construtor
Paciente::Paciente(const std::string& id, bool alta, int ano, int mes, int dia, int hora, 
                   int grau, int mh, int tl, int ei, int im) 
    : id(id), alta(alta), grauUrgencia(grau), medidasHospitalares(mh), testesLaboratorio(tl), 
      examesImagem(ei), instrumentosMedicamentos(im), tempoEspera(0), tempoAtendido(0) {

    if(alta){
        medidasHospitalares = 0;
        testesLaboratorio = 0;
        examesImagem = 0;
        instrumentosMedicamentos = 0;
    }

    // Converte a data e hora de admissão para segundos desde o epoch
    tempoAdmissao = parseDataSegundos(ano, mes, dia, hora);

    tempoTotal = tempoAdmissao;
    
}





//----------------#Funções secundárias#----------------


void Paciente::setTempoFila(double tempo) {
    tempoFila = tempo;
}

void Paciente::setTempoEspera(double tempo) {
    tempoEspera = tempo;
}

void Paciente::setTempoAtendido(double tempo) {
    tempoAtendido = tempo;
}

void Paciente::setTempoSaida(double tempo) {
    tempoSaida = tempo;
}

void Paciente::setTempoTotal(double tempo){
    tempoTotal = tempo;
}

double Paciente::getTempoFila() const {
    return tempoFila;
}

// Retorna tempo total em espera
double Paciente::getTempoEspera() const {
    return tempoEspera;
}

// Retorna tempo total no hospital (permanência)
double Paciente::getTempoAtendido() const {
    return tempoAtendido;
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

double Paciente::getTempoAdmissao() const {
    return tempoAdmissao;
}



// Função para escrever o output do paciente (usando funções simplificadas)
void Paciente::escreverOutput() const {
    std::ostringstream oss;
    oss << std::stoi(id) << " "  // Remove leading zeros by converting to int
        << parseDataString(tempoAdmissao) << " "
        << parseDataString(tempoSaida) << " "
        << std::fixed << std::setprecision(2) 
        << (tempoAtendido / 3600) + (tempoEspera / 3600)  << "  " << tempoAtendido / 3600 << " " << tempoEspera / 3600;
    std::cout << oss.str() << std::endl;
}
