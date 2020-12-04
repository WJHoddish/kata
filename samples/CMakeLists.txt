cmake_minimum_required( VERSION 3.14 )
project( kata_samples )

set( CMAKE_CXX_STANDARD 14 )

function( add name )
    add_executable( ${name} ${name}.cpp )
    target_link_libraries( ${name} gtest gtest_main )
endfunction()

# NOTE: Samples (functional components).
add( pattern )
add( task )