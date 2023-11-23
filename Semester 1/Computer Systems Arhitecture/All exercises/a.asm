bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "ana.txt", 0   ; filename to be created
    access_mode db "w", 0       ; file access mode:
                                ; w - creates an empty file for writing
    file_descriptor dd -1       ; variable to hold the file descriptor
    text db "Ana are 17 mere.", 0  ; text to be write to file
    len equ ($-text)
    change db "X"
    two db 2

; our code starts here
segment code use32 class=code
    start:
        ;A file name and a text (defined in the data segment) are given. The text contains lowercase letters, digits and spaces. Replace all the digits with the character ‘X’. Create the file with the given name and write the generated text to file.
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor], eax  ; store the file descriptor returned by fopen
        
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final
        mov ecx,len
        mov esi, 0
        loop_1:
            mov al, [text+esi]
            cmp al, '9'                     ;test if the character is a digit
            ja end_loop
                cmp al, '0'
                jl end_loop
                    mov al ,[change]           ;change the character with X
                    mov [text+esi],al
            end_loop:
            inc esi 
        loop loop_1
        ; write the text to file using fprintf()
        ; fprintf(file_descriptor, text)
        push dword text
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*2

        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

      final:

        ; exit(0)
        push dword 0      
        call [exit]