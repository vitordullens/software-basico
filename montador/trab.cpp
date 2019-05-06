#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

string replaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

void preprocessa(string saida, ifstream &arqEntrada){
  int linhaNum = 0;
  string linha;
  ofstream arqSaida;
  arqSaida.open(saida.c_str());
  while(getline(arqEntrada, linha)){
    while((int)linha[0] == 0 || linha[0] == ';'){
      getline(arqEntrada, linha);
    }
    linha = replaceAll(linha, "\t", " ");
    linha = replaceAll(linha, "\r", "");
    arqSaida << linha << endl;
  }


  arqSaida.close();
}

int main(int argc, char *argv[]){
  string entrada;
  string saida;
  ifstream arqEntrada;


  if (argc != 2){
    cout << "Nao foi especificado o nome do arquivo.";
    return -1;
  }

  entrada = argv[1];

  arqEntrada.open(entrada.c_str());
  if (!arqEntrada){
    cerr << "Nao foi possivel abrir o arquivo " << argv[1] << endl;
    return -1;
  }

  saida = entrada.substr(0, entrada.size()-3);
  saida.append("pre");

  preprocessa(saida, arqEntrada);

  arqEntrada.close();


  return 0;
}
