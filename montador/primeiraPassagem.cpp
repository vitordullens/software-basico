#include "headers/primeiraPassagem.hpp"
#include "headers/func.hpp"

void primeiraPassagem(std::string entrada, std::map<std::string, int> &tab_simb, std::map<std::string, int> &map_constante, std::map<std::string, int> &map_sections, std::map<std::string, bool> instrucoes, std::map<std::string, bool> diretivas){
  std::string str, rotulo, operacao, operandos;
  std::fstream arq;
  int linha = 0;
  int endereco = 0;
  int text = 0;
  size_t pos = 0;
  std::vector<std::string> linhas;
  arq.open(entrada.c_str());

  //armazena cada linha do arquivo em um vetor de strings
  while(getline(arq, str)){
    linhas.push_back(str);
  }

  arq.close();

  for(linha = 0; linha <= (int)linhas.size()-1; linha++){
    /*
    PROCURA LABELS
    */
    //acha uma label qualquer
    if(linhas[linha].find(":") != std::string::npos){
      //verifica se tem duas labels na mesma linha. nao para a montagem
      if(std::count(linhas[linha].begin(), linhas[linha].end(), ':') > 1){
        erro("Dois rotulos na mesma linha (TIPO DO ERRO)", linha+1);
      }
      pos = linhas[linha].find(":");
      rotulo = linhas[linha].substr(0,pos);
      //erro de rotulo ja definido. ainda tem q falar o tipo de erro
      if(tab_simb.count(rotulo)){
        erro("Rotulo ja definido (TIPO DO ERRO)", linha+1);
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
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "SUB"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "MULT"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "DIV"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "JMP"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "JMPN"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "JMPP"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "JMPZ"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "COPY"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 3;
      }
      else if(operacao == "LOAD"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "STORE"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "INPUT"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "OUTPUT"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 2;
      }
      else if(operacao == "STOP"){
        std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //executa
        endereco = endereco + 1;
      }
    }

    /*
    PROCURA DIRETIVAS
    */
    //verifica se a operacao eh uma diretiva
    else if(diretivas[operacao] == true){
      size_t end = linhas[linha].find("\n");
      if(operacao == "SECTION"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        if(linhas[linha].substr(linhas[linha].find("SECTION ")+8, end) == "TEXT"){
          std::cout << "Achou a secao TEXT" << std::endl;
          text = 1;
          map_sections.insert (std::pair<std::string, int>("TEXT", endereco));
        }
        else if(linhas[linha].substr(linhas[linha].find("SECTION ")+8, end) == "DATA"){
          std::cout << "Achou a secao DATA" << std::endl;
          map_sections.insert (std::pair<std::string, int>("DATA", endereco));
        }
        else{
          erro("Secao Invalida (TIPO ERRO)", linha+1);
        }
        //acho q n tem q fazer nada, so deixa ela la no arquivo pre processado
        //endereco = endereco + 0;
      }
      else if(operacao == "SPACE"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        if(linhas[linha].find("SPACE ") != std::string::npos){
          pos = linhas[linha].find("SPACE ");
          int num = std::stoi(linhas[linha].substr(pos+6,end));
          endereco = endereco + num;
        }
        else endereco = endereco + 1;
      }
      else if(operacao == "CONST"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        pos = linhas[linha].find("CONST ");
        std::string num = linhas[linha].substr(pos+6,end);
        int val;
        if(num.find("0X") != std::string::npos) 
          val = std::stoi(num,nullptr,16);
        else
          val = std::stoi(num);

          map_constante.insert (std::pair<std::string, int>(rotulo, val));
        


        endereco = endereco + 1;
      }
      else if(operacao == "EQU"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
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
        std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
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
      else if(operacao == "MACRO"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //vai dar trabalho
        //endereco = endereco + 0;
      }
      else if(operacao == "END"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //marca o fim de uma macro
        //endereco = endereco + 0;
      }
    }
    //diretiva ou instrucao invalida
    else{
      erro("Instrucao ou diretiva invalida (ERRO LEXICO)", linha+1);
      linhas.erase(linhas.begin()+linha);
      linha--;
    }
  }

  //erro secao text ausente
  if(text == 0) erro("Secao TEXT ausente", 0);

  std::cout << std::endl << std::endl << std::endl;
  std::cout << "Saida do programa:" << std::endl;
  std::for_each(linhas.begin(), linhas.end(), print);

  //grava o arquivo pre processado
  std::ofstream arq2;
  arq2.open(entrada.c_str(), std::ofstream::trunc);
  std::ostream_iterator<std::string> output_iterator(arq2, "\n");
  std::copy(linhas.begin(), linhas.end(), output_iterator);
  arq2.close();


  //imprime a tabela de simbolos, apenas para debug por enquanto
  std::cout << std::endl << std::endl << "Tabela de simbolos:" << std::endl;
  for (auto it = tab_simb.cbegin(); it != tab_simb.cend(); ++it) {
    std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
  }
}