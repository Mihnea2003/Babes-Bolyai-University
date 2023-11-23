bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
                          
segment data use32 class=data
    a dw 0
    b dw 0
    message1 db "a=",0
    message2 db "b=",0
    format db "%d",0
segment  code use32 class=code ; code segment
    start:
    ;Read two numbers a and b (base 10) from the keyboard and calculate: (a+b)*(a-b). The result of multiplication will be stored in a variable called ;"result" (defined in the data segment).
    push dword message1
    call [printf]
    add esp,4
    push dword a
    push dword format
    call [scanf]
    add esp,4*2
    push dword message2
    call [printf]
    add esp,4
    push dword b
    push dword format
    call [scanf]
    add esp,4*2
    mov ax,[a]
    add ax,word[b]
    mov bx,[a]
    sub bx,word[b]
    mul bx   ;result in dx:ax
    push dx
    push ax
    pop eax
    push eax
    push dword format
    call[printf]
    add esp,4*2
    call[exit]
    
    