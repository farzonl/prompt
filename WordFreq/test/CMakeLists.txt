project(${CMAKE_PROJECT_NAME}_TEST)

download_file(https://raw.githubusercontent.com/onqtam/doctest/2.4.6/doctest/doctest.h 
              ${CMAKE_SOURCE_DIR}/packages/doctest/doctest.h
              MD5
              1494db8a28035bcf6caeea817c4b2b65)

include_directories(${CMAKE_SOURCE_DIR}/packages/
                    ${CMAKE_SOURCE_DIR}/src/lib
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/files
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}
               test.cpp
               ${CMAKE_SOURCE_DIR}/src/lib/parser.cpp
)
