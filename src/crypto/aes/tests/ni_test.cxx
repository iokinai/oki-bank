#include "../aes_ni.hxx"
#include <iostream>

int main() {
  std::string supported = "aes not supported";

  if (okibank::aes::has_aes_ni()) {
    supported = "aes supported";
  }

  std::cout << supported << std::endl;
}