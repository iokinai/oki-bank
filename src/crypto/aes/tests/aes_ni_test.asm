global _start

section .data
s_no_aes: db "no aes", 10
s_aes: db "aes supported", 10

section .text
_start:
  mov eax, 0x00000001
  cpuid
  test ecx, 0x2000000
  jne aes_supported

no_aes:
  mov rax, 1
  mov rdi, 1
  mov rsi, s_no_aes
  mov rdx, 7
  syscall

  jmp exit

aes_supported:
  mov rax, 1
  mov rdi, 1
  mov rsi, s_aes
  mov rdx, 14
  syscall

exit:
  xor rdi, rdi
  mov eax, 60
  syscall

