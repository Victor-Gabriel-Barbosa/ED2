#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct InfoVar {
  int linhaDefinicao; // Linha em que a variável foi definida
  int ultimoUso;      // Última linha em que a variável é usada como operando
  bool utilizada; // Indica se a variável aparece como fonte (operando)
};

// Verifica se o token é um número (constante)
bool ehNumero(const string &s) {
  for (char c : s) if (!isdigit(c)) return false;
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  unordered_map<string, InfoVar> variaveis;
  vector<string> linhas;
  string linha;
  while (getline(cin, linha)) {
    if (linha.empty()) continue; // Ignora linhas vazias
    linhas.push_back(linha);
  }

  int n = linhas.size();

  // Processa cada instrução
  for (int i = 0; i < n; i++) {
    istringstream fluxoEntrada(linhas[i]);
    vector<string> tokens;
    string token;
    while (fluxoEntrada >> token) tokens.push_back(token);
  
    // Instrução de declaração: "A := B" (3 tokens)
    if (tokens.size() == 3) {
      string variavel = tokens[0];
      // Se a variável já foi definida, erro
      if (variaveis.find(variavel) != variaveis.end()) {
        cout << "Compilation error";
        return 0;
      }
      // O token B deve ser um número
      if (!ehNumero(tokens[2])) {
        cout << "Compilation error";
        return 0;
      }
      InfoVar informacao;
      informacao.linhaDefinicao = i + 1;
      informacao.ultimoUso = -1; // Ainda não foi usada como operando
      informacao.utilizada = false;
      variaveis[variavel] = informacao;
    }
    // Instrução de soma: "A := B + C" (5 tokens)
    else if (tokens.size() == 5) {
      string variavel = tokens[0];
      // Verifica atribuição única
      if (variaveis.find(variavel) != variaveis.end()) {
        cout << "Compilation error";
        return 0;
      }
      // Para cada operando (tokens[2] e tokens[4])
      for (int j = 2; j <= 4; j += 2) {
        // Se o operando não for um número, deve ser variável já definida
        if (!ehNumero(tokens[j])) {
          if (variaveis.find(tokens[j]) == variaveis.end()) {
            cout << "Compilation error";
            return 0;
          }
          // Atualiza o último uso da variável para a linha atual
          InfoVar &informacao = variaveis[tokens[j]];
          informacao.utilizada = true;
          informacao.ultimoUso = max(informacao.ultimoUso, i + 1);
        }
      }
      // Registra a variável de destino
      InfoVar informacao;
      informacao.linhaDefinicao = i + 1;
      informacao.ultimoUso = -1;
      informacao.utilizada = false;
      variaveis[variavel] = informacao;
    } else {
      // Formato inesperado
      cout << "Compilation error";
      return 0;
    }
  }

  // Cria os intervalos de vida para as variáveis que foram usadas como operando
  // O intervalo é [linhaDefinicao, ultimoUso]
  vector<pair<int, int>> intervalos;
  for (auto &p : variaveis) {
    InfoVar informacao = p.second;
    if (informacao.utilizada) intervalos.push_back({informacao.linhaDefinicao, informacao.ultimoUso});
  }

  // Usa sweep‑line para contar o número máximo de intervalos sobrepostos
  vector<pair<int, int>> eventos;
  for (auto &intervalo : intervalos) {
    eventos.push_back({intervalo.first, 1});
    eventos.push_back({intervalo.second + 1, -1});
  }
  sort(eventos.begin(), eventos.end());
  int atual = 0, maxVivas = 0;
  for (auto &ev : eventos) {
    atual += ev.second;
    maxVivas = max(maxVivas, atual);
  }
  // Se em algum ponto mais de 2 variáveis estão vivas, não compila
  if (maxVivas > 2) cout << "Compilation error";
  else cout << "OK";

  return 0;
}
