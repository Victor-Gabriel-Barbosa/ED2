#include <iostream>
#include <list>
#include <string>
#include "../utils/extra.hpp"
using namespace std;

auto listaPares(const int& N) {
  list<int> par;
  for (int i = 0; i < N; i+=2) par.push_back(i);
  return par;
}

int main() {
  PrintConfig config("", "e", 2, true, true);
  list<int> par;
  list<string> pal;
  for (int i = 0; i < 10; i++) pal.push_back("Ana" + to_string(i));
  par = listaPares(10);
  print(par);
  PrintConfig conf(" ", "", 6, true, false);
  configure(conf);
  print("[", pal, "]");
}
