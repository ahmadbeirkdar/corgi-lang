cmake_minimum_required(VERSION 3.17)
project(corgi-lang)

set(CMAKE_CXX_STANDARD 20)

add_executable(corgi-lang main.cpp token.h lexer.cpp lexer.h AST.cpp AST.h parser.cpp parser.h)
set(LLVM_DIR "/usr/local/Cellar/llvm/11.0.1/lib/cmake/llvm")

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(corgi-lang ${llvm_libs})