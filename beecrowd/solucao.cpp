#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

bool ehVariavel(const string& s) {
    if (s.empty() || s.length() > 8) return false;
    for (char c : s) {
        if (c < 'a' || c > 'z') return false;
    }
    return true;
}

bool ehInteiro(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

int main() {
    string linha;
    unordered_set<string> variaveisFonte;
    unordered_map<string, bool> variaveisAtribuidas;

    while (getline(cin, linha)) {
        if (linha.empty()) continue;

        istringstream fluxoEntrada(linha);
        string destino, atribuicao, fonte1, operador, fonte2;

        fluxoEntrada >> destino >> atribuicao;
        if (atribuicao != ":=") {
            cout << "Compilation Error" << endl;
            return 0;
        }

        if (!ehVariavel(destino)) {
            cout << "Compilation Error" << endl;
            return 0;
        }

        if (variaveisAtribuidas.find(destino) != variaveisAtribuidas.end()) {
            cout << "Compilation Error" << endl;
            return 0;
        }
        variaveisAtribuidas[destino] = true;

        fluxoEntrada >> fonte1;
        if (fluxoEntrada >> operador) { // Instrução de soma
            if (operador != "+") {
                cout << "Compilation Error" << endl;
                return 0;
            }

            fluxoEntrada >> fonte2;
            if (ehVariavel(fonte1)) {
                if (variaveisAtribuidas.find(fonte1) == variaveisAtribuidas.end()) {
                    cout << "Compilation Error" << endl;
                    return 0;
                }
                variaveisFonte.insert(fonte1);
            } else if (!ehInteiro(fonte1)) {
                cout << "Compilation Error" << endl;
                return 0;
            }

            if (ehVariavel(fonte2)) {
                if (variaveisAtribuidas.find(fonte2) == variaveisAtribuidas.end()) {
                    cout << "Compilation Error" << endl;
                    return 0;
                }
                variaveisFonte.insert(fonte2);
            } else if (!ehInteiro(fonte2)) {
                cout << "Compilation Error" << endl;
                return 0;
            }
        } else { // Instrução de declaração
            if (!ehInteiro(fonte1)) {
                cout << "Compilation Error" << endl;
                return 0;
            }
        }

        if (variaveisFonte.size() > 2) {
            cout << "Compilation Error" << endl;
            return 0;
        }
    }

    cout << "OK" << endl;
    return 0;
}