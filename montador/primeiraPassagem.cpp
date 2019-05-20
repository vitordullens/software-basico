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
  std::vector<std::string> mnt;
  std::map<std::string, std::string> mdt;

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
      //verifica se os caracteres do rotulo sao validos
      if(identValid(rotulo) == 0){
        erro("Rotulo com caractere invalido (TIPO DO ERRO)", linha+1);
      }
      //erro de rotulo ja definido. ainda tem q falar o tipo de erro
      if(tab_simb.count(rotulo)){
        erro("Rotulo ja definido (TIPO DO ERRO)", linha+1);
      }
      //insere rotulo na tabela de simbolos
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
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "SUB"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "MULT"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "DIV"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "JMP"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "JMPN"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "JMPP"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "JMPZ"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "COPY"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 3;
      }
      else if(operacao == "LOAD"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "STORE"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "INPUT"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "OUTPUT"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        endereco = endereco + 2;
      }
      else if(operacao == "STOP"){
        //std::cout << "Achou operacao " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
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
        //std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        if(linhas[linha].substr(linhas[linha].find("SECTION ")+8, end) == "TEXT"){
          //std::cout << "Achou a secao TEXT" << std::endl;
          text = 1;
          map_sections.insert (std::pair<std::string, int>("TEXT", endereco));
        }
        else if(linhas[linha].substr(linhas[linha].find("SECTION ")+8, end) == "DATA"){
          //std::cout << "Achou a secao DATA" << std::endl;
          map_sections.insert (std::pair<std::string, int>("DATA", endereco));
        }
        else{
          erro("Secao Invalida (TIPO ERRO)", linha+1);
        }
        //acho q n tem q fazer nada, so deixa ela la no arquivo pre processado
        //endereco = endereco + 0;
      }
      else if(operacao == "SPACE"){
        //std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        if(linhas[linha].find("SPACE ") != std::string::npos){
          pos = linhas[linha].find("SPACE ");
          int num = std::stoi(linhas[linha].substr(pos+6,end));
          endereco = endereco + num;
        }
        else endereco = endereco + 1;
      }
      else if(operacao == "CONST"){
        //std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
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
      else if(operacao == "MACRO"){
        //std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        pos = linhas[linha].find(":");
        rotulo = linhas[linha].substr(0,pos);
        pos = linhas[linha].find("MACRO ");
        std::string macro_def = linhas[linha]; //o que vai ser guardado na mnt
        std::string macro_arg[4]; //vetor com os argumentos da macro
        if(linhas[linha].find('&') == std::string::npos){ //verifica se a macro possui argumentos
          macro_def = rotulo + ',' + "0";
          mnt.push_back(macro_def);
        }
        else{ //trata macros com argumentos
          int arg_num = 0; //numero de argumentos da macro
          std::string arg[3]; //nome dos argumentos
          int tam_arg; //numero de caracteres do argumento
          pos = pos+6;
          while(linhas[linha].find('&', pos) != std::string::npos && arg_num < 4){
            if(linhas[linha].find(',', pos) != std::string::npos){
              tam_arg = linhas[linha].find(',', pos) - pos;
              macro_arg[arg_num] = linhas[linha].substr(pos, tam_arg);
              pos = pos + tam_arg+2;
            }
            else{
              tam_arg = linhas[linha].length() - pos;
              macro_arg[arg_num] = linhas[linha].substr(pos, tam_arg);
              pos = pos + tam_arg;
            }
            arg_num++;
          }
          //Considera no maximo 3 argumentos em uma macro
          if(arg_num >= 4){
            erro("Macro com mais de 3 argumentos (TIPO ERRO)", linha);
            arg_num = 3;
          }
          //guarda a macro na mnt no formato: label,numero de args, arg1, arg2, arg3
          macro_def = rotulo + "," + std::to_string(arg_num);
          for(int i = 0; i<arg_num; i++){
            macro_def = macro_def + "," + macro_arg[i];
          }
          mnt.push_back(macro_def);
        }
        linhas.erase(linhas.begin()+linha);
        macro_def.clear();
        int achou_end = 0;
        for(int j = linha; j <= (int)linhas.size()-1; j++){
          if(linhas[j].find("MACRO") != std::string::npos) break;
          if(linhas[j].find("END") != std::string::npos){
            achou_end = 1;
          }
        }
        if(achou_end == 1){
          while(linhas[linha] != "END"){
            macro_def = macro_def + linhas[linha] + ";";
            linhas.erase(linhas.begin()+linha);
          }
          linhas.erase(linhas.begin()+linha);
          mdt.insert(std::pair<std::string, std::string>(rotulo, macro_def));
        }
        else{
          mdt.erase(rotulo); //apaga macro sem end da mdt
          mnt.pop_back(); //apaga macro sem end da mnt
          erro("Macro sem END (TIPO ERRO)", linha);
        }
        linha--;
      }
      /*else if(operacao == "END"){
        std::cout << "Achou diretiva " << operacao << " na linha " << linha+1 << " endereco " << endereco << std::endl;
        //marca o fim de uma macro
        //endereco = endereco + 0;
      }*/
    }
    //verifica se eh um macro
    else if(findSubVec(mdt, operacao) == 1) {
      //std::cout << "CHAMANDO MACRO " << operacao << std::endl;
      int salva_linha = linha; //salva a linha na qual a macro vai ser expandida

      std::string argc1, argc2, argc3; //argumentos da chamada da macro
      std::string arg1, arg2, arg3; //argumentos dentro da macro

      //procura macro na mnt
      int mnt_num = 0;
      for(std::size_t i = 0; i < mnt.size(); ++i){
        if(mnt[i].find(operacao) != std::string::npos){
          mnt_num = i;
          break;
        }
      }

      pos = mnt[mnt_num].find(",");
      std::string str;
      std::string str2;
      int num_arg = std::stoi(mnt[mnt_num].substr(pos+1, 1));
      str = mnt[mnt_num].substr(pos);
      str2 = linhas[linha];
      if(std::count(str2.begin(), str2.end(), ' ') != num_arg){
        erro("Chamada de macro com numero de argumentos invalido(TIPO ERRO)", linha);
        num_arg = 0; //expande a macro como se nao tivesse argumento
      }
      pos = pos + 3;
      int pos2 = str2.find(" ");
      if(num_arg == 1){
        str = mnt[mnt_num].substr(pos);
        str2 = str2.substr(pos2+1);
        int tam_arg = str.find(',');
        int tam_arg2 = str2.find(' ');
        arg1 = str.substr(0, tam_arg);
        argc1 = str2.substr(0, tam_arg2);
      }
      if(num_arg == 2){
        str = mnt[mnt_num].substr(pos);
        str2 = str2.substr(pos2+1);
        int tam_arg = str.find(',');
        int tam_arg2 = str2.find(' ');
        arg1 = str.substr(0, tam_arg);
        argc1 = str2.substr(0, tam_arg2);

        str = str.substr(tam_arg+1);
        str2 = str2.substr(tam_arg2+1);
        tam_arg = str.find(',');
        tam_arg2 = str2.find(' ');
        arg2 = str.substr(0, tam_arg);
        argc2 = str2.substr(0, tam_arg2);
      }
      if(num_arg == 3){
        str = mnt[mnt_num].substr(pos);
        str2 = str2.substr(pos2+1);
        int tam_arg = str.find(',');
        int tam_arg2 = str2.find(' ');
        arg1 = str.substr(0, tam_arg);
        argc1 = str2.substr(0, tam_arg2);

        str = str.substr(tam_arg+1);
        str2 = str2.substr(tam_arg2+1);
        tam_arg = str.find(',');
        tam_arg2 = str2.find(' ');
        arg2 = str.substr(0, tam_arg);
        argc2 = str2.substr(0, tam_arg2);

        str = str.substr(tam_arg+1);
        str2 = str2.substr(tam_arg2+1);
        tam_arg = str.find(',');
        tam_arg2 = str2.find(' ');
        arg3 = str.substr(0, tam_arg);
        argc3 = str2.substr(0, tam_arg2);
      }

      linhas.erase(linhas.begin()+linha);
      std::string str_aux, str_aux2;
      //procura definicao da macro na mdt
      for (auto it = mdt.cbegin(); it != mdt.cend(); ++it) {
        if((*it).first == operacao){
          str_aux = (*it).second;
        }
      }
      //expande a macro
      while(str_aux.find(";") != std::string::npos){
        pos = 0;
        str_aux2 = str_aux.substr(pos, str_aux.find(";"));
        if(num_arg == 1){
          str_aux2 = replaceAll(str_aux2, arg1, argc1);
        }
        if(num_arg == 2){
          str_aux2 = replaceAll(str_aux2, arg1, argc1);
          str_aux2 = replaceAll(str_aux2, arg2, argc2);
        }
        if(num_arg == 3){
          str_aux2 = replaceAll(str_aux2, arg1, argc1);
          str_aux2 = replaceAll(str_aux2, arg2, argc2);
          str_aux2 = replaceAll(str_aux2, arg3, argc3);
        }
        linhas.insert(linhas.begin()+linha, str_aux2);
        linha++;
        pos = str_aux.find(";");
        str_aux = str_aux.substr(pos+1, str_aux.find_last_of(";"));
      }
      linha = salva_linha - 1; //volta para a linha em que a macro for expandida
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

  //print na tela o arquivo pre processado
  /*std::cout << std::endl << std::endl << std::endl;
  std::cout << "Saida do programa:" << std::endl;
  std::for_each(linhas.begin(), linhas.end(), print);*/

  //grava o arquivo pre processado
  std::ofstream arq2;
  arq2.open(entrada.c_str(), std::ofstream::trunc);
  std::ostream_iterator<std::string> output_iterator(arq2, "\n");
  std::copy(linhas.begin(), linhas.end(), output_iterator);
  arq2.close();


  //imprime a tabela de simbolos, apenas para debug por enquanto
  /*std::cout << std::endl << std::endl << "Tabela de simbolos:" << std::endl;
  for (auto it = tab_simb.cbegin(); it != tab_simb.cend(); ++it) {
    std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
  }*/

  //imprime a mnt, apenas para debug por enquanto
  /*std::cout << std::endl << "MNT:";
  std::for_each(mnt.begin(), mnt.end(), print);
  std::cout << std::endl << std::endl;*/

  //imprime a mdt, apenas para debug por enquanto
  /*std::cout << std::endl << "MDT:" << std::endl;
  for (auto it = mdt.cbegin(); it != mdt.cend(); ++it) {
    std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
  }*/
}