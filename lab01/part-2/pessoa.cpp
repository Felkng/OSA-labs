#include "pessoa.hpp"
#include <string>
using namespace std;

Pessoa::Pessoa(int age, string name) : age(age), name(name) {}

string Pessoa::to_string() {
  return "Nome: " + name + " | " + "Idade: " + std::to_string(age);
}

Pessoa *Pessoa::convert_string_to_registro(string age, string name) {

  auto newReg = new Pessoa(stoi(age), name);
  return newReg;
}
