/*
 * node_graph_bfs_iterator.c
 *
 * This file provides the implementations of a NodeGraphBFSIterator that
 * iterates over the node vertices of a NodeGraph in breadth-first order.
 *
 * @since 2017-03-30
 * @author philip gust
 */

#include <stdlib.h>
#include <limits.h>
#include "node_graph.h"
#include "node_graph_bfs_iterator.h"
#include "array_queue.h"
#include "hash_set.h"

/**
 * Value returned by getNodeGraphBFSIteratorAvailable if count unavailable
 */
const int NODEGRAPH_BFS_ITR_UNAVAILABLE = INT_MIN;

/**
 * Create and initialize a new NodeGraphBFSIterator
 *
 * @param graph the graph
 * @param startNodeVertex the starting vertex
 * @return an iterator for the specified binary tree
 */
NodeGraphBFSIterator* createNodeGraphBFSIterator(
		NodeGraph* theGraph, GraphNodeVertex* startNodeVertex) {
	NodeGraphBFSIterator* itr = (NodeGraphBFSIterator*)malloc(sizeof(NodeGraphBFSIterator));
	itr->graph = theGraph;
	itr->queue = createArrayQueue();
	itr->count = 0;
	itr->startNodeVertex = startNodeVertex;
	itr->visited = createHashSet();

	// Mark the current node vertex as visited and enqueue it
	addHashSetKey(itr->visited, startNodeVertex);
	enqueueArrayQueueData(itr->queue, (QueueData){startNodeVertex});

 	return itr;
}

/**
 * Freeing iterator storage.
 *
 * @param itr the NodeGraphBFSIterator to delete
 */
void freeNodeGraphBFSIterator(NodeGraphBFSIterator* itr) {
	freeArrayQueue(itr->queue);
	itr->queue = (ArrayQueue*)NULL;
	itr->graph = (NodeGraph*)NULL;
	freeHashSet(itr->visited);
	itr->visited = (HashSet*)NULL;
	itr->count = INT_MIN;
	free(itr);
}

/**
 * Determine whether node vertex has been visited.
 *
 * @param itr the iterator
 * @param node the GraphNodeVertex
 * @return true if node vertex has been visited
 */
static bool isGraphNodeVertexVisited(NodeGraphBFSIterator* itr, GraphNodeVertex* node) {
	return containsHashSetKey(itr->visited, node);
}


/**
 * Mark graph node vertex visited
 *
 * @param itr the iterator
 * @param node the GraphNodeVertex
 */
static void visitGraphNodeVertex(NodeGraphBFSIterator* itr, GraphNodeVertex* node) {
	addHashSetKey(itr->visited, node);
}

/**
 * Gets next node vertex in the graph
 *
 * @param itr the NodeGraphBFSIterator
 * @return the next node or NULL if iterator is at end of tree
 */
GraphNodeVertex* getNextGraphNodeVertexBFS(NodeGraphBFSIterator* itr) {
	GraphNodeVertex* nextNode = (GraphNodeVertex*)NULL;
	if (!isEmptyArrayQueue(itr->queue)) {
		// dequeue vertex from queue to return;
		// NOTE: passing in local QueueData storage for results
		QueueData* data = dequeueArrayQueueData(itr->queue, &(QueueData){});
		nextNode = data->node;
		itr->count++;

        // Get all adjacent vertices of the dequeued vertex nextNode
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
		for (int iv = 0; iv < nextNode->edgeCount; iv++) {
			GraphNodeVertex* vertexForEdge = nextNode->edgeTo[iv].vertex;
			if (!isGraphNodeVertexVisited(itr, vertexForEdge)) {
				visitGraphNodeVertex(itr, vertexForEdge);
				enqueueArrayQueueData(itr->queue, (QueueData){vertexForEdge});
			}
		}
	}
	return nextNode;
}

/**
 * Determines whether there is another node in the binary tree.
 *
 * @param itr the NodeGraphBFSIterator
 * @return true if there is another node, false otherwise
 */
bool hasNextGraphNodeVertexBFS(NodeGraphBFSIterator* itr) {
	return !isEmptyArrayQueue(itr->queue);
}

/**
 * Gets previous node in the binary tree.
 *
 * @param itr the NodeGraphBFSIterator
 * @return the previous node or NULL if iterator is at end of list
 */
GraphNodeVertex* getPrevGraphNodeVertexBFS(NodeGraphBFSIterator* itr) {
	return (GraphNodeVertex*)NULL;
}

/**
 * Determines whether there is a previous node in the binary tree.
 *
 * @param itr the NodeGraphBFSIterator
 * @return true if there is a previous node, false otherwise
 */
bool hasPrevGraphNodeVertexBFS(NodeGraphBFSIterator* itr) {
	return false;
}

/**
 * Resets the binary tree iterator to the root of the tree.
 *
 * @param itr the NodeGraphBFSIterator
 * @return true if successful, false if not supported
 */
bool resetNodeGraphBFSIterator(NodeGraphBFSIterator* itr) {
	clearArrayQueue(itr->queue);
	enqueueArrayQueueData(itr->queue, (QueueData){itr->startNodeVertex});
	clearHashSet(itr->visited);
	return true;
}

/**
 * Returns the number of nodes returned so far.
 *
 * @param itr the NodeGraphBFSIterator
 */
int getNodeGraphBFSIteratorCount(NodeGraphBFSIterator* itr) {
	return itr->count;
}

/**
 * Returns the number of nodes available.
 *
 * @param itr the NodeGraphBFSIterator
 * @return available number of node or UNAVAILABLE if cannot perform operation.
 */
int getNodeGraphBFSIteratorAvailable(NodeGraphBFSIterator* itr)
{
	return NODEGRAPH_BFS_ITR_UNAVAILABLE;
}
