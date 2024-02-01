#include "app_init.hxx"
#include "database/sqlite/sqlite3_db.hxx"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, const char *argv[]) {
  std::vector<std::string> args(argv + 1, argc + argv);

  for (const auto &arg : args) {
    std::cout << arg << std::endl;
  }

  using db = okibank::sqlite3_db;

  auto connection = okibank::app::open_db<db>("/home/okinai/hello");

  okibank::app::init_db(connection);
}