CMAKE_MINIMUM_REQUIRED(VERSION 2.8.1)
PROJECT(BoneDoc)

IF((CMAKE_SYSTEM_NAME STREQUAL Linux) AND 
    ((CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64) OR
        (CMAKE_SYSTEM_PROCESSOR STREQUAL armv7l)))

    # linux found - tested with x86_64/arm systems
    MESSAGE("Using configuration for Linux ...")

    # c++11 is used
    ADD_DEFINITIONS(-std=c++11)

    SET(BoneDoc_SOURCES BoneDocServer.cpp main.cpp Anatomy.cpp Femur.cpp Humerus.cpp Tibia.cpp)
    SET(BoneDoc_HEADERS BoneDocServer.h Anatomy.h Femur.h Humerus.h Tibia.h)

    # BOOST
    FIND_PACKAGE(Boost REQUIRED)
    SET(Boost_LIBRARIES boost_system boost_thread boost_filesystem)

    # VTK
    FIND_PACKAGE(VTK REQUIRED)


    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS})

    ADD_EXECUTABLE(BoneDoc ${BoneDoc_SOURCES} ${BoneDoc_HEADERS})

    TARGET_LINK_LIBRARIES(BoneDoc ${VTK_LIBRARIES} ${Boost_LIBRARIES})

ELSE()

    # other systems not supported
    MESSAGE("System not supported!")

ENDIF()

