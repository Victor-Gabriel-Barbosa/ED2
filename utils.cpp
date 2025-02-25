#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

template <typename T>
typename enable_if<is_arithmetic<T>::value, size_t>::type
print(const T& value) {
  cout << value;
  return 1;
}

size_t print(const string& s) {
  cout << s;
  return s.length();
}

size_t print(const char* s) {
  cout << s;
  return strlen(s);
}

template <typename Container>
typename enable_if<!is_arithmetic<Container>::value && !is_same<Container, string>::value, size_t>::type
print(const Container& a) {
  size_t count = 0;
  for (const auto& e : a) {
    cout << e << " ";
    ++count;
  }
  return count;
}

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  cout << v.size() << endl;
  cout << print(v) << endl;  
  print(42);            
  print(3.14);      

  int n;  
  print("Digite um número");
  cin >> n;
  print(n);
  cout << "Fim" << endl;
}