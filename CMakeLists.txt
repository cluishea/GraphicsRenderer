cmake_minimum_required(VERSION 3.28)

    project(MySFMLProject
        VERSION 1.0
        LANGUAGES CXX
    )

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)           

        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            Debug
            Release
            RelWithDebInfo
            MinSizeRel
        )
    endif()

    find_package(SFML 3 REQUIRED COMPONENTS
        Graphics
        Window
        System
    )

    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    )
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.h"
    )

    add_executable(game
        ${SOURCES}
        ${HEADERS}
    )

    target_include_directories(game PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/includes"
    )

    target_link_libraries(game PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
    )

    target_compile_options(game PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
