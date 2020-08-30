cmake_minimum_required(VERSION 3.10)


project(solitaire C)


set(SRCS
    generate-boards-files.c
    libsolitaire.c
    list-opti.c
    )

set(SRCS2
    play.c
    libsolitaire.c
    list-opti.c
    )


set(HEADERS
    libsolitaire.h
    list-opti.h
    )

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(CURSES_NEED_NCURSES true)


# add the executable
add_executable(generate-boards-files ${SRCS} ${HEADERS})

add_executable(showboardfile showboardfile.c)

add_executable(statboardfile statboardfile.c)

add_executable(solboard ${SRCS2} ${HEADERS})
target_link_libraries(solboard ${CURSES_LIBRARY})
