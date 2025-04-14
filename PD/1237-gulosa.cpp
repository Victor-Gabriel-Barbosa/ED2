using namespace std;
#include <bits/stdc++.h>

// Encontra a maior substring comum usando abordagem gulosa
int substringGulosa(string linha1, string linha2) {
  int tam1 = linha1.length();
  int tam2 = linha2.length();
  int maiorComprimento = 0;

  // Percorre todas as posições possíveis nas duas strings
  for (int i = 0; i < tam1; i++) {
    for (int j = 0; j < tam2; j++) {
      // Tenta encontrar uma substring comum a partir das posições i e j
      int k = 0;
      while ((i + k < tam1) && (j + k < tam2) && (linha1[i + k] == linha2[j + k])) k++;

      // Atualiza o maior comprimento se encontrou uma substring maior
      maiorComprimento = max(maiorComprimento, k);
    }
  }

  return maiorComprimento;
}

int main() {
  string linha1, linha2;

  // Lê as strings até o final da entrada
  while (getline(cin, linha1) && getline(cin, linha2)) cout << substringGulosa(linha1, linha2) << endl;

  return 0;
}