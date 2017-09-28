/*
 * binary_tree_node.h
 *
 *  @since 2017-02-17

 */

#ifndef BINARY_TREE_NODE_H_
#define BINARY_TREE_NODE_H_

#include <stdbool.h>

/**
 * Enums for accessing BinaryTreeNode.linkTo[] array.
 */
typedef enum {
	leftLink = 0,
	rightLink,
	parentLink
} BinaryTreeNodeLink;

/**
 * Binary tree node data field. Defines type of data in a BinaryTreeNode.
 */
typedef struct _BinaryTreeNodeData {
// something
	const char* strval;  // temporary for testing only
} BinaryTreeNodeData;

/**
 * Binary tree node with a data field and a linkTo field
 * for left child node, right child node, and parent node.
 */
typedef struct _BinaryTreeNode {
	BinaryTreeNodeData* data;
	struct _BinaryTreeNode* linkTo[3];
} BinaryTreeNode;

/**
 * Compare the data for two binary tree nodes.
 *
 * @param data1 the first node data
 * @param data2 the second node data
 * @return <0 if data1<data2, =0 if data1=data2, >0 if data1>data2
 */
int compareBinaryTreeNodeData(BinaryTreeNodeData * data1, BinaryTreeNodeData* data2);

/**
 * Create a new BinaryTreeNode with specified data or NULL.
 *
 * @param data the value of the data field
 * @return a new BinaryTreeNode
 */
BinaryTreeNode* newBinaryTreeNode(BinaryTreeNodeData* data);

/**
 * Delete a BinaryTreeNode. Data must be freed by caller.
 *
 * @param node the node to free
 */
void deleteBinaryTreeNode(BinaryTreeNode* node);

/**
 * Determines the cardinality of a tree node.
 *
 * @param node a node in the tree
 * @return return 0 if a leaf, 2 if both links present, 1 if one link present
 */
int binaryTreeNodeCardinality(BinaryTreeNode* node);

/**
 * Determines whether tree node is a leaf.
 *
 * @param node a node in the tree
 * @return true if the node is a leaf and false otherwise
 */
bool isBinaryTreeNodeLeaf(BinaryTreeNode* node);

/**
 * Determines whether tree node is a root.
 *
 * @param node a node in the tree
 * @return true if the node is a root and false otherwise
 */
bool isBinaryTreeNodeRoot(BinaryTreeNode* node);

/**
 * Returns the BinaryTreeNodeLink enumeration for the "other" child.
 *
 * @param childLink the child link enumeration (leftNode or rightNode)
 * @return the enumeration for the "other" child link (rightNode or leftNode),
 *   or the original enumeration if the childLink is not leftNode or rightNode
 */
BinaryTreeNodeLink otherBinaryTreeNodeChildLink(BinaryTreeNodeLink childLink);

#endif /* BINARY_TREE_NODE_H_ */
