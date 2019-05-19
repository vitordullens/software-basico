SECTION TEXT
		INPUT		B
		TRIANGULO: EQU 1
		INPUT		H
		COPY B, H, H ;teste copy com 3 args
Z:   	
		LOAD		B
		COPY B, H
		DIV zero ;divide por 0
		fdsa fdsa fdsa ;coisas aleatorias
		MULT		H
		ADD H B ;add com 2 args
		IF TRIANGULO
		ADD DOIS
AA: DIV		DOIS
S: fdsa ;coisas aleatorias
		STORE		R
		JMP B ;pulo para secao invalida
		JMPZ B
		JMP Z
AA:		OUTPUT	R
		STOP B ;stop com argumentos
SECTION DATA
	B:		SPACE
	H:		SPACE
	R:		SPACE
	ZERO:	CONST		0
	DOISF: const 0xFF ;hexadecimal