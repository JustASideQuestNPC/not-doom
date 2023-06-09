cmake_minimum_required(VERSION 3.21)
project(NotDoom LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(NotDoom
    src/main.cpp
    src/controls.h)

target_link_libraries(NotDoom PRIVATE sfml-graphics)
target_compile_features(NotDoom PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET NotDoom POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:NotDoom> $<TARGET_FILE_DIR:NotDoom> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS NotDoom)
