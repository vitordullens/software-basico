#include "pre-processador.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

void print(const std::string i){
	std::cout << i << '\n';
}

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
  std::string str, rotulo, operacao, operandos;
  std::fstream arq;
  int linha = 0;
  int endereco = 0;
  size_t pos = 0;
  std::vector<std::string> linhas;
  arq.open(entrada.c_str());

  //armazena cada linha do arquivo em um vetor de strings
  while(getline(arq, str)){
    linhas.push_back(str);
  }

  for(linha = 0; linha <= linhas.size()-1; linha++){
    /*
    PROCURA LABELS
    */
    //acha uma label qualquer
    if(linhas[linha].find(":") != std::string::npos){
      pos = linhas[linha].find(":");
      rotulo = linhas[linha].substr(0,pos);
      //erro de rotulo ja definido. ainda tem q falar o tipo de erro
      if(tab_simb.count(rotulo)){
        erro("Rotulo ja definido (TIPO DO ERRO)", linha);
      }
      else{
        //std::cout << "Rotulo " << rotulo << " marcado com endereco " << endereco << std::endl;
        tab_simb.insert (std::pair<std::string, int>(rotulo,endereco));
      }
    }

    /*
    PROCURA INSTRUCOES
    */
    //separa uma operacao que contem um label antes
    if(linhas[linha].find(":") != std::string::npos){
      pos = linhas[linha].find(":");
      operacao = linhas[linha];
      operacao.erase(0, pos+2);
      pos = operacao.find(" ");
      operacao = operacao.substr(0,pos);
      
    }
    //separa uma operacao que nao contem um label antes
    else{
      pos = linhas[linha].find(" ");
      operacao = linhas[linha].substr(0,pos);
    }
    //verifica se a operacao eh uma instrucao
    if(instrucoes[operacao] == true){
      if(operacao == "ADD"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "SUB"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "MULT"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "DIV"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "JMP"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "JMPN"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "JMPP"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "JMPZ"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "COPY"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 3;
      }
      else if(operacao == "LOAD"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "STORE"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "INPUT"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "OUTPUT"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "STOP"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 1;
      }
    }

    /*
    PROCURA DIRETIVAS
    */
    //verifica se a operacao eh uma diretiva
    else if(diretivas[operacao] == true){
      if(operacao == "SECTION"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //acho q n tem q fazer nada, so deixa ela la no arquivo pre processado
        //endereco = endereco + 0;
      }
      else if(operacao == "SPACE"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //inclui a linha seguinte se o q vem depois de IF for 1
        endereco = endereco + 1;
      }
      else if(operacao == "CONST"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //inclui a linha seguinte se o q vem depois de IF for 1
        endereco = endereco + 1;
      }
      else if(operacao == "EQU"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        pos = linhas[linha].find(":");
        rotulo = linhas[linha].substr(0,pos);
        std::string equ = linhas[linha].substr(linhas[linha].find("EQU ")+4, 1); //equ so de um char por enquanto. ultimo argumento
        linhas.erase(linhas.begin()+linha);
        for(int j=linha; j<=linhas.size()-1; j++){
          if(linhas[j].find(rotulo) != std::string::npos){
            linhas[j] = replaceAll(linhas[j], rotulo, equ);
          }
        }
        linha--;
        //endereco = endereco + 0;
      }
      else if(operacao == "IF"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //inclui a linha seguinte se o q vem depois de IF for 1
        //endereco = endereco + 0;
      }
      else if(operacao == "MACRO"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //vai dar trabalho
        //endereco = endereco + 0;
      }
      else if(operacao == "END"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha << " endereco " << endereco << std::endl;
        //marca o fim de uma macro
        //endereco = endereco + 0;
      }
    }
  }
  std::cout << std::endl << std::endl << std::endl;
  std::cout << "Saida do programa:" << std::endl;
  std::for_each(linhas.begin(), linhas.end(), print);

  //imprime a tabela de simbolos, apenas para debug por enquanto
  std::cout << std::endl << std::endl << "Tabela de simbolos:" << std::endl;
  for (auto it = tab_simb.cbegin(); it != tab_simb.cend(); ++it) {
    std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
  }
}