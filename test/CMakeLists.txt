set( FOLDER_LIST
        container
        controller
        gem
        more_traits
        task
        )

foreach ( folder ${FOLDER_LIST} )
    gtest_folder( ${folder} main.cpp gtest gtest_main )
endforeach ()
