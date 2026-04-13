cmake_minimum_required(VERSION 3.10)

project(homework1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- ESTA É A LINHA QUE FALTAVA ---
find_package(OpenCV REQUIRED)
find_package(glm REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS}
                    ${GLM_INCLUDE_DIRS})

add_executable(question2
    scripts/q2.cpp
)
add_executable(question4
    scripts/q4.cpp
)       
add_executable(question5
    scripts/q5.cpp
)    

target_include_directories(question2 PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(question2 ${OpenCV_LIBS})
target_include_directories(question4 PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(question4 ${OpenCV_LIBS})
target_include_directories(question5 PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(question5 ${OpenCV_LIBS})
