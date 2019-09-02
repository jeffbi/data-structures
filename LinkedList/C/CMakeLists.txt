
set(LIBNAME "linked_list")

list(APPEND SOURCES
    linked_list.c
)

list(APPEND HEADERS
    linked_list.h
)

add_library("${LIBNAME}" ${LIB_TYPE} ${HEADERS} ${SOURCES})

add_subdirectory(sample)