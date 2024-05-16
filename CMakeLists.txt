cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(Qt6_DIR "/usr/lib/x86_64-linux-gnu/cmake")
set(QT_VERSION_MAJOR 6)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Boost_DIR "/usr/lib/x86_64-linux-gnu")
find_package(Qt NAMES Qt6 COMPONENTS PrintSupport Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport Widgets REQUIRED)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/qcustomplot) # here adding qcustomplot subfolder

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED COMPONENTS locale unit_test_framework)

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(main)

target_include_directories(tests PUBLIC lib)
target_include_directories(main PUBLIC lib)
