cmake_minimum_required(VERSION 3.15)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab5 main.cpp Token.h Token.cpp Scanner.cpp Scanner.h Parser.cpp Parser.h DatalogProgram.cpp DatalogProgram.h Predicate.cpp Predicate.h Parameter.cpp Parameter.h Rule.cpp Rule.h Tuple.cpp Tuple.h Scheme.cpp Scheme.h Relations.cpp Relations.h Database.cpp Database.h Node.cpp Node.h Graph.cpp Graph.h)