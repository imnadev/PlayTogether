cmake_minimum_required(VERSION 3.20)
project(PlayTogether C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(PlayTogether
        main/main.c
        database/database.c database/database.h
        struct/user.h
        socket/server/server.c socket/server/server.h
        screen/setup/setup_window.c screen/setup/setup_window.h
        screen/main/main_window.c screen/main/main_window.h
        socket/client/client.c socket/client/client.h
        vlc/vlc.c vlc/vlc.h struct/constants.h)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})
target_link_libraries(PlayTogether ${GTK3_LIBRARIES})

#pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
#include_directories(${GTK2_INCLUDE_DIRS})
#link_directories(${GTK2_LIBRARY_DIRS})
#add_definitions(${GTK2_CFLAGS_OTHER})
#target_link_libraries(PlayTogether ${GTK2_LIBRARIES})

install(TARGETS PlayTogether
        COMPONENT linapp
        RUNTIME DESTINATION "/home/"
        LIBRARY DESTINATION "/home/"
        DESTINATION "/home/"
        )

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "KK") #required
INCLUDE(CPack)