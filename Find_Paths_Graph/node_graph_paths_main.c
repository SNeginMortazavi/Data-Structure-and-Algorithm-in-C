/*
 * hash_map_main.c
 *
 * This file provides the unit tests for a HashMap and HashMapIterator.
 *
 * @since 2017-02-15
 * @author philip gust
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "node_graph.h"
#include "node_graph_iterator.h"
#include "node_graph_bfs_iterator.h"
#include "node_graph_dfs_iterator.h"
#include "node_graph_paths.h"

/**
 * Build version of graph1 for use in other tests.
 *            ,--->1--->4
 *           /     | \
 *   5 ---> 0      |  \
 *         / \     |   \
 *        ^   |    |    |
 *        |   v    |    |
 *         \ /     |    |
 *          2 <----'    |
 *          |           v
 *          '---------->3---.
 *                      ^   |
 *                      '---'
 */
static NodeGraph* buildGraph1(void) {
	NodeGraph* graph = createNodeGraph();

	GraphNodeVertex* node0 = addGraphNodeVertexForData(graph, (GraphVertexData){"0"});
	GraphNodeVertex* node1 = addGraphNodeVertexForData(graph, (GraphVertexData){"1"});
	GraphNodeVertex* node2 = addGraphNodeVertexForData(graph, (GraphVertexData){"2"});
	GraphNodeVertex* node3 = addGraphNodeVertexForData(graph, (GraphVertexData){"3"});
	GraphNodeVertex* node4 = addGraphNodeVertexForData(graph, (GraphVertexData){"4"});
	GraphNodeVertex* node5 = addGraphNodeVertexForData(graph, (GraphVertexData){"5"});

	addEdgeToGraphNodeVertex(node5, node0, (GraphEdgeData){});
	addEdgeToGraphNodeVertex(node0, node1, (GraphEdgeData){});
	addEdgeToGraphNodeVertex(node1, node2, (GraphEdgeData){});
	addEdgeToGraphNodeVertex(node1, node4, (GraphEdgeData){});
	addEdgeToGraphNodeVertex(node2, node3, (GraphEdgeData){});
	addBidirectionalEdgeToGraphNodeVertex(node0, node2, (GraphEdgeData){});
	addEdgeToGraphNodeVertex(node3, node3, (GraphEdgeData){});
	addEdgeToGraphNodeVertex(node1, node3, (GraphEdgeData){});

	return graph;
}

/**
 * Tests getNodeGraphPaths().
 */
static void test_getNodeGraphPaths(void) {
	GraphNodeVertex* vertices[2];
	int maxVertices = 1;
	NodeGraph* graph = buildGraph1();

	// choose the node labeled "2" as a stating point
	const char* nodeLabel = "5";
	int vertexCount = getGraphNodeVerticesForData(
				graph, (GraphVertexData){nodeLabel}, vertices, maxVertices);
	CU_ASSERT_EQUAL(vertexCount, 1);
	CU_ASSERT_STRING_EQUAL(vertices[0]->data.strval, nodeLabel);
	if (vertexCount != 1) return;
	GraphNodeVertex* fromVertex = vertices[0];

	nodeLabel = "3";
	vertexCount = getGraphNodeVerticesForData(
				graph, (GraphVertexData){nodeLabel}, vertices, maxVertices);
	CU_ASSERT_EQUAL(vertexCount, 1);
	CU_ASSERT_STRING_EQUAL(vertices[0]->data.strval, nodeLabel);
	if (vertexCount != 1) return;
	GraphNodeVertex* toVertex = vertices[0];

	int maxPaths = 5;
	GraphNodeVertex** paths[] = {NULL,NULL,NULL,NULL,NULL,NULL};
	int nPaths = getNodeGraphPaths(fromVertex, toVertex, paths, maxPaths);
	CU_ASSERT_EQUAL(nPaths, 3);
	if (nPaths == 3) {
		const char* testPath0[] = {"5", "0", "1", "2", "3"};
		const char* testPath1[] = {"5", "0", "1", "3"};
		const char* testPath2[] = {"5", "0", "2", "3"};
		const char** testPaths[] = {testPath0, testPath1, testPath2};

		for (int i = 0; i < nPaths; i++) {
			CU_ASSERT_PTR_NOT_NULL(paths[i]);
			GraphNodeVertex** path = paths[i];
			if (path != (GraphNodeVertex**)NULL) {
				for (int j = 0; path[j] != NULL; j++) {
					CU_ASSERT_STRING_EQUAL(testPaths[i][j],
							               path[j]->data.strval);
				}
			}
		}
		CU_ASSERT_PTR_NULL(paths[nPaths]);
	}
}


/**
 * Test all the functions for this application.
 *
 * @return test error code
 */
static int test_all(void) {
	// initialize the CUnit test registry -- only once per application
	CU_initialize_registry();

	// add a suite to the registry with no init or cleanup
	CU_pSuite pSuite = CU_add_suite("NodeGraph Tests", NULL, NULL);

	// add the tests to the suite
	CU_add_test(pSuite, "test_getNodeGraphPaths", test_getNodeGraphPaths);

	// run all test suites using the basic interface
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	// display information on failures that occurred
	CU_basic_show_failures(CU_get_failure_list());

	// Clean up registry and return status
	CU_cleanup_registry();
	return CU_get_error();
}

/**
 * Main program to invoke test functions
 *
 * @return the exit status of the program
 */
int main(void) {

	// test all the functions
	CU_ErrorCode code = test_all();

	return (code == CUE_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}


