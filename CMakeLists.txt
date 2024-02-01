cmake_minimum_required(VERSION 3.5)

include(cmake/info.cmake)

project("${OKI_PROJECT}" LANGUAGES C CXX VERSION 1.0)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(
  CMAKE_CXX_STANDARD 23
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(WINDOWS ON)
endif()

configure_file("cfg.hxx.in" "cfg.hxx" @ONLY)

include_directories(${CMAKE_BINARY_DIR} include/sqlite3)

add_compile_options(-Wall)

link_directories(lib/)

add_library(oki-bank-models SHARED ${MODELS_PROJECT_FILES})
add_library(oki-bank-sqlite3 SHARED ${SQLITE3_PROJECT_FILES})
add_library(oki-bank-database SHARED ${DATABASE_PROJECT_FILES})
add_executable(oki-bank ${OKI_BANK})

target_link_libraries(oki-bank-sqlite3 PUBLIC oki-bank-database)
target_link_libraries(oki-bank PUBLIC oki-bank-models PUBLIC oki-bank-sqlite3 PUBLIC libsqlite3.a)