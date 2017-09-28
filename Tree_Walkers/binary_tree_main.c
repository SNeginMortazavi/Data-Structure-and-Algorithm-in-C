/*
 * binary_tree_main.c
 *
 *  Created on: Mar 2, 2017

 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "binary_tree.h"
#include "binary_tree_node_queue.h"

/**
 * Postfix depth-first tree walker callback
 */
void toPostfix(
		BinaryTreeNode* node,
		DepthFirstTraversalState tState,
		DepthFirstTraversalData tData);

/**
 * Prefix depth-first tree walker callback
 */
void toPrefix(
		BinaryTreeNode* node,
		DepthFirstTraversalState tState,
		DepthFirstTraversalData tData);

/**
 * Infix depth-first tree walker callback
 */
void toInfix(
		BinaryTreeNode* node,
		DepthFirstTraversalState tState,
		DepthFirstTraversalData tData);

/**
 * Get leaf nodes breadth-first tree walker callback
 */
void getLeafNodes(
	BinaryTreeNode* node,
	BreadthFirstTraversalData tData);

/*
 * Creates the following height 0 expression tree:
 *
 *                   5
 */
BinaryTreeNode* makeExprTree0() {
	// root node
	BinaryTreeNodeData* rootData = malloc(sizeof(BinaryTreeNodeData));
	rootData->strval = "5";
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	return root;
}

/*
 * Creates the following height 1 balanced expression tree:
 *
 *                   -
 *        .----------'----------.
 *        9                     4
 */
BinaryTreeNode* makeExprTree1() {
	// root node
	BinaryTreeNodeData* rootData = malloc(sizeof(BinaryTreeNodeData));
	rootData->strval = "-";
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	// left level 1
	BinaryTreeNodeData* node10Data = malloc(sizeof(BinaryTreeNodeData));
	node10Data->strval = "9";
	BinaryTreeNode* node10 = newBinaryTreeNode(node10Data);

	// right level 1
	BinaryTreeNodeData* node11Data = malloc(sizeof(BinaryTreeNodeData));
	node11Data->strval = "4";
	BinaryTreeNode* node11 = newBinaryTreeNode(node11Data);


	// root to left level 1
	addBinaryTreeNodeAfter(node10, root, leftLink);

	// root to right level 1
	addBinaryTreeNodeAfter(node11, root, rightLink);

	return root;
}

/*
 * Creates the following height 1 right-heavy expression tree:
 *
 *                  sqr
 *        .----------'----------.
 *                              2
 */
BinaryTreeNode* makeExprTree12() {
	// root node
	BinaryTreeNodeData* rootData = malloc(sizeof(BinaryTreeNodeData));
	rootData->strval = "sqr";
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	// right level 1
	BinaryTreeNodeData* node11Data = malloc(sizeof(BinaryTreeNodeData));
	node11Data->strval = "2";
	BinaryTreeNode* node11 = newBinaryTreeNode(node11Data);


	// root to right level 1
	addBinaryTreeNodeAfter(node11, root, rightLink);

	return root;
}

/*
 * Creates the following height 2 right-heavy expression tree:
 *
 *                   -
 *        .----------'----------.
 *        9                    sqr
 *                         .----'----.
 *                                   2
 */
BinaryTreeNode* makeExprTree22() {
	// root node
	BinaryTreeNodeData* rootData = malloc(sizeof(BinaryTreeNodeData));
	rootData->strval = "-";
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	// left level 1
	BinaryTreeNodeData* node10Data = malloc(sizeof(BinaryTreeNodeData));
	node10Data->strval = "9";
	BinaryTreeNode* node10 = newBinaryTreeNode(node10Data);

	// right level 1
	BinaryTreeNodeData* node11Data = malloc(sizeof(BinaryTreeNodeData));
	node11Data->strval = "sqr";
	BinaryTreeNode* node11 = newBinaryTreeNode(node11Data);

	// right right level 2
	BinaryTreeNodeData* node23Data = malloc(sizeof(BinaryTreeNodeData));
	node23Data->strval = "2";
	BinaryTreeNode* node23 = newBinaryTreeNode(node23Data);

	// root to left level 1
	addBinaryTreeNodeAfter(node10, root, leftLink);

	// root to right level 1
	addBinaryTreeNodeAfter(node11, root, rightLink);

	// level2 right right to level 1 right
	addBinaryTreeNodeAfter(node23, node11, rightLink);

	return root;
}

