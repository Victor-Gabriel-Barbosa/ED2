using namespace std;
#include <bits/stdc++.h>

// Encontra a maior substring comum usando programação dinâmica
int substrPD(string L1, string L2) {
  int M = 0, tamL1 = L1.length(), tamL2 = L2.length();
  vector<vector<int>> pd(tamL1 + 1, vector<int>(tamL2 + 1, 0));

  // Preenche a matriz de programação dinâmica
  for (int i = 1; i < tamL1 + 1; i++) {
    for (int j = 1; j < tamL2 + 1; j++) {
      if (L1[i - 1] == L2[j - 1]) {
        // Atualiza o maior comprimento se encontra uma substring maior
        M = max(M, (pd[i][j] = pd[i - 1][j - 1] + 1));
      }
    }
  }

  return M;
}

int main() {
  string L1, L2;

  // Lê e processa as entradas
  while (getline(cin, L1) && getline(cin, L2)) cout << substrPD(L1, L2) << endl;

  return 0;
}