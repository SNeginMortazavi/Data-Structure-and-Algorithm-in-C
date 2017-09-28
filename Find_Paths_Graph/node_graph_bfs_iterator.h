/*
 * node_graph_iterator.c
 *
 * This file provides the declarations of a NodeGraphBFSIterator that
 * iterates over the node vertices of a NodeGraph in breadth-first order
 *
 * @since 2017-03-30
 * @author philip gust
 */

#ifndef NODE_GRAPH_BFS_ITERATOR_H_
#define NODE_GRAPH_BFS_ITERATOR_H_

#include "array_queue.h"
#include "node_graph.h"
#include "hash_set.h"

typedef struct {
	NodeGraph* graph;
	ArrayQueue* queue;
	GraphNodeVertex* startNodeVertex;
	HashSet* visited;
	int count;
} NodeGraphBFSIterator;

/**
 * Value returned by getNodeGraphBFSIteratorAvailable if count unavailable
 */
extern const int NODEGRAPH_BFS_ITR_UNAVAILABLE;

/**
 * Create and initialize a new NodeGraphBFSIterator
 *
 * @param graph the graph
 * @param startNodeVertex the starting vertex
 * @return an iterator for the specified binary tree
 */
NodeGraphBFSIterator* createNodeGraphBFSIterator(
		NodeGraph* theGraph, GraphNodeVertex* startNodeVertex);

/**
 * Freeing iterator storage.
 *
 * @param itr the NodeGraphBFSIterator to delete
 */
void freeNodeGraphBFSIterator(NodeGraphBFSIterator* itr);

/**
 * Gets next link node in the binary tree
 *
 * @param itr the NodeGraphBFSIterator
 * @return the next node or NULL if iterator is at end of tree
 */
GraphNodeVertex* getNextGraphNodeVertexBFS(NodeGraphBFSIterator* itr);

/**
 * Determines whether there is another node in the binary tree.
 *
 * @param itr the NodeGraphBFSIterator
 * @return true if there is another node, false otherwise
 */
bool hasNextGraphNodeVertexBFS(NodeGraphBFSIterator* itr);

/**
 * Gets previous node in the binary tree.
 *
 * @param itr the NodeGraphBFSIterator
 * @return the previous node or NULL if iterator is at end of list
 */
GraphNodeVertex* getPrevGraphNodeVertexBFS(NodeGraphBFSIterator* itr);

/**
 * Determines whether there is a previous node in the binary tree.
 *
 * @param itr the NodeGraphBFSIterator
 * @return true if there is a previous node, false otherwise
 */
bool hasPrevGraphNodeVertexBFS(NodeGraphBFSIterator* itr);

/**
 * Resets the binary tree iterator to the root of the tree.
 *
 * @param itr the NodeGraphBFSIterator
 * @return true if successful, false if not supported
 */
bool resetNodeGraphBFSIterator(NodeGraphBFSIterator* itr);

/**
 * Returns the number of nodes returned so far.
 *
 * @param itr the NodeGraphBFSIterator
 */
int getNodeGraphBFSIteratorCount(NodeGraphBFSIterator* itr);

/**
 * Returns the number of nodes available.
 *
 * @param itr the NodeGraphBFSIterator
 * @return available number of node or UNAVAILABLE if cannot perform operation.
 */
int getNodeGraphBFSIteratorAvailable(NodeGraphBFSIterator* itr);

#endif /* NODE_GRAPH_BFS_ITERATOR_H_ */
