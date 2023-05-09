add_subdirectory(RRT)

add_executable(rrt_exec main.cpp)

target_link_libraries(rrt_exec sfml-window sfml-graphics sfml-system rrt)