/*
 * node_graph.h
 *
 * The implementation of a node graph
 *
 * @since 2017-03-28
 * @author philip Gust
 */

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "node_graph.h"
#include "graph_node_vertex_impl.h"

#ifndef INITIAL_NODE_GRAPH_CAPACITY
#define INITIAL_NODE_GRAPH_CAPACITY 16
#endif

/**
 * Create a node graph
 *
 * @return a new NodeGraph
 */
NodeGraph* createNodeGraph() {
	NodeGraph* graph = (NodeGraph*)malloc(sizeof(NodeGraph));
	graph->vertexCount = 0;
	graph->vertexCapacity = INITIAL_NODE_GRAPH_CAPACITY;
	graph->vertices = (GraphNodeVertex**)malloc(graph->vertexCapacity * sizeof(GraphNodeVertex*));
	return graph;
}

/**
 * Free a node graph and its vertices and edges
 *
 * @param graph the graph to free
 */
void freeNodeGraph(NodeGraph* graph) {
	clearNodeGraph(graph);
	free(graph->vertices);
	graph->vertices = (GraphNodeVertex**)NULL;
	graph->vertexCount = INT_MIN;
	graph->vertexCapacity= INT_MIN;
	free(graph);
}

/**
 * Clear the vertices and edges for the node graph.
 *
 * @param graph the graph to free
 */
void clearNodeGraph(NodeGraph* graph) {
	for (int i = 0; i < graph->vertexCount; i++) {
		deleteGraphNodeVertex(graph->vertices[i]);
		graph->vertices[i] = (GraphNodeVertex*)NULL;
	}
	graph->vertexCount = 0;
}

/**
 * Get the number of vertices in the graph.
 *
 * @param the node graph
 * @return the number of vertices in the graph
 */
int getNodeGraphVertexCount(NodeGraph *graph) {
	return graph->vertexCount;
}

/**
 * Get the size as the number of vertices in the graph.
 *
 * @param the node graph
 * @return the size as the number of vertices in the graph
 */
int getNodeGraphSize(NodeGraph *graph) {
	return getNodeGraphVertexCount(graph);
}

/**
 * Finds the graph node vertex in the graph
 *
 * @param graph the graph
 * @param node the node vertex
 * @return index of node vertex in vertex array or -1 if not found
 */
static int findGraphNodeVertex(NodeGraph* graph, GraphNodeVertex* node) {
	for (int ig = 0; ig < graph->vertexCount; ig++) {
		if (graph->vertices[ig] == node) {
			return ig;
		}
	}
	return -1; // if not found
}

/**
 * Determines whether the graph contains the node vertex.
 *
 * @param graph the graph
 * @param node the node vertex
 * @return true if the graph contains the specified node vertex
 */
bool hasGraphNodeVertex(NodeGraph* graph, GraphNodeVertex* node) {
	return (findGraphNodeVertex(graph, node) != -1);
}

/**
 * Determines whether the graph contains a node vertex with
 * the specified data
 *
 * @param graph the graph
 * @param data the data
 * @return true if the graph contains a node with the specified data,
 *   or false otherwise;
 */
bool hasGraphNodeVertexForData(NodeGraph* graph, GraphVertexData data) {
	for (int i = 0; i < graph->vertexCount; i++) {
		if (compareGraphVertexData(graph->vertices[i]->data, data) == 0) {
			return true;
		}
	}
	return false;
}

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
	NodeGraph* graph, GraphVertexData data, GraphNodeVertex** results, int maxResults) {
	int nResults = 0;
	results[0] = (GraphNodeVertex*)NULL;
	for (int i = 0; i < graph->vertexCount; i++) {
		if (compareGraphVertexData(graph->vertices[i]->data, data) == 0) {
			if (results != (GraphNodeVertex**)NULL && nResults < maxResults) {
				results[nResults] = graph->vertices[i];
				results[nResults+1] = (GraphNodeVertex*)NULL;
			}
			nResults++;
		}
	}
	return nResults;
}

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
	NodeGraph* graph, GraphNodeVertex* vertex, GraphNodeVertex** results, int maxResults) {
	int nResults = 0;
	if (results != (GraphNodeVertex**)NULL) {
		results[0] = (GraphNodeVertex*)NULL;
	}
	for (int ig = 0; ig < graph->vertexCount; ig++) {
		// next vertex from vertex list
		GraphNodeVertex* vtx = graph->vertices[ig];
		// examine edges of vtx vertex from vertex list
		for (int iv = 0; iv < vtx->edgeCount; iv++) {
			if (vtx->edgeTo[iv].vertex == vertex) {
				if (nResults < maxResults && results != (GraphNodeVertex**)NULL) {
					results[nResults] = vtx;
					results[nResults+1] = (GraphNodeVertex*)NULL;
				}
				nResults++;
			}
		}
	}
	return nResults;

}

/**
 * Determines whether vertex is a root of the graph. A vertex is a
 * root if it there are no links into the vertex.
 *
 * @param graph the graph
 * @param vertex the vertex to match
 * @return true of graph node has 0 in degrees for the node vertex
 */
bool isGraphNodeVertexRoot(NodeGraph* graph, GraphNodeVertex* vertex) {
	return (getGraphNodeVerticesIntoVertex(graph, vertex, (GraphNodeVertex**)NULL, 0) == 0);
}


/**
 * Adds a new graph node vertex with the specified data to the graph.
 *
 * @param graph the graph
 * @param data the data
 * @return a new node vertex that was added to the graph
 */
GraphNodeVertex* addGraphNodeVertexForData(NodeGraph* graph, GraphVertexData data) {
	if (graph->vertexCount >= graph->vertexCapacity) {
		// reallocate vertex array
		graph->vertexCapacity += graph->vertexCapacity;
		graph->vertices =
			(GraphNodeVertex**)realloc(graph->vertices, graph->vertexCapacity * sizeof(GraphNodeVertex*));
	}
	GraphNodeVertex* vertex = newGraphNodeVertex(data);
	graph->vertices[graph->vertexCount++] = vertex;
	return vertex;
}


/**
 * Removes graph node vertex and corresponding incoming and outgoing
 * edges from the graph.
 *
 * @param graph the graph
 * @param node the vertex
 * @return true if the node was removed, false if the node vertex
 *   was not in the graph.
 */
bool removeGraphNodeVertex(NodeGraph* graph, GraphNodeVertex* node) {
	int foundAt = -1;  // index where node vertex was found
	for (int ig = 0; ig < graph->vertexCount; ig++) {
		GraphNodeVertex* vtx = graph->vertices[ig];
		if (vtx == node) {
			// remove from list
			foundAt = ig;
		} else {
			// remove edge from vtx to node
			removeEdgeToGraphNodeVertex(vtx, node);
			if (foundAt >= 0) {
				// if past found node vertex, move others down
				graph->vertices[ig-1] = graph->vertices[ig];
			}
		}
	}

	if (foundAt != -1) {
		graph->vertexCount--;

		// free the node vertex if found
		deleteGraphNodeVertex(node);
		return true;
	}
	return false;
}
