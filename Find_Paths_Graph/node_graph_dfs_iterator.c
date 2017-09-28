/*
 * node_graph_bfs_iterator.c
 *
 * This file provides the implementations of a NodeGraphBFSIterator that
 * iterates over the node vertices of a NodeGraph in breadth-first order.
 *
 * @since 2017-04-01
 * @author philip gust
 */

#include <stdlib.h>
#include <limits.h>
#include "node_graph.h"
#include "node_graph_dfs_iterator.h"
#include "array_queue.h"
#include "hash_set.h"

/**
 * Value returned by getNodeGraphDFSIteratorAvailable if count unavailable
 */
const int NODEGRAPH_DFS_ITR_UNAVAILABLE = INT_MIN;

/**
 * Create and initialize a new NodeGraphDFSIterator
 *
 * @param graph the graph
 * @param startNodeVertex the starting vertex
 * @return an iterator for the specified binary tree
 */
NodeGraphDFSIterator* createNodeGraphDFSIterator(
		NodeGraph* theGraph, GraphNodeVertex* startNodeVertex) {
	NodeGraphDFSIterator* itr = (NodeGraphDFSIterator*)malloc(sizeof(NodeGraphDFSIterator));
	itr->graph = theGraph;
	itr->queue = createArrayQueue();
	itr->count = 0;
	itr->startNodeVertex = startNodeVertex;
	itr->visited = createHashSet();

	// Mark the current node vertex as visited and enqueue it
	addHashSetKey(itr->visited, startNodeVertex);
	pushArrayQueueData(itr->queue, (QueueData){startNodeVertex});

 	return itr;
}

/**
 * Freeing iterator storage.
 *
 * @param itr the NodeGraphDFSIterator to delete
 */
void freeNodeGraphDFSIterator(NodeGraphDFSIterator* itr) {
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
static bool isGraphNodeVertexVisited(NodeGraphDFSIterator* itr, GraphNodeVertex* node) {
	return containsHashSetKey(itr->visited, node);
}


/**
 * Mark graph node vertex visited
 *
 * @param itr the iterator
 * @param node the GraphNodeVertex
 */
static void visitGraphNodeVertex(NodeGraphDFSIterator* itr, GraphNodeVertex* node) {
	addHashSetKey(itr->visited, node);
}

/**
 * Gets next node vertex in the graph
 *
 * @param itr the NodeGraphDFSIterator
 * @return the next node or NULL if iterator is at end of tree
 */
GraphNodeVertex* getNextGraphNodeVertexDFS(NodeGraphDFSIterator* itr) {
	GraphNodeVertex* nextNode = (GraphNodeVertex*)NULL;
	if (!isEmptyArrayQueue(itr->queue)) {
		// dequeue vertex from queue to return;
		// NOTE: passing in local QueueData storage for results
		QueueData* data = popArrayQueueData(itr->queue, &(QueueData){});
		nextNode = data->node;
		itr->count++;

        // Get all adjacent vertices of the dequeued vertex nextNode
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
		for (int iv = 0; iv < nextNode->edgeCount; iv++) {
			GraphNodeVertex* vertexForEdge = nextNode->edgeTo[iv].vertex;
			if (!isGraphNodeVertexVisited(itr, vertexForEdge)) {
				visitGraphNodeVertex(itr, vertexForEdge);
				pushArrayQueueData(itr->queue, (QueueData){vertexForEdge});
			}
		}
	}
	return nextNode;
}

/**
 * Determines whether there is another node in the binary tree.
 *
 * @param itr the NodeGraphDFSIterator
 * @return true if there is another node, false otherwise
 */
bool hasNextGraphNodeVertexDFS(NodeGraphDFSIterator* itr) {
	return !isEmptyArrayQueue(itr->queue);
}

/**
 * Gets previous node in the binary tree.
 *
 * @param itr the NodeGraphDFSIterator
 * @return the previous node or NULL if iterator is at end of list
 */
GraphNodeVertex* getPrevGraphNodeVertexDFS(NodeGraphDFSIterator* itr) {
	return (GraphNodeVertex*)NULL;
}

/**
 * Determines whether there is a previous node in the binary tree.
 *
 * @param itr the NodeGraphDFSIterator
 * @return true if there is a previous node, false otherwise
 */
bool hasPrevGraphNodeVertexDFS(NodeGraphDFSIterator* itr) {
	return false;
}

/**
 * Resets the binary tree iterator to the root of the tree.
 *
 * @param itr the NodeGraphDFSIterator
 * @return true if successful, false if not supported
 */
bool resetNodeGraphDFSIterator(NodeGraphDFSIterator* itr) {
	clearArrayQueue(itr->queue);
	enqueueArrayQueueData(itr->queue, (QueueData){itr->startNodeVertex});
	clearHashSet(itr->visited);
	return true;
}

/**
 * Returns the number of nodes returned so far.
 *
 * @param itr the NodeGraphDFSIterator
 */
int getNodeGraphDFSIteratorCount(NodeGraphDFSIterator* itr) {
	return itr->count;
}

/**
 * Returns the number of nodes available.
 *
 * @param itr the NodeGraphDFSIterator
 * @return available number of node or UNAVAILABLE if cannot perform operation.
 */
int getNodeGraphDFSIteratorAvailable(NodeGraphDFSIterator* itr)
{
	return NODEGRAPH_DFS_ITR_UNAVAILABLE;
}
