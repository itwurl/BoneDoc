CMAKE_MINIMUM_REQUIRED(VERSION 2.8.1)
PROJECT(BoneDocServer)

IF((CMAKE_SYSTEM_NAME STREQUAL Linux) AND 
    ((CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64) OR
        (CMAKE_SYSTEM_PROCESSOR STREQUAL armv7l)))

    # linux found - tested with x86_64/arm systems
    MESSAGE("Using configuration for Linux ...")

    # c++11 is used
    ADD_DEFINITIONS(-std=c++11)

    SET(BoneDocServer_SOURCES src/BoneDocServer.cpp src/main.cpp src/Anatomy.cpp src/Femur.cpp src/Humerus.cpp src/Tibia.cpp src/Study.cpp)
    SET(BoneDocServer_HEADERS src/BoneDocServer.h src/Anatomy.h src/Femur.h src/Humerus.h src/Tibia.h src/Study.h)

    # BOOST
    FIND_PACKAGE(Boost REQUIRED)
    SET(Boost_LIBRARIES boost_system boost_thread boost_filesystem)

    # VTK
    FIND_PACKAGE(VTK REQUIRED)

    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS})

    # build executable
    SET(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
    MESSAGE("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})
    SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

    ADD_EXECUTABLE(BoneDocServer ${BoneDocServer_SOURCES} ${BoneDocServer_HEADERS})

    TARGET_LINK_LIBRARIES(BoneDocServer ${VTK_LIBRARIES} ${Boost_LIBRARIES})

ELSE()

    # other systems not supported
    MESSAGE("System not supported!")

ENDIF()

