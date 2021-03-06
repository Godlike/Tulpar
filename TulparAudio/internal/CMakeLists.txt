# Copyright (C) 2018 by Godlike
# This code is licensed under the MIT license (MIT)
# (http://opensource.org/licenses/MIT)

cmake_minimum_required(VERSION 3.8)
cmake_policy(VERSION 3.8)

project(TulparAudio_Internal)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(${PROJECT_NAME} OBJECT "")
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_library(Tulpar::Audio::Internal ALIAS ${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# OpenAL
include(OpenALConfig)

# STB
include(stb)

set(INTERNAL_HEADERS
    include/tulpar/internal/Collection.hpp
    include/tulpar/internal/Collection.imp

    include/tulpar/internal/BufferCollection.hpp
    include/tulpar/internal/Context.hpp
    include/tulpar/internal/Device.hpp
    include/tulpar/internal/ListenerController.hpp
    include/tulpar/internal/SourceCollection.hpp
)

set(INTERNAL_SOURCES
    source/BufferCollection.cpp
    source/Context.cpp
    source/Device.cpp
    source/ListenerController.cpp
    source/SourceCollection.cpp
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${INTERNAL_HEADERS}
        ${INTERNAL_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    SYSTEM
        PUBLIC
            ${OPENAL_INCLUDE_DIR}
            ${STB_INCLUDE_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE
        $<TARGET_PROPERTY:Tulpar::Audio,INTERFACE_INCLUDE_DIRECTORIES>
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<TARGET_PROPERTY:Mule::Utilities,INTERFACE_INCLUDE_DIRECTORIES>
)

set_target_properties(
    ${PROJECT_NAME}

    PROPERTIES

    FOLDER "${TARGET_FOLDER_ROOT}"
)

target_compile_definitions(
    ${PROJECT_NAME}

    PUBLIC

    ${OPENAL_DEFINITIONS}
)

if (UNIX)
    set_target_properties(
        ${PROJECT_NAME}

        PROPERTIES

        POSITION_INDEPENDENT_CODE ON
    )
endif()
