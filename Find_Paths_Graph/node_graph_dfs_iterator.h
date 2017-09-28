/*
 * node_graph_bfs_iterator.c
 *
 * This file provides the declarations of a NodeGraphDFSIterator that
 * iterates over the node vertices of a NodeGraph in depth-first order.
 *
 * @since 2017-04-01
 * @author philip gust
 */

#ifndef NODE_GRAPH_DFS_ITERATOR_H_
#define NODE_GRAPH_DFS_ITERATOR_H_

#include "array_queue.h"
#include "node_graph.h"
#include "hash_set.h"

typedef struct {
	NodeGraph* graph;
	ArrayQueue* queue;
	GraphNodeVertex* startNodeVertex;
	HashSet* visited;
	int count;
} NodeGraphDFSIterator;

/**
 * Value returned by getNodeGraphDFSIteratorAvailable if count unavailable
 */
extern const int NODEGRAPH_DFS_ITR_UNAVAILABLE;

/**
 * Create and initialize a new NodeGraphDFSIterator
 *
 * @param graph the graph
 * @param startNodeVertex the starting vertex
 * @return an iterator for the specified binary tree
 */
NodeGraphDFSIterator* createNodeGraphDFSIterator(
		NodeGraph* theGraph, GraphNodeVertex* startNodeVertex);

/**
 * Freeing iterator storage.
 *
 * @param itr the NodeGraphDFSIterator to delete
 */
void freeNodeGraphDFSIterator(NodeGraphDFSIterator* itr);

/**
 * Gets next link node in the binary tree
 *
 * @param itr the NodeGraphDFSIterator
 * @return the next node or NULL if iterator is at end of tree
 */
GraphNodeVertex* getNextGraphNodeVertexDFS(NodeGraphDFSIterator* itr);

/**
 * Determines whether there is another node in the binary tree.
 *
 * @param itr the NodeGraphDFSIterator
 * @return true if there is another node, false otherwise
 */
bool hasNextGraphNodeVertexDFS(NodeGraphDFSIterator* itr);

/**
 * Gets previous node in the binary tree.
 *
 * @param itr the NodeGraphDFSIterator
 * @return the previous node or NULL if iterator is at end of list
 */
GraphNodeVertex* getPrevGraphNodeVertexDFS(NodeGraphDFSIterator* itr);

/**
 * Determines whether there is a previous node in the binary tree.
 *
 * @param itr the NodeGraphDFSIterator
 * @return true if there is a previous node, false otherwise
 */
bool hasPrevGraphNodeVertexDFS(NodeGraphDFSIterator* itr);

/**
 * Resets the binary tree iterator to the root of the tree.
 *
 * @param itr the NodeGraphDFSIterator
 * @return true if successful, false if not supported
 */
bool resetNodeGraphDFSIterator(NodeGraphDFSIterator* itr);

/**
 * Returns the number of nodes returned so far.
 *
 * @param itr the NodeGraphDFSIterator
 */
int getNodeGraphDFSIteratorCount(NodeGraphDFSIterator* itr);

/**
 * Returns the number of nodes available.
 *
 * @param itr the NodeGraphDFSIterator
 * @return available number of node or UNAVAILABLE if cannot perform operation.
 */
int getNodeGraphDFSIteratorAvailable(NodeGraphDFSIterator* itr);

#endif /* NODE_GRAPH_DFS_ITERATOR_H_ */
