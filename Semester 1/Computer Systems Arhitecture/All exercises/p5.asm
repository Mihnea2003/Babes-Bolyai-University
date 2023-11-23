bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
    a  db 15
	b  db 5
    c  db 97
    d  db 5
    e  dw 120
    f  dw 120
    g  dw 100
    h  dw 15
segment  code use32 class=code ; code segment
start: 
    ;(f*g-a*b*e)/(h+c*d)  a,b,c,d-byte, e,f,g,h-word (120*100-15*5*120)/(15+97*5)=(12000-9000)/(500)=3000/500=6

    mov AX, [f]
    mul word [g]    ;->DX:AX=f*g=120*100=12000
    
    push DX
    push AX
    pop EBX         ;EBX->DX:AX=12000
    
    
    mov AL, [a]
    mul byte [b]    ;AX=a*b=15*5=75
    
    mul word [e]    ;->DX:AX ->a*b*e=15*5*120=9000
    
    push DX
    push AX
    pop EAX         ;-> EAX=DX:AX=9000
    
    sub EBX,EAX     ;->EBX=(f*g-a*b*e)=(120*100-15*5*120)=3000
    
    mov AL, [c]
    mul byte [d]    ;AX=c*d
    add AX, [h]     ;AX->(h+c*d)=(15+97*5)=500
    mov CX,AX       ;CX->AX
    
    push EBX
    pop AX
    pop DX    ;so we can divide (h+c*d)  ->DX:AX=(f*g-a*b*e)
    div CX    ; =(f*g-a*b*e)/(h+c*d)=6 the result is in AX and the reminder is in DX
    
    
    call[exit]
    
    
    