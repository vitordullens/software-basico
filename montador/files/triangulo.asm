SECTION TEXT
		INPUT		B
		TRIANGULO: EQU 1
		INPUT		H
	TESTE2: MACRO &a, &b, &c
		ADD 1
		fsafdsa
		SUB 2
		ADD 2
		END
		COPY B, H, H ;teste copy com 3 args
	TESTESEMEND: MACRO &a, &B
		ADD 1
		ADD 2
Z:   	
		LOAD		B
		COPY B, H
		DIV zero ;divide por 0
	TESTE3: MACRO
		ADD 5
		TESTE2
		SUB 5
		END
		fdsa fdsa fdsa ;coisas aleatorias
		MULT		H
		TESTE2
		ADD H B ;add com 2 args
		TESTE3
		IF TRIANGULO
		ADD DOIS
		TESTESEMEND
		
AA: DIV		DOISF
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