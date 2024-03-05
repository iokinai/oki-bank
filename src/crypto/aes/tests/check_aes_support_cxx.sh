clean() {
  if [ -f $1.out ]; then
    rm $1.out
  fi
}

compile()  {
  clang++ -std=c++20 $1 $2 -o $3.out
}

run() {
  ./$1.out
}

CXX_FILE_NAMES="ni_test.cxx aes_ni.cxx"
OUTPUT_FILE_NAME=ni_test_cxx

compile $CXX_FILE_NAMES $OUTPUT_FILE_NAME
run $OUTPUT_FILE_NAME

clean $OUTPUT_FILE_NAME