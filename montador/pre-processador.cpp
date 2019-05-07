#include "pre-processador.h"

std::string replaceAll(std::string str, const std::string& from, const std::string& to){
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

void preProcessa(std::string saida, std::ifstream &arqEntrada){
  int linhaNum = 0;
  std::string linha;
  std::ofstream arqSaida;
  arqSaida.open(saida.c_str());
  while(getline(arqEntrada, linha)){
    while((int)linha[0] == 0 || linha[0] == ';'){
      getline(arqEntrada, linha);
    }
    linha = replaceAll(linha, "\t", " ");
    linha = replaceAll(linha, "\r", "");
    arqSaida << linha << std::endl;
  }

  arqSaida.close();
}