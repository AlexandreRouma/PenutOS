%define    BASE    0x100
%define KSIZE    54

[BITS 16]
[ORG 0x0]

jmp start

%include "UTIL.INC"
%include "GDT.INC"

start:

    mov ax, 0x07C0
    mov ds, ax
    mov es, ax
    mov ax, 0x8000    ; stack en 0xFFFF
    mov ss, ax
    mov sp, 0xf000


    mov [bootdrv], dl 



; affiche un msg
    mov si, msgDebut
    call afficher
	

; Change mode
    
    mov ah, 00h
    mov al, 0x03
    int 10h
	
    

; charger le noyau
    xor ax, ax
    int 0x13

    push es
    mov ax, BASE
    mov es, ax
    mov bx, 0
    
    mov ah, 2
    mov al, KSIZE
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [bootdrv]
    int 0x13
    pop es


; initialisation de la GDT
    ; descInit base(32), limite(20/32), acces/type(8), flags(4/8), adresse(16)
    descInit 0, 0xFFFFF, 10011011b, 1101b, gdt_cs
    descInit 0, 0xFFFFF, 10010011b, 1101b, gdt_ds

; initialisation du pointeur sur la GDT
    mov ax, gdtend    ; calcule la limite de GDT
    mov bx, gdt
    sub ax, bx
    mov word [gdtptr], ax

    xor eax, eax    ; calcule l'adresse lineaire de GDT
    mov  ax, ds
    mov  bx, gdt
    call calcadr
    mov dword [gdtptr+2], ecx

; passage en modep
    cli
    lgdt [gdtptr]    ; charge la gdt
    mov eax, cr0
    or   ax, 1
    mov cr0, eax    ; PE mis a 1 (CR0)

    jmp next
next:
    
    
	

    mov ax, 0x10    ; segment de donne
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x9F000
    
    

    jmp dword 0x8:0x1000

end:
    jmp end


;--------------------------------------------------------------------
msgDebut db "loading...", 13, 10, 0

gdt:
gdt_null:
    dw 0, 0, 0, 0
gdt_cs:
    dw 0, 0, 0, 0
gdt_ds:
    dw 0, 0, 0, 0
gdtend:

gdtptr:
    dw    0x0000    ; limite
    dd    0         ; base

bootdrv: db 0

;--------------------------------------------------------------------
;; NOP jusqu'a 510
times 510-($-$$) db 144
dw 0xAA55

