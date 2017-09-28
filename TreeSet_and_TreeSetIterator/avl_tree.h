/*
 * avl_tree.h
 *
 *  @since 2017-03-01
 *  @author Philip Gust
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_
#include "binary_search_tree.h"

/**
 * Add a node to a binary search tree.
 *
 * @param node the root of the binary tree
 * @param data the node data for the new node (takes ownership of data)
 * @return the new node or NULL if already in the tree
 */
BinaryTreeNode* addAvlTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data);

/**
 * Add a node to a binary search tree.
 *
 * @param node the root of the binary tree
 * @param data the node data for the node to remove
 * @return the root of the tree
 */
BinaryTreeNode* removeAvlTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data);

#endif /* AVL_TREE_H_ */
