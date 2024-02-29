clean() {
  if [ -f $1.o ]; then
    rm $1.o
  fi

  if [ -f $1.out ]; then
    rm $1.out
  fi
}

compile()  {
  nasm -f elf64 $1.asm -o $1.o
  ld $1.o -o $1.out
}

run() {
  ./$1.out
}

AES_FILE_NAME=aes_ni_test

compile $AES_FILE_NAME
run $AES_FILE_NAME

clean $AES_FILE_NAME