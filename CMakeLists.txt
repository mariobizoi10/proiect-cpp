cmake_minimum_required(VERSION 4.1)
project(ProiectProgramare_2_C__)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(ProiectProgramare_2_C__
        app2.cpp
        shared/classes/Data.cpp
        shared/classes/Elev.cpp
        shared/classes/Nota.cpp
        shared/classes/Absenta.cpp
        shared/classes/CerereMotivare.cpp
)

add_executable(app1
        app1.cpp
        shared/classes/Data.cpp
        shared/classes/Elev.cpp
        shared/classes/Nota.cpp
        shared/classes/Absenta.cpp
        shared/classes/CerereMotivare.cpp
        app1.cpp
)