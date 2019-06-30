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
  preProcessa2(saida);
}

void preProcessa2(std::string saida){
  std::fstream arqSaida;
  std::string str, operacao, rotulo;
  size_t pos = 0;
  std::vector<std::string> linhas;

  arqSaida.open(saida.c_str());
  int linha;

  //armazena cada linha do arquivo em um vetor de strings
  while(getline(arqSaida, str)){
    linhas.push_back(str);
  }
  arqSaida.close();

  for(linha = 0; linha <= (int)linhas.size()-1; linha++){
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
    if(operacao == "EQU"){
        //std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        pos = linhas[linha].find(":");
        rotulo = linhas[linha].substr(0,pos);
        std::string equ = linhas[linha].substr(linhas[linha].find("EQU ")+4, 1); //equ so de um char por enquanto. ultimo argumento
        linhas.erase(linhas.begin()+linha); //apaga a linha do equ
        for(int j=linha; j<=(int)linhas.size()-1; j++){ //substitui equ em todas as outras linhas
          if(linhas[j].find(rotulo) != std::string::npos){
            linhas[j] = replaceAll(linhas[j], rotulo, equ);
          }
        }
        linha--;
        //endereco = endereco + 0;
      }
      else if(operacao == "IF"){
        //std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        pos = linhas[linha].find(" ");
        int valor_if = std::stoi(linhas[linha].substr(pos+1,pos+2));
        //se o valor de if for 1, apaga a linha do if e deixa a proxima linha
        if(valor_if == 1){
          linhas.erase(linhas.begin()+linha);
          linha--;
        }
        //se o valor de if for diferente de 1, apaga a linha do if e a proxima
        else{
          linhas.erase(linhas.begin()+linha);
          linhas.erase(linhas.begin()+linha);
          linha--;
        }
        //endereco = endereco + 0;
      }
  }

  //grava o arquivo pre processado
  std::ofstream arq2;
  arq2.open(saida.c_str(), std::ofstream::trunc);
  std::ostream_iterator<std::string> output_iterator(arq2, "\n");
  std::copy(linhas.begin(), linhas.end(), output_iterator);
  arq2.close();

}
