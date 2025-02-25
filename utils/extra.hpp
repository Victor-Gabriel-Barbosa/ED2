#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <type_traits>
#include <sstream>
#include <iomanip>
using namespace std;

struct PrintConfig {  
  string sep = " ";
  string end = "\n";
  int prc = 6;
  bool scf = false;
  bool shp = false;

  PrintConfig() 
    : sep(" ")
    , end("\n")
    , prc(6)
    , scf(false)
    , shp(false) {}

  PrintConfig(const string& sep, const string& e, int prec, bool sci, bool pos)
    : sep(sep)
    , end(e)
    , prc(prec)
    , scf(sci)
    , shp(pos) {}
};

static PrintConfig config;

void configure(const PrintConfig& newConfig) {
  config = newConfig;
}

template<typename T>
string formatNumber(const T& value) {
  ostringstream ss;
  if (config.scf) ss << scientific;  
  ss << setprecision(config.prc);
  if (config.shp) ss << showpos;  
  ss << value;
  return ss.str();
}

template <typename T>
typename enable_if<is_arithmetic<T>::value, size_t>::type
print(const T& value, const string& sep = "") {
  const string& actualSep = sep.empty() ? config.sep : sep;  
  string formatted = formatNumber(value);
  cout << formatted << actualSep;
  return formatted.length();
}

size_t print(const string& s, const string& sep = "") {
  const string& actualSep = sep.empty() ? config.sep : sep;  
  cout << s << actualSep;
  return s.length();
}

size_t print(const char* s, const string& sep = "") {
  const string& actualSep = sep.empty() ? config.sep : sep;  
  cout << s << actualSep;
  return strlen(s);
}

template <typename Container>
typename enable_if<!is_arithmetic<Container>::value && !is_same<Container, string>::value, size_t>::type
print(const Container& container, const string& sep = "") {
  const string& actualSep = sep.empty() ? config.sep : sep; 
  size_t count = 0;
  bool first = true;
  for (const auto& element : container) {
    if (!first) cout << actualSep;
    count += print(element, "");
    first = false;
  }
  
  cout << config.end;
  return count;
}

size_t print() {
  cout << config.end;
  return 0;
}

template<typename First, typename... Rest>
size_t print(const First& first, const Rest&... rest) {
  size_t count = print(first);
  count += print(rest...);
  return count;
}

template<typename Container>
void print(const Container& data, const vector<int>& widths) {
  size_t col = 0;
  for (const auto& element : data) {
    if (col < widths.size()) {
      cout << setw(widths[col]) << left << element;
      col++;
    }
  }
  cout << config.end;
}
