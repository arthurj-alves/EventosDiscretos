#include "Paciente.hpp"
#include "Procedimento.hpp"
#include "Fila.hpp"
#include "Escalonador.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    // Verifica se o nome do arquivo foi passado como argumento
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.csv>" << std::endl;
        return 1;
    }

    // Abre o arquivo especificado como argumento
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return 1;
    }

    double tempotriagem, tempoatendimento, tempomh, tempotl, tempoei, tempoim;
    int numerotriagem, numeroatendimento, numeromh, numerotl, numeroei, numeroim, numeropacientes;

    // Lendo os tempos e números dos procedimentos
    file >> tempotriagem >> numerotriagem;
    file >> tempoatendimento >> numeroatendimento;
    file >> tempomh >> numeromh;
    file >> tempotl >> numerotl;
    file >> tempoei >> numeroei;
    file >> tempoim >> numeroim;
    file >> numeropacientes;

    // Inicializando os procedimentos
    Procedimento triagem(tempotriagem * 3600, numerotriagem);
    Procedimento atendimento(tempoatendimento * 3600, numeroatendimento);
    Procedimento medidas(tempomh * 3600, numeromh);
    Procedimento testes(tempotl * 3600, numerotl);
    Procedimento imagem(tempoei * 3600, numeroei);
    Procedimento instrumentos(tempoim * 3600, numeroim);

    Paciente* pacientes[numeropacientes];
    Escalonador escalonador(numeropacientes);

    // Lendo os pacientes
    int counter = 0;
    std::string line;
    std::getline(file, line); // Descarta o cabeçalho ou linha em branco (se necessário)

    while (std::getline(file, line) && counter < numeropacientes) {
        std::istringstream iss(line);
        std::string id;
        int alta, ano, mes, dia, hora, grau, mh, tl, ei, im;

        if (!(iss >> id >> alta >> ano >> mes >> dia >> hora >> grau >> mh >> tl >> ei >> im)) {
            std::cerr << "Erro ao processar a linha: " << line << std::endl;
            break; // Final do arquivo ou erro de leitura
        }

        // Criar e armazenar o paciente no array
        pacientes[counter] = new Paciente(id, alta, ano, mes, dia, hora, grau, mh, tl, ei, im);
        escalonador.insereEscalonador(pacientes[counter], 1);
        counter++;
    }

    // Fecha o arquivo
    file.close();

     double tempoRelogio = 0;


    // Enquanto houver eventos ou filas não vazias
    while (!escalonador.vazio() || !triagem.procedimentoVazio() || !atendimento.procedimentoVazio() || !medidas.procedimentoVazio() || !testes.procedimentoVazio() || !imagem.procedimentoVazio() || !instrumentos.procedimentoVazio()) {


        Evento* evento = nullptr;
        if(!escalonador.vazio()){
            evento = escalonador.retiraEvento();
            if(evento->tempoInicio > tempoRelogio){
                tempoRelogio = evento->tempoInicio;
            }
        }
        
        if(evento){
            switch (evento->tipo)
            {
            case 1:
                evento->paciente->setTempoFila(tempoRelogio);
                triagem.enfileirarTriagem(evento->paciente);
                // std::cout << "Chegada do Paciente" << std::endl;
                break;
            case 2:
                evento->paciente->setTempoFila(tempoRelogio);
                triagem.desalocarProcedimento();
                atendimento.enfileirarProcedimento(evento->paciente);
                // std::cout << "Sai da triagem e enfileira atendimento" << std::endl;
                break;
            case 3:
                evento->paciente->setTempoFila(tempoRelogio);
                atendimento.desalocarProcedimento();
                if(!evento->paciente->getAlta())medidas.enfileirarProcedimento(evento->paciente);
                else evento->paciente->setTempoSaida(evento->tempoInicio);
                // std::cout << "Sai da atendimento e enfileira medidas" << std::endl;
                break;
            case 4:
                evento->paciente->setTempoFila(tempoRelogio);
                medidas.desalocarProcedimento();
                testes.enfileirarProcedimento(evento->paciente);
                // std::cout << "Sai da medidas e enfileira testes" << std::endl;
                break;
            case 5:
                evento->paciente->setTempoFila(tempoRelogio);
                testes.desalocarProcedimento();
                imagem.enfileirarProcedimento(evento->paciente);
                // std::cout << "Sai da testes e enfileira imagens" << std::endl;
                break;
            case 6:
                evento->paciente->setTempoFila(tempoRelogio);
                imagem.desalocarProcedimento();
                instrumentos.enfileirarProcedimento(evento->paciente);
                // std::cout << "Sai da imagens e enfileira instrumentos" << std::endl;
                break;
            default:
                instrumentos.desalocarProcedimento();
                evento->paciente->setTempoSaida(evento->tempoInicio);
                // std::cout << evento->tempoInicio << std::endl;
                //std::cout << "Sai de instrumentos" << std::endl;
                break;
            }
            delete evento;
        }


        if(!triagem.grauVerde.filaVazia() && triagem.temUnidadesLivres()){
            for(int i = 0; i < triagem.getUnidadesLivres(); i++){
                int unidadesLivres = triagem.getUnidadesLivres();
                if(unidadesLivres != 0 && !triagem.grauVerde.filaVazia()){
                    double aux = 0;
                    auto paciente = triagem.retornaProximoTriagem();
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    triagem.alocarProcedimento();
                    
                    aux = tempoRelogio + triagem.getTempoMedio();
                    paciente->setTempoAtendido(triagem.getTempoMedio() + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);

                    escalonador.insereEscalonador(paciente, 2);
                    
                }
            }
        }

        if(!atendimento.grauVermelho.filaVazia() && atendimento.temUnidadesLivres()){
            for(int i = 0; i < atendimento.getUnidadesLivres(); i++){
                int unidadesLivres = atendimento.getUnidadesLivres();
                if(unidadesLivres != 0 && !atendimento.grauVermelho.filaVazia()){
                    double aux = 0;
                    auto paciente = atendimento.retornaProximoProcedimento(2);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    atendimento.alocarProcedimento();
                    
                    aux = tempoRelogio + atendimento.getTempoMedio();
                    paciente->setTempoAtendido(atendimento.getTempoMedio() + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 3);
                    
                }
            }
        }
        if(!atendimento.grauAmarelo.filaVazia() && atendimento.temUnidadesLivres()){
            for(int i = 0; i < atendimento.getUnidadesLivres(); i++){
                int unidadesLivres = atendimento.getUnidadesLivres();
                if(unidadesLivres != 0 && !atendimento.grauAmarelo.filaVazia()){
                    double aux = 0;
                    auto paciente = atendimento.retornaProximoProcedimento(1);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    atendimento.alocarProcedimento();
                    
                    aux = tempoRelogio + atendimento.getTempoMedio();
                    paciente->setTempoAtendido(atendimento.getTempoMedio() + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 3);
                    
                }
            }
        }
        if(!atendimento.grauVerde.filaVazia() && atendimento.temUnidadesLivres()){
            for(int i = 0; i < atendimento.getUnidadesLivres(); i++){
                int unidadesLivres = atendimento.getUnidadesLivres();
                if(unidadesLivres != 0 && !atendimento.grauVerde.filaVazia()){
                    double aux = 0;
                    auto paciente = atendimento.retornaProximoProcedimento(0);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    atendimento.alocarProcedimento();
                    
                    aux = tempoRelogio + atendimento.getTempoMedio();
                    paciente->setTempoAtendido(atendimento.getTempoMedio() + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 3);
                    
                }
            }
        }
        if(!medidas.grauVermelho.filaVazia() && medidas.temUnidadesLivres()){
            for(int i = 0; i < medidas.getUnidadesLivres(); i++){
                int unidadesLivres = medidas.getUnidadesLivres();
                if(unidadesLivres != 0 && !medidas.grauVermelho.filaVazia()){
                    double aux = 0;
                    auto paciente = medidas.retornaProximoProcedimento(2);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    medidas.alocarProcedimento();
                    
                    aux = tempoRelogio + (medidas.getTempoMedio() * paciente->getMedidasHospitalares());
                    paciente->setTempoAtendido((medidas.getTempoMedio() * paciente->getMedidasHospitalares())  + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 4);
                    
                }
            }
        }
        if(!medidas.grauAmarelo.filaVazia() && medidas.temUnidadesLivres()){
            for(int i = 0; i < medidas.getUnidadesLivres(); i++){
                int unidadesLivres = medidas.getUnidadesLivres();
                if(unidadesLivres != 0 && !medidas.grauAmarelo.filaVazia()){
                    double aux = 0;
                    auto paciente = medidas.retornaProximoProcedimento(1);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    medidas.alocarProcedimento();
                    
                    aux = tempoRelogio + (medidas.getTempoMedio() * paciente->getMedidasHospitalares());
                    paciente->setTempoAtendido((medidas.getTempoMedio() * paciente->getMedidasHospitalares()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 4);
                    
                }
            }
        }
        if(!medidas.grauVerde.filaVazia() && medidas.temUnidadesLivres()){
            for(int i = 0; i < medidas.getUnidadesLivres(); i++){
                int unidadesLivres = medidas.getUnidadesLivres();
                if(unidadesLivres != 0 && !medidas.grauVerde.filaVazia()){
                    double aux = 0;
                    auto paciente = medidas.retornaProximoProcedimento(0);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    medidas.alocarProcedimento();
                    
                    aux = tempoRelogio + (medidas.getTempoMedio() * paciente->getMedidasHospitalares());
                    paciente->setTempoAtendido((medidas.getTempoMedio() * paciente->getMedidasHospitalares()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 4);
                    
                }
            }
        }
        if(!testes.grauVermelho.filaVazia() && testes.temUnidadesLivres()){
            for(int i = 0; i < testes.getUnidadesLivres(); i++){
                int unidadesLivres = testes.getUnidadesLivres();
                if(unidadesLivres != 0 && !testes.grauVermelho.filaVazia()){
                    double aux = 0;
                    auto paciente = testes.retornaProximoProcedimento(2);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    testes.alocarProcedimento();
                    
                    aux = tempoRelogio + (testes.getTempoMedio() * paciente->getTestesLaboratorio());
                    paciente->setTempoAtendido((testes.getTempoMedio() * paciente->getTestesLaboratorio()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 5);
                    
                }
            }
        }
        if(!testes.grauAmarelo.filaVazia() && testes.temUnidadesLivres()){
            for(int i = 0; i < testes.getUnidadesLivres(); i++){
                int unidadesLivres = testes.getUnidadesLivres();
                if(unidadesLivres != 0 && !testes.grauAmarelo.filaVazia()){
                    double aux = 0;
                    auto paciente = testes.retornaProximoProcedimento(1);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    testes.alocarProcedimento();
                    
                    aux = tempoRelogio + (testes.getTempoMedio() * paciente->getTestesLaboratorio());
                    paciente->setTempoAtendido((testes.getTempoMedio() * paciente->getTestesLaboratorio()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 5);
                    
                }
            }
        }
        if(!testes.grauVerde.filaVazia() && testes.temUnidadesLivres()){
            for(int i = 0; i < testes.getUnidadesLivres(); i++){
                int unidadesLivres = testes.getUnidadesLivres();
                if(unidadesLivres != 0 && !testes.grauVerde.filaVazia()){
                    double aux = 0;
                    auto paciente = testes.retornaProximoProcedimento(0);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    testes.alocarProcedimento();
                    
                    aux = tempoRelogio + (testes.getTempoMedio() * paciente->getTestesLaboratorio());
                    paciente->setTempoAtendido((testes.getTempoMedio() * paciente->getTestesLaboratorio()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 5);
                    
                }
            }
        }
        if(!imagem.grauVermelho.filaVazia() && imagem.temUnidadesLivres()){
            for(int i = 0; i < imagem.getUnidadesLivres(); i++){
                int unidadesLivres = imagem.getUnidadesLivres();
                if(unidadesLivres != 0 && !imagem.grauVermelho.filaVazia()){
                    double aux = 0;
                    auto paciente = imagem.retornaProximoProcedimento(2);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    imagem.alocarProcedimento();
                    
                    aux = tempoRelogio + (imagem.getTempoMedio() * paciente->getExamesImagem());
                    paciente->setTempoAtendido((imagem.getTempoMedio() * paciente->getExamesImagem()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 6);
                    
                }
            }
        }
        if(!imagem.grauAmarelo.filaVazia() && imagem.temUnidadesLivres()){
            for(int i = 0; i < imagem.getUnidadesLivres(); i++){
                int unidadesLivres = imagem.getUnidadesLivres();
                if(unidadesLivres != 0 && !imagem.grauAmarelo.filaVazia()){
                    double aux = 0;
                    auto paciente = imagem.retornaProximoProcedimento(1);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    imagem.alocarProcedimento();
                    
                    aux = tempoRelogio + (imagem.getTempoMedio() * paciente->getExamesImagem());
                    paciente->setTempoAtendido((imagem.getTempoMedio() * paciente->getExamesImagem()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 6);
                    
                }
            }
        }
        if(!imagem.grauVerde.filaVazia() && imagem.temUnidadesLivres()){
            for(int i = 0; i < imagem.getUnidadesLivres(); i++){
                int unidadesLivres = imagem.getUnidadesLivres();
                if(unidadesLivres != 0 && !imagem.grauVerde.filaVazia()){
                    double aux = 0;
                    auto paciente = imagem.retornaProximoProcedimento(0);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    imagem.alocarProcedimento();
                    
                    aux = tempoRelogio + (imagem.getTempoMedio() * paciente->getExamesImagem());
                    paciente->setTempoAtendido((imagem.getTempoMedio() * paciente->getExamesImagem()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 6);
                    
                }
            }
        }
        if(!instrumentos.grauVermelho.filaVazia() && instrumentos.temUnidadesLivres()){
            for(int i = 0; i < instrumentos.getUnidadesLivres(); i++){
                int unidadesLivres = instrumentos.getUnidadesLivres();
                if(unidadesLivres != 0 && !instrumentos.grauVermelho.filaVazia()){
                    double aux = 0;
                    auto paciente = instrumentos.retornaProximoProcedimento(2);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    instrumentos.alocarProcedimento();
                    
                    aux = tempoRelogio + (instrumentos.getTempoMedio() * paciente->getInstrumentosMedicamentos());
                    paciente->setTempoAtendido((instrumentos.getTempoMedio() * paciente->getInstrumentosMedicamentos()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 7);
                    
                }
            }
        }
        if(!instrumentos.grauAmarelo.filaVazia() && instrumentos.temUnidadesLivres()){
            for(int i = 0; i < instrumentos.getUnidadesLivres(); i++){
                int unidadesLivres = instrumentos.getUnidadesLivres();
                if(unidadesLivres != 0 && !instrumentos.grauAmarelo.filaVazia()){
                    double aux = 0;
                    auto paciente = instrumentos.retornaProximoProcedimento(1);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    instrumentos.alocarProcedimento();
                    
                    aux = tempoRelogio + (instrumentos.getTempoMedio() * paciente->getInstrumentosMedicamentos());
                    paciente->setTempoAtendido((instrumentos.getTempoMedio() * paciente->getInstrumentosMedicamentos()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 7);
                    
                }
            }
        }
        if(!instrumentos.grauVerde.filaVazia() && instrumentos.temUnidadesLivres()){
            for(int i = 0; i < instrumentos.getUnidadesLivres(); i++){
                int unidadesLivres = instrumentos.getUnidadesLivres();
                if(unidadesLivres != 0 && !instrumentos.grauVerde.filaVazia()){
                    double aux = 0;
                    auto paciente = instrumentos.retornaProximoProcedimento(0);
                    double tempoEspera = tempoRelogio - paciente->getTempoFila();
                    paciente->setTempoEspera(tempoEspera + paciente->getTempoEspera());
                    instrumentos.alocarProcedimento();
                    
                    aux = tempoRelogio + (instrumentos.getTempoMedio() * paciente->getInstrumentosMedicamentos());
                    paciente->setTempoAtendido((instrumentos.getTempoMedio() * paciente->getInstrumentosMedicamentos()) + paciente->getTempoAtendido());
                    paciente->setTempoTotal(aux);
                    escalonador.insereEscalonador(paciente, 7);
                    
                }
            }
        }
    }

    for(int j = 0; j < numeropacientes; j++){
        pacientes[j]->escreverOutput();
    }

    return 0;
}
