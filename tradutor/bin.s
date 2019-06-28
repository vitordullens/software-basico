section .text
L1: mov ebx, [DOIS]
idiv ebx
sub edx, edx
mov ebx, [DOIS]
imul ebx
sub eax, [TMP_DATA]
section .data
DOIS dd 2
OLD_DATA dd 0
NEW_DATA dd 0
TMP_DATA dd 0
