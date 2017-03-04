cmake_minimum_required (VERSION 3.5)

if (COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
    if (CMAKE_VERSION VERSION_GREATER 2.8.12 OR CMAKE_VERSION VERSION_EQUAL 2.8.12)
        # INTERFACE_LINK_LIBRARIES defines the link interface
        cmake_policy (SET CMP0022 NEW)
    endif ()
    if (CMAKE_VERSION VERSION_GREATER 3.0.0 OR CMAKE_VERSION VERSION_EQUAL 3.0.0)
        # Disallow use of the LOCATION target property - therefore we set to OLD as we still need it
        cmake_policy (SET CMP0026 OLD)
        # MACOSX_RPATH is enabled by default
        cmake_policy (SET CMP0042 NEW)
    endif ()
endif ()

# Set project name
project (Second)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Set CMake modules search path
# Urho3D should be build at folder "<urho3d git root>/build/"
set (CMAKE_MODULE_PATH ${URHO3D_HOME}/../CMake/Modules)

# Include Urho3D Cmake common module
include (Urho3D-CMake-common)

# Define target name
set (TARGET_NAME Urho3DTest)

# Define source files
file (GLOB CPP_FILES src/*.cpp)
file (GLOB H_FILES src/*.h)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})
message(STATUS "SOURCE_FILES ${SOURCE_FILES}")

# Setup target with resource copying
setup_main_executable ()