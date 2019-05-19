// bibliotecas adicionais utilizadas
#include <string>
#include <fstream>
#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

// troca todas as aparicoes de uma string por outra
std::string replaceAll(std::string str, const std::string& from, const std::string& to);

// imprime no console a string i
void print(const std::string i);

// imprime no console uma mensagem de erro e a linha que ela se encontra
void erro(std::string mensagem, int linha);