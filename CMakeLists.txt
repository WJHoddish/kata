cmake_minimum_required( VERSION 3.17 )
project( kata )

set( CMAKE_CXX_STANDARD 14 )

aux_source_directory( . DIR_MAIN )

add_subdirectory( third-party )