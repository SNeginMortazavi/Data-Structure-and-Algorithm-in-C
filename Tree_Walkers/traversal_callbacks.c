/*
 * binary_tree_node_queue.h
 *
 *  Created on: Mar 7, 2017
 *      Author: Negin Mortazavi
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "binary_tree.h"
#include "binary_tree_node_queue.h"

/**
 * Prefix order expression string to depth first traversal data string buffer.
 *
 * @param node the root node in the tree
 * @param tState the state for depth first traversal callback
 * @param callbackData the traversal callback data
 */

void toPrefix(BinaryTreeNode* node,
	          DepthFirstTraversalState tState,
	          DepthFirstTraversalData tData){

	switch(tState){
	case fromParent:
		assert(node != (BinaryTreeNode*)NULL);
		if(!isBinaryTreeNodeLeaf(node)){
			strcat(tData, "( ");
			strcat(tData, node->data->strval);
			strcat(tData, " ");
		}else if(isBinaryTreeNodeRoot(node)){
			strcat(tData, node->data->strval);
		}else{
			strcat(tData, node->data->strval);
			strcat(tData, " ");
		}
		break;

	case fromLeft:
		break;

	case fromRight:
		strcat(tData, ")");
		if(!isBinaryTreeNodeRoot(node)){
			strcat(tData, " ");
		}

	break;


	}
}


/**
 * Infix order expression string to depth first traversal data string buffer.
 *
 * @param node the root node in the tree
 * @param tState the state for depth first traversal callback
 * @param callbackData the traversal callback data
 */

void toInfix(BinaryTreeNode* node,
	          DepthFirstTraversalState tState,
	          DepthFirstTraversalData tData){

	switch(tState){

	case fromParent:
		assert(node != (BinaryTreeNode*)NULL);

		if(!isBinaryTreeNodeLeaf(node)){
			strcat(tData, "( ");
		}else{
			strcat(tData, node->data->strval);
			if(!isBinaryTreeNodeRoot(node)){
				strcat(tData, " ");
		}
	}
		break;

	case fromLeft:
		strcat(tData, node->data->strval);
		strcat(tData, " ");

		break;
	case fromRight:
		strcat(tData, ")");
		if(!isBinaryTreeNodeRoot(node)){
			strcat(tData, " ");
		}
		break;
	}
}


/**
 * Postfix order expression string to depth first traversal data string buffer.
 *
 * @param node the root node in the tree
 * @param tState the state for depth first traversal callback
 * @param callbackData the traversal callback data
 */
void toPostfix(BinaryTreeNode* node,
	          DepthFirstTraversalState tState,
	          DepthFirstTraversalData tData){

	switch(tState){

	case fromParent:
		assert(node != (BinaryTreeNode*)NULL);
		if(isBinaryTreeNodeLeaf(node)){
			strcat(tData, node->data->strval);
			if(!isBinaryTreeNodeRoot(node)){
				strcat(tData, " ");
				}
			}
		break;

	case fromLeft:
		break;

	case fromRight:
		if(!isBinaryTreeNodeRoot(node)){
			strcat(tData, node->data->strval);
			strcat(tData, " ");
		}else{
			strcat(tData, node->data->strval);
		}
		break;

	}
}

/**
 * Enqueues just the leaf nodes in the tree in a BinaryTreeNodeQueue
 * using in the queue breadth-first traversal.
 *
 * @param node the visited tree node
 * @param tData the traversal data -- BinaryTreeNodeQueue
 */
void getLeafNodes(
	BinaryTreeNode* node,
	BreadthFirstTraversalData tData){
	if(binaryTreeNodeCardinality(node) == 0){
		enqueueBinaryTreeNodeQueue(tData, node);
	}
}


