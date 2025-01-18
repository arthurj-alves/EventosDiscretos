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
    Paciente* retornaProximoTriagem(); 
    
    void enfileirarProcedimento(Paciente* paciente);
    void alocarProcedimento();
    void desalocarProcedimento(); 
    Paciente* retornaProximoProcedimento(int grau);
    
    bool temUnidadesLivres() const; // Verifica se há unidades livres
    bool procedimentoVazio(); // Verifica se o procedimento está vazio

    // Getters
    double getTempoMedio() const;
    int getUnidadesLivres() const;
};

#endif // PROCEDIMENTO_HPP
