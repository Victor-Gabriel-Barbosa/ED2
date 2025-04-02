#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// Classe que implementa o Algoritmo de Blossom (Edmonds)
class Blossom {
private:
  int n;                     // Número de vértices no grafo
  vector<vector<int>> grafo; // Lista de adjacência representando o grafo
  vector<int> match;         // match[v] armazena o parceiro atual de v no emparelhamento ou -1
  vector<int> pai;           // pai[v] indica o antecessor de v na árvore de busca
  vector<int> base;          // base[v] armazena a base da flor que contém v
  vector<bool> visitado;     // Controle de vértices visitados na BFS

  // Encontra a base comum da flor formada por dois vértices u e v
  int encontrarBase(int u, int v) {
    vector<bool> usado(n, false);

    // 1º percurso: sobe na árvore a partir de u e marca as bases
    bool continua = true;
    while (continua) {
      u = base[u];     // Obtém a base atual de u (importante para flores já contraídas)
      usado[u] = true; // Marca esta base
      if (match[u] == -1) { // Se chegou a um vértice livre, para o percurso
        continua = false;
      } else {
        u = pai[match[u]]; // Continua subindo na árvore alternante
      }
    }

    // 2º percurso: sobe na árvore a partir de v até encontrar um vértice marcado
    continua = true;
    while (continua) {
      v = base[v];    // Obtém a base atual de v
      if (usado[v]) { // Se encontrou um vértice já visitado no percurso de u
        continua = false;
      } else {
        v = pai[match[v]]; // Continua subindo na árvore
      }
    }

    return v; // Retorna o vértice base comum encontrado
  }

  // Marca todos os vértices no caminho de u até a base b como pertencentes à mesma flor
  void marcarCaminho(int u, int b) {
    while (base[u] != b) {
      int v = match[u]; // Parceiro atual de u no emparelhamento

      // Atualiza a base de u e seu parceiro para b (contração da flor)
      base[u] = base[v] = b;

      // Continua subindo na árvore alternante
      u = pai[v];
    }
  }

  // Busca em largura (BFS) para encontrar um caminho aumentante
  bool bfs(int raiz) {
    // Inicializa as estruturas para uma nova busca
    for (int i = 0; i < n; i++) {
      pai[i] = -1;         // Nenhum vértice tem pai inicialmente
      base[i] = i;         // Cada vértice é sua própria base no início
      visitado[i] = false; // Nenhum vértice foi visitado
    }

    // Inicia a BFS a partir do vértice raiz (não emparelhado)
    queue<int> q;
    q.push(raiz);
    visitado[raiz] = true;

    // Loop principal do BFS
    while (!q.empty()) {
      int u = q.front();
      q.pop();

      // Examina todos os vizinhos do vértice atual
      for (int v : grafo[u]) {
        // CASO 0: Ignora se v é parceiro de u ou se estão na mesma flor contraída
        if (base[u] == base[v] || match[u] == v) {
          continue;
        }

        // CASO 1: Detecção de ciclo ímpar (flor)
        if (v == raiz || (match[v] != -1 && pai[match[v]] != -1)) {
          // Encontra a base comum da flor
          int b = encontrarBase(u, v);

          // Contrai a flor atualizando as bases dos vértices envolvidos
          marcarCaminho(u, b);
          marcarCaminho(v, b);

          // Adiciona todos os vértices da flor contraída à fila BFS
          for (int i = 0; i < n; i++) {
            if (base[i] == b && !visitado[i]) {
              visitado[i] = true;
              q.push(i);
            }
          }
        }
        // CASO 2: Vértice ainda não visitado - expande a árvore de busca
        else if (pai[v] == -1) {
          pai[v] = u; // Registra u como pai de v

          // SUBCASO 2.1: v é um vértice livre - encontrou um caminho aumentante!
          if (match[v] == -1) {
            // Reconstrói o caminho aumentante e atualiza o emparelhamento
            int atual = v;
            while (atual != -1) {
              int proximo = pai[atual];
              int proxProximo = match[proximo];

              // Atualiza o emparelhamento ao longo do caminho
              match[atual] = proximo;
              match[proximo] = atual;

              // Move para o próximo par no caminho
              atual = proxProximo;
            }
            return true; // Caminho aumentante encontrado e processado
          }

          // SUBCASO 2.2: v já está emparelhado - continua a BFS através do parceiro
          visitado[match[v]] = true;
          q.push(match[v]);
        }
      }
    }

    // Se chegou aqui, nenhum caminho aumentante foi encontrado
    return false;
  }

public:
  // Construtor da classe Blossom
  Blossom(int vertices) : n(vertices) {
    grafo.resize(n);
    match.assign(n, -1); // Inicialmente nenhum vértice está emparelhado
    pai.resize(n);
    base.resize(n);
    visitado.resize(n);
  }

  // Adiciona uma aresta não direcionada ao grafo
  void adicionarAresta(int u, int v) {
    grafo[u].push_back(v);
    grafo[v].push_back(u);
  }

  // Calcula o emparelhamento máximo no grafo
  int emparelhamentoMaximo() {
    int resultado = 0;

    // Para cada vértice não emparelhado, tenta encontrar um caminho aumentante
    for (int i = 0; i < n; i++) {
      if (match[i] == -1 && bfs(i)) {
        resultado++; // Incrementa o contador quando um caminho é encontrado
      }
    }

    return resultado;
  }
};

int main() {
  int casosTeste;
  cin >> casosTeste;

  // Loop para processar cada caso de teste
  while (casosTeste--) {
    // Parâmetros do problema:
    int N, M; // N = total de camisetas, M = número de voluntários
    cin >> N >> M;

    // Mapeamento de tamanhos de camiseta para índices (0-5)
    map<string, int> tamanhoParaIndice = {{"XXL", 0}, {"XL", 1}, {"L", 2},
                                          {"M", 3},   {"S", 4},  {"XS", 5}};

    // Construção do grafo bipartido:
    // - Parte 1: M vértices representando voluntários (índices 0 a M-1)
    // - Parte 2: N vértices representando camisetas (índices M a M+N-1)
    int totalVertices = M + N;
    Blossom blossom(totalVertices);

    // Processa as preferências de cada voluntário
    for (int i = 0; i < M; i++) {
      string tamanho1, tamanho2;
      cin >> tamanho1 >> tamanho2;

      int indice1 = tamanhoParaIndice[tamanho1];
      int indice2 = tamanhoParaIndice[tamanho2];

      // Conecta o voluntário a todas as camisetas dos tamanhos desejados
      // Cada tamanho tem N/6 camisetas disponíveis
      for (int j = 0; j < N / 6; j++) {
        // Adiciona arestas entre o voluntário i e as camisetas dos tamanhos
        // desejados
        blossom.adicionarAresta(i, M + (indice1 * N / 6) + j);
        blossom.adicionarAresta(i, M + (indice2 * N / 6) + j);
      }
    }

    // Verifica se é possível atender todos os voluntários
    int maxMatch = blossom.emparelhamentoMaximo();

    // Se todos os voluntários podem receber camisetas, imprime "YES" 
    // caso contrário, imprime "NO"
    cout << (maxMatch == M ? "YES" : "NO") << endl;
  }

  return 0;
}