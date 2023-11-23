bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fprintf,fclose,printf,scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll   
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll    
import scanf msvcrt.dll 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    text db "",0
    file_name db "examen.txt", 0
    message_string db "string=",0
    format db "%s",0
    file_descriptor dd -1
    access_mode db "w", 0
    text2 db "",0
    len equ 100

; our code starts here
segment code use32 class=code
    start:
        ;Read a 100 characters string from the keyboard. The string contains a hidden message.
        ;The message was hidden by reversing the order of the letters and turning each letter in its ASCII code (in base 16).
        ;Write in a file the original message in a file. The original message does not contain spaces or digits.
        ;opening the file
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2
        mov [file_descriptor],eax
        cmp eax,0
        je final
        
        push dword message_string
        call[printf]
        add esp,4  
        ;reading from the console the text
        push dword text
        push dword format
        call[scanf]
        add esp,4 * 2
        
        mov esi,len
        mov ecx,[len]
        mov edi,0
        repeta:
            mov bl,[text+esi]
            mov [text2+edi],bl
            dec esi
            inc edi
        loop repeta
        ;printing the string in the file
        push dword text2
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*2
        final:
        ;closing the file
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

