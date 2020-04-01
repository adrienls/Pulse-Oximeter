cmake_minimum_required(VERSION 3.15)
project(Pulse_Oximeter C)

set(CMAKE_C_STANDARD 11)

add_executable(Pulse_Oximeter main.c affichage.c affichage.h define.h fir.c fir.h iir.c iir.h integration.c integration.h lecture.c lecture.h mesure.c mesure.h fichiers.c fichiers.h)