CMAKE_MINIMUM_REQUIRED(VERSION 2.8.1)
PROJECT(BoneDoc)

SET(BoneDoc_SOURCES BoneDoc.cpp BoneDocServer.cpp main.cpp Anatomy.cpp Femur.cpp Humerus.cpp Tibia.cpp)
SET(BoneDoc_HEADERS BoneDoc.h BoneDocServer.h Anatomy.h Femur.h Humerus.h Tibia.h)

ADD_DEFINITIONS(-std=c++11)

IF((CMAKE_SYSTEM_NAME STREQUAL Linux) AND (CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64))

    # Linux, Ubuntu
    MESSAGE("Using configuration for Ubuntu ...")

    ### BOOST ###
    SET(BOOST_INCLUDES "/usr/include")
    SET(BOOST_LIBRARY_DIR "/usr/lib/x86_64-linux-gnu")
    SET(BOOST_LIBRARIES boost_system pthread)

    ### VTK ###
    SET(VTK_DIR "/opt/VTK-8.1.0/build")
    FIND_PACKAGE(VTK REQUIRED)	
    INCLUDE(${VTK_USE_FILE})

ELSEIF(CMAKE_SYSTEM_NAME STREQUAL Linux AND CMAKE_SYSTEM_PROCESSOR STREQUAL armv7l)

    # Rasperry Pi 
    MESSAGE("Using configuration for Rasperry PI ...")

    ### BOOST ###
    SET(BOOST_INCLUDES "/usr/include")
    SET(BOOST_LIBRARY_DIR "/usr/lib/arm-linux-gnueabihf")
    SET(BOOST_LIBRARIES boost_system pthread)

    ### VTK ###
    SET(VTK_DIR "/home/pi/bin/VTK-8.1.0")
    FIND_PACKAGE(VTK REQUIRED)
    INCLUDE(${VTK_USE_FILE})
ELSE()

	# Other systems (windows, mac oc, ...) are not supported
	MESSAGE("System not supported")
	
ENDIF()


INCLUDE_DIRECTORIES(${VTK_INCLUDES} ${BOOST_INCLUDES})
LINK_DIRECTORIES(${VTK_LIBRARY_DIR})

ADD_EXECUTABLE(BoneDoc ${BoneDoc_SOURCES} ${BoneDoc_HEADERS})

TARGET_LINK_LIBRARIES(BoneDoc ${VTK_LIBRARIES} ${BOOST_LIBRARIES})
