cmake_minimum_required(VERSION 4.2)

project(Gecko)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_DEBUG_POSTFIX _d)

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${OIS_ROOT}/include/ois)

target_link_libraries(${PROJECT_NAME} OgreBites)
target_link_libraries(${PROJECT_NAME} debug ${OIS_ROOT}/lib/OIS_d.lib optimized ${OIS_ROOT}/lib/OIS.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/Gecko)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
