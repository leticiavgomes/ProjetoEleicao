cmake_minimum_required(VERSION 3.31)
project(untitled2 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled2 main.c
        uf.c
        uf.h
        eleicao.c
        eleicao.h
        pessoa.c
        pessoa.h
        gerais.c
        gerais.h
        candidato_eleicao.c
        candidato_eleicao.h
        voto.c
        voto.h
        comparecimento.c
        comparecimento.h
       )
