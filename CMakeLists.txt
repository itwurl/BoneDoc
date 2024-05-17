cmake_minimum_required(VERSION 3.10)
project(BoneDoc)

# Setze den C++-Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setze Ausgabeverzeichnisse auf das Arbeitverzeichnis von CMake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

# Suche nach Boost und VTK (nur Release-Versionen)
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(VTK REQUIRED)

# Fasse Quell- und Headerdateien in Variablen zusammen
file(GLOB BoneDoc_SOURCES "src/*.cpp")
file(GLOB BoneDoc_HEADERS "src/*.h")

# Füge die Include-Verzeichnisse von Boost und VTK hinzu
include_directories(${Boost_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS})

# Erstelle das ausführbare Binary BoneDoc
add_executable(BoneDoc ${BoneDoc_SOURCES} ${BoneDoc_HEADERS})

# Verknüpfe das Binary mit den Boost- und VTK-Bibliotheken
target_link_libraries(BoneDoc ${Boost_LIBRARIES} ${VTK_LIBRARIES})
