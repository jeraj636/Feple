cmake_minimum_required(VERSION 3.20)

project(Feple)

add_subdirectory(HenigmaEngine)

add_executable(${PROJECT_NAME}
    ../test.cpp 
)

target_link_libraries(${PROJECT_NAME} PRIVATE
HenigmaEngine
)




