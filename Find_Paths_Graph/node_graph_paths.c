/*
 * node_graph_paths.c
 *
 * This file implements a function to get all the paths between
 * a specified starting and ending node vertex.
 *
 * @since 2017-04-01
 * @author philip gust
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "node_graph_paths.h"
#include "hash_set.h"
#include "array_queue.h"
#include <string.h>

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
		GraphNodeVertex*** paths, int maxPaths) {

	HashSet* visited = createHashSet(); //to record visited node vertices
	ArrayQueue* stack = createArrayQueue(); //to record the node vertices in the current path as a stack.
	int count = 0; //number of path
	count = helper(fromVertex, toVertex, paths, visited, stack, &count);
	return count;
}

/** is the helper function with the following parameters.

 * @param fromVertex the initial node vertex
 * @param toVertex the final node vertex
 * @param paths an array of pointers to null-terminated path arrays
 *   where up to maxPaths paths will be returned (size must be maxPaths+1)
 * @param visited, HashSet to record visited node vertices
 * @param stack, ArrayQueue used as a stack to record the node vertices in the current path
 * @param count, an integer, the total number of paths from fromVertex to toVertex
 * @return the total number of paths available from fromVertex to
 *   toVertex; may be greater than maxPaths
 */

int helper(GraphNodeVertex* fromVertex, GraphNodeVertex* toVertex, GraphNodeVertex*** paths,HashSet* visited, ArrayQueue* stack, int* count){
	addHashSetKey(visited, fromVertex);
	pushArrayQueueData(stack, (QueueData){fromVertex});
		if(fromVertex == toVertex){
			paths[*count] = (GraphNodeVertex**)malloc(sizeof(GraphNodeVertex*) * stack->size + 1);
			int size = stack->size;
			for(int i = 0; i < size; i++){
				paths[*count][i] = stack->data[i].node;
			}
			paths[*count][size] = (GraphNodeVertex*)NULL;
			(*count)++;
		}else{
			for (int iv = 0; iv < fromVertex->edgeCount; iv++) {
				GraphNodeVertex* vertexForEdge = fromVertex->edgeTo[iv].vertex;
				if (!containsHashSetKey(visited, vertexForEdge)) {
					helper(vertexForEdge, toVertex, paths, visited, stack, count);
				}
			}
		}
		QueueData* popedNode = popArrayQueueData(stack, &(QueueData){});
		removeHashSetKey(visited, popedNode->node);
	return *count;
}
