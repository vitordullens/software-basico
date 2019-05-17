#include "pre-processador.h"
#include <iostream>
#include <map>
#include <string.h>

std::map<std::string, bool> diretivas = 
{
    {"SECTION", true},
    {"END", true},
    {"CONST", true},
    {"EQU", true},
    {"IF", true},
    {"MACRO", true},
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

std::string replaceAll(std::string str, const std::string& from, const std::string& to){
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

void erro(std::string mensagem, int linha){
  std::cout << "ERRO: " << mensagem << " na linha " << linha << std::endl;
}

//tabela de simbolos
std::map<std::string, int> tab_simb;

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
  std::string linha, rotulo, operacao, operandos;
  std::fstream arq;
  int line = 1;
  int endereco = 0;
  size_t pos = 0;
  arq.open(entrada.c_str());

  while(getline(arq, linha)){
    /*
    PROCURA LABELS
    */
    if(linha.find(":") != std::string::npos){
      pos = linha.find(":");
      rotulo = linha.substr(0,pos);
      //erro de rotulo ja definido. ainda tem q falar o tipo de erro
      if(tab_simb.count(rotulo)){
        erro("Rotulo ja definido (TIPO DO ERRO)", line);
      }
      else if(linha.find("SPACE") != std::string::npos){
        tab_simb.insert (std::pair<std::string, int>(rotulo,endereco));
        std::cout << "Achou space" << std::endl;
        //pode ser um ou mais enderecos. como fazer no caso de mais de um?
        endereco = endereco + 1;
      }
      else if(linha.find("EQU") != std::string::npos){
        tab_simb.insert (std::pair<std::string, int>(rotulo,endereco));
        std::cout << "Achou equ" << std::endl;
        //troca todo rotulo por o q vem dps de EQU
      }
      else{
        //apenas guarda o endereco do rotulo na tabela de simbolos
        tab_simb.insert (std::pair<std::string, int>(rotulo,endereco));
        std::cout << "Achou rotulo " << rotulo <<  " na linha " << line << " Endereco: " << endereco << std::endl;
        endereco = endereco + 2;
      }
    }
    else{
      pos = linha.find(" ");
      operacao = linha.substr(0,pos);

      /*
      PROCURA INSTRUCOES
      */
      if(instrucoes[operacao] == true){
        if(operacao == "ADD"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "SUB"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "MULT"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "DIV"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "JMP"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "JMPN"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "JMPP"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "JMPZ"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "COPY"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 3;
        }
        else if(operacao == "LOAD"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "STORE"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "INPUT"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "OUTPUT"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 2;
        }
        else if(operacao == "STOP"){
          std::cout << "Achou operacao " << operacao << " na linha " << line << std::endl;
          //executa
          endereco = endereco + 1;
        }
      }

      /*
      PROCURA DIRETIVAS (MENOS SPACE, QUE JA FOI TRATADA ACIMA JUNTO COM OS ROTULOS)
      */
      else if(diretivas[operacao] == true){
        if(operacao == "SECTION"){
          std::cout << "Achou diretiva " << operacao << " na linha " << line << std::endl;
          //acho q n tem q fazer nada, so deixa ela la no arquivo pre processado
          //endereco = endereco + 0;
        }
        else if(operacao == "CONST"){
          std::cout << "Achou diretiva " << operacao << " na linha " << line << std::endl;
          //reserva memoria para constante. pode ser decimal ou hexadecimal
          endereco = endereco + 1;
        }
        else if(operacao == "IF"){
          std::cout << "Achou diretiva " << operacao << " na linha " << line << std::endl;
          //inclui a linha seguinte se o q vem depois de IF for 1
          //endereco = endereco + 0;
        }
        else if(operacao == "MACRO"){
          std::cout << "Achou diretiva " << operacao << " na linha " << line << std::endl;
          //vai dar trabalho
          //endereco = endereco + 0;
        }
        else if(operacao == "END"){
          std::cout << "Achou diretiva " << operacao << " na linha " << line << std::endl;
          //marca o fim de uma macro
          //endereco = endereco + 0;
        }
      }
    }
    line++;
  }


//imprime a tabela de simbolos, apenas para debug por enquanto
  std::cout << std::endl << std::endl << "Tabela de simbolos:" << std::endl;
  for (auto it = tab_simb.cbegin(); it != tab_simb.cend(); ++it) {
    std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
  }
}