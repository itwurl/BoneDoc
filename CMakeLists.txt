cmake_minimum_required(VERSION 3.10)
project(BoneDoc)

# set the c++ standard 11
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

# pthread flag
set(THREADS_PREFER_PTHREAD_FLAG ON)

# set output directories to cmake's working directory 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

# set threads package explicitly
find_package(Threads REQUIRED)

# set boost and vtk package
find_package(Boost REQUIRED COMPONENTS filesystem system thread)
find_package(VTK REQUIRED)

# combine sources and headers
file(GLOB BoneDoc_SOURCES "src/*.cpp")
file(GLOB BoneDoc_HEADERS "src/*.h")

# add include directries to cmake variable
include_directories(${Boost_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS})

# create binary
add_executable(BoneDoc ${BoneDoc_SOURCES} ${BoneDoc_HEADERS})

# link binary with boost, vtk and threads library
target_link_libraries(BoneDoc ${Boost_LIBRARIES} ${VTK_LIBRARIES} ${Thread_Libraries})
