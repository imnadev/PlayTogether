cmake_minimum_required(VERSION 3.20)
project(PlayTogether C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")

add_executable(PlayTogether
        main/main.c
        database/database.c database/database.h
        struct/user.h
        socket/server/server_socket.c socket/server/server_socket.h
        screen/setup/setup_window.c screen/setup/setup_window.h
        screen/server/server_window.c screen/server/server_window.h
        screen/client/client_window.c screen/client/client_window.h
        socket/client/client_socket.c socket/client/client_socket.h
        vlc/vlc.c vlc/vlc.h)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})
target_link_libraries(PlayTogether ${GTK3_LIBRARIES})