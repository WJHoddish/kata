cmake_minimum_required( VERSION 3.10 )
project( kata )

set( CMAKE_CXX_STANDARD 17 )

include_directories( include )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin )

function( my_executable name )
    add_executable( ${name} ${name}.cpp )

    set( INDEX 1 )
    while ( INDEX LESS ${ARGC} )
        target_link_libraries( ${name} ${ARGV${INDEX}} )
        math( EXPR INDEX "${INDEX} + 1" )
    endwhile ()
endfunction()

add_subdirectory( test )
