# This is the important bit for you, if you want to change the name of your extension in the build system
set( EXTENSION_NAME A3EXT )

# Only edit below if you need to
cmake_minimum_required( VERSION 3.8 )

project( ${EXTENSION_NAME} )

SOURCE_GROUP( "Template Files" REGULAR_EXPRESSION ".*tpp" )

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )

if( MSVC )
#    add_compile_options( /W4 )
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
#    add_compile_options( -Wall -Wextra )
endif()

file( GLOB TARGET_SOURCES *.cpp *.hpp Framework/*.cpp Framework/*.hpp Framework/*.tpp )

set( SOURCE_FILES ${TARGET_SOURCES} )

add_library( ${EXTENSION_NAME} SHARED ${SOURCE_FILES} )

target_include_directories( ${EXTENSION_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Framework/ThridParty )