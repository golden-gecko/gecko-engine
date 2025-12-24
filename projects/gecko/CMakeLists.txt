cmake_minimum_required(VERSION 4.2)

project(Gecko)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/OIS/include)

target_link_libraries(${PROJECT_NAME} OgreBites)
target_link_libraries(${PROJECT_NAME} debug ${CMAKE_SOURCE_DIR}/lib/OIS/lib/OIS_d.lib optimized ${CMAKE_SOURCE_DIR}/lib/OIS/lib/OIS.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/system
)
