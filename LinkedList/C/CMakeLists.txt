
set(LIBNAME "single_linked_list")

list(APPEND SOURCES
    single_linked_list.c
)

list(APPEND HEADERS
    single_linked_list.h
)

add_library("${LIBNAME}" ${LIB_TYPE} ${HEADERS} ${SOURCES})

add_subdirectory(sample)