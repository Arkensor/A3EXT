cmake_minimum_required( VERSION 3.8 )

##################################################################
# define a source group for template files in Visual Studio
SOURCE_GROUP( "Template Files" REGULAR_EXPRESSION ".*tpp" )

project( A3EXT )

if( MSVC )
#    add_compile_options( /W4 )
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
#    add_compile_options( -Wall -Wextra )
endif()

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( TARGET_HEADERS
     Framework/DataTypes.hpp
     Framework/StartParameterHandler.hpp
     Framework/ExtensionBase.hpp
     Framework/ProcessorWorkload.hpp
     Framework/ProcessorResult.hpp
     Framework/ProcessorQueue.hpp
     Framework/Processor.hpp
     Configuration.hpp  )

set( TARGET_TEMPLATES
     Framework/ProcessorQueue.tpp )

set( TARGET_SOURCES
     Framework/ExtensionBase.cpp
     Framework/StartParameterHandler.cpp
     Framework/ExtensionEntry.cpp
     Framework/ProcessorWorkload.cpp
     Framework/ProcessorResult.cpp
     Framework/Processor.cpp
     Extension.cpp )

set( INIH_SOURCES
     Framework/ThridParty/inih/INI.hpp
     Framework/ThridParty/inih/INI.cpp
     Framework/ThridParty/inih/INIReader.hpp
     Framework/ThridParty/inih/INIReader.cpp )

set( SOURCE_FILES ${TARGET_HEADERS} ${TARGET_TEMPLATES} ${TARGET_SOURCES} ${INIH_SOURCES} )

include_directories( ${PROJECT_SOURCE_DIR}/Framework/ThridParty )

add_library( A3EXT SHARED ${SOURCE_FILES} )