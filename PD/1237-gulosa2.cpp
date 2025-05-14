#include <bits/stdc++.h>
using namespace std;

int substrGulosa(string L1, string L2) {
  int M = 0, tam = L1.length();

  for (int i = 0; i < tam; ++i) {
    for (int j = i + 1; j <= tam; ++j) {
      string substr = L1.substr(i, j - i);
      if (L2.find(substr) != string::npos && substr.length() > M) M = substr.length();
    }
  }

  return M;
}

int main() {
  string L1, L2;

  while (getline(cin, L1) && getline(cin, L2)) cout << substrGulosa(L1, L2) << endl;

  return 0;
}