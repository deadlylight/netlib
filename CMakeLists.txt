cmake_minimum_required(VERSION 3.10)

add_compile_options(-g)
add_compile_options(-Wall -Werror)
add_compile_options(-fPIC)

add_subdirectory(src)
add_subdirectory(test)
