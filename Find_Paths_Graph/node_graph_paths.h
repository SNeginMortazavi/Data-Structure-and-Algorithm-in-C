/*
 * This file defines a function to get all the paths between
 * a specified starting and ending node vertex.
 *
 * @since 2017-04-01
 * @author philip gust
 */

#ifndef NODE_GRAPH_PATHS_H_
#define NODE_GRAPH_PATHS_H_

#include "node_graph.h"
#include "node_graph_iterator.h"
#include "node_graph_bfs_iterator.h"
#include "node_graph_dfs_iterator.h"
#include "node_graph_paths.h"

/**
 * Return up to maxPaths paths between the initial fromNode and the
 * final toNode in the graph.
 *
 * Adds up to maxPaths paths to paths array passed in, then a null
 * terminator at the end. Each path is allocated as a null-terminated
 * array of GraphNodeVertex pointers in the path. The allocated path
 * arrays must be freed when no longer needed.
 *
 * @param fromVertex the initial node vertex
 * @param toVertex the final node vertex
 * @param paths an array of pointers to null-terminated path arrays
 *   where up to maxPaths paths will be returned (size must be maxPaths+1)
 * @param maxPaths the maximum number of paths to return
 * @return the total number of paths available from fromVertex to
 *   toVertex; may be greater than maxPaths
 */
int getNodeGraphPaths(
		GraphNodeVertex* fromVertex, GraphNodeVertex* toVertex,
		GraphNodeVertex*** paths, int maxPaths);

int helper(GraphNodeVertex* fromVertex, GraphNodeVertex* toVertex,
		GraphNodeVertex*** paths,HashSet* visited, ArrayQueue* stack, int* count);

#endif /* NODE_GRAPH_PATHS_H_ */
