cmake_minimum_required(VERSION 3.17)

project(QtVTKDemo)

#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt5 COMPONENTS Core Gui OpenGL Widgets REQUIRED)

#======================= INCLUSION OF VTK ======================#
set(VTK_DIR $ENV{VTK_DIR})
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

#======================= INCLUSION OF Our Code ======================#
message("CMAKE_SOURCE_DIR " ${CMAKE_SOURCE_DIR})
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${SOURCE_DIR}/*.cpp"
	"${SOURCE_DIR}/*.ui"
	"${SOURCE_DIR}/*.h"
)
message("SOURCES " ${SOURCES})
# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS})

# Add the executable
if (WIN32) 
    add_executable(QtVTKDemo WIN32 ${SOURCES})
elseif(UNIX)
    add_executable(QtVTKDemo ${SOURCES})
endif()

# Add the target includes
target_include_directories(QtVTKDemo PRIVATE ${SOURCE_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries( QtVTKDemo ${QT_LIBRARIES}${VTK_LIBRARIES})
