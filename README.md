# RRT Playground

## Installation
- [SFML](https://www.sfml-dev.org/)
- [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)
- [CMake](https://cmake.org/): Version > 3.10
```
$ sudo apt-get install libsfml-dev libeigen3-dev
```

## Results
### RRT
At each iteration, a point is sampled within a given search radius, and then is connected to the closest node in the tree. The process terminates when the goal is found. RRTs are probabilistically complete, but not optimal.
![RRT](images/rrt_demo.gif)

### RRT*
At each iteration, a point is sampled within a given search radius, and then is connected to the node with the minimum cost to come from the start node. The other nodes around this new node are then rewired if the new node improves their existing cost to come. The process terminates after a set number of iterations or a goal distance threshold has been reached. RRT* is asymptotically optimal.
![RRT*](images/rrt_star_demo_v2.gif)

### Anytime RRT
The RRT algorithm is performed until a goal has been found. Once found, the RRT* algorithm is performed until a set number of iterations or a goal distance threshold has been reached. Anytime RRT is asymptotically optimal.
![AnytimeRRT](images/anytime_rrt_demo_v2.gif)

### Informed RRT*
The RRT* algorithm is performed until a goal has been found. Once found, the search area is reduced to an ellipse, with foci as the start and goal nodes, and the major and minor axes derived from the minimum and maximum length paths. The process terminates after a set number of iterations or a goal distance threshold has been reached. Informed RRT* is asymptotically optimal, and converges faster than RRT* and Anytime RRT.
![InformedRRT](images/informed_rrt_demo.gif)

## References
[[1]](http://msl.cs.uiuc.edu/~lavalle/papers/Lav98c.pdf) Steven M. LaValle, "Rapidly-exploring random trees: A new tool for path planning," Technical Report. Computer Science Department, Iowa State University (TR 98–11).

[[2]](https://arxiv.org/pdf/1005.0416.pdf) S. Karaman and E. Frazzoli, "Incremental Sampling-based Algorithms for Optimal Motion Planning," arXiv:1005.0416, May. 2010.

[[3]](https://ieeexplore.ieee.org/document/6942976?arnumber=6942976) J. D. Gammell, S. S. Srinivasa, and T. D. Barfoot, “Informed RRT*: Optimal sampling-based path planning focused via direct sampling of an admissible ellipsoidal heuristic,” in 2014 IEEE/RSJ International Conference on Intelligent Robots and Systems, 2014, pp. 2997–3004.