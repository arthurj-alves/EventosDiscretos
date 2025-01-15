#ifndef PROCEDIMENTO_HPP
#define PROCEDIMENTO_HPP

#include "Paciente.hpp"
#include "Fila.hpp"

class Procedimento {
private:
    double tempoMedio;  // Tempo médio de execução do procedimento
    int numUnidades;    // Número total de unidades disponíveis
    int unidadesLivres; // Número de unidades atualmente livres
    
public:

    // Filas para cada grau de urgência
    Fila grauVerde;    
    Fila grauAmarelo;
    Fila grauVermelho;

    // Construtor
    Procedimento(double tempoMedio, int numUnidades);

    // Métodos principais
    void enfileirarTriagem(Paciente* paciente);
    void alocarTriagem(Paciente* paciente);
    void desalocarTriagem(); // Libera uma unidade de triagem
    
    void enfileirarAtendimento(Paciente* paciente);
    void alocarAtendimento(Paciente* paciente);
    // void desalocarAtendimento(); // Libera uma unidade de atendimento
    Paciente* desalocarAtendimento(); // Libera uma unidade de atendimento
    
    bool temUnidadesLivres() const; // Verifica se há unidades livres
    bool procedimentoVazio(); // Verifica se o procedimento está vazio

    // Getters
    double getTempoMedio() const;
};

#endif // PROCEDIMENTO_HPP
