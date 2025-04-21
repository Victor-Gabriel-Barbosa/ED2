using namespace std;
#include <bits/stdc++.h>

// Encontra a maior substring comum usando abordagem gulosa
int substrGulosa(string L1, string L2) {
  int M = 0, K = 0, tamL1 = L1.length(), tamL2 = L2.length();

  // Percorre todas as posições possíveis nas duas strings
  for (int i = 0; i < tamL1; i++) {
    for (int j = 0; j < tamL2; j++) {
      // Tenta encontrar uma substring comum a partir das posições i e j
      while ((tamL1 > i + K) && (tamL2 > j + K) && (L1[i + K] == L2[j + K])) K++;

      // Atualiza o maior comprimento se encontrou uma substring maior
      M = max(M, K);
      K = 0; 
    }
  }

  return M;
}

int main() {
  string L1, L2;
  
  // Recebe e processa as entradas
  while (getline(cin, L1) && getline(cin, L2)) cout << substrGulosa(L1, L2) << endl;

  return 0;
}