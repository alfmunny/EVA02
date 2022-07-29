cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -ggdb -std=c++17 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

project(eva02)

include_directories(.)

set(LIB_SRC
    src/logging.cpp
    )

add_library(eva02 SHARED 
    ${LIB_SRC}
    )

set(LIBS
    eva02
    )

add_executable(test_logging
    test/test_logging.cpp
    )

add_dependencies(test_logging ${LIBS})
target_link_libraries(test_logging ${LIBS})

add_custom_target(test
    COMMAND bin/test_logging
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    )

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
