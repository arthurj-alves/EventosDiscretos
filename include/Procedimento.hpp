#ifndef PROCEDIMENTO_HPP
#define PROCEDIMENTO_HPP

#include "Paciente.hpp"
#include "Fila.hpp"

class Procedimento {
private:
    double tempoMedio;  // Tempo médio de execução do procedimento
    int numUnidades;    // Número total de unidades disponíveis
    int unidadesLivres; // Número de unidades atualmente livres

    // Filas para cada grau de urgência
    Fila grauVerde;    
    Fila grauAmarelo;
    Fila grauVermelho;
    
public:

    // Construtor
    Procedimento(double tempoMedio, int numUnidades);

    // Métodos principais
    void alocarUnidade(Paciente* paciente);    // Tenta alocar uma unidade, retorna true se sucesso
    void desalocarUnidade(); // Libera uma unidade
    bool temUnidadesLivres() const; // Verifica se há unidades livres

    // Getters
    double getTempoMedio() const;
};

#endif // PROCEDIMENTO_HPP
