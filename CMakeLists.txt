cmake_minimum_required(VERSION 3.5)

include(cmake/info.cmake)

project("${OKI_PROJECT}" LANGUAGES C CXX VERSION 1.0)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(WINDOWS ON)
endif()

configure_file("cfg.hxx.in" "cfg.hxx" @ONLY)

include_directories(${CMAKE_BINARY_DIR} include/sqlite3)

add_compile_options(-Wall)

if(LINKER_LANGUAGE STREQUAL "CXX")
  add_compile_options(-std=c++20)
endif()

link_directories(lib/)

add_library(oki-bank-models SHARED ${MODELS_PROJECT_FILES})
add_library(oki-bank-sqlite3 SHARED ${SQLITE3_PROJECT_FILES})

target_link_libraries(oki-bank-sqlite3 PUBLIC sqlite3)