/**
 * Creates the following height 3 expression tree:
 *                    +
 *         .----------'----------.
 *         -                     *
 *    .----'----.           .----'----.
 *    9        sqr          /         7
 *           .--'--.     .--'--.
 *                 2     8     4
 */
BinaryTreeNode* makeExprTree3() {
	// root node
	BinaryTreeNodeData* rootData = malloc(sizeof(BinaryTreeNodeData));
	rootData->strval = "+";
	BinaryTreeNode* root = newBinaryTreeNode(rootData);

	// left level 1
	BinaryTreeNodeData* node10Data = malloc(sizeof(BinaryTreeNodeData));
	node10Data->strval = "-";
	BinaryTreeNode* node10 = newBinaryTreeNode(node10Data);

	// right level 1
	BinaryTreeNodeData* node11Data = malloc(sizeof(BinaryTreeNodeData));
	node11Data->strval = "*";
	BinaryTreeNode* node11 = newBinaryTreeNode(node11Data);

	// left left level 2
	BinaryTreeNodeData* node20Data = malloc(sizeof(BinaryTreeNodeData));
	node20Data->strval = "9";
	BinaryTreeNode* node20 = newBinaryTreeNode(node20Data);

	// right left level 2
	BinaryTreeNodeData* node21Data = malloc(sizeof(BinaryTreeNodeData));
	node21Data->strval = "sqr";
	BinaryTreeNode* node21 = newBinaryTreeNode(node21Data);

	// left right level 22
	BinaryTreeNodeData* node22Data = malloc(sizeof(BinaryTreeNodeData));
	node22Data->strval = "/";
	BinaryTreeNode* node22 = newBinaryTreeNode(node22Data);

	// right right level 2
	BinaryTreeNodeData* node23Data = malloc(sizeof(BinaryTreeNodeData));
	node23Data->strval = "7";
	BinaryTreeNode* node23 = newBinaryTreeNode(node23Data);


	// right left level 3
	BinaryTreeNodeData* node30Data = malloc(sizeof(BinaryTreeNodeData));
	node30Data->strval = "2";
	BinaryTreeNode* node30 = newBinaryTreeNode(node30Data);

	// left right level 3
	BinaryTreeNodeData* node31Data = malloc(sizeof(BinaryTreeNodeData));
	node31Data->strval = "8";
	BinaryTreeNode* node31 = newBinaryTreeNode(node31Data);

	// right right level 3
	BinaryTreeNodeData* node32Data = malloc(sizeof(BinaryTreeNodeData));
	node32Data->strval = "4";
	BinaryTreeNode* node32 = newBinaryTreeNode(node32Data);

	// root to left level 1
	addBinaryTreeNodeAfter(node10, root, leftLink);

	// root to right level 1
	addBinaryTreeNodeAfter(node11, root, rightLink);

	// level2 left left to level 1 left
	addBinaryTreeNodeAfter(node20, node10, leftLink);

	// level2 right left to level 1 left
	addBinaryTreeNodeAfter(node21, node10, rightLink);

	// level2 left right to level 1 right
	addBinaryTreeNodeAfter(node22, node11, leftLink);

	// level2 right right to level 1 right
	addBinaryTreeNodeAfter(node23, node11, rightLink);

	// level3 left left right
	// use right for to make operator prefix for single parameter
	addBinaryTreeNodeAfter(node30, node21, rightLink);

	// level3 left left right
	addBinaryTreeNodeAfter(node31, node22, leftLink);

	// level2 right right to level 1 right
	addBinaryTreeNodeAfter(node32, node22, rightLink);

	return root;
}

/**
 * Test of toInfix() callback to depth-first binary tree walker
 */
static void test_toInfix_Callback(void) {
	BinaryTreeNode* exprTree;
	char strbuf[128];

	exprTree = makeExprTree0();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toInfix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "5");

	exprTree = makeExprTree1();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toInfix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "( 9 - 4 )");

	exprTree = makeExprTree12();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toInfix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "( sqr 2 )");

	exprTree = makeExprTree22();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toInfix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "( 9 - ( sqr 2 ) )");

	exprTree = makeExprTree3();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toInfix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "( ( 9 - ( sqr 2 ) ) + ( ( 8 / 4 ) * 7 ) )");
}

/**
 * Test of toPrefix() depth-first binary tree walker.
 */
