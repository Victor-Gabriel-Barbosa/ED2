#include <iostream>
#include <list>
#include <vector>
using namespace std;

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

int main() {
  int N;
  cin >> N;
  HashTable escada(N);

  for (int i = 1; i <= (N * (N + 1)) / 2; i++) escada.push(i);
  escada.print();

  return 0;
}