/*
 * node_graph_iterator.c
 *
 * This file provides the declarations of a NodeGraphIterator that
 * iterates over the node vertices of a NodeGraph
 *
 * @since 2017-03-30
 * @author philip gust
 */

#ifndef NODE_GRAPH_ITERATOR_H_
#define NODE_GRAPH_ITERATOR_H_

#include <stdbool.h>

typedef struct {
	NodeGraph* graph;
	int count;
} NodeGraphIterator;

/**
 * Value returned by getNodeGraphIteratorAvailable if count unavailable
 */
extern const int NODEGRAPH_ITR_UNAVAILABLE;

/**
 * Create and initialize a new NodeGraphIterator
 *
 * @param graph the graph
 * @param startNodeVertex the starting vertex
 * @return an iterator for the specified binary tree
 */
NodeGraphIterator* createNodeGraphIterator(NodeGraph* theGraph);

/**
 * Freeing iterator storage.
 *
 * @param itr the NodeGraphIterator to delete
 */
void freeNodeGraphIterator(NodeGraphIterator* itr);

/**
 * Gets next link node in the binary tree
 *
 * @param itr the NodeGraphIterator
 * @return the next node or NULL if iterator is at end of tree
 */
GraphNodeVertex* getNextGraphNodeVertex(NodeGraphIterator* itr);

/**
 * Determines whether there is another node in the binary tree.
 *
 * @param itr the NodeGraphIterator
 * @return true if there is another node, false otherwise
 */
bool hasNextGraphNodeVertex(NodeGraphIterator* itr);

/**
 * Gets previous node in the binary tree.
 *
 * @param itr the NodeGraphIterator
 * @return the previous node or NULL if iterator is at end of list
 */
GraphNodeVertex* getPrevGraphNodeVertex(NodeGraphIterator* itr);

/**
 * Determines whether there is a previous node in the binary tree.
 *
 * @param itr the NodeGraphIterator
 * @return true if there is a previous node, false otherwise
 */
bool hasPrevGraphNodeVertex(NodeGraphIterator* itr);

/**
 * Resets the binary tree iterator to the root of the tree.
 *
 * @param itr the NodeGraphIterator
 * @return true if successful, false if not supported
 */
bool resetNodeGraphIterator(NodeGraphIterator* itr);

/**
 * Returns the number of nodes returned so far.
 *
 * @param itr the NodeGraphIterator
 */
int getNodeGraphIteratorCount(NodeGraphIterator* itr);

/**
 * Returns the number of nodes available.
 *
 * @param itr the NodeGraphIterator
 * @return available number of node or UNAVAILABLE if cannot perform operation.
 */
int getNodeGraphIteratorAvailable(NodeGraphIterator* itr);


#endif /* NODE_GRAPH_ITERATOR_H_ */
