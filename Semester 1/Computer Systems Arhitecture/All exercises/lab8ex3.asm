bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
                          
segment data use32 class=data
	a dw  0h       
    b dw 0h
	message1  db "a=", 0  
    message2 db "b=", 0
	format  db "%d", 0  ; %d <=> a decimal number (base 10)
    format1 db "%x", 0 ;hexa
    
segment code use32 class=code
    start:
        ;Read two words a and b in base 10 from the keyboard. Determine the doubleword c such that the low word of c is given by the sum of the a and b and the high word of c is given by the difference between a and b. Display the result in base 16
        push dword message1
        call [printf]      ; call function printf for printing
        add esp, 4       ; free parameters on the stack; 
        push dword a       ; ! addressa of a, not value
        push dword format
        call [scanf]       ; call function scanf for reading
        add esp, 4 * 2
        push dword message2 
        call [printf]      
        add esp, 4       
        push dword b       ; ! addressa of b, not value
        push dword format
        call [scanf]       ; call function scanf for reading
        add esp, 4 * 2     ; free parameters on the stack
        mov AX, [a]
        sub AX,[b]
        mov AH,0 
        and eax,0000ffffh
        mov cl,16          ;making the high word with the difference between a and b
        sal eax,cl
        mov ebx,0
        mov BX, [a]
        add BX, [b]
        mov Bh, 0
        and ebx,0000ffffh ;making the low word with the sum of a and b
        add eax,ebx        ;the doubleword is in eax
        push dword eax
        push dword format1
        call [printf]
        add esp,4 *2
        ; exit(0)
        push dword 0      ; place on stack parameter for exit
        call [exit]       ; call exit to terminate the program