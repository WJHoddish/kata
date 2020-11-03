cmake_minimum_required( VERSION 3.17 )
project( kata_test )

set( CMAKE_CXX_STANDARD 14 )

add_executable( pmath pmath.cpp )
target_link_libraries( pmath gtest gtest_main )
