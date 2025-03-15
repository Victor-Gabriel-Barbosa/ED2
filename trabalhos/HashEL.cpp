#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <iomanip>
using namespace std;

// Classe que representa a tabela hash
class TabelaHash {
private:
  int tamanho;
  vector<list<string>> tabela;
  int totalColisoes;
  vector<int> distribuicao; 
  int totalElementos;

public:
  TabelaHash(int tam) {
    tamanho = tam;
    tabela.resize(tamanho); // Cada posição contém uma lista vazia
    totalColisoes = 0;
    totalElementos = 0;
    distribuicao.resize(12, 0); // Para armazenar contagem de 0, 1, 2, ..., 10, >10 elementos
  }

  // Função hash que implementa o método do enlaçamento limite
  int hash(const string& cidade) {
    const int GRUPO_TAMANHO = 3; // Tamanho de cada grupo de caracteres
    vector<int> grupos;
    
    // Converte a string em grupos de valores numéricos
    for (size_t i = 0; i < cidade.length(); i += GRUPO_TAMANHO) {
      int valor = 0;
      size_t fim = min(i + GRUPO_TAMANHO, cidade.length());
      
      // Calcula valor numérico para cada grupo
      for (size_t j = i; j < fim; j++) valor = valor * 10 + static_cast<unsigned char>(cidade[j]) % 10;
      
      grupos.push_back(valor);
    }
    
    // Inverte os grupos do meio
    for (size_t i = 1; i < grupos.size() - 1; i++) {
      // Inverte os dígitos do número
      int original = grupos[i];
      int invertido = 0;
      
      while (original > 0) {
        invertido = invertido * 10 + original % 10;
        original /= 10;
      }
      
      grupos[i] = invertido;
    }
    
    // Soma todos os grupos
    int soma = 0;
    for (int valor : grupos) soma += valor;
    
    return soma % tamanho;
  }

  // Insere uma cidade na tabela hash usando o método do enlaçamento limite
  void inserir(const string& cidade) {
    int indice = hash(cidade);
    
    // Se a lista na posição indice não está vazia, tem-se uma colisão
    if (!tabela[indice].empty()) totalColisoes++;
    
    // Adiciona a cidade no final da lista na posição calculada pelo hash
    tabela[indice].push_back(cidade);
    totalElementos++;
  }

  // Calcula as estatísticas de distribuição (quantas cidades por posição)
  void calcularDistribuicao() {
    // Reseta a distribuição para recalcular
    fill(distribuicao.begin(), distribuicao.end(), 0);
    
    // Conta quantas posições têm 0, 1, 2, ... elementos
    for (int i = 0; i < tamanho; i++) {
      int tamanhoLista = tabela[i].size();
      
      if (tamanhoLista > 10) distribuicao[11]++; // Posições com mais de 10 elementos
      else distribuicao[tamanhoLista]++; // Posições com 0, 1, 2, ... 10 elementos
    }
  }

  // Exibe as estatísticas
  void mostrarEstatisticas() {
    double fatorCarga = static_cast<double>(totalElementos) / tamanho;
    int enderecosUsados = tamanho - distribuicao[0]; // Posições não vazias
    
    cout << endl;
    cout << "╒═══════════════════════════════════════════╕\n";
    cout << "│           ESTATÍSTICAS DA TABELA          │\n";
    cout << "╞═══════════════════════════════════════════╡\n";
    
    cout << setprecision(4) << fixed;
    cout << "│ Tamanho da tabela: " << setw(9) << tamanho << setw(18) << " │\n";
    cout << "│ Total de elementos: " << setw(8) << totalElementos << setw(18) << " │\n";
    cout << "│ Fator de carga: " << setw(13) << fatorCarga << setw(17) << " │\n";
    cout << "│ Total de colisões: " << setw(9) << totalColisoes << setw(18) << " │\n";
    cout << "│ Endereços utilizados: " << setw(7) << enderecosUsados << " (" 
         << setw(8) << (enderecosUsados * 100.0 / tamanho) << "%) │\n";
    cout << "└───────────────────────────────────────────┘\n";
    
    cout << endl;
    cout << "┌───────────────────────────────────────────────┐\n";
    cout << "│       DISTRIBUIÇÃO DE CIDADES POR POSIÇÃO     │\n";
    cout << "├───────┬───────────┬─────────┬─────────────────┤\n";
    cout << "│ Quant.│ Endereços │    %    │   Acumulado %   │\n";
    cout << "├───────┼───────────┼─────────┼─────────────────┤\n";
    
    double acumulado = 0.0;
    for (int i = 0; i < 11; i++) {
      double porcentagem = (distribuicao[i] * 100.0) / tamanho;
      acumulado += porcentagem;
      cout << "│ " << setw(5) << i << " │ " << setw(9) << distribuicao[i] << " │ " 
           << setw(6) << setprecision(2) << porcentagem << "% │ " << setw(10) 
           << setprecision(2) << acumulado << "%     │\n";
    }
    
    double porcentagem = (distribuicao[11] * 100.0) / tamanho;
    acumulado += porcentagem;
    cout << "│   >10 │ " << setw(9) << distribuicao[11] << " │ " 
         << setw(6) << porcentagem << "% │ " << setw(10) << acumulado << "%     │\n";
    
    cout << "└───────┴───────────┴─────────┴─────────────────┘\n";
  }
  
  // Exporta as estatísticas para um arquivo CSV
  void exportarParaCSV(ofstream& arquivo, double tempoExecucao) {
    double fatorCarga = static_cast<double>(totalElementos) / tamanho;
    int enderecosUsados = tamanho - distribuicao[0];
    double porcentagemEnderecos = (enderecosUsados * 100.0) / tamanho;
    
    // Informações gerais da tabela
    arquivo << tamanho << "," 
            << totalElementos << ","
            << fatorCarga << ","
            << totalColisoes << ","
            << enderecosUsados << ","
            << porcentagemEnderecos << ","
            << tempoExecucao;
    
    // Informações de distribuição
    for (int i = 0; i < distribuicao.size(); i++) arquivo << "," << distribuicao[i];
    arquivo << endl;
  }
  
  int getTotalColisoes() const { return totalColisoes; }
  int getTotalElementos() const { return totalElementos; }
  const vector<int>& getDistribuicao() const { return distribuicao; }
};

int main() {
  // Vetores de tamanhos para testar
  vector<int> tamanhos = {853, 1000, 1500, 2000, 2500};
  
  ifstream arquivo("c:/Users/usuario/Desktop/Programas/ED_2/trabalhos/cidades.txt");
  if (!arquivo.is_open()) {
    cerr << "Erro ao abrir o arquivo cidades.txt" << endl;
    return 1;
  }

  // Lê todas as cidades do arquivo
  vector<string> cidades;
  string cidade;
  while (getline(arquivo, cidade)) if (!cidade.empty()) cidades.push_back(cidade);

  arquivo.close();
  
  // Cria o arquivo CSV para exportação
  ofstream csvArquivo("c:/Users/usuario/Desktop/Programas/ED_2/trabalhos/resultados_hash2.csv");
  if (!csvArquivo.is_open()) {
    cerr << "Erro ao criar arquivo de resultados CSV" << endl;
    return 1;
  }
  
  // Escreve o cabeçalho do CSV
  csvArquivo << "Tamanho,Elementos,FatorCarga,Colisoes,EnderecosUsados,PorcentagemEnderecos,TempoExecucao";
  for (int i = 0; i <= 10; i++) csvArquivo << ",Qtd_" << i;
  csvArquivo << ",Qtd_>10" << endl;

  cout << endl;
  cout << "╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍\n";
  cout << "        ANÁLISE DE TABELA HASH DE CIDADES      \n";
  cout << "╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍╍\n";
  cout << "Total de cidades carregadas: " << cidades.size() << endl;

  // Executa para cada tamanho de tabela
  for (int tamanho : tamanhos) {
    TabelaHash tabela(tamanho);
    
    // Marca o início do tempo
    auto inicio = chrono::high_resolution_clock::now();
    
    // Insere todas as cidades na tabela
    for (const string& cidade : cidades) tabela.inserir(cidade);
    
    // Calcula a distribuição
    tabela.calcularDistribuicao();
    
    // Marca o fim do tempo
    auto fim = chrono::high_resolution_clock::now();
    auto duracao = chrono::duration_cast<chrono::microseconds>(fim - inicio);
    double tempoExecucao;
    
    // Determina o valor de tempo a ser usado no CSV (em ms)
    if (duracao.count() > 10000) {
      auto duracaoMs = chrono::duration_cast<chrono::milliseconds>(fim - inicio);
      tempoExecucao = duracaoMs.count();
    } else tempoExecucao = duracao.count() / 1000.0; // Converte μs para ms
    
    // Exporta os resultados para CSV
    tabela.exportarParaCSV(csvArquivo, tempoExecucao);
    
    cout << "┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅" << endl;
    // Tabela de resultados
    cout << "┌───────┬────────────┬────────┬────────────────┐\n";
    cout << "│ Tabela│  Colisões  │ F.Carga│ Tempo (ms/μs)  │\n";
    cout << "├───────┼────────────┼────────┼────────────────┤\n";
    cout << "│ " << setw(5) << tamanho << " │ " << setw(10) << tabela.getTotalColisoes()
         << " │ " << setw(6) << fixed << setprecision(3) 
         << (static_cast<double>(tabela.getTotalElementos()) / tamanho);
    
    // Formata tempo (ms para valores maiores, μs para menores)
    if (duracao.count() > 10000) {
      auto duracaoMs = chrono::duration_cast<chrono::milliseconds>(fim - inicio);
      cout << " │ " << setw(8) << duracaoMs.count() << " ms    │\n";
    } else cout << " │ " << setw(8) << duracao.count() << " μs    │\n";
    cout << "└───────┴────────────┴────────┴────────────────┘\n";

    // Mostra as estatísticas detalhadas
    tabela.mostrarEstatisticas();
    cout << "\n";
  }
  
  csvArquivo.close();
  cout << "Resultados exportados para: c:/Users/usuario/Desktop/Programas/ED_2/trabalhos/resultados_hash2.csv" << endl;

  return 0;
}