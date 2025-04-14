using namespace std;
#include <bits/stdc++.h>

// Encontra a maior substring comum usando programação dinâmica
int substringPD(string linha1, string linha2) {
  int tam1 = linha1.length();
  int tam2 = linha2.length();
  int maiorComprimento = 0;

  // Armazena os resultados de subproblemas
  // pd[i][j] = tamanho da maior substring comum que termina em linha1[i-1] e linha2[j-1]
  vector<vector<int>> pd(tam1 + 1, vector<int>(tam2 + 1, 0));

  // Preenche a matriz de programação dinâmica
  for (int i = 1; i <= tam1; i++) {
    for (int j = 1; j <= tam2; j++) {
      // Se os caracteres atuais correspondem
      if (linha1[i - 1] == linha2[j - 1]) {
        // Estende a substring comum em 1
        pd[i][j] = pd[i - 1][j - 1] + 1;

        // Atualiza o maior comprimento se encontra uma substring maior
        maiorComprimento = max(maiorComprimento, pd[i][j]);
      }
    }
  }

  return maiorComprimento;
}

int main() {
  string linha1, linha2;

  // Lê as strings até o final da entrada
  while (getline(cin, linha1) && getline(cin, linha2)) cout << substringPD(linha1, linha2) << endl;

  return 0;
}