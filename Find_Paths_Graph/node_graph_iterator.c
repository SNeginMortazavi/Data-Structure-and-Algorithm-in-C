/*
 * node_graph_iterator.c
 *
 * This file provides the implementations of a NodeGraphIterator that
 * iterates over the node vertices of a NodeGraph.
 *
 * @since 2017-03-30
 * @author philip gust
 */

#include <stdlib.h>
#include <limits.h>
#include "node_graph.h"
#include "node_graph_iterator.h"

/**
 * Value returned by getNodeGraphIteratorAvailable if count unavailable
 */
const int NODEGRAPH_ITR_UNAVAILABLE = INT_MIN;

/**
 * Create and initialize a new NodeGraphIterator
 *
 * @param graph the graph
 * @param startNodeVertex the starting vertex
 * @return an iterator for the specified binary tree
 */
NodeGraphIterator* createNodeGraphIterator(NodeGraph* theGraph) {
	NodeGraphIterator* itr = (NodeGraphIterator*)malloc(sizeof(NodeGraphIterator));
	itr->graph = theGraph;
	itr->count = 0;
	return itr;
}

/**
 * Freeing iterator storage.
 *
 * @param itr the NodeGraphIterator to delete
 */
void freeNodeGraphIterator(NodeGraphIterator* itr) {
	itr->graph = (NodeGraph*)NULL;
	itr->count = INT_MIN;
	free(itr);
}

/**
 * Gets next link node in the binary tree
 *
 * @param itr the NodeGraphIterator
 * @return the next node or NULL if iterator is at end of tree
 */
GraphNodeVertex* getNextGraphNodeVertex(NodeGraphIterator* itr) {
	if (hasNextGraphNodeVertex(itr)) {
		return itr->graph->vertices[itr->count++];
	}
	return (GraphNodeVertex*)NULL;
}

/**
 * Determines whether there is another node in the binary tree.
 *
 * @param itr the NodeGraphIterator
 * @return true if there is another node, false otherwise
 */
bool hasNextGraphNodeVertex(NodeGraphIterator* itr) {
	return itr->count < getNodeGraphSize(itr->graph);
}

/**
 * Gets previous node in the binary tree.
 *
 * @param itr the NodeGraphIterator
 * @return the previous node or NULL if iterator is at end of list
 */
GraphNodeVertex* getPrevGraphNodeVertex(NodeGraphIterator* itr) {
	if (hasPrevGraphNodeVertex(itr)) {
		return itr->graph->vertices[--itr->count];
	}
	return (GraphNodeVertex*)NULL;
}

/**
 * Determines whether there is a previous node in the binary tree.
 *
 * @param itr the NodeGraphIterator
 * @return true if there is a previous node, false otherwise
 */
bool hasPrevGraphNodeVertex(NodeGraphIterator* itr) {
	return itr->count > 0;
}

/**
 * Resets the binary tree iterator to the root of the tree.
 *
 * @param itr the NodeGraphIterator
 * @return true if successful, false if not supported
 */
bool resetNodeGraphIterator(NodeGraphIterator* itr) {
	itr->count = 0;
	return true;
}

/**
 * Returns the number of nodes returned so far.
 *
 * @param itr the NodeGraphIterator
 */
int getNodeGraphIteratorCount(NodeGraphIterator* itr) {
	return itr->count;
}

/**
 * Returns the number of nodes available.
 *
 * @param itr the NodeGraphIterator
 * @return available number of node or NODEGRAPH_BFS_UNAVAILABLE
 *   if cannot perform operation.
 */
int getNodeGraphIteratorAvailable(NodeGraphIterator* itr) {
	return getNodeGraphSize(itr->graph) - itr->count;
}

