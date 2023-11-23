bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
segment data use32 class=data
	number dd  11100111b       
    r db 0
    ten db 10
    two db 2
    four db 4
    format1 db "%x", 0 ;hexa
    
segment code use32 class=code
    start:
     mov eax,[number]
    ; Convert EAX (binary) to hexadecimal

    ; Convert EAX (binary) to hexadecimal

mov dx, 16 ; Set base (16) for conversion

convert_loop:
    idiv dx ; Divide EAX by 16 and store result in EAX, remainder in EDX
    add dl, '0' ; Convert remainder to hexadecimal digit
    cmp dl, '9' ; Check if digit is a number
    jbe print_digit ; If digit is a number, print it
    add dl, 7 ; If digit is a letter, convert it to the corresponding hexadecimal letter

print_digit:
    ; Print hexadecimal digit
    push dword edx
    push dword format1
    call [printf]
    add esp,4 *2
    cmp eax, 0 ; Check if result is 0
    jne convert_loop ; If result is not 0, repeat loop

        
    call [exit]
