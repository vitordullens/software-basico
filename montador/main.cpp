#include "pre-processador.h" // adiciona tambem a <string> e <fstream>
#include <iostream>

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

  arqEntrada.close();


  return 0;
}