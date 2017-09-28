/*
 * node_graph.h
 *
 * The definition of a node graph
 *
 * @since 2017-03-28
 * @author philip Gust
 */

#ifndef NODE_GRAPH_H_
#define NODE_GRAPH_H_

#include <stdlib.h>
#include <stdbool.h>
#include "graph_node_vertex.h"

/**
 * Data structure for a NodeGraph
 */
typedef struct _NodeGraph {
	GraphNodeVertex** vertices;
	int vertexCount;
	int vertexCapacity;
} NodeGraph;

/**
 * Create a node graph
 *
 * @return a new NodeGraph
 */
NodeGraph* createNodeGraph();

/**
 * Free a node graph and its vertices and edges
 */
void freeNodeGraph(NodeGraph* graph);

/**
 * Clear the vertices and edges for the node graph.
 */
void clearNodeGraph(NodeGraph* graph);

/**
 * Get the number of vertices in the graph.
 *
 * @param the node graph
 * @return the number of vertices in the graph
 */
int getNodeGraphVertexCount(NodeGraph *graph);

/**
 * Get the size as the number of vertices in the graph
 *
 * @param the node graph
 * @return the number of vertices in the graph
 */
int getNodeGraphSize(NodeGraph *graph);

/**
 * Determines whether the graph contains the node vertex.
 *
 * @param graph the graph
 * @param node the node vertex
 * @return true if the graph contains the specified node vertex
 */
bool hasGraphNodeVertex(NodeGraph* nodeGraph, GraphNodeVertex* node);

/**
 * Determines whether the graph contains a node vertex with
 * the specified data
 *
 * @param graph the graph
 * @param data the data
 * @return true if the graph contains a node with the specified data,
 *   or false otherwise;
 */
bool hasGraphNodeVertexForData(NodeGraph* graph, GraphVertexData data);

/**
* Places pointers to the node vertices with the specified data in the
 * results array. At most maxResults will be returned. The return count
 * is the actual number of matching graph node vertices in the graph.
 *
 * @param graph the graph
 * @param data the data to match
 * @param results an array of null terminated GraphNodeVertex* for the results
 *   (size of array == maxResults+1); null for no results returned
 * @param maxResults the maximum number of results to return
 * @return number of total vertices in the graph with the specific data
 */
int getGraphNodeVerticesForData(
	NodeGraph* graph, GraphVertexData data, GraphNodeVertex** results, int maxResults);

/**
 * Places pointers to the node vertices that have edges to the specified
 * vertex in the results array. At most maxResults will be returned. The
 * return count is the actual number of matching graph node vertices in
 * the graph.
 *
 * @param graph the graph
 * @param vertex the vertex to match
 * @param results an array of null terminated GraphNodeVertex* for the results
 *   (size of array == maxResults+1); null for no results returned
 * @param maxResults the maximum number of results to return
 * @return number of total vertices in the graph with the specific data
 */
int getGraphNodeVerticesIntoVertex(
	NodeGraph* graph, GraphNodeVertex* vertex, GraphNodeVertex** results, int maxResults);

/**
 * Determines whether vertex is a root of the graph. A vertex is a
 * root if it there are no links into the vertex.
 *
 * @param graph the graph
 * @param vertex the vertex to match
 * @return true of graph node has 0 in degrees for the node vertex
 */
bool isGraphNodeVertexRoot(NodeGraph* graph, GraphNodeVertex* vertex);

/**
 * Adds a new graph node vertex with the specified data to the graph.
 *
 * @param graph the graph
 * @param data the data
 * @return a new node vertex that was added to the graph
 */
GraphNodeVertex* addGraphNodeVertexForData(NodeGraph* graph, GraphVertexData data);

/**
 * Removes graph node vertex from the graph.
 *
 * @param graph the graph
 * @param node the vertex
 * @return true if the node was removed, false if the node vertex
 *   was not in the graph.
 */
bool removeGraphNodeVertex(NodeGraph* graph, GraphNodeVertex* node);


#endif /* NODE_GRAPH_H_ */
