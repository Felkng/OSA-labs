#ifndef PESSOA_H
#define PESSOA_H
#include <string>
using namespace std;

class Pessoa {
public:
  int age;
  string name;

  Pessoa(int age, string name);

  string to_string();

  static Pessoa *convert_string_to_registro(string age, string name);
};

#endif
