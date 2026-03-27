cmake_minimum_required(VERSION 3.16)

project(03-PlainCppApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(03-PlainCppApp main.cpp)

include(GNUInstallDirs)
install(TARGETS 03-PlainCppApp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
