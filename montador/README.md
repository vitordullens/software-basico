# Montador

Um software capaz de montar um código na linguagem Assembly Hipotética utilizada durante a disciplina, gerando assim seu código objeto (opcodes + operandos) e o código pre-processado.


## to-do

- [X] NAO ser sensivel ao caso, podendo aceitar instrucoes/diretivas/rotulos em maiusculas e minusculas.
- [X] Gerar dois arquivos de de saida em formato TEXTO (mais detalhes serao descritos a seguir).
- [X] Desconsiderar tabulacoes, quebras de linhas e espa¸cos desnecessarios em qualquer lugar do codigo.
- [X] A diretiva CONST deve aceitar numeros positivos (inteiros e hexadecimal) e negativos (inteiros).
- [ ] Deve ser possıvel trabalhar com vetores (SPACE com operando, e usar operacoes do tipo: LABEL + Numero, colocando espaco entre o ’+’).
- [X] Capacidade de aceitar comentarios indicados pelo simbolo “;” em qualquer lugar do codigo.
- [X] O comando COPY deve utilizar uma virgula e um espaco entre os operandos (COPY A, B).
- [X] Ser capaz de aceitar MACROS (mais detalhes serao descritos a seguir).
- [X] Uma macro pode chamar outra macro.
- [X] Poder criar um rotulo, dar quebra de linha e continuar a linha depois (o rotulo seria equivalente a linha seguinte).

### tipo de erros:
- [X] declaracoes e rotulos ausentes;
- [X] declaracoes e rotulos repetidos;
- [X] pulo para rotulos invalidos;
- [X] pulo para secao errada;
- [X] diretivas invalidas;
- [X] instrucoes invalidas;
- [ ] diretivas ou instrucoes na secao errada;
- [X] divisao por zero (para constante);
- [X] instrucoes com a quantidade de operando invalida;
- [ ] instrucoes com o tipo de operando invalido;
- [X] tokens invalidos;
- [X] dois rotulos na mesma linha;
- [X] secao TEXT faltante;
- [X] secao invalida;
- [X] tipo de argumento invalido;
- [ ] modificacao de um valor constante;
- [ ] acessar posicao nao reservada pelo SPACE (exemplo accesar SPACE + 4, sendo que somente foi reservada uma posicao)