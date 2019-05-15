#include "pre-processador.h"
#include <iostream>

/*std::map<std::string, bool> directiveMap = 
{
    {"SECTION", true},
    {"BEGIN", true},
    {"END", true},
    {"CONST", true},
    {"SPACE", true}
    {"EQU", true},
    {"IF", true},
    {"MACRO", true},
};*/

std::string replaceAll(std::string str, const std::string& from, const std::string& to){
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

void prepreProcessa(std::string saida, std::ifstream &arqEntrada){
  std::string linha;
  std::ofstream arqSaida;
  arqSaida.open(saida.c_str());
  
  while(getline(arqEntrada, linha)){
    // retirada de comentarios
    if (linha.find(";") != std::string::npos) 
      linha.erase(linha.find(";"), linha.length());

    //troca todos os tabs por espaco
    linha = replaceAll(linha, "\t", " ");

    //retirada de espacos no meio
    while(linha.find("  ") != std::string::npos)
      linha = replaceAll(linha, "  ", " ");
    
    //retirada espaco em branco comeco
    while(linha[0] == ' ') linha.replace(0, 1,"");
    
    //retirada espaco em branco final
    if((int)linha[0] != 0)
      while(linha[linha.length()-1] == ' ') 
        linha.replace(linha.length()-1, 1, "");

    //troca tudo pra maiuscula
    for(int i=0; i < (int)linha.length(); i++)
      if(linha[i]>=97 && linha[i]<=122)
		    linha[i]=linha[i]-32;
    
    //Escreve a linha se não for uma linha vazia
    if((int)linha[0] != 0) 
      arqSaida << linha << std::endl;
  }

  arqSaida.close();
}

void preProcessa(std::string entrada){
  std::string linha;
  std::fstream arq;
  arq.open(entrada.c_str());

  while(getline(arq, linha)){
    while(linha.find("EQU") != std::string::npos){
      std::cout << "EQU" << std::endl;
      getline(arq, linha);
    }
  }
}