/* Pesquisa Sequencial e Binária
Busca e Compressão
Instruções
Desenvolva um sistema que gere aleatoriamente 100 números com valores entre 0 e 100.
Implemente a busca Sequencial para encontrar todas as ocorrências de um determinado valor dentro da coleção
1. Exiba a quantidade de vezes que o valor apareceu e as posições.
2. Exiba a quantidade de verificações que foram realizadas

Implemente a busca binária para encontrar todas as ocorrências de um determinado valor dentro da coleção
1. Exiba a quantidade de vezes que o valor apareceu e as posições.
2. Exiba a quantidade de verificações que foram realizadas */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void imprimeVet(int vet[], int tam) {
  for(int i = 0; i < tam; i++) {
    cout << vet[i] << " ";
    if((i + 1) % 10 == 0) cout << endl;
  }
}

void imprimeResultados(vector<int>& posi, int ver) {
  if(!posi.empty()) {
    cout << "O valor foi encontrado " << posi.size() << " vez(es)" << endl;
    cout << "Posições: ";
    for(size_t i = 0; i < posi.size(); i++) {
      cout << posi[i];
      if(i < posi.size() - 1) cout << ", ";
    }
    cout << endl;
  } else {
    cout << "Valor não encontrado" << endl;
  }
  cout << "Quantidade de verificações realizadas: " << ver << endl;
}

int primeiraOcorrencia(int vet[], int tam, int valor, int& ver) {
  int inicio = 0;
  int fim = tam - 1;
  
  while(inicio <= fim) {
    ver++;
    int meio = (inicio + fim) / 2;
    
    if(vet[meio] == valor) return meio;
    else if(vet[meio] < valor) inicio = meio + 1;
    else fim = meio - 1;
  }
  
  return -1;
}

void buscaBinaria(int vet[], int tam, int valor) {
  vector<int> posi;
  int ver = 0;
  
  int indice = primeiraOcorrencia(vet, tam, valor, ver);
  
  if(indice != -1) {
    posi.push_back(indice);
    
    int i = indice - 1;
    while(i >= 0 && vet[i] == valor) {
      ver++;
      posi.push_back(i);
      i--;
    }
    
    i = indice + 1;
    while(i < tam && vet[i] == valor) {
      ver++;
      posi.push_back(i);
      i++;
    } 
  }
  
  imprimeResultados(posi, ver);
}

void buscaSequencial(int vet[], int tam, int valor) {
  vector<int> posi;
  int ver = 0;
  
  for(int i = 0; i < tam; i++) {
    ver++;
    if(vet[i] == valor) posi.push_back(i);
  }
  
  imprimeResultados(posi, ver);
}

int main() {
  const int TAM = 100;
  int numeros[TAM];
  
  srand(time(0));
  
  for(int i = 0; i < TAM; i++) numeros[i] = rand() % 101;
  
  sort(numeros, numeros + TAM);
  
  cout << "Vetor gerado e ordenado:" << endl;
  imprimeVet(numeros, TAM);
  
  int busca;
  cout << "\nDigite um número para buscar: ";
  cin >> busca;
  
  cout << "\n--- Busca Sequencial ---" << endl;
  buscaSequencial(numeros, TAM, busca);
  
  cout << "\n--- Busca Binária ---" << endl;
  buscaBinaria(numeros, TAM, busca);
  
  return 0;
}