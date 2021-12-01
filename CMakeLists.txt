cmake_minimum_required(VERSION 3.20)
project(PlayTogether C)

set(CMAKE_C_STANDARD 99)

add_executable(PlayTogether main.c db.c db.h structs.h socket.c socket.h setup_window.c setup_window.h server_window.c server_window.h client_window.c client_window.h)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})
target_link_libraries(PlayTogether ${GTK3_LIBRARIES})