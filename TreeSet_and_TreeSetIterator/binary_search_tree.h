/*
 * binary_search_tree.h
 *
 *  @since 2017-02-22
 *  @author Philip Gust
 */

#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_
#include "binary_tree.h"

/**
 * Find the node in the tree whose data equals the given data
 *
 * @param node the root of a binary tree
 * @param data the data for the node being sought
 * @return the node or NULL if not found
 */
BinaryTreeNode*
  findEqualBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data);

/**
 * Find the node with the smallest value that is greater than
 * or equal to the given data.
 *
 * @param node the root of a binary tree
 * @param data the data for the node being sought
 * @return the node or NULL if not found
 */
BinaryTreeNode*
  findBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data);

/**
 * Add a node to a binary search tree.
 *
 * @param node the root of the binary tree
 * @param data the node data for the new node (takes ownership of data)
 * @return the new node or NULL if already in the tree
 */
BinaryTreeNode* addBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data);

/**
 * Remove the node with this node data from the tree.
 *
 * @param node the root of a binary search tree
 * @param data of the node to remove
 * @return the parent node of the node removed or NULL if node not in the tree.
 */
BinaryTreeNode* removeBinarySearchTreeNode (BinaryTreeNode* node, BinaryTreeNodeData* data);

#endif /* BINARY_SEARCH_TREE_H_ */
