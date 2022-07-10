project(${CMAKE_PROJECT_NAME}_TEST)

download_file(https://github.com/catchorg/Catch2/releases/download/v2.13.8/catch.hpp
              ${CMAKE_SOURCE_DIR}/packages/catch2/catch.hpp
              MD5
              e45f70693208dca2b6813a078e3e64eb)

include_directories(${CMAKE_SOURCE_DIR}/packages/
                    ${CMAKE_SOURCE_DIR}/src/lib
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/files
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}
               test.cpp
               ${CMAKE_SOURCE_DIR}/src/lib/parser.cpp
)
