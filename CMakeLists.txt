cmake_minimum_required(VERSION 3.28)
project(GameTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameTest main.cpp BoardGame_Classes.h Pyramid_XO.h
        Word_TicTacToe.h
        dic.txt
        Pyramid_XO_AI.h
        Word_AI.h
        TicTacToe_Prob7.h)
