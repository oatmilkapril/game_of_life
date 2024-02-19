cmake_minimum_required(VERSION 3.15)
project(gameoflife C)

add_executable(gameoflife src/gameoflife.c src/main.c)

target_include_directories(gameoflife PRIVATE include/)
target_link_libraries(gameoflife PRIVATE ncurses)
target_compile_definitions(gameoflife PRIVATE NCURSES_WIDECHAR=1)
