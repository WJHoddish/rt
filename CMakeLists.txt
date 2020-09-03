cmake_minimum_required(VERSION 3.10.0)
project( rt VERSION 0.1.0 )

include(CTest)
enable_testing()

# switch on optimization
set ( optimize true )

if( optimize MATCHES true )
    set( cpp_version "-std=c++11" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cpp_version} -I /usr/local/include -Wall -O2 -pthread -fopenmp")
    message( "Jiaheng: currently using " ${cpp_version} )
else()
    # do nothing
    message( "Jiaheng: no optimization used" )
endif()


# file( GLOB_RECURSE DIR_SRC src/*.cpp src/*.h )

aux_source_directory( . DIR_MAIN )
add_executable( rt ${DIR_MAIN} )
target_link_libraries( rt gtest gtest_main )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)