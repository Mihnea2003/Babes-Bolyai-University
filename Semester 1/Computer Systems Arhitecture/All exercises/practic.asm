bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
                          
segment data use32 class=data
    a db 15
    b db 10
    c db 7
    d dw 20
    two db 2
    five db 5
segment  code use32 class=code ; code segment
    start:
    ;[(a-b)5+d]-2c
;a,b,c - byte, d - word
    mov al, [a]
    sub al,byte[b]
    mul byte[five]
    add ax,word[d]
    mov bx,ax
    mov al,byte[c]
    mul byte[two]
    sub bx,ax
    call[exit]