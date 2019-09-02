#
# CMake master file for building the DataStructures code.
#

cmake_minimum_required(VERSION 3.0)

project(DataStructures)

#compiler options
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
endif()

set(LIB_TYPE STATIC)


# Documentation
option(BUILD_DOC "Build Documentation" OFF)

if (BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started.")

        add_custom_target(  doc_doxygen
                            ALL     # allows docs to be built together with library
                            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                            COMMENT "Generating API docs with Doxygen."
                            VERBATIM
                        )
    else (DOXYGEN_FOUND)
        message("Install Doxygen to generate documentation")
    endif (DOXYGEN_FOUND)
endif (BUILD_DOC)

add_subdirectory(LinkedList)
add_subdirectory(Stack)
