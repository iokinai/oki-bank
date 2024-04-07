#include "app_init.hxx"
#include "database/sqlite/sqlite3_db.hxx"
#include <string>

int main(int argc, const char *argv[]) {
  using db = okibank::sqlite3_db;

  auto connection = okibank::app::open_db<db>("hello");

  okibank::app::init_db(connection);

  auto server = okibank::app::create_http_server();

  server->listen("localhost", 8080);
}