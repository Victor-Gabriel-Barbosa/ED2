/*
Implemente o algoritmo Naive String Matcher, considerando:
- O algoritmo deve aceitar um caractere coringa no Padrão
- O caractere coringa pode ocorrer várias vezes no Padrão, nenhuma vez no Texto

Implemente o algoritmo Rabin Karp Matcher
- Dado um texto, encontrar a ocorrência de qualquer padrão dentre um conjunto de padrões de comprimentos diferentes.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<int> verificaCoringa (string texto, string padrao, char coringa = '*') {
  vector<int> ocorrencias;
  int n = texto.length();
  int m = padrao.length();
  
  for (int i = 0; i <= n - m; i++) {
    bool match = true;
    for (int j = 0; j < m && match; j++) {
      if (padrao[j] != coringa && padrao[j] != texto[i + j]) match = false;
    }
    if (match) ocorrencias.push_back(i);
  }
  return ocorrencias;
}

long long calculaHash(string& str, int inicio, int fim) {
  const int p = 31;
  const int m = 1e9 + 9;
  long long hash_value = 0;
  long long p_pow = 1;
  
  for (int i = inicio; i < fim; i++) {
    hash_value = (hash_value + (str[i] - 'a' + 1) * p_pow) % m;
    p_pow = (p_pow * p) % m;
  }
  return hash_value;
}

vector<pair<int, string>> rabinKarpMultiPadroes(string texto, vector<string>& padroes) {
  vector<pair<int, string>> resultados;
  unordered_map<long long, vector<string>> hash_padroes;
  
  for (string& padrao : padroes) {
    long long hash = calculaHash(padrao, 0, padrao.length());
    hash_padroes[hash].push_back(padrao);
  }
  
  for (int i = 0; i < texto.length(); i++) {
    for (string& padrao : padroes) {
      if (i + padrao.length() <= texto.length()) {
        long long hash_atual = calculaHash(texto, i, i + padrao.length());
        
        if (hash_padroes.find(hash_atual) != hash_padroes.end()) {
          for (string& p : hash_padroes[hash_atual]) {
            if (texto.substr(i, p.length()) == p) resultados.push_back({i, p});
          }
        }
      }
    }
  }
  return resultados;
}

int main() {
  string texto1 = "ABCDEFGHIJK";
  string padrao1 = "A*C";
  vector<int> res1 = verificaCoringa(texto1, padrao1);
  
  cout << "Naive String Matcher com coringa:\n";
  for (int pos : res1) cout << "Padrão encontrado na posição: " << pos << endl;
  
  string texto2 = "AABAACAADAABAAABAA";
  vector<string> padroes = {"AA", "AAB", "AABA"};
  vector<pair<int, string>> res2 = rabinKarpMultiPadroes(texto2, padroes);
  
  cout << "\nRabin-Karp com múltiplos padrões:\n";
  for (auto& match : res2) cout << "Padrão \"" << match.second << "\" encontrado na posição: " << match.first << endl;
  
  return 0;
}