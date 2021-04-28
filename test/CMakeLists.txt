set( TEST_LIST
        TestKata
        )

foreach ( target ${TEST_LIST} )
    my_executable( ${target} gtest gtest_main pthread )
endforeach ()
