section .text
global _start
_start:
add eax, [OLD_DATA]
L1: mov ebx, [DOIS]
idiv ebx
add eax, [NEW_DATA]
sub edx, edx
mov ebx, [DOIS]
imul ebx
add eax, [TMP_DATA]
add eax, [OLD_DATA]
sub eax, [TMP_DATA]
add eax, [TMP_DATA]
mov eax, [NEW_DATA]
mov [OLD_DATA], eax
add eax, [OLD_DATA]
cmp eax, 0
jg L1
section .data
DOIS dd 2
OLD_DATA dd 00
NEW_DATA dd 0
TMP_DATA dd 000000
SLA_DA dd 0
