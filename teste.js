// Lista
let lista = [1, 2, 3];
lista.push(4);
lista.splice(1, 1);

// Fila
class Fila {
    constructor() {
        this.items = [];
    }
    enqueue(item) {
        this.items.push(item);
    }
    dequeue() {
        return this.items.shift();
    }
}
let fila = new Fila();
fila.enqueue(1);
fila.dequeue();

// Pilha
let pilha = [];
pilha.push(1);
pilha.pop();

// Árvore
class Node {
    constructor(value) {
        this.value = value;
        this.left = null;
        this.right = null;
    }
}

console.log('1' * '12');
console.log('2' * '5');