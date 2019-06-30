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

// imprime no console a string i + quebra de linha
void print(const std::string i);

// imprime no console a string i
void printSemBarra(const std::string i);

// imprime no console uma mensagem de erro e a linha que ela se encontra
void erro(std::string mensagem, int linha);

//procura substring em um vetor de string
int findSubVec(std::map<std::string, std::string>, std::string);

//verifica se um identificador é válido
int identValid(std::string);

//verifica se uma string eh numero
int strNum(std::string ident);