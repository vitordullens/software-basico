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

// retira comentarios, espacos e tabs
void preProcessa(std::string saida, std::ifstream &arqEntrada);

// blah
void primeiraPassagem(std::string entrada);

// blah
void segundaPassagem(std::string entrada);

//funcao q imprime o erro
void erro(std::string, int);
