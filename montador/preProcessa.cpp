#include "headers/preProcessa.hpp"
#include "headers/func.hpp"

void preProcessa(std::string saida, std::ifstream &arqEntrada){
  std::string linha, linha_aux;
  std::ofstream arqSaida;
  int concat = 0;
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

    //retira quebra de linha depois de labels
    if (linha.find(":") != std::string::npos){
      size_t pos = linha.find(":");
      if((int)linha[pos+1] == 0){
        linha_aux = linha;
        concat = 1;
      }
    }
    
    //Escreve a linha se não for uma linha vazia
    if((int)linha[0] != 0){
      if(concat == 1){
        concat = 2;
      }
      else if(concat == 2){
        linha = linha_aux + " " + linha;
        arqSaida << linha << std::endl;
        concat = 0;
      }
      else{
        arqSaida << linha << std::endl;
      }
    }
  }

  arqSaida.close();
}
