; move.asm
section .data
      bNum  db    123
      wNum  dw    12345
      dNum  dd    1234567890
      qNum1 dq    1234567890123456789
      qNum2 dq    123456
      qNum3 dq    3.14
section .bss
section .text
      global main
main:
    mov rbp, rsp; for correct debugging
      push  rbp
      mov   rbp,rsp
      mov rax, -1           ; fill rax with 1s
      mov al, byte [bNum]   ; does NOT clear upper bits of rax
      xor rax,rax           ; clear rax
      xor al, byte [bNum]   ; now rax has the correct value

      mov rax, -1           ; fill rax with 1s
      mov ax, word [wNum]   ; does NOT clear upper bits of rax
      xor rax,rax           ; clear rax
      mov ax, word [wNum]   ; now rax has the correct value

      mov rax, -1           ; fill rax with 1s
      mov rax, qword [qNum1] ; does clear upper bits of rax
      mov qword [qNum2], rax ; one operand always a register
      mov rax, 123456       ; source operand an immediate value
      movq xmm0, [qNum3]    ; instruction for floating point

mov rsp,rbp
pop rbp
ret

   


