#include "headers/func.hpp"

void erro(std::string mensagem, int linha){
  std::cout << "ERRO: " << mensagem << " na linha " << linha << std::endl;
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to){
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

void print(const std::string i){
	std::cout << i << '\n';
}

void printSemBarra(const std::string i){
	std::cout << i;
}

int findSubVec(std::map<std::string, std::string> mdt, std::string str){
  int achou = 0;
  for (auto it = mdt.cbegin(); it != mdt.cend(); ++it) {
    if((*it).first == str) achou = 1;
  }
  return achou;
}

int identValid(std::string ident){
  int valid = 1;
  if(isdigit(ident[0]) != 0) return 0; //verifica se comeca com numero
  else{
    //verifica se cada caractere da string eh alfanumerico ou _
    for (std::size_t i = 0; i < ident.size(); i++){
      if((ident[i] < 'A' || ident[i] > 'Z') && ident[i] != '_' && (ident[i] < '0' || ident[i] > '9')){
          valid = 0;
      }
    }
    return valid;
  }
}

int strNum(std::string ident){
  int valid = 1;
  //verifica se cada caractere da string eh um numero
  if(isdigit(ident[0]) == 0 && ident[0] != '-') valid = 0;
  else{
    for (std::size_t i = 1; i < ident.size(); i++){
      if(isdigit(ident[i]) == 0){
          valid = 0;
      }
    }
  }
  return valid;
}