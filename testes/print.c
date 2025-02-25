#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da "classe" Obj
typedef struct Obj {
    char *nome;
    int id;

    // Métodos (ponteiros para função)
    void (*print)(struct Obj*);
    void (*destroy)(struct Obj*);
} Obj;

// Método print
void obj_print(Obj *self) {
    printf("Objeto: %s, ID: %d\n", self->nome, self->id);
}

// Método destroy (libera memória)
void obj_destroy(Obj *self) {
    free(self->nome);
    free(self);
}

// "Construtor" - cria um novo objeto
Obj *newObj(const char *nome, int id) {
    Obj *self = malloc(sizeof(Obj));
    if (!self) return NULL;

    self->nome = strdup(nome);
    self->id = id;
    
    // Atribuindo os métodos
    self->print = obj_print;
    self->destroy = obj_destroy;
    
    return self;
}

// Testando nossa "classe"
int main() {
    Obj *meuObjeto = newObj("MeuObjeto", 42);
    if (!meuObjeto) return 1;

    meuObjeto->print(meuObjeto); // Chama o "método" print
    meuObjeto->destroy(meuObjeto); // Chama o "método" destroy

    return 0;
}
