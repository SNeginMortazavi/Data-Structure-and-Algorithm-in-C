/*
 * graph_node_vertex.h
 *
 * The definition of a graph node vertex
 *
 * @since 2017-03-28
 * @author philip Gust
 */

#ifndef GRAPH_NODE_VERTEX_H_
#define GRAPH_NODE_VERTEX_H_

#include <stdbool.h>

/**
 * Graph vertex data field. Defines type of data in a graph vertex.
 */
typedef struct _GraphVertexData {
// something
	const char* strval;  // temporary for testing only
} GraphVertexData;

/**
 * Graph edge data field. Defines type of data in a graph edge
 */
typedef struct {
// something
} GraphEdgeData;

/**
 * Graph node edge points to another GraphNodeVertext
 */
typedef struct {
	GraphEdgeData data;					// the data for the edge
	struct _GraphNodeVertex* vertex;	// pointer to the other vertex
} GraphNodeEdge;

/**
 * Graph node vertex with a data field and a edgeTo field to connected
 * GraphNodeVertex.
 */
typedef struct _GraphNodeVertex {
	GraphVertexData data;
	GraphNodeEdge* edgeTo;
	int edgeCount;
	int edgeCapacity;
} GraphNodeVertex;

/**
 * Compare the data for two binary tree nodes.
 *
 * @param data1 the first node data
 * @param data2 the second node data
 * @return <0 if data1<data2, =0 if data1=data2, >0 if data1>data2
 */
int compareGraphVertexData(GraphVertexData data1, GraphVertexData data2);

/**
 * Determines the cardinality of a graph node. The cardinality is the
 * number of edges from this node vertex to other node vertices
 *
 * @param node a node in the tree
 * @return the cardinality of links from node to other nodes
 */
int graphNodeVertexCardinality(GraphNodeVertex* node);

/**
 * Determines the bi-directional cardinality of a graph node vertex.
 * The bi-directional cardinality is the number of edges from this
 * this node vertex to other node vertices that have edges to this one.
 *
 * @param vertex node in the graph
 * @return the cardinality of edges from this node vertex to other
 * node vertices that have edges to this one.
 */
int graphNodeVertexBidirectionalCardinality(GraphNodeVertex* node);

/**
 * Clear the edges from this node vertex and the corresponding
 * edges from the vertices connected by this node vertex.
 */
void clearGraphNodeEdges(GraphNodeVertex* node);

/**
 * Clear the edges from this node vertex and the corresponding
 * edges from the vertices connected by this node vertex.
 */
void clearGraphNodeBidirectionalEdges(GraphNodeVertex* node);

/**
 * Determines whether graph node vertex is a leaf.
 *
 * @param node a node vertex in the graph
 * @return true if the node vertex is a leaf and false otherwise
 */
bool isGraphNodeVertexLeaf(GraphNodeVertex* node);

/**
 * Determines whether graph node vertex is a bi-directional root.
 * A vertex can only determine whether another vertex to which it
 * has an edge also has an edge to that the vertex.
 *
 * @param node a node vertex in the graph
 * @return true if the node vertex is a root and false otherwise
 */
bool isGraphNodeVertexBidirectionalRoot(GraphNodeVertex* node);

/**
 * Determines whether node vertex has an edge to the specified node vertex
 *
 * @param node the node vertex
 * @param toNode the other node vertex
 * @return true if graph has edge to other node vertex, false otherwise
 */
bool hasEdgeToGraphNodeVertex(GraphNodeVertex *node, GraphNodeVertex* toNode);

/**
 * Returns the edge from the node vertex to the specified node vertex.
 *
 * @param node the node vertex
 * @param toNode the other node vertex
 * @return the edge between the two node vertices
 */
GraphNodeEdge* getEdgeToGraphNodeVertex(GraphNodeVertex *node, GraphNodeVertex* toNode);

/**
 * Determines whether an edge is bi-directional between this node vertex.
 * and the specified node vertex.
 *
 * @param node the node
 * @param toNode the other node
 * @return true if graph is linked, false otherwise
 */
bool hasGraphNodeBindirectionalEdgeTo(
		GraphNodeVertex *node, GraphNodeVertex* toNode);

/**
 * Adds an edge from node vertex to specified node vertex.
 *
 * @param node the node vertex
 * @param toNode the other node
 * @param edgeData the edge data
 * @return edge if edge was added, NULL if edge already exists
 */
GraphNodeEdge* addEdgeToGraphNodeVertex(
		GraphNodeVertex* node, GraphNodeVertex* toNode, GraphEdgeData edgeData);

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
		GraphNodeVertex* node, GraphNodeVertex* toNode, GraphEdgeData edgeData);


/**
 * Removes an edge from node vertex to specified node vertex.
 *
 * @param node the node vertex
 * @param toNode the other node
 * @return true if link was removed, false otherwise
 */
bool removeEdgeToGraphNodeVertex(GraphNodeVertex* node, GraphNodeVertex* toNode);

/**
 * Removes a bidirectional edge between node vertex and specified node vertex.
 *
 * @param node the node vertex
 * @param toNode the other node vertex
 * @return true if edge was removed, false otherwise
 */
bool removeBidirectionalEdgeToGraphNodeVertex(
		GraphNodeVertex* node, GraphNodeVertex* toNode);


#endif /* GRAPH_NODE_VERTEX_H_ */
