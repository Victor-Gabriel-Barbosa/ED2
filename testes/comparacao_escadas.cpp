#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <list>
using namespace std;

// Implementação da primeira solução (HashTable)
class HashTable {
private:
  int M, ctPulos = 0;
  vector<list<int>> tabela;

public:
  HashTable(int tam) : M(tam) {
    tabela.resize(M);
  }

  void push(int chave) {
    int posi = (chave - 1 + ctPulos) % M;
    while (posi < M) {
      if ((int)tabela[posi].size() < posi + 1) {
        tabela[posi].push_front(chave);
        return;
      }
      posi++; 
      ctPulos++;
    }
  }

  void print() {
    for (int i = 0; i < M; i++) {
      for (int chave : tabela[i]) cout << chave << " ";
      cout << endl;
    }
  }
};

void solucao1(int N, bool imprimir = false) {
    HashTable escada(N);
    for (int i = 1; i <= (N * (N + 1)) / 2; i++) 
        escada.push(i);
    if (imprimir) escada.print();
}

void escada2(int N, bool imprimir = false) {
    int cont = 1, temp;
    int escada[N][N];

    for (int i = 0; i < N; i++) {
        escada[i][i] = cont++;
        temp = N;
        for (int j = i + 1; j < N; j++) 
            escada[j][i] = escada[j-1][i] + temp--;
    }

    if (imprimir) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; i >= j; j++) 
                cout << escada[i][j] << " ";
            cout << endl;
        }
    }
}

int main() {
    vector<int> tamanhos = {5, 10, 50, 100, 500};
    const int NUM_TESTES = 10000; // número de execuções para cada tamanho

    cout << "Comparação de tempo de execução (média de " << NUM_TESTES << " execuções):\n\n";
    cout << setw(10) << "N" << setw(20) << "HashTable (µs)" << setw(20) << "Array (µs)" << endl;
    cout << string(50, '-') << endl;

    for (int N : tamanhos) {
        long long tempo_total1 = 0;
        long long tempo_total2 = 0;

        for (int teste = 0; teste < NUM_TESTES; teste++) {
            // Teste da primeira solução (HashTable)
            auto inicio1 = chrono::high_resolution_clock::now();
            solucao1(N, false);
            auto fim1 = chrono::high_resolution_clock::now();
            tempo_total1 += chrono::duration_cast<chrono::microseconds>(fim1 - inicio1).count();

            // Teste da segunda solução (Array)
            auto inicio2 = chrono::high_resolution_clock::now();
            escada2(N, false);
            auto fim2 = chrono::high_resolution_clock::now();
            tempo_total2 += chrono::duration_cast<chrono::microseconds>(fim2 - inicio2).count();
        }

        double media1 = tempo_total1 / (double)NUM_TESTES;
        double media2 = tempo_total2 / (double)NUM_TESTES;

        cout << setw(10) << N 
             << setw(20) << fixed << setprecision(2) << media1 
             << setw(20) << fixed << setprecision(2) << media2 << endl;
    }

    return 0;
}
