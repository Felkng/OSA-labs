#include "SistemaGerenciador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <limits>

using namespace std;

SistemaGerenciador::SistemaGerenciador(const string& csv, const string& dados, const string& indice)
    : arquivoCSV(csv), arquivoDados(dados), arquivoIndice(indice) {}

void SistemaGerenciador::iniciar() {
    int opcao;
    
    do {
        exibirMenu();
        cin >> opcao;
        limparBuffer();
        
        switch (opcao) {
            case 1:
                gerarArquivoDados();
                break;
            case 2:
                gerarArquivoIndice();
                break;
            case 3:
                buscarRegistroPorMatricula();
                break;
            case 4:
                cout << "\nEncerrando o sistema..." << endl;
                break;
            default:
                cout << "\nOpcao invalida! Tente novamente." << endl;
        }
        
        if (opcao != 4) {
            cout << "\nPressione Enter para continuar...";
            cin.get();
        }
        
    } while (opcao != 4);
}

void SistemaGerenciador::exibirMenu() {
    cout << "\n===========================================\n";
    cout << "   Sistema de Gerenciamento de Alunos\n";
    cout << "===========================================\n";
    cout << "1. Gerar Arquivo de Dados a partir do CSV\n";
    cout << "2. Gerar Arquivo de Indice\n";
    cout << "3. Buscar Aluno por Matricula\n";
    cout << "4. Sair\n";
    cout << "===========================================\n";
    cout << "Escolha uma opcao: ";
}

void SistemaGerenciador::limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void SistemaGerenciador::escreverRegistro(ofstream& out, const Aluno& aluno) {
    out.write(reinterpret_cast<const char*>(&aluno), sizeof(Aluno));
}

bool SistemaGerenciador::lerRegistro(ifstream& in, Aluno& aluno, long offset) {
    if (offset != -1) {
        in.seekg(offset, ios::beg);
    }
    
    in.read(reinterpret_cast<char*>(&aluno), sizeof(Aluno));
    return in.good();
}

void SistemaGerenciador::gerarArquivoDados() {
    cout << "\n--- Gerando Arquivo de Dados ---\n";
    
    string nomeCSV;
    cout << "Digite o nome do arquivo CSV (ex: alunos_mil.csv): ";
    getline(cin, nomeCSV);
    
    ifstream csvIn(nomeCSV);
    if (!csvIn.is_open()) {
        cout << "ERRO: Nao foi possivel abrir o arquivo CSV: " << nomeCSV << endl;
        return;
    }
    
    cout << "Processando arquivo: " << nomeCSV << endl;
    
    ofstream dadosOut(arquivoDados, ios::binary);
    if (!dadosOut.is_open()) {
        cout << "ERRO: Nao foi possivel criar o arquivo de dados: " << arquivoDados << endl;
        csvIn.close();
        return;
    }
    
    string linha;
    int contador = 0;
    
    getline(csvIn, linha);
    
    while (getline(csvIn, linha)) {
        stringstream ss(linha);
        string matriculaStr, nome, curso;
        
        if (getline(ss, matriculaStr, ',') &&
            getline(ss, nome, ',') &&
            getline(ss, curso, ',')) {
            
            int matricula = stoi(matriculaStr);
            Aluno aluno(matricula, nome.c_str(), curso.c_str());
            escreverRegistro(dadosOut, aluno);
            contador++;
        }
    }
    
    csvIn.close();
    dadosOut.close();
    
    cout << "\nArquivo de dados gerado com sucesso!" << endl;
    cout << "Total de registros: " << contador << endl;
    cout << "Arquivo: " << arquivoDados << endl;
}

void SistemaGerenciador::gerarArquivoIndice() {
    cout << "\n--- Gerando Arquivo de Indice ---\n";
    
    ifstream dadosIn(arquivoDados, ios::binary);
    if (!dadosIn.is_open()) {
        cout << "ERRO: Nao foi possivel abrir o arquivo de dados: " << arquivoDados << endl;
        cout << "Execute a opcao 1 primeiro para gerar o arquivo de dados." << endl;
        return;
    }
    
    vector<Indice> indices;
    Aluno aluno;
    long offset = 0;
    
    while (lerRegistro(dadosIn, aluno)) {
        Indice idx(aluno.matricula, offset);
        indices.push_back(idx);
        offset += sizeof(Aluno);
    }
    
    dadosIn.close();
    
    if (indices.empty()) {
        cout << "AVISO: Nenhum registro encontrado no arquivo de dados." << endl;
        return;
    }
    
    sort(indices.begin(), indices.end());
    
    ofstream indiceOut(arquivoIndice, ios::binary);
    if (!indiceOut.is_open()) {
        cout << "ERRO: Nao foi possivel criar o arquivo de indice: " << arquivoIndice << endl;
        return;
    }
    
    for (const auto& idx : indices) {
        indiceOut.write(reinterpret_cast<const char*>(&idx), sizeof(Indice));
    }
    
    indiceOut.close();
    
    cout << "\nArquivo de indice gerado com sucesso!" << endl;
    cout << "Total de indices: " << indices.size() << endl;
    cout << "Arquivo: " << arquivoIndice << endl;
}

void SistemaGerenciador::buscarRegistroPorMatricula() {
    cout << "\n--- Buscar Aluno por Matricula ---\n";
    
    ifstream indiceIn(arquivoIndice, ios::binary);
    if (!indiceIn.is_open()) {
        cout << "ERRO: Nao foi possivel abrir o arquivo de indice: " << arquivoIndice << endl;
        cout << "Execute a opcao 2 primeiro para gerar o arquivo de indice." << endl;
        return;
    }
    
    vector<Indice> indices;
    Indice idx;
    
    while (indiceIn.read(reinterpret_cast<char*>(&idx), sizeof(Indice))) {
        indices.push_back(idx);
    }
    
    indiceIn.close();
    
    if (indices.empty()) {
        cout << "AVISO: Nenhum indice encontrado." << endl;
        return;
    }
    
    int matriculaBusca;
    cout << "Digite a matricula do aluno: ";
    cin >> matriculaBusca;
    limparBuffer();
    
    int esquerda = 0;
    int direita = indices.size() - 1;
    int encontrado = -1;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        
        if (indices[meio].matricula == matriculaBusca) {
            encontrado = meio;
            break;
        } else if (indices[meio].matricula < matriculaBusca) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    if (encontrado == -1) {
        cout << "\nAluno com matricula " << matriculaBusca << " nao encontrado." << endl;
        return;
    }
    
    ifstream dadosIn(arquivoDados, ios::binary);
    if (!dadosIn.is_open()) {
        cout << "ERRO: Nao foi possivel abrir o arquivo de dados." << endl;
        return;
    }
    
    Aluno aluno;
    long offset = indices[encontrado].byte_offset;
    
    if (lerRegistro(dadosIn, aluno, offset)) {
        cout << "\n===========================================\n";
        cout << "           ALUNO ENCONTRADO\n";
        cout << "===========================================\n";
        cout << "Matricula: " << aluno.matricula << endl;
        cout << "Nome:      " << aluno.nome << endl;
        cout << "Curso:     " << aluno.curso << endl;
        cout << "===========================================\n";
    } else {
        cout << "ERRO: Nao foi possivel ler o registro." << endl;
    }
    
    dadosIn.close();
}
