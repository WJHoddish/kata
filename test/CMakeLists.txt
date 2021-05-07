set( TEST_LIST
        container
        controller
        gem
        more_traits
        pattern
        task
        )

foreach ( target ${TEST_LIST} )
    gtest_folder( ${target} gtest gtest_main pthread )
endforeach ()
