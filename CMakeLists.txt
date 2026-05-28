cmake_minimum_required(VERSION 3.10)
project(LetterboxdOOP VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Para a Questão 4 (verificar memory leaks em modo Debug)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address,undefined -Wall -Wextra)
    add_link_options(-fsanitize=address,undefined)
endif()

file(GLOB SOURCES "src/*.cpp")

add_executable(meu_exe ${SOURCES})
