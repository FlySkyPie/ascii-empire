set(AI_VERSION "1.0.0")
set(AI_SRCS Beta_AI.cpp )

add_library(empire-ai-beta SHARED ${AI_SRCS} ${EMPIRE_HEADERS})
target_include_directories(empire-ai-beta PRIVATE ${EMPIRE_HEADER_DIR})
set_target_properties(empire-ai-beta PROPERTIES VERSION ${AI_VERSION})
set_target_properties(empire-ai-beta PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${AI_LIBRARY_DIR}) 
