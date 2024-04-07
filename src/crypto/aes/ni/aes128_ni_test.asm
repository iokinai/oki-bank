section .data
  encword: db "Hello world", 10

section .bss
  cur_s: resb 2

section .text

global _start

_start:
  mov rdi, 12
  mov rsi, encword

  call write_string_as_symbols

endpr:
  mov rax, 60
  xor rdi, rdi
  syscall

write: 
  push rax,
  push rdi,
  push rsi
  push rdx
  pushf

  mov rax, 1
  mov rdi, 1
  mov rsi, encword
  mov rdx, 12
  syscall

  popf
  pop rsi
  pop rdx
  pop rdi
  pop rax

  ret

; string_len: rdi
; string: rsi
write_string_as_symbols:
  push rax
  push rdi
  push rcx
  push rdx
  push rbx
  pushf

  dec rdi
  mov r8, rdi
  dec rsi

print_loop:

  mov rax, 1
  mov rdi, 1
  inc rsi
  push rsi
  mov bl, byte [rsi]
  mov byte [cur_s], bl
  mov byte [cur_s+1], 9
  mov rsi, cur_s
  mov rdx, 2
  syscall

  pop rsi
  dec r8

  cmp r8, 0
  jnbe print_loop

  popf
  pop rbx
  pop rdx
  pop rcx
  pop rdi
  pop rax
  ret
