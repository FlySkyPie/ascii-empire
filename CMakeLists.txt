cmake_minimum_required (VERSION 2.6)

project (Ascii_Empire)

set(CORE_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib)

set(EMPIRE_HEADERS ${CLIENT_DEFINITION} ${SERVER_DEFINITION})

#include_directories(${Mylib_SOURCE_DIR}/include) 

#set (HELLO_SRCS hello.c)
#add_executable (hello ${HELLO_SRCS})

#create core libaray
set(CORE_SOURCE_DIRECTORY "src/core")
set(CORE_VERSION "1.0.0")
set(CORE_SRCS ${CORE_SOURCE_DIRECTORY}/Empire.cpp ${CORE_SOURCE_DIRECTORY}/Extra.cpp)
add_library(empire-core SHARED ${CORE_SRCS} ${EMPIRE_HEADERS})
target_include_directories(empire-core PRIVATE include)
set_target_properties(empire-core PROPERTIES VERSION ${CORE_VERSION})
set_target_properties(empire-core PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CORE_LIBRARY_DIR})


#example AI
#add_executable(Alpha_AI.so.0.1 ${AI_ALPHA_SRCS})

#add_executable(Beta_AI.so.0.1 ${AI_BETA_SRCS})
