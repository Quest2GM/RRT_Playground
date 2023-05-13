add_subdirectory(RRT)
add_subdirectory(RRTStar)
add_subdirectory(InformedRRTStar)
add_subdirectory(AnytimeRRT)

add_executable(rrt_exec main.cpp)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries(rrt_exec sfml-window
                               sfml-graphics 
                               sfml-system 
                               Eigen3::Eigen 
                               rrt
                               rrtstar
                               infrrtstar
                               anytimerrt)