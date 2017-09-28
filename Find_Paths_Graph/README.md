Graph can be used to model systems that have pathways from one point to another. In a maze, for example, the vertices represent locations in the maze, and the vertices represent the paths between those locations. The goal is to move from the entrance of the maze to the exit

Some mazes have just one non-looping path between the entrance and the exit, while other mazes have several non-looping paths of varying degrees. The degree of a path is the number of interior vertices, not counting the entrance and exit.

In this assignment, you will implement a function getNodeGraphPath(). The function is given a starting and an ending node vertex. It returns all the paths in the graph that start at the first node vertex, and end at the second one. Here is a descripton of the parameters:

Parameter	    Decriptiption
GraphNodeVertex* fromVertex	The starting node vertex on the path
GraphNodeVertex* toVertex	The ending node vertex on the path
GraphNodeVertex*** paths	A null-terminated array of pointers to null-terminated path arrays. A path array is an ordered list of pointers to node verticies in the path. Path arrays are allocated by the function and added to paths.
int maxPaths	   Up to maxPaths paths will be returned in the paths array. The size of the paths array must be at least maxPaths+1.
The function returns the total number of paths between fromVertex and toVertex. This may be greater than maxPath if there are more paths, or less than maxPath if there are fewer paths.

Starting at the fromVertex, the function pushes the current node vetex onto a ArrayQueue used as a stack, and marks it as visited in a HashSet to prevent loops. Then, it checks whether the current node is the toVertex. If so, it creates a null-terminated node vertex path with the nodes in the stack, and adds it to the paths array. Otherwise, it recursively processes the node vertex of each edge that has not been visited. Finally, it backtracks by popping the node vertex from the path stack, and marking it as not visited so that other paths that include the node vertex can be explored

Here is a summary of the algorithm:

Create a HashSet to record visited node vertices and a ArrayQueue used as a stack to record the node vertices in the current path. Also null terminate the paths array.
Perform the following steps recursively, starting with fromVertex:
Mark the current node as visited and add it to the current path
If the current node vertex is the final node, record the path in the paths array.
Otherwise, repeat these steps for each edge of the current node vertex
Finally, backtrack by removing the current node vertex from the path and marking it as unvisited
Hint: Put the initialization code in the getNodeGraphPath() function and call a helper function to perform the recursive portion of the algorithm. This is a very common design pattern for recursive algorithms

This recursive version of the algorithm would be acceptable as a solution. However, for paths of higher degree, it creates as may function records on the call stack as the degree of the longest path, and may exceed the call stack capacity for large graphs. It would be better to develop an iterative version.

As a challenge, once you have the recursive version working, try making getNodeGraphPath() iteratve by using another ArrayQueue as a stack to manage the edge node vertices, rather than relying on recursion. The iterative version does not require a helper function. The instructor will be happy to offer suggestions, but try it on your own first.

The code that you will use as a starting point is in the "2017SPCS5002SV/prog-assignment-7-template" repository, including a "node_graph_paths.h" header file and a "node_graph_paths.c" file with a stub implementation for the function. The repository also contains a "node_graph_paths_main.c" file with unit tests for the function