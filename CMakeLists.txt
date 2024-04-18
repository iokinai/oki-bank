cmake_minimum_required(VERSION 3.5)

include(cmake/info.cmake)
include(GenerateExportHeader)

project("${OKI_PROJECT}" LANGUAGES CXX VERSION 1.0)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(
  CMAKE_CXX_STANDARD 23
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(WINDOWS ON)
endif()

configure_file("cfg.hxx.in" "cfg.hxx" @ONLY)

include_directories(${CMAKE_BINARY_DIR} include)

add_compile_options(-Wall)

link_directories(lib/)

find_library(sqlitelib NAMES sqlite3 REQUIRED)

add_compile_options(-g)

add_library(oki-bank-models SHARED ${MODELS_PROJECT_FILES})
add_library(oki-bank-sqlite3 SHARED ${SQLITE3_PROJECT_FILES})
add_library(oki-bank-database SHARED ${DATABASE_PROJECT_FILES})
add_library(oki-bank-thread SHARED ${OKI_THREAD})
add_library(oki-bank-cache SHARED ${OKI_CACHE})
add_library(oki-bank-crypto SHARED ${OKI_CRYPTO})
add_library(oki-bank-http SHARED ${OKI_SERVER})
add_executable(oki-bank ${OKI_BANK})

target_link_libraries(oki-bank-sqlite3 PUBLIC oki-bank-database PUBLIC ${sqlitelib})

target_link_libraries(oki-bank PUBLIC oki-bank-models PUBLIC oki-bank-sqlite3 PUBLIC oki-bank-cache PUBLIC oki-bank-crypto PUBLIC oki-bank-http)