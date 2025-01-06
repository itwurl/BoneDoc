cmake_minimum_required(VERSION 3.10)
project(BoneDoc)

# Setze den C++ Standard
set(CMAKE_CXX_STANDARD 11)

# Finde die Boost und VTK Bibliotheken
find_package(Boost REQUIRED COMPONENTS filesystem system thread)
find_package(VTK REQUIRED)

# Füge die Quellcode-Dateien hinzu
file(GLOB BoneDoc_SOURCES "src/*.cpp")
file(GLOB BoneDoc_HEADERS "src/*.h")

# Inklusive Verzeichnisse für Boost und VTK
include_directories(${Boost_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS})

# Setze den Ausgabepfad für ausführbare Dateien
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Erstelle die ausführbare Datei
add_executable(BoneDoc ${BoneDoc_SOURCES} ${BoneDoc_HEADERS})

# Linke die Bibliotheken
target_link_libraries(BoneDoc ${Boost_LIBRARIES} ${VTK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
