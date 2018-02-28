cmake_minimum_required(VERSION 3.9)
project(learning_blockchain_dev C)

set(CMAKE_C_STANDARD 99)
set(CFLAGS "DTFM_DESC")

include_directories(include)
link_directories(lib)
link_libraries(libtommath.a libtfm.a libtomcrypt.a)
add_executable(learning_blockchain_dev src/lecture8_verify_block.c)