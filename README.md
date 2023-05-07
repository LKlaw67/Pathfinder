# Pathfinder
This is an A* search algorithm programmed in C++. The algorithm navigates within an obstacle filled 20 x 20 grid from a start position to an end position.

## Process
I was inspired after watching a YouTube video by The Action Lab about a liquid completing a maze.

https://www.youtube.com/watch?v=ztOk-v8epAg

My first program had the following properties:
* A node starts at the end point.
* The node checks for surrounding valid points.
* The node will spread in all valid directions.
* Each node has a "concentration" that increases from the end point and spreads.
* Once a node reaches the start point, a path is traced back following the highest concentrations.

After testing this prototype, the algorithm performed very slowly when the path length increased due to obstacles. The nodes would spread in every direction instead of towards the destination, resulting in an inefficient algorithm.

After researching pathfinding algorithms I found my algorithm was most similar to Dijkstra's algorithm. This algorithm suffered the same issues as my algorithm, but could be solved by using A*, an improved version of Dijkstra's algorithm.

The new programs had the following changes:
* Each node checks the distance between the node position and the destination. The nodes are ordered from closest to farthest.
* The closest nodes will spread in all valid directions before farther nodes.

## Functions
* The numbers printed onto the console show the time taken per frame in miliseconds.
* Left click creates obstacles.
* Right click removes obstacles.
