#Set assets path
set(ASSETS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")

#Generate Config.hpp
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in
    ${CMAKE_BINARY_DIR}/demos/core_demo/config.hpp
)

#Look in build for includes
target_include_directories(core_demo PRIVATE ${CMAKE_BINARY_DIR}/demos/core_demo)