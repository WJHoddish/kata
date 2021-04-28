set( TEST_LIST
        Test
        TestGem
        TestMoreTraits
        TestThreadPool
        )

foreach ( target ${TEST_LIST} )
    my_executable( ${target} gtest gtest_main pthread )
endforeach ()
