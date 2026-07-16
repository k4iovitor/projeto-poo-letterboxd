cmake_minimum_required(VERSION 3.10)
project(LetterboxdOOP VERSION 2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Para verificar memory leaks em modo Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address,undefined -Wall -Wextra)
    add_link_options(-fsanitize=address,undefined)
endif()

# Executável principal — busca recursivamente todos os .cpp em src/
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(meu_exe ${SOURCES})
target_include_directories(meu_exe PRIVATE src)

# ============================================================
# Q4 — Catch2 (Testes Automatizados)
# ============================================================
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Fontes para testes (todos os .cpp exceto main.cpp)
file(GLOB_RECURSE TEST_SOURCES "src/*.cpp")
list(FILTER TEST_SOURCES EXCLUDE REGEX "main\\.cpp$")

add_executable(testes
    tests/test_tp2.cpp
    ${TEST_SOURCES}
)
target_include_directories(testes PRIVATE src)
target_link_libraries(testes PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(testes)
