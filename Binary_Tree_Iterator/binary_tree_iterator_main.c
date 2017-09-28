/*
 * binary_tree_main.c
 *
 * This file provides the unit tests for a binary tree iterator.
 *
 * @since 2017-02-15

 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "binary_tree.h"
#include "binary_tree_iterator.h"


/*
 * Creates the following height 0 expression tree:
 *
 *                   5
 */
BinaryTreeNode* makeExprTree0(void) {
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
BinaryTreeNode* makeExprTree1(void) {
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
BinaryTreeNode* makeExprTree12(void) {
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
BinaryTreeNode* makeExprTree22(void) {
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
BinaryTreeNode* makeExprTree3(void) {
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
 * Test of binary tree iterator for empty (NULL) expr tree
 */
static void testBinaryTreeIteratorNULL(void) {
    const char* results[] = {};
    int nodeCount = 0;
    BinaryTreeNode* tree = (BinaryTreeNode*)NULL;

    BinaryTreeIterator* itr = createBinaryTreeIterator(tree);
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
	int count = 0;
	for ( ; hasNextBinaryTreeNode(itr) && count < nodeCount; count++) {
    	BinaryTreeNode* node = getNextBinaryTreeNode(itr);
    	CU_ASSERT_PTR_NOT_NULL(node);
    	if (node != (BinaryTreeNode*)NULL) {
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results[count]);
    	}
    }
    CU_ASSERT_EQUAL(nodeCount, count);
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
    CU_ASSERT_FALSE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

	resetBinaryTreeIterator(itr);
    CU_ASSERT_FALSE(hasNextBinaryTreeNode(itr));  // no nodes
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
}

/**
 * Test of binary tree iterator for 0 height expr tree
 */
static void testBinaryTreeIterator0(void) {
    const char* results[] = {"5"};
    int nodeCount = 1;
    BinaryTreeNode* tree = makeExprTree0();

    BinaryTreeIterator* itr = createBinaryTreeIterator(tree);
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
	int count = 0;
	for ( ; hasNextBinaryTreeNode(itr) && count < nodeCount; count++) {
    	BinaryTreeNode* node = getNextBinaryTreeNode(itr);
    	CU_ASSERT_PTR_NOT_NULL(node);
    	if (node != (BinaryTreeNode*)NULL) {
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results[count]);
    	}
    }
    CU_ASSERT_EQUAL(nodeCount, count);
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
    CU_ASSERT_FALSE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

	resetBinaryTreeIterator(itr);
    CU_ASSERT_TRUE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
}

/**
 * Test of binary tree iterator for 0 height expr tree
 */
static void testBinaryTreeIterator1(void) {
    const char* results[] = {"9", "-", "4"};
    int nodeCount = 3;
    BinaryTreeNode* tree = makeExprTree1();

    BinaryTreeIterator* itr = createBinaryTreeIterator(tree);
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
	int count = 0;
	for ( ; hasNextBinaryTreeNode(itr) && count < nodeCount; count++) {
    	BinaryTreeNode* node = getNextBinaryTreeNode(itr);
    	CU_ASSERT_PTR_NOT_NULL(node);
    	if (node != (BinaryTreeNode*)NULL) {
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results[count]);
    	}
    }
    CU_ASSERT_EQUAL(nodeCount, count);
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
    CU_ASSERT_FALSE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

	resetBinaryTreeIterator(itr);
    CU_ASSERT_TRUE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
}

/**
 * Test of binary tree iterator for 1 height expr tree inbalanced right
 */
static void testBinaryTreeIterator12(void) {
    const char* results[] = {"sqr", "2"};
    int nodeCount = 2;
    BinaryTreeNode* tree = makeExprTree12();

    BinaryTreeIterator* itr = createBinaryTreeIterator(tree);
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
	int count = 0;
	for ( ; hasNextBinaryTreeNode(itr) && count < nodeCount; count++) {
    	BinaryTreeNode* node = getNextBinaryTreeNode(itr);
    	CU_ASSERT_PTR_NOT_NULL(node);
    	if (node != (BinaryTreeNode*)NULL) {
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results[count]);
    	}
    }
    CU_ASSERT_EQUAL(nodeCount, count);
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
    CU_ASSERT_FALSE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

	resetBinaryTreeIterator(itr);
    CU_ASSERT_TRUE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
}

/**
 * Test of binary tree iterator for 2 height expr tree inbalanced right
 */
static void testBinaryTreeIterator22(void) {
    const char* results[] = {"9", "-", "sqr", "2"};
    int nodeCount = 4;
    BinaryTreeNode* tree = makeExprTree22();

    BinaryTreeIterator* itr = createBinaryTreeIterator(tree);
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
	int count = 0;
	for ( ; hasNextBinaryTreeNode(itr) && count < nodeCount; count++) {
    	BinaryTreeNode* node = getNextBinaryTreeNode(itr);
    	CU_ASSERT_PTR_NOT_NULL(node);
    	if (node != (BinaryTreeNode*)NULL) {
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results[count]);
    	}
    }
    CU_ASSERT_EQUAL(nodeCount, count);
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
    CU_ASSERT_FALSE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

	resetBinaryTreeIterator(itr);
    CU_ASSERT_TRUE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
}

/**
 * Test of binary tree iterator for 2 height expr tree
 */
static void testBinaryTreeIterator3(void) {
    const char* results[] = {"9", "-", "sqr", "2", "+", "8", "/", "4", "*", "7"};
    int nodeCount = 10;
    BinaryTreeNode* tree = makeExprTree3();

    BinaryTreeIterator* itr = createBinaryTreeIterator(tree);
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
	int count = 0;
	for ( ; hasNextBinaryTreeNode(itr) && count < nodeCount; count++) {
    	BinaryTreeNode* node = getNextBinaryTreeNode(itr);
    	CU_ASSERT_PTR_NOT_NULL(node);
    	if (node != (BinaryTreeNode*)NULL) {
    		CU_ASSERT_STRING_EQUAL(node->data->strval, results[count]);
    	}
    }
    CU_ASSERT_EQUAL(nodeCount, count);
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorCount(itr));
    CU_ASSERT_FALSE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorAvailable(itr));

	resetBinaryTreeIterator(itr);
    CU_ASSERT_TRUE(hasNextBinaryTreeNode(itr));
	CU_ASSERT_EQUAL(0, getBinaryTreeIteratorCount(itr));
	CU_ASSERT_EQUAL(nodeCount, getBinaryTreeIteratorAvailable(itr));
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
	CU_pSuite pSuite = CU_add_suite("BinaryTreeIterator Tests", NULL, NULL);

	// add the tests to the suite
	CU_add_test(pSuite, "testBinaryTreeIteratorNULL", testBinaryTreeIteratorNULL);
	CU_add_test(pSuite, "testBinaryTreeIterator0", testBinaryTreeIterator0);
	CU_add_test(pSuite, "testBinaryTreeIterator1", testBinaryTreeIterator1);
	CU_add_test(pSuite, "testBinaryTreeIterator12", testBinaryTreeIterator12);
	CU_add_test(pSuite, "testBinaryTreeIterator2", testBinaryTreeIterator22);
	CU_add_test(pSuite, "testBinaryTreeIterator3", testBinaryTreeIterator3);

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


