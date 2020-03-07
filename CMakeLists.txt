cmake_minimum_required (VERSION 3.1)

project (Ascii_Empire)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CORE_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib)
set(SIMULATOR_BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(AI_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/bin/intelligences)
set(AI_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/ai)
set(EMPIRE_HEADER_DIR ${CMAKE_SOURCE_DIR}/include)

#create core libaray
set(CORE_SOURCE_DIRECTORY "src/core")
set(CORE_VERSION "1.0.0")
set(CORE_SRCS ${CORE_SOURCE_DIRECTORY}/Empire.cpp ${CORE_SOURCE_DIRECTORY}/Extra.cpp)
add_library(empire-core SHARED ${CORE_SRCS})
target_link_libraries(empire-core ${CMAKE_DL_LIBS})
target_include_directories(empire-core PRIVATE ${EMPIRE_HEADER_DIR})
set_target_properties(empire-core PROPERTIES VERSION ${CORE_VERSION})
set_target_properties(empire-core PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CORE_LIBRARY_DIR})

#create simulator
link_directories(${CORE_LIBRARY_DIR})
set(SIMULATOR_SOURCE_DIRECTORY "src/simulator")
add_executable(simulator ${SIMULATOR_SOURCE_DIRECTORY}/main.cpp)
target_link_libraries(simulator Threads::Threads)
target_link_libraries(simulator empire-core)
target_include_directories(simulator PRIVATE ${EMPIRE_HEADER_DIR})
set_target_properties(simulator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SIMULATOR_BIN_DIR})

#example AI
add_subdirectory(${AI_SOURCE_DIR}/Alpha) 
#add_executable(Alpha_AI.so.0.1 ${AI_ALPHA_SRCS})

#add_executable(Beta_AI.so.0.1 ${AI_BETA_SRCS})
