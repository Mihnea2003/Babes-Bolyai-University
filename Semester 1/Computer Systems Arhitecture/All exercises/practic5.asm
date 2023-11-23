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
    n dd 0
    cuvant dd 0
    message1 db "a=",0
    message2 db "cuvant=",0
    format db "%d",0
    format2 db "%s",10,13,0
    file_name db "ptpractic.txt",0
    access_mode db "a",0
    file_descriptor dd -1
segment  code use32 class=code ; code segment
    start:
    push dword access_mode     
    push dword file_name
    call [fopen]
    add esp, 4*2                ; clean-up the stack

    mov [file_descriptor], eax  ; store the file descriptor returned by fopen
            
    cmp eax, 0
    je final
        ;pana aici deschid fisierul
    push dword message1
    call[printf]
    add esp,4
    
    push dword n
    push dword format
    call[scanf]
    add esp,4*2
    citire:
        
        pushad
        push dword message2
        call [printf]
        add esp,4
        
        push dword cuvant
        push dword format2
        call[scanf]
        add esp,4*2
        
        cmp byte[cuvant],"#"
        je final 
                ;aici scrii
                
                 push dword cuvant
                 push dword format2
                 push dword [file_descriptor]
                 call [fprintf]
                 add esp, 4*3
        popad
        jmp citire
        final:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
    call [exit]
        
        