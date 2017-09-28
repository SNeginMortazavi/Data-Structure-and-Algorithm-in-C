/*
 * graph_node_vertex.c
 *
 * The implementation of a graph node vertex
 *
 * @since 2017-03-28
 * @author philip Gust
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>
#include "graph_node_vertex_impl.h"

#ifndef INITIAL_EDGE_CAPACITY
#define INITIAL_EDGE_CAPACITY 4
#endif

/**
 * Compare the data for two graph nodes.
 *
 * @param data1 the first node data
 * @param data2 the second node data
 * @return <0 if data1<data2, =0 if data1=data2, >0 if data1>data2
 */
int compareGraphVertexData(GraphVertexData data1, GraphVertexData data2)
{
	return strcmp(data1.strval, data2.strval);
}


/**
 * Initialize contents of graph node vertex.
 *
 * @param node the graph node vertex
 * @param data the graph data
 */
static void initGraphNodeVertex(GraphNodeVertex* node, GraphVertexData data) {
	node->data = data;
	node->edgeCount = 0;
	node->edgeCapacity = INITIAL_EDGE_CAPACITY;
	node->edgeTo =
		(GraphNodeEdge*)malloc(INITIAL_EDGE_CAPACITY * sizeof(GraphNodeEdge));
}

/**
 * Create a new GraphNodeVertex with specified data.
 *
 * @param data the value of the data field
 * @return a new GraphNode
 */
GraphNodeVertex* newGraphNodeVertex(GraphVertexData data) {
	GraphNodeVertex* node = (GraphNodeVertex*)malloc(sizeof(GraphNodeVertex));
	initGraphNodeVertex(node, data);
	return node;
}

/**
 * Delete a graphNode and ensure edges bi-directionally in and out are
 * removed. Data must be freed by caller.
 *
 * @param node the node to free
 */
void deleteGraphNodeVertex(GraphNodeVertex* node) {
	// remove edges
	clearGraphNodeEdges(node);
	free(node->edgeTo);
	node->edgeTo = (GraphNodeEdge*)NULL;

	free(node);
}

/**
 * Clear the edges from this node vertex and the corresponding
 * edges from the vertices connected by this node vertex.
 */
void clearGraphNodeEdges(GraphNodeVertex* node) {
	node->edgeCount = 0;
}

/**
 * Clear the edges from this node vertex and the corresponding
 * edges from the vertices connected by this node vertex.
 */
void clearGraphNodeBidirectionalEdges(GraphNodeVertex* node) {
	// remove bidirectional links from other nodes
	for (int i = 0; i < node->edgeCount; i++) {
		removeEdgeToGraphNodeVertex(node->edgeTo[i].vertex, node);
	}
	node->edgeCount = 0;
}

/**
 * Determines the cardinality of a graph node vertex. The cardinality
 * is the number of edges from this node vertex to other node verticies
 *
 * @param node a node vertex in the graph
 * @return the cardinality of edges from node to other nodes
 */
int graphNodeVertexCardinality(GraphNodeVertex* node) {
	return node->edgeCount;
}

/**
 * Determines the bi-directional cardinality of a graph node vertex.
 * The bi-directional cardinality is the number of edges from this
 * this node vertex to other node verticies that have edges to this one.
 *
 * @param vertex node in the graph
 * @return the cardinality of edges from this node vertex to other
 * node verticies that have edges to this one.
 */
int graphNodeVertexBidirectionalCardinality(GraphNodeVertex* node) {
	// remove bidirectional links from other nodes
	int count = 0;
	for (int i = 0; i < node->edgeCount; i++) {
		count += hasEdgeToGraphNodeVertex(node->edgeTo[i].vertex, node);
	}
	return count;
}

/**
 * Determines whether graph node vertex is a leaf.
 *
 * @param node a node vertex in the graph
 * @return true if the node vertex is a leaf and false otherwise
 */
bool isGraphNodeVertexLeaf(GraphNodeVertex* node) {
	return graphNodeVertexCardinality(node) == 0;
}

/**
 * Determines whether graph node vertex is a bi-directional root.
 * A vertex can only determine whether another vertex to which it
 * has an edge also has an edge to that the vertex.
 *
 * @param node a node vertex in the graph
 * @return true if the node vertex is a root and false otherwise
 */
bool isGraphNodeVertexBidirectionalRoot(GraphNodeVertex* node) {
	return graphNodeVertexBidirectionalCardinality(node) == 0;
}

/**
 * Determines whether node vertex has an edge to the specified node vertex
 *
 * @param node the node vertex
 * @param toNode the other node vertex
 * @return true if graph has edge to other node vertex, false otherwise
 */
bool hasEdgeToGraphNodeVertex(GraphNodeVertex *node, GraphNodeVertex* toNode) {
	for (int i = 0; i < node->edgeCount; i++) {
		if (node->edgeTo[i].vertex == toNode) {
			return true;
		}
	}
	return false;
}

/**
 * Returns the edge from the node vertex to the specified node vertex.
 *
 * @param node the node vertex
 * @param toNode the other node vertex
 * @return the edge between the two node vertices
 */
GraphNodeEdge* getEdgeToGraphNodeVertex(GraphNodeVertex *node, GraphNodeVertex* toNode) {
	for (int i = 0; i < node->edgeCount; i++) {
		if (node->edgeTo[i].vertex == toNode) {
			return &(node->edgeTo[i]);
		}
	}
	return (GraphNodeEdge*)NULL;
}


/**
 * Determines whether an edge is bi-directional between this node vertex
 * and the specified node vertex.
 *
 * @param node the node
 * @param toNode the other node
 * @return true if graph is linked, false otherwise
 */
bool hasBindirectionalEdgeToGraphNodeVertex(GraphNodeVertex *node, GraphNodeVertex* toNode) {
	for (int i = 0; i < node->edgeCount; i++) {
		if (   node->edgeTo[i].vertex == toNode
			&& hasEdgeToGraphNodeVertex(toNode, node)) {
			return true;
		}
	}
	return false;
}

/**
 * Adds an edge from node vertex to specified node vertex.
 *
 * @param node the node vertex
 * @param toNode the other node
 * @param edgeData the edge data
 * @return edge if edge was added, NULL if edge already exists
 */
GraphNodeEdge* addEdgeToGraphNodeVertex(
		GraphNodeVertex* node, GraphNodeVertex* toNode, GraphEdgeData edgeData) {
	for (int i = 0; i < node->edgeCount; i++) {
		if (node->edgeTo[i].vertex == toNode) {
			return (GraphNodeEdge*)NULL;
		}
	}
	// grow linkTo array if necessary
	if (node->edgeCount >= node->edgeCapacity) {
		node->edgeCapacity *= 2;
		node->edgeTo =
			(GraphNodeEdge*)realloc(node->edgeTo, node->edgeCapacity * sizeof(GraphNodeEdge));
	}
	// add edge to end of edge array
	node->edgeTo[node->edgeCount].vertex = toNode;
	node->edgeTo[node->edgeCount].data = edgeData;
	node->edgeCount++;

	return &node->edgeTo[node->edgeCount-1];
}

/**
 * Adds an edge from node vertex to specified node vertex, and one
 * from the specified node vertex to back to node vertex.
 *
 * @param node the node vertex
 * @param toNode the other node
 * @param edgeData the edge data
 * @return edge if edge was added, NULL if edge already exists
 */
GraphNodeEdge* addBidirectionalEdgeToGraphNodeVertex(
		GraphNodeVertex* node, GraphNodeVertex* toNode, GraphEdgeData edgeData) {
	GraphNodeEdge* edge = addEdgeToGraphNodeVertex(node, toNode, edgeData);
	if (edge != (GraphNodeEdge*)NULL) {
		GraphNodeEdge* toEdge = addEdgeToGraphNodeVertex(toNode, node, edgeData);
		if (toEdge == (GraphNodeEdge*)NULL) {
			// remove first edge if cannot add second one.
			removeEdgeToGraphNodeVertex(node, toNode);
			edge = (GraphNodeEdge*)NULL;
		}
	}
	return edge;
}

/**
 * Removes an edge from node vertex to specified node vertex.
 *
 * @param node the node vertex
 * @param toNode the other node
 * @return true if link was removed, false otherwise
 */
bool removeEdgeToGraphNodeVertex(GraphNodeVertex* node, GraphNodeVertex* toNode) {

	int i = 0;
	for ( ; i < node->edgeCount; i++) {
		if (node->edgeTo[i].vertex == toNode) {
			break;
		}
	}
	// not found
	if (i >= node->edgeCount) {
		return false;
	}

	for (node->edgeCount--; i < node->edgeCount; i++) {
		node->edgeTo[i] = node->edgeTo[i+1];
	}
	return true;

}

/**
 * Removes a bidirectional edge between node vertex and specified node vertex.
 *
 * @param node the node vertex
 * @param toNode the other node vertex
 * @return true if edge was removed, false otherwise
 */
bool removeBidirectionalEdgeToGraphNodeVertex(GraphNodeVertex* node, GraphNodeVertex* toNode) {
	return    removeEdgeToGraphNodeVertex(node, toNode)
		   || removeEdgeToGraphNodeVertex(toNode, node);
}



