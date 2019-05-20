#include "headers/segundaPassagem.hpp"
#include "headers/func.hpp"

void segundaPassagem(std::string entrada, std::map<std::string, int> &tab_simb, std::map<std::string, int> &map_constante, std::map<std::string, int> &map_sections, std::map<std::string, bool> instrucoes, std::map<std::string, bool> diretivas){
  std::fstream arqPre;
  std::string str;
  std::vector<std::string> linhas;
  int linha;


  arqPre.open(entrada.c_str());

  while(getline(arqPre, str)){
    linhas.push_back(str);
  }
  arqPre.close();

  for(linha = 0; linha <= (int)linhas.size()-1; linha++){
    size_t pos = 0;
    std::string operacao;
    std::string parametro;
    size_t end = linhas[linha].find("\n");

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
    
    if(instrucoes[operacao] == true){
      
      if(operacao == "ADD"){
        pos = linhas[linha].find("ADD ");
        parametro = linhas[linha].substr(pos+4, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "1 "+ parametro + " ";
      }
      else if(operacao == "SUB"){
        pos = linhas[linha].find("SUB ");
        parametro = linhas[linha].substr(pos+4, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "2 "+ parametro + " ";
      }
      else if(operacao == "MULT"){
        pos = linhas[linha].find("MULT ");
        parametro = linhas[linha].substr(pos+5, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "3 "+ parametro + " ";
      }
      else if(operacao == "DIV"){
        pos = linhas[linha].find("DIV ");
        parametro = linhas[linha].substr(pos+4, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            if(map_constante[parametro] == 0)
              erro("Divisao por zero (ERRO SEMANTICO)", linha+1);
            else{
              int x = tab_simb[parametro];
              parametro = std::to_string(x);
            }
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "4 "+ parametro + " ";
      }
      else if(operacao == "JMP"){
        pos = linhas[linha].find("JMP ");
        parametro = linhas[linha].substr(pos+4, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            if(x >= map_sections["DATA"])
              erro("Pulo para secao invalida (ERRO SEMANTICO)", linha+1);
            else 
              parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "5 "+ parametro + " ";
      }
      else if(operacao == "JMPN"){
        pos = linhas[linha].find("JMPN ");
        parametro = linhas[linha].substr(pos+5, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            if(x >= map_sections["DATA"])
              erro("Pulo para secao invalida (ERRO SEMANTICO)", linha+1);
            else 
              parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "6 "+ parametro + " ";
      }
      else if(operacao == "JMPP"){
        pos = linhas[linha].find("JMPP ");
        parametro = linhas[linha].substr(pos+5, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            if(x >= map_sections["DATA"])
              erro("Pulo para secao invalida (ERRO SEMANTICO)", linha+1);
            else 
              parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "7 "+ parametro + " ";
      }
      else if(operacao == "JMPZ"){
        pos = linhas[linha].find("JMPZ ");
        parametro = linhas[linha].substr(pos+5, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            if(x >= map_sections["DATA"])
              erro("Pulo para secao invalida (ERRO SEMANTICO)", linha+1);
            else 
              parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "8 "+ parametro + " ";
      }
      else if(operacao == "COPY"){
        std::string parametro2;
        pos = linhas[linha].find("COPY ");
        parametro = linhas[linha].substr(pos+5, end);
        if (parametro.find(", ") != std::string::npos){
          pos = parametro.find(" ");
          parametro2 = parametro.substr(pos+1, end);
          parametro = parametro.substr(0, pos-1);
          if(parametro2.find(" ") == std::string::npos){
            if(tab_simb.count(parametro) && tab_simb.count(parametro2)){
              int x = tab_simb[parametro];
              int y = tab_simb[parametro2];
              parametro = std::to_string(x);
              parametro2 = std::to_string(y);
            }
            else
              erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
          }
          else
            erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "9 "+ parametro + " " + parametro2 + " ";
      }
      else if(operacao == "LOAD"){
        pos = linhas[linha].find("LOAD ");
        parametro = linhas[linha].substr(pos+5, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "10 "+ parametro + " ";
      }
      else if(operacao == "STORE"){
        pos = linhas[linha].find("STORE ");
        parametro = linhas[linha].substr(pos+6, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "11 "+ parametro + " ";
      }
      else if(operacao == "INPUT"){
        pos = linhas[linha].find("INPUT ");
        parametro = linhas[linha].substr(pos+6, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "12 "+ parametro + " ";
      }
      else if(operacao == "OUTPUT"){
        pos = linhas[linha].find("OUTPUT ");
        parametro = linhas[linha].substr(pos+7, end);
        if (parametro.find(" ") == std::string::npos){
          if(tab_simb.count(parametro)){
            int x = tab_simb[parametro];
            parametro = std::to_string(x);
          }
          else
            erro("Nao achou operando na Tabela de Simbolos (ERRO SEMANTICO)", linha+1);
        }
        else 
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "13 "+ parametro + " ";
      }
      else if(operacao == "STOP"){
        if(linhas[linha].find("STOP ") != std::string::npos)
          erro("Numero de operandos invalido (ERRO SINTATICO)", linha+1);
        linhas[linha] = "14 ";
      }
    }
    else if (diretivas[operacao] == true) {
        if(operacao == "SPACE"){
          if(linhas[linha].find("SPACE ") != std::string::npos){
            pos = linhas[linha].find("SPACE ");
            std::string num = linhas[linha].substr(pos+6,end);
            int val;
            if(num.find("0X") != std::string::npos) 
              val = std::stoi(num,nullptr,16);
            else
              val = std::stoi(num);
            if(val <= 0) 
              erro("Atribuindo valor invalido ao SPACE (ERRO SEMANTICO)", linha+1);
            linhas[linha] = "0 ";
            for(int i=1;i<val;i++) 
              linhas[linha] += "0 ";
            //linhas[linha] += " ";
          }
          else 
            linhas[linha] = "0 ";
        }
        else if(operacao == "CONST"){
          pos = linhas[linha].find("CONST ");
          std::string num = linhas[linha].substr(pos+6,end);
          int val;
          if(num.find("0X") != std::string::npos) 
            val = std::stoi(num,nullptr,16);
          else if(strNum(num) == 0){
            val = 1;
          }
          else
            val = std::stoi(num);
          linhas[linha] = std::to_string(val) + " ";
          
        }
        else if(operacao == "SECTION") linhas[linha] = "";
    }
  }

  //imprime na tela o arquivo obj
  /*std::cout << std::endl << std::endl << std::endl;
  std::cout << "Saida do programa:" << std::endl;
  std::for_each(linhas.begin(), linhas.end(), printSemBarra);*/

  //grava o arquivo pre processado
  std::ofstream arq2;
  std::string saida = entrada.substr(0, entrada.size()-3);
  saida.append("obj");
  arq2.open(saida.c_str(), std::ofstream::trunc);
  std::ostream_iterator<std::string> output_iterator(arq2, "");
  std::copy(linhas.begin(), linhas.end(), output_iterator);
  arq2.close();

}