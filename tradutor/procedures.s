section .data
inteiro resd 1
char    resb 1
string  resd 5
var1    resd 1
var2    resd 1

section .text
global I_Input
global I_Ouput
global C_Input
global C_Output
global H_Input
global H_Output
global S_Input
global S_Output

global _start
I_Input:
                push ebp
                push ebx
                push ecx
                push edx
                mov ebp, esp

                mov ecx, [ebp+20]
                mov eax, 3
                mov ebx, 0
                mov edx, 11
                int 80h
        
                sub eax, eax
                mov ebx, [ebp+20]
                sub ecx, ecx
        loopII:
                movzx edx, byte [ebx]
                inc ebx
                cmp edx, 0x2D
                jz loopII
                cmp edx, 0x30 ; verifica se é dígito
                jb fimII
                cmp edx, 0x39
                ja fimII
                sub edx, 0x30
                imul eax, 10
                add eax, edx
                inc ecx
                jmp loopII
        fimII:
                sub ebx, ecx
                sub ebx, 2
                movzx edx, byte [ebx]
                cmp edx, 0x2D
                jne posII
                neg eax

        posII:
                mov ebx, [ebp+20]
                mov [ebx], eax
                mov eax, ecx                
                pop edx
                pop ecx
                pop ebx
                pop ebp
                ret 4

I_Output:
                push ebp
                push eax
                push ebx
                push ecx
                push edx
                mov ebp, esp
                mov eax, [ebp+24]

                sub ecx, ecx
                cmp eax, 0
                jge loopIO
                neg eax

        loopIO:
                sub edx, edx
                mov ebx, 10
                idiv ebx
                mov ebx, edx
                add edx, 0x30
                mov [var1+ecx], edx
                inc ecx
                cmp eax, 0
                jnz loopIO

                mov eax, [ebp+24]
                cmp eax, 0
                jge posIO
                mov byte [var1+ecx], 0x2D
                inc ecx
                
        posIO:    
                dec ecx
                sub eax, eax
        loop2IO:
                mov dl, [var1+eax]
                mov [var2+ecx], dl
                inc eax
                dec ecx
                cmp ecx, -1
                jnz loop2IO

                mov byte [var2+eax], 0x0A
                
                mov ecx, var2
                mov esi, 0
        loop3IO:
                cmp byte [ecx], 0x0A
                je fimIO
                mov eax, 4
                mov ebx, 1
                mov edx, 1
                int 80h
                inc ecx
                inc esi
                jmp loop3IO

        fimIO:
                pop edx
                pop ecx
                pop ebx
                pop eax
                pop ebp
                ret 4

C_Input:
                push ebp
                push ebx
                push ecx
                push edx
                mov ebp, esp
                mov ecx, [ebp+20]
                mov eax, 3
                mov ebx, 0
                mov edx, 2
                int 80h
                mov byte [ecx+1], 0x0
                mov eax, 1
                pop edx
                pop ecx
                pop ebx
                pop ebp
                ret

C_Output:
                push ebp
                push eax
                push ebx
                push ecx
                push edx
                mov ebp, esp
                mov ecx, [ebp+24]
                mov eax, 4
                mov ebx, 1
                mov edx, 1
                int 80h
                pop edx
                pop ecx
                pop ebx
                pop eax
                pop ebp
                ret

H_Input:
                ret

H_Output:
                ret

S_Input:
                push ebp
                mov ebp, esp
                push ebx
                push ecx
                push edx
                mov ebx, 0
                mov eax, 3
                mov edx, dword [ebp + 8]
                mov ecx, dword [ebp + 12]
                int 80h
                sub eax, eax
                mov ebx, dword [ebp + 12]
        loopSI:
                cmp byte [ebx + eax], 0xa
                je fimSI
                cmp eax, dword [ebp + 8]
                jge fimSI
                inc eax
                jmp loopSI
        fimSI:
                pop edx
                pop ecx
                pop ebx
                mov ebp, esp
                pop ebp
                ret

S_Output:
                push ebp
                mov ebp, esp
                push ebx
                push ecx
                push edx
                mov ebx, 1
                mov eax, 4
                mov ecx, dword [ebp + 12]
                mov edx, dword [ebp + 8]
                int 80h
                pop edx
                pop ecx
                pop ebx
                mov eax, dword [ebp + 8]
                mov esp, ebp
                pop ebp
                ret