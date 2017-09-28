/*
 * graph_node_vertex.h
 *
 * The implementation-specific definition of a graph node vertex
 *
 * @since 2017-03-28
 * @author philip Gust
 */

#ifndef GRAPH_NODE_VERTEX_IMPL_H_
#define GRAPH_NODE_VERTEX_IMPL_H_

#include <stdbool.h>
#include "graph_node_vertex.h"

/**
 * Create a new GraphNode with specified data
 *
 * @param data the value of the data field
 * @return a new GraphNode
 */
GraphNodeVertex* newGraphNodeVertex(GraphVertexData data);

/**
 * Delete a graphNode and ensure edges bi-directionally in and out are
 * removed. Data must be freed by caller.
 *
 * @param node the node to free
 */
void deleteGraphNodeVertex(GraphNodeVertex* node);


#endif /* GRAPH_NODE_VERTEX_IMPL_H_ */
