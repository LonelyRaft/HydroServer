# Reference:
# https://doc.qt.io/qt-6/cmake-get-started.html

# minimal cmake version
cmake_minimum_required(VERSION 3.23)

# cpp standard
set(CMAKE_CXX_COMPILER ${CMAKE_PREFIX_PATH}/bin/g++.exe)
set(CMAKE_CXX_FLAGS "-Wall -Wshadow")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# project attributes: name, version, language
project(SktAssist VERSION 0.01 LANGUAGES CXX)

# build type: Debug/Release
# set(CMAKE_BUILD_TYPE Debug)

# output directory: build
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

# static library: build/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# shared library: build/shared
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# executable file: build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# find qt6 package
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)
qt_standard_project_setup()

# user interface library
# set(LIB_UI hsui)
# add_subdirectory(interface)

# build target
aux_source_directory(. PROTJECT_SRC_LIST)
add_executable(${PROJECT_NAME} ${PROTJECT_SRC_LIST})
target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Widgets
    # PRIVATE ${LIB_UI}
    PRIVATE Qt6::Network
)

if(CMAKE_BUILD_TYPE STREQUAL Release)
    # Prevent the creation of a console window on Windows.
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
endif()

# install binary
file(
    COPY
    ${CMAKE_PREFIX_PATH}/bin/Qt6Core.dll
    ${CMAKE_PREFIX_PATH}/bin/Qt6Gui.dll
    ${CMAKE_PREFIX_PATH}/bin/Qt6Widgets.dll
    ${CMAKE_PREFIX_PATH}/bin/Qt6Network.dll
    ${CMAKE_PREFIX_PATH}/plugins/platforms
    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
