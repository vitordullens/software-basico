#include "headers/preProcessa.hpp"
#include "headers/primeiraPassagem.hpp"
#include "headers/segundaPassagem.hpp"

int main(int argc, char *argv[]){
  std::string entrada;
  std::string saida;
  std::ifstream arqEntrada;


  if (argc != 2){
    std::cout << "Nao foi especificado o nome do arquivo.";
    return -1;
  }

  entrada = argv[1];

  arqEntrada.open(entrada.c_str());
  if (!arqEntrada){
    std::cerr << "Nao foi possivel abrir o arquivo " << argv[1] << std::endl;
    return -1;
  }

  saida = entrada.substr(0, entrada.size()-3);
  saida.append("pre");

  preProcessa(saida, arqEntrada);

  std::map<std::string, bool> diretivas = 
  {
    {"SECTION", true},
    {"SPACE", true},
    {"CONST", true},
    {"EQU", true},
    {"IF", true},
    {"MACRO", true},
    {"END", true},
  };

  std::map<std::string, bool> instrucoes = 
  {
    {"ADD", true},
    {"SUB", true},
    {"MULT", true},
    {"DIV", true},
    {"JMP", true},
    {"JMPN", true},
    {"JMPP", true},
    {"JMPZ", true},
    {"COPY", true},
    {"LOAD", true},
    {"STORE", true},
    {"INPUT", true},
    {"OUTPUT", true},
    {"STOP", true},
  };  

  std::map<std::string, int> tab_simb;
  std::map<std::string, int> map_constante;
  std::map<std::string, int> map_sections;

  primeiraPassagem(saida, tab_simb, map_constante, map_sections, instrucoes, diretivas);
  segundaPassagem(saida, tab_simb, map_constante, map_sections, instrucoes, diretivas);

  arqEntrada.close();


  return 0;
}