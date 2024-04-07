nasm -f elf64 aes128_ni_test.asm -o aes128_ni_test.o
ld aes128_ni_test.o -o aes128_ni_test
./aes128_ni_test

if [ $1 != "--noremove" ]
then 
  rm aes128_ni_test
fi