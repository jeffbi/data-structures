
set(LIBNAME "stack")

list(APPEND SOURCES
    stack.c
)

list(APPEND HEADERS
    stack.h
)

add_library("${LIBNAME}" ${LIB_TYPE} ${HEADERS} ${SOURCES})

add_subdirectory(sample)
