bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose ,printf, scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll    
import scanf msvcrt.dll     

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    n dw 0
    message1 db "a=",0
    message2 db "cuvant=",0
    format db "%d",0
    format2 db "%s",0
    two db 2
    cuvant dd 0
    cuvant2 dd 0
    litera db 'p'
segment  code use32 class=code ; code segment
    start:
    push dword message2
    call[printf]
    add esp,4
    
    push dword cuvant
    push dword format2
    call [scanf]
    add esp,4*2
    
    push dword message1
    call [printf]
    add esp,4
    
    push dword n
    push dword format
    call[scanf]
    add esp,4*2
    
    mov cx,word[n]
    div byte[two]
    cmp ah,0
    jne var2
        mov esi,0
        repeta:
            mov al,[cuvant+esi]
            cmp AL,0x00
            je stop_loop
               add al,20
               mov byte[cuvant+esi],al
               inc esi
        jmp repeta
        stop_loop:
        push dword cuvant
        push dword format2
        call[printf]
        add esp,4*2
    var2:
        mov esi,0
        mov edi,0
        repeta2:
            mov al,[cuvant+esi]
            cmp AL,0x00
            je stop_loop1
            mov byte[cuvant2+edi],al
            inc edi
            mov bl,byte[litera]
            mov byte[cuvant2+edi],bl
            inc edi
            mov byte[cuvant2+edi],al
            inc edi
        jmp repeta2
        stop_loop1:
        push dword cuvant2
        push dword format2
        call[printf]
        add esp,4*2
    call[exit]
    
    
    
    
    
    
    
    