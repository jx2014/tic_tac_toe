cmake_minimum_required(VERSION 3.7...3.23)
project(cal VERSION 0.1.0
                DESCRIPTION "Tic Tac Toe"
                LANGUAGES C)

include(CTest)
enable_testing()

add_executable(tic_tac_toe main.c interface.c tictactoe.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
