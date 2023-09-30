cmake_minimum_required(VERSION 3.14)

project(QtSimpleVotingDemoApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick RemoteObjects)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick RemoteObjects)

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)
# add_subdirectory(management)
