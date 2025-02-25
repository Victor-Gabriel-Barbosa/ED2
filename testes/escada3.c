#include <stdio.h>

int main() {
  int N, cont = 1, temp;
  scanf("%d", &N);
  int escada[N][N];

  for (int i = 0; i < N; i++) {
    escada[i][i] = cont++;
    temp = N;
    for (int j = i + 1; j < N; j++) escada[j][i] = escada[j-1][i] + temp--;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; i >= j; j++) printf("%d ", escada[i][j]);
    printf("\n");
  }

  return 0;
}