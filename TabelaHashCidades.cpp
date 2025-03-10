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
  vector<pair<string, bool>> tabela; // Cada entrada agora é um par (cidade, ocupado)
  int totalColisoes;
  vector<int> distribuicao; 
  int totalElementos;

public:
  TabelaHash(int tam) {
    tamanho = tam;
    tabela.resize(tamanho, {"", false}); // Inicializa com pares vazios (não ocupados)
    totalColisoes = 0;
    totalElementos = 0;
    distribuicao.resize(12, 0); // Para armazenar contagem de 0, 1, 2, ..., 10, >10 elementos
  }

  // Função hash que combina códigos ASCII das letras
  int hash(const string& cidade) {
    unsigned long hash = 0;
    for (char c : cidade) hash = hash * 31 + static_cast<unsigned char>(c);
    return hash % tamanho;
  }

  // Insere uma cidade na tabela hash usando método da divisão (sondagem linear)
  void inserir(const string& cidade) {
    int indice = hash(cidade);
    int indiceOriginal = indice;
    bool colisaoOcorreu = false;
    
    // Se a posição já está ocupada, procura próxima posição livre
    while (tabela[indice].second) {
      // Se a cidade já existe na tabela, não insere novamente
      if (tabela[indice].first == cidade) return;
      
      // Registramos colisão na primeira ocorrência
      if (!colisaoOcorreu) {
        totalColisoes++;
        colisaoOcorreu = true;
      }
      
      // Sondagem linear
      indice = (indice + 1) % tamanho;
      
      // Se voltamos ao ponto inicial, a tabela está cheia
      if (indice == indiceOriginal) {
        cerr << "Tabela cheia! Impossível inserir." << endl;
        return;
      }
    }
    
    // Adiciona a cidade na posição encontrada
    tabela[indice].first = cidade;
    tabela[indice].second = true;
    totalElementos++;
  }

  // Calcula as estatísticas de distribuição (este conceito muda com endereçamento aberto)
  void calcularDistribuicao() {
    // Reseta a distribuição para recalcular
    fill(distribuicao.begin(), distribuicao.end(), 0);
    
    // No método da divisão, não temos listas, apenas posições ocupadas ou não
    // Então a distribuição seria basicamente: distribuicao[0] = posições vazias, distribuicao[1] = posições ocupadas
    for (int i = 0; i < tamanho; i++) {
      if (tabela[i].second) {
        distribuicao[1]++; // Posição ocupada
      } else {
        distribuicao[0]++; // Posição vazia
      }
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
           << setprecision(2) << acumulado << "% │\n";
    }
    
    double porcentagem = (distribuicao[11] * 100.0) / tamanho;
    acumulado += porcentagem;
    cout << "│   >10 │ " << setw(9) << distribuicao[11] << " │ " 
         << setw(6) << porcentagem << "% │ " << setw(10) << acumulado << "% │\n";
    
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
  
  // Getters para uso no main
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
  ofstream csvArquivo("c:/Users/usuario/Desktop/Programas/ED_2/trabalhos/resultados_hash.csv");
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
    
    // Formatar tempo (ms para valores maiores, μs para menores)
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
  cout << "Resultados exportados para: c:/Users/usuario/Desktop/Programas/ED_2/trabalhos/resultados_hash.csv" << endl;

  return 0;
}
