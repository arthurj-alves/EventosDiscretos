// Arquivo: Procedimento.cpp
#include "Procedimento.hpp"

// Construtor
Procedimento::Procedimento(double tempoMedio, int numUnidades)
    : tempoMedio(tempoMedio), numUnidades(numUnidades), unidadesLivres(numUnidades) {}

// Tenta alocar uma unidade
void Procedimento::alocarUnidade() {
    if (unidadesLivres > 0) {
        unidadesLivres--;
    }
}

// Desaloca uma unidade
void Procedimento::desalocarUnidade() {
    if (unidadesLivres < numUnidades) {
        unidadesLivres++;
    }
}

// Verifica se há unidades livres
bool Procedimento::temUnidadesLivres() const {
    return unidadesLivres > 0;
}

// Retorna o tempo médio de execução do procedimento
double Procedimento::getTempoMedio() const {
    return tempoMedio;
}