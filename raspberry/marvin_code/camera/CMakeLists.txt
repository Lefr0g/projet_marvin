cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( testCamera camera.cpp socket_tools.cpp ft_itoa.cpp)
target_link_libraries( testCamera ${OpenCV_LIBS} )