static void test_toPrefix_Callback(void) {
	BinaryTreeNode* exprTree;
	char strbuf[128];

	exprTree = makeExprTree0();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toPrefix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "5");

	exprTree = makeExprTree1();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toPrefix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "( - 9 4 )");

	exprTree = makeExprTree12();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toPrefix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "( sqr 2 )");

	exprTree = makeExprTree22();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toPrefix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "( - 9 ( sqr 2 ) )");

	exprTree = makeExprTree3();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toPrefix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "( + ( - 9 ( sqr 2 ) ) ( * ( / 8 4 ) 7 ) )");
}

/**
 * Test of toPostfix() depth-first binary tree walker.
 */
static void test_toPostfix_Callback(void) {
	BinaryTreeNode* exprTree;
	char strbuf[128];

	exprTree = makeExprTree0();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toPostfix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "5");

	exprTree = makeExprTree1();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toPostfix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "9 4 -");

	exprTree = makeExprTree12();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toPostfix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "2 sqr");
//
	exprTree = makeExprTree22();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toPostfix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "9 2 sqr -");
//
	exprTree = makeExprTree3();
	strcpy(strbuf,"");
	binaryTreeTraverseDepthFirst(exprTree, toPostfix, strbuf);
	CU_ASSERT_STRING_EQUAL(strbuf, "9 2 sqr - 8 4 / 7 * +");
}

/**
 * Test of getLeafNodes() breadth-first binary tree walker.
 */
static void test_getLeafNodes_Callback(void) {
	BinaryTreeNode* exprTree;

	exprTree = makeExprTree0();
	BinaryTreeNodeQueue* queue0 = newBinaryTreeNodeQueue();
	binaryTreeTraverseBreadthFirst(exprTree, getLeafNodes, queue0);
	int q0count = getNumElementsBinaryTreeNodeQueue(queue0);
	CU_ASSERT_EQUAL(q0count, 1);
	if (q0count == 1) {
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue0)->data->strval, "5");
	}

	exprTree = makeExprTree1();
	BinaryTreeNodeQueue* queue1 = newBinaryTreeNodeQueue();
	binaryTreeTraverseBreadthFirst(exprTree, getLeafNodes, queue1);
	int q1count = getNumElementsBinaryTreeNodeQueue(queue1);
	CU_ASSERT_EQUAL(q1count, 2);
	if (q1count == 2) {
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue1)->data->strval, "9");
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue1)->data->strval, "4");
	}

	exprTree = makeExprTree12();
	BinaryTreeNodeQueue* queue12 = newBinaryTreeNodeQueue();
	binaryTreeTraverseBreadthFirst(exprTree, getLeafNodes, queue12);
	int q12count = getNumElementsBinaryTreeNodeQueue(queue12);
	CU_ASSERT_EQUAL(q12count, 1);
	if (q12count == 1) {
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue12)->data->strval, "2");
	}

	exprTree = makeExprTree22();
	BinaryTreeNodeQueue* queue22 = newBinaryTreeNodeQueue();
	binaryTreeTraverseBreadthFirst(exprTree, getLeafNodes, queue22);
	int q22count = getNumElementsBinaryTreeNodeQueue(queue22);
	CU_ASSERT_EQUAL(q22count, 2);
	if (q22count == 2) {
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue22)->data->strval, "9");
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue22)->data->strval, "2");
	}

	exprTree = makeExprTree3();
	BinaryTreeNodeQueue* queue3 = newBinaryTreeNodeQueue();
	binaryTreeTraverseBreadthFirst(exprTree, getLeafNodes, queue3);
	int q3count = getNumElementsBinaryTreeNodeQueue(queue3);
	CU_ASSERT_EQUAL(q3count, 5);
	if (q3count == 5) {
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue3)->data->strval, "9");
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue3)->data->strval, "7");
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue3)->data->strval, "2");
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue3)->data->strval, "8");
		CU_ASSERT_STRING_EQUAL(dequeueBinaryTreeNodeQueue(queue3)->data->strval, "4");
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
	CU_pSuite pSuite = CU_add_suite("function_tests", NULL, NULL);

	// add the tests to the suite
	CU_add_test(pSuite, "test_toInfix", test_toInfix_Callback);
	CU_add_test(pSuite, "test_toPrefix", test_toPrefix_Callback);
	CU_add_test(pSuite, "test_toPostFix", test_toPostfix_Callback);
	CU_add_test(pSuite, "test_getLeafNodes", test_getLeafNodes_Callback);

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


