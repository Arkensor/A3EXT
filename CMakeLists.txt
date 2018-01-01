cmake_minimum_required( VERSION 3.8 )

project( A3DB )

if( MSVC )
#    add_compile_options( /W4 )
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
#    add_compile_options( -Wall -Wextra )
endif()

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( TARGET_HEADERS
     Source/Framework/DataTypes.hpp
     Source/Framework/StartParameterHandler.hpp
     Source/Framework/ExtensionBase.hpp
     Source/Framework/ProcessorWorkload.hpp
     Source/Framework/ProcessorResult.hpp
     Source/Framework/ProcessorQueue.hpp
     Source/Framework/Processor.hpp
     Source/Configuration.hpp  )

set( TARGET_TEMPLATES
     Source/Framework/ProcessorQueue.tpp )

set( TARGET_SOURCES
     Source/Framework/ExtensionBase.cpp
     Source/Framework/StartParameterHandler.cpp
     Source/Framework/ExtensionEntry.cpp
     Source/Framework/ProcessorWorkload.cpp
     Source/Framework/ProcessorResult.cpp
     Source/Framework/Processor.cpp
     Source/Extension.cpp )

set( INIH_SOURCES
     Source/Framework/ThridParty/inih/INI.hpp
     Source/Framework/ThridParty/inih/INI.cpp
     Source/Framework/ThridParty/inih/INIReader.hpp
     Source/Framework/ThridParty/inih/INIReader.cpp )

set( SOURCE_FILES ${TARGET_HEADERS} ${TARGET_TEMPLATES} ${TARGET_SOURCES} ${INIH_SOURCES} )

include_directories( ${PROJECT_SOURCE_DIR}/Source/Framework/ThridParty )

add_library( A3DB SHARED ${SOURCE_FILES} )