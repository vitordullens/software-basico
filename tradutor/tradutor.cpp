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

int main(int argc, char *argv[]){
  std::string entrada;
  std::string saida;
  std::ifstream arqEntrada;
  std::ofstream arqSaida;


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
  saida.append("s");

  std::vector<std::string> linhas, linhas2;
  std::string str, operacao;
  std::string label;

  int linha = 0;
  int linha2 = 0;

  size_t pos = 0;
  //armazena cada linha do arquivo em um vetor de strings
  while(getline(arqEntrada, str)){
    linhas.push_back(str);
  }
  arqEntrada.close();

  for(linha = 0; linha <= (int)linhas.size()-1; linha++){
    std::cout << "Lendo linha: " << linhas[linha] << std::endl;
    size_t end = linhas[linha].find("\n");
    /*
    PROCURA INSTRUCOES
    */
    //separa uma operacao que contem um label antes
    if(linhas[linha].find(":") != std::string::npos){
      pos = linhas[linha].find(":");
      operacao = linhas[linha];
      label = operacao.substr(0, pos+1);
      label = label + " ";
      operacao.erase(0, pos+2);
      pos = operacao.find(" ");
      operacao = operacao.substr(0,pos);      
    }
    //separa uma operacao que nao contem um label antes
    else{
      pos = linhas[linha].find(" ");
      operacao = linhas[linha].substr(0,pos);
      label = "";
    }
    if(operacao == "SECTION"){
      pos = operacao.find(" ");
      operacao = operacao.substr(0,pos);
      if(linhas[linha].substr(linhas[linha].find("SECTION ")+8, end) == "TEXT"){
        linhas2.insert(linhas2.begin()+linha2, "section .text");
        linha2++;
        linhas2.insert(linhas2.begin()+linha2, "global _start");
        linha2++;
        linhas2.insert(linhas2.begin()+linha2, "_start:");
      }
      else if(linhas[linha].substr(linhas[linha].find("SECTION ")+8, end) == "DATA"){
        linhas2.insert(linhas2.begin()+linha2, "section .data");
      }
      linha2++;
    }
    else if(operacao == "SPACE"){
      label.erase(label.length()-2, label.length()-2);
      if(linhas[linha].find("SPACE ") != std::string::npos){
        pos = linhas[linha].find("SPACE ");
        std::string num = linhas[linha].substr(pos+6,end);
        int val;
        if(num.find("0X") != std::string::npos) 
          val = std::stoi(num,nullptr,16);
        else
          val = std::stoi(num);
        std::string zeros = "0";
        for(int z = 1; z < val; z++)
          zeros += "0";
        linhas2.insert(linhas2.begin()+linha2, label + " dd " + zeros);
      }
      else{
        label.erase(label.length()-2, label.length()-2);
        linhas2.insert(linhas2.begin()+linha2, label + " dd 0");
      }
      linha2++;
    }
    else if(operacao == "CONST"){
      pos = linhas[linha].find("CONST ");
      label.erase(label.length()-2, label.length()-2);
      std::string num = linhas[linha].substr(pos+6,end);
      linhas2.insert(linhas2.begin()+linha2, label + " dd " + num);
      linha2++;
    }
    else if(operacao == "ADD"){
      pos = linhas[linha].find("ADD ");
      std::string num = linhas[linha].substr(pos+4,end);
      linhas2.insert(linhas2.begin()+linha2, label + "add eax, " + "[" + num + "]");
      linha2++;
    }
    else if(operacao == "SUB"){
      pos = linhas[linha].find("SUB ");
      std::string num = linhas[linha].substr(pos+4,end);
      linhas2.insert(linhas2.begin()+linha2, label + "sub eax, " + "[" + num + "]");
      linha2++;
    }
    else if(operacao == "MULT"){
      pos = linhas[linha].find("MULT ");
      std::string num = linhas[linha].substr(pos+5,end);
      linhas2.insert(linhas2.begin()+linha2, label + "sub edx, edx");
      linha2++;
      linhas2.insert(linhas2.begin()+linha2, "mov ebx, [" + num + "]");
      linha2++;
      linhas2.insert(linhas2.begin()+linha2, "imul ebx");
      linha2++;
    }
    else if(operacao == "DIV"){
      pos = linhas[linha].find("DIV ");
      std::string num = linhas[linha].substr(pos+4,end);
      linhas2.insert(linhas2.begin()+linha2, label + "mov ebx, [" + num + "]");
      linha2++;
      linhas2.insert(linhas2.begin()+linha2, "idiv ebx");
      linha2++;
    }
    else if(operacao == "JMP"){
      pos = linhas[linha].find("JMP ");
      std::string num = linhas[linha].substr(pos+4,end);
      linhas2.insert(linhas2.begin()+linha2, label + "jmp " + num );
      linha2++;
    }
    else if(operacao == "JMPN"){
      pos = linhas[linha].find("JMPN ");
      std::string num = linhas[linha].substr(pos+5,end);
      linhas2.insert(linhas2.begin()+linha2, label + "cmp eax, 0");
      linha2++;
      linhas2.insert(linhas2.begin()+linha2, "jl " + num);
      linha2++;
    }
    else if(operacao == "JMPP"){
      pos = linhas[linha].find("JMPP ");
      std::string num = linhas[linha].substr(pos+5,end);
      linhas2.insert(linhas2.begin()+linha2, label + "cmp eax, 0");
      linha2++;
      linhas2.insert(linhas2.begin()+linha2, "jg " + num);
      linha2++;
    }
    else if(operacao == "JMPZ"){
      pos = linhas[linha].find("JMPZ ");
      std::string num = linhas[linha].substr(pos+5,end);
      linhas2.insert(linhas2.begin()+linha2, label + "cmp eax, 0");
      linha2++;
      linhas2.insert(linhas2.begin()+linha2, "je " + num);
      linha2++;
    }
    else if(operacao == "COPY"){
        std::string num2;
        pos = linhas[linha].find("COPY ");
        std::string num = linhas[linha].substr(pos+5, end);
        if (num.find(", ") != std::string::npos){
          pos = num.find(" ");
          num2 = num.substr(pos+1, end);
          num = num.substr(0, pos-1);
        }
        linhas2.insert(linhas2.begin()+linha2, label + "mov eax, [" + num + "]");
        linha2++;
        linhas2.insert(linhas2.begin()+linha2, "mov [" + num2 + "], eax");
        linha2++;
    }
    else if(operacao == "LOAD"){
      pos = linhas[linha].find("LOAD ");
      std::string num = linhas[linha].substr(pos+5,end);
      linhas2.insert(linhas2.begin()+linha2, label + "add eax, " + "[" + num + "]");
      linha2++;
    }
    else if(operacao == "STORE"){
      pos = linhas[linha].find("STORE ");
      std::string num = linhas[linha].substr(pos+6,end);
      linhas2.insert(linhas2.begin()+linha2, label + "add eax, " + "[" + num + "]");
      linha2++;
    }
    //agr é os de ler e escrever la
  }

  arqSaida.open(saida.c_str(), std::ofstream::trunc);
  std::ostream_iterator<std::string> output_iterator(arqSaida, "\n");
  std::copy(linhas2.begin(), linhas2.end(), output_iterator);
  arqSaida.close();

  return 0;
}