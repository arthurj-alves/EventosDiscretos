#include "Procedimento.hpp"
#include <stdexcept>
#include <iostream>

// Construtor
Procedimento::Procedimento(double tempoMedio, int numUnidades)
    : tempoMedio(tempoMedio), numUnidades(numUnidades), unidadesLivres(numUnidades) {
    if (tempoMedio <= 0) {
        throw std::invalid_argument("Tempo medio deve ser maior que zero.");
    }
    if (numUnidades <= 0) {
        throw std::invalid_argument("Numero de unidades deve ser maior que zero.");
    }
}

// Alocar uma unidade para um paciente
void Procedimento::alocarUnidade(Paciente* paciente) {
    if (!temUnidadesLivres()) {
        throw std::runtime_error("Nao ha unidades livres para alocacao.");
    }

    // Decide qual fila de prioridade será atendida primeiro
    if (!grauVermelho.filaVazia()) {
        grauVermelho.desenfileira();
    } else if (!grauAmarelo.filaVazia()) {
        grauAmarelo.desenfileira();
    } else if (!grauVerde.filaVazia()) {
        grauVerde.desenfileira();
    } else {
        throw std::runtime_error("Nao ha pacientes para alocar.");
    }

    unidadesLivres--;
}

// Desalocar uma unidade
void Procedimento::desalocarUnidade() {
    if (unidadesLivres >= numUnidades) {
        throw std::runtime_error("Todas as unidades ja estao livres.");
    }

    unidadesLivres++;
}

// Verifica se há unidades livres
bool Procedimento::temUnidadesLivres() const {
    return unidadesLivres > 0;
}

// Getter para o tempo médio
double Procedimento::getTempoMedio() const {
    return tempoMedio;
}
