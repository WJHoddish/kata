cmake_minimum_required( VERSION 3.14 )
project( kata_test )

set( CMAKE_CXX_STANDARD 14 )

function( add name )
    add_executable( ${name} ${name}.cpp )
    target_link_libraries( ${name} gtest gtest_main )
endfunction()

#TODO: Add your test cases below.
add( more_traits )
add( pmath )
add( task ) # cpp multi-thread
add( text )
