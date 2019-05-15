#include <string>
#include <fstream>
// troca todas as aparicoes de uma string por outra
std::string replaceAll(std::string str, const std::string& from, const std::string& to);

// retira comentarios, espacos e tabs
void prepreProcessa(std::string saida, std::ifstream &arqEntrada);

// blah
void preProcessa(std::string entrada);
