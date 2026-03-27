cmake_minimum_required(VERSION 3.16)

project(CheckCoordinates VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Sql Network)

set(PROJ_ROOT "C:/msys64/home/Jan Perme/PROJ/build")

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        dbmanager.h
        dbmanager.cpp
        locationrow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CheckCoordinates
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        progressdialog.h progressdialog.cpp progressdialog.ui
        logindialog.h logindialog.cpp
    )
else()
    if(ANDROID)
        add_library(CheckCoordinates SHARED ${PROJECT_SOURCES})
    else()
        add_executable(CheckCoordinates ${PROJECT_SOURCES})
    endif()
endif()
# Embed the Windows icon

if(WIN32)
    target_sources(CheckCoordinates PRIVATE appicon.rc)
endif()


# --- PROJ integration ---
# set(PROJ_INCLUDE "C:/Qt/Tools/mingw1310_64/x86_64-w64-mingw32/include")
# set(PROJ_LIB     "C:/Qt/Tools/mingw1310_64/x86_64-w64-mingw32/lib")

target_include_directories(CheckCoordinates PRIVATE ${PROJ_INCLUDE})
target_link_directories(CheckCoordinates PRIVATE ${PROJ_LIB})

target_link_libraries(CheckCoordinates PRIVATE
    proj
    sqlite3
    z
    pthread
)
# -------------------------

target_link_libraries(CheckCoordinates PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CheckCoordinates)
endif()

set_target_properties(CheckCoordinates PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CheckCoordinates
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CheckCoordinates)
endif()
