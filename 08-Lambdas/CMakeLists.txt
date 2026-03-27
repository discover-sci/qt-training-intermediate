cmake_minimum_required(VERSION 3.16)

project(08-Lambdas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(08-Lambdas main.cpp)

include(GNUInstallDirs)
install(TARGETS 08-Lambdas
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
