#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<std::string> args(argv + 1, argc + argv);

  for (const auto &arg : args) {
    std::cout << arg << std::endl;
  }
}