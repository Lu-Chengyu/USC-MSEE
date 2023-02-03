cmake_minimum_required( VERSION 2.8 )
project ( EE669HW )

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c99 -march=native -O3" )
set( CMAKE_C_FLAGS "-Wno-implicit-function-declaration " )
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR} )
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib )


############### dependencies ######################

include_directories( 
	${PROJECT_SOURCE_DIR}
)
add_library( HW3 SHARED
    	node_util.c
    	prune_util.c
    	read_util.c
    	slope_util.c
	tsvq_util.c
	tsvqe_util.c
	write_util.c
)


add_executable( tsvq tsvq.c )
target_link_libraries(tsvq
	HW3 m
)

add_executable( tsvqe tsvqe.c )
target_link_libraries(tsvqe
	HW3 m
)


