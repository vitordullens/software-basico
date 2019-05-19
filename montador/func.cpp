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
