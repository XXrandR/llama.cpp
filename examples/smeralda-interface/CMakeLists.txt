set(TARGET smeralda)
set(RESOURCES tokenizer.cpp)
set(RESOURCES_LLAMA_WRAPPER LlamaInterface.h LlamaInterface.cpp LlamaWrapper.h LlamaWrapper.cpp)
add_executable(${TARGET} ${RESOURCES})
install(TARGETS ${TARGET} RUNTIME)

# adding both libraries
add_library(${TARGET}_base SHARED ${RESOURCES})
add_library(${TARGET}_llama SHARED ${RESOURCES_LLAMA_WRAPPER})

# add for the executable
target_link_libraries(${TARGET} PRIVATE common llama ${CMAKE_THREAD_LIBS_INIT})

# add plugins for the libraries
target_link_libraries(${TARGET}_base PRIVATE common llama ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TARGET}_llama PRIVATE common llama ${CMAKE_THREAD_LIBS_INIT})

target_compile_features(${TARGET} PRIVATE cxx_std_17)

