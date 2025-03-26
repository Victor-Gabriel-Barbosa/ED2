#define MAX_INSTRUCOES 2000
#define TAMANHO_MAX_NOME_VAR 8

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registro {
  char *nome;
  int tipo;
} Registrador;

typedef struct intervalo {
  int inicio;
  int fim;
} Intervalo;

typedef struct no_registro {
  Registrador reg;
  void *proximo;
} NoRegistrador;

typedef struct instrucao {
  int operacao;
  char **tokens;
} Instrucao;

enum { literal, expressao };

#define ASCII_MINUSCULO_A 97
#define ASCII_MINUSCULO_Z 122
#define ASCII_MAIUSCULO_A 65
#define ASCII_MAIUSCULO_Z 90

enum { declaracao, soma };

#define ASCII_ZERO 48
#define ASCII_NOVE 57

NoRegistrador *cabeca = NULL;

int noIntervalo(int numArgs, ...) {
  va_list listaVA;
  va_start(listaVA, numArgs);
  int resultado = 0, i, n;
  Intervalo intervalo;

  for (i = 0; i < numArgs; i++) {
    if (i == 0) {
      n = va_arg(listaVA, int);
    } else {
      intervalo = va_arg(listaVA, Intervalo);
      resultado =
          (n - intervalo.inicio) * (n - intervalo.fim) <= 0 ? 1 : resultado;
    }
  }

  va_end(listaVA);

  return resultado;
}

void inserirPrimeiro(Registrador dados) {
  NoRegistrador *ligacao = (NoRegistrador *)malloc(sizeof(NoRegistrador));

  ligacao->reg = dados;
  ligacao->proximo = cabeca;
  cabeca = ligacao;
}

NoRegistrador *encontrar(char *chave) {
  NoRegistrador *atual = cabeca;

  if (cabeca == NULL) {
    return NULL;
  }

  while (strcmp(atual->reg.nome, chave) != 0) {
    if (atual->proximo == NULL) {
      return NULL;
    } else {
      atual = atual->proximo;
    }
  }

  return atual;
}

NoRegistrador *deletar(char chave) {
  NoRegistrador *atual = cabeca;
  NoRegistrador *anterior = NULL;
  if (cabeca == NULL)
    return NULL;

  while (strcmp(atual->reg.nome, chave) != 0) {
    if (atual->proximo == NULL)
      return NULL;
    else {
      anterior = atual;
      atual = atual->proximo;
    }
  }

  if (atual == cabeca)
    cabeca = cabeca->proximo;
  else
    anterior->proximo = atual->proximo;

  return atual;
}

Instrucao extrairDadosInstrucao(char *linhaCodigo) {
  int i = 0, passo = 0;
  Instrucao inst;
  char *token;
  inst.tokens = malloc(sizeof(char *));

  token = strtok(linhaCodigo, " ");

  while (token != NULL) {
    switch (passo++) {
    case 0:
      inst.tokens[0] = malloc(strlen(token) + 1);
      strcpy(inst.tokens[0], token);
      break;
    case 1:
      if (strcmp(token, ":=") != 0) {
        token = NULL;
        continue;
      }
      break;
    case 2:
      inst.tokens[1] = calloc(strlen(token) + 1, sizeof(char));
      strcpy(inst.tokens[1], token);
      break;
    case 3:
      if (strcmp(token, "+") != 0) {
        token = NULL;
        continue;
      }
      break;
    case 4:
      inst.tokens[2] = calloc(11, sizeof(char));
      strcpy(inst.tokens[2], token);
      break;
    default:
      break;
    }
    token = strtok(NULL, " ");
  }
  if (passo == 2 || passo == 4)
    return (Instrucao){.tokens = NULL, .operacao = -1};

  inst.operacao = (passo == 5) ? soma : declaracao;
  return inst;
}

int definirRegistrador(Instrucao inst) {
  Registrador reg;
  int i, tiposValor[2] = {literal}, tamanhoNome = strlen(inst.tokens[0]);

  if (tamanhoNome > 8)
    return 0;

  reg.nome = malloc(tamanhoNome * sizeof(char));
  strcpy(reg.nome, inst.tokens[0]);

  switch (inst.operacao) {
  case declaracao:
    reg.tipo = literal;
    break;
  case soma:
    reg.tipo = literal;
    for (i = 1; i <= 2; i++) {
      if (noIntervalo(3, inst.tokens[i][0],
                      (Intervalo){.inicio = ASCII_MINUSCULO_A,
                                  .fim = ASCII_MINUSCULO_Z},
                      (Intervalo){.inicio = ASCII_MAIUSCULO_A,
                                  .fim = ASCII_MAIUSCULO_Z})) {
        reg.tipo = expressao;
        tiposValor[i - 1] = expressao;
      }
    }
    break;
  }

  if (encontrar(reg.nome))
    return 0;

  inserirPrimeiro(reg);

  NoRegistrador *var;
  int controle = 0;

  for (i = 0; i < 2; i++) {
    if (tiposValor[i] == expressao) {
      var = encontrar(inst.tokens[i + 1]);
      controle += var->reg.tipo == literal;
    } else
      controle++;
  }
  return controle == 2;
}

int main() {
  int i, j, numInstrucoes;
  char caracterAtual;
  Instrucao instrucao;

  char **listaInstrucoes = malloc(MAX_INSTRUCOES * sizeof(char *));
  for (i = 0; i < MAX_INSTRUCOES; i++)
    listaInstrucoes[i] = calloc((TAMANHO_MAX_NOME_VAR * 3 + 8), sizeof(char));

  i = 0;
  j = 0;

  while (1) {
    caracterAtual = getchar();
    if (caracterAtual == 10) {
      if (j == 0)
        break;
      else {
        j = 0;
        i++;
        continue;
      }
    }
    listaInstrucoes[i][j++] = caracterAtual;
  }

  numInstrucoes = i;

  for (i = 0; i < numInstrucoes; i++) {
    instrucao = extrairDadosInstrucao(listaInstrucoes[i]);
    for (j = 0; j < strlen(instrucao.tokens[0]); j++) {
      if (!noIntervalo(3, instrucao.tokens[0][j],
                       (Intervalo){.inicio = ASCII_MINUSCULO_A,
                                   .fim = ASCII_MINUSCULO_Z},
                       (Intervalo){.inicio = ASCII_MAIUSCULO_A,
                                   .fim = ASCII_MAIUSCULO_Z})) {
        printf("Compilation Error\n");
        return 0;
      }
    }
    if (!definirRegistrador(instrucao)) {
      printf("Compilation Error\n");
      return 0;
    }
  }

  printf("OK\n");

  return 0;
}