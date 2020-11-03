cmake_minimum_required( VERSION 3.14 )
project( kata )

set( CMAKE_CXX_STANDARD 14 )

include_directories( ./kata )

add_subdirectory( ./test )
