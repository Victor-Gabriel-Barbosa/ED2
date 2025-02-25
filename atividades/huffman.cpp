#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// Estrutura do nó da árvore de Huffman
struct Node {
  char ch;
  int freq;
  Node *left, *right;

  Node(char c, int f) {
    ch = c;
    freq = f;
    left = right = nullptr;
  }
};

// Comparador para a fila de prioridade
struct Compare {
  bool operator()(Node* l, Node* r) {
    return l->freq > r->freq;
  }
};

class HuffmanCoding {
private:
  // Mapeia caracteres para seus códigos Huffman
  unordered_map<char, string> huffmanCodes;
  
  // Gera os códigos Huffman recursivamente
  void gerarCodigos(Node* raiz, string str) {
    if (!raiz) return;
        
    // Encontrou uma folha
    if (!raiz->left && !raiz->right) huffmanCodes[raiz->ch] = str;
    
    gerarCodigos(raiz->left, str + "0");
    gerarCodigos(raiz->right, str + "1");
  }
    
public:
  // Constrói a árvore de Huffman e retorna a raiz
  Node* construirArvoreHuffman(string texto) {
    // Conta a frequência de cada caractere
    unordered_map<char, int> freq;
    for (char c : texto) freq[c]++;
    
    // Cria fila de prioridade mínima
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    
    // Cria um nó folha para cada caractere e adiciona à fila
    for (auto pair : freq) minHeap.push(new Node(pair.first, pair.second));
    
    // Constrói a árvore de Huffman
    while (minHeap.size() > 1) {
      Node *esquerda = minHeap.top(); minHeap.pop();
      Node *direita = minHeap.top(); minHeap.pop();
      
      Node *novo = new Node('$', esquerda->freq + direita->freq);
      novo->left = esquerda;
      novo->right = direita;
      
      minHeap.push(novo);
    }
    
    return minHeap.top();
  }
  
  // Codifica o texto usando a árvore de Huffman
  string codificar(string texto) {
    Node* raiz = construirArvoreHuffman(texto);
    
    // Gera códigos Huffman para cada caractere
    gerarCodigos(raiz, "");
    
    // Codifica o texto
    string textoCodificado = "";
    for (char c : texto) textoCodificado += huffmanCodes[c];
    
    return textoCodificado;
  }
  
  // Decodifica o texto usando a árvore de Huffman
  string decodificar(string textoCodificado, Node* raiz) {
    string textoDecodificado = "";
    Node* atual = raiz;
    
    for (char bit : textoCodificado) {
      if (bit == '0') atual = atual->left;
      else atual = atual->right;
      
      // Encontrou uma folha
      if (!atual->left && !atual->right) {
        textoDecodificado += atual->ch;
        atual = raiz;
      }
    }
    
    return textoDecodificado;
  }
  
  // Imprime os códigos Huffman para cada caractere
  void imprimirCodigos() {
    cout << "Códigos Huffman:" << endl;
    for (auto pair : huffmanCodes) cout << pair.first << ": " << pair.second << endl;
  }
};

// Função principal para demonstração
int main() {
  string texto;
  cout << "Digite o texto para compressão: ";
  getline(cin, texto);
  
  HuffmanCoding huffman;
  string textoCodificado = huffman.codificar(texto);
  
  cout << "\nTexto original: " << texto << endl;
  cout << "Texto codificado: " << textoCodificado << endl;
  
  huffman.imprimirCodigos();
  
  Node* raiz = huffman.construirArvoreHuffman(texto);
  string textoDecodificado = huffman.decodificar(textoCodificado, raiz);
  
  cout << "\nTexto decodificado: " << textoDecodificado << endl;
  
  // Calcula e exibe a taxa de compressão
  float taxaCompressao = (float)(textoCodificado.length()) / (texto.length() * 8) * 100;
  cout << "\nTaxa de compressão: " << taxaCompressao << "%" << endl;
  
  return 0;
}