project(${CMAKE_PROJECT_NAME})

set(SourceFiles  cli/main.cpp
                 lib/hanoi.cpp
)

set(HeaderFiles lib/hanoi.h
)

add_executable(${PROJECT_NAME} ${SourceFiles} ${HeaderFiles})


target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)