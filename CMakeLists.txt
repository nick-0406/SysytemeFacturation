cmake_minimum_required(VERSION 3.10)
project(SystemeFacturation C)

set(CMAKE_C_STANDARD 11)

add_executable(SystemeFacturation
        main.c
        traitement.c
        affichage.c
        gestion.h
        gestion.c
)
