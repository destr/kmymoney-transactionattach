# The CMake version we require
cmake_minimum_required(VERSION 2.8.7)

# Setting the name of the main project
project(kmymoney-transactionattach)

set(CMAKE_AUTOMOC TRUE)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "0")
set(VERSION_PATCH "2")

if(NOT WIN32)
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
else(WIN32)
find_package(Qt4 REQUIRED QtCore)
endif(NOT WIN32)

include_directories(${KDE4_INCLUDES})
include_directories(${QT_INCLUDES})
add_definitions( ${QT_DEFINITIONS} ${KDE4_DEFINITIONS} ${KDEPIM_DEFINITIONS})
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}")

if(NOT WIN32)
  # use position independent code
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif(NOT WIN32)



if(NOT WIN32)
add_subdirectory(src)
else(WIN32)
endif(NOT WIN32)
add_subdirectory(tests)
add_subdirectory(po)

