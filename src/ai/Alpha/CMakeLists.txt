set(AI_VERSION "1.0.0")
set(AI_SRCS Alpha_AI.cpp )

add_library(empire-ai-alpha SHARED ${AI_SRCS} ${EMPIRE_HEADERS})
target_include_directories(empire-ai-alpha PRIVATE ${EMPIRE_HEADER_DIR})
set_target_properties(empire-ai-alpha PROPERTIES VERSION ${AI_VERSION})
set_target_properties(empire-ai-alpha PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${AI_LIBRARY_DIR}) 
