import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Stack;

public class testeED2 {
    public static void main(String[] args) {
        // Lista
        ArrayList<Integer> lista = new ArrayList<>();
        lista.add(1);
        lista.remove(0);
        System.out.println("Lista vazia: " + lista.isEmpty());

        // Fila
        LinkedList<Integer> fila = new LinkedList<>();
        fila.add(1);
        fila.remove();
        System.out.println("Fila vazia: " + fila.isEmpty());
 
        // Pilha
        Stack<Integer> pilha = new Stack<>();
        pilha.push(1);
        pilha.pop();
        System.out.println("Pilha vazia: " + pilha.isEmpty());

        // Árvore - exemplo de criação
        Node raiz = new Node(10);
        raiz.left = new Node(5);
        raiz.right = new Node(15);
        System.out.println("Valor da raiz: " + raiz.value);
    }

    // Classe Node
    static class Node {
        int value;
        Node left, right;

        Node(int value) {
            this.value = value;
            left = right = null;
        }
    }
}