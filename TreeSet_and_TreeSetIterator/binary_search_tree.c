/*
 * binary_search_tree.c
 *
 *  @since 2017-02-22
 *  @author Philip Gust
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>
#include <assert.h>

#include "binary_search_tree.h"

/**
 * Find the node in the tree whose data equals the given data
 *
 * @param node the root of a binary tree
 * @param data the data for the node being sought
 * @return the node or NULL if not found
 */
BinaryTreeNode*
  findEqualBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode* cur = node;
	while (cur != (BinaryTreeNode*)NULL) {
		int comp = compareBinaryTreeNodeData(data, cur->data);
		if (comp < 0) {
			cur = cur->linkTo[leftLink];
		} else if (comp > 0) {
			cur = cur->linkTo[rightLink];
		} else {
			break;  // found node
		}
	}
	return cur;
}

/**
 * Find the node with the smallest value that is greater than
 * or equal to the given data.
 *
 * @param node the root of a binary trxee
 * @param data the data for the node being sought
 * @return the node or NULL if not found
 */
BinaryTreeNode*
  findBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode* cur = node;
	BinaryTreeNode* prv = (BinaryTreeNode*)NULL;

	while (cur != (BinaryTreeNode*)NULL) {
		int comp = compareBinaryTreeNodeData(data, cur->data);
		if (comp < 0) {
			prv = cur;
			cur = cur->linkTo[leftLink];
		} else if (comp > 0) {
			cur = cur->linkTo[rightLink];
		} else {
			return cur;
		}
	}
	return (prv == (BinaryTreeNode*)NULL) ? (BinaryTreeNode*)NULL : prv;
}

/**
 * Find the node with the largest value less than or equal to
 * the specified data.
 *
 * @param node the root of the binary tree
 * @param the value beings sought
 * @return  the node with the largest value less than or equal to
 *
 * For implementation only
 */
BinaryTreeNode*
  findLastBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode* cur = node;
	BinaryTreeNode* prv = (BinaryTreeNode*)NULL;

	while (cur != (BinaryTreeNode*)NULL) {
		prv = cur;
		int c = compareBinaryTreeNodeData(data, cur->data);
		if (c < 0) {
			cur = cur->linkTo[leftLink];
		} else if (c > 0) {
			cur = cur->linkTo[rightLink];
		} else {
			return cur;
		}
	}
	return prv;
}

/**
 * Add the data to the left or right of the specified node.
 *
 * @param node the parent of the new node
 * @param data the node data for the new node (takes ownership of data)
 * @return new node or NULL if data already in tree
 *
 * For implementation only
 */
static BinaryTreeNode*
  addBinarySearchTreeChildNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	if (node == (BinaryTreeNode*)NULL) {
		return newBinaryTreeNode(data);
	}

	int comp = compareBinaryTreeNodeData(data, node->data);
	if (comp == 0) {
		return (BinaryTreeNode*)NULL;
	}

	// determine on which side to insert this child
	BinaryTreeNodeLink whichLink = (comp < 0) ? leftLink : rightLink;

	// child should be null
	assert (node->linkTo[whichLink] == (BinaryTreeNode*)NULL);

	BinaryTreeNode* newNode = newBinaryTreeNode(data);
	newNode->linkTo[parentLink] = node;
	node->linkTo[whichLink] = newNode;
	return newNode;
}

/**
 * Add a node to a binary search tree.
 *
 * @param node the root of the binary tree
 * @param data the node data for the new node (takes ownership of data)
 * @return the new node or NULL if already in the tree
 */
BinaryTreeNode* addBinarySearchTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode *last = findLastBinarySearchTreeNode(node, data);
	return addBinarySearchTreeChildNode(last, data);
}

/**
 * Splice the specified node out of the tree. The node
 * must have only 0 or 1 children.
 *
 * @param node the node to splice out
 */
static void spliceBinarySearchTreeNode (BinaryTreeNode* node) {
	BinaryTreeNode* nextNode;
	BinaryTreeNode* prevNode;
	if (node->linkTo[leftLink] != (BinaryTreeNode*)NULL) {
		nextNode = node->linkTo[leftLink];
	} else {
		nextNode = node->linkTo[rightLink];
	}

	if (node->linkTo[parentLink] == (BinaryTreeNode*)NULL) { // is root
		prevNode = (BinaryTreeNode*)NULL;
	} else {
		prevNode = node->linkTo[parentLink];
		BinaryTreeNodeLink link = // left or right parent link
				(prevNode->linkTo[leftLink] == node) ? leftLink : rightLink;
		prevNode->linkTo[link] = nextNode; // relink parent link to next node
	}
	if (nextNode != (BinaryTreeNode*)NULL) {
		nextNode->linkTo[parentLink] = prevNode;
	}
}

/**
 * Remove this node from the tree.
 * 
 * @param node the node to remove
 * @return the parent of the node removed
 *
 * For implementation only
 */
BinaryTreeNode* removeBinarySearchTreeChildNode (BinaryTreeNode* node) {
	BinaryTreeNodeLink exteriorLink =
		(node->linkTo[leftLink] == (BinaryTreeNode*)NULL) ? rightLink : leftLink;
	BinaryTreeNodeLink interiorLink = otherBinaryTreeNodeChildLink(exteriorLink);
	BinaryTreeNode* nextNode = node;
	if (nextNode->linkTo[exteriorLink] != (BinaryTreeNode*)NULL) {
		// find deepest interior node of exterior child node
		nextNode = nextNode->linkTo[exteriorLink];
		while (nextNode->linkTo[interiorLink] != (BinaryTreeNode*)NULL) {
			nextNode = nextNode->linkTo[interiorLink];
		}
		// Remove interior node by having it become the next larger
		node->data = nextNode->data;
	}
	// record the parent of node being removed
	BinaryTreeNode* parentNode = nextNode->linkTo[parentLink];

	// then splicing out the no longer needed node
	spliceBinarySearchTreeNode(nextNode);
	return parentNode;

//	BinaryTreeNode* parentNode;
//	if (node->linkTo[leftLink] == (BinaryTreeNode*)NULL) {
//		// record the parent of node being removed
//		parentNode = node->linkTo[parentLink];
//		spliceBinarySearchTreeNode(node);
//	} else {
//		// find leaf node with smallest value larger than node.
//		BinaryTreeNode* nextLarger = node->linkTo[rightLink];
//		while (nextLarger->linkTo[leftLink] != (BinaryTreeNode*)NULL) {
//			nextLarger = nextLarger->linkTo[leftLink];
//		}
//		// Remove interior node by having it become the next larger
//		node->data = nextLarger->data;
//
//		// record the parent of node being removed
//		parentNode = nextLarger->linkTo[parentLink];
//
//		// then splicing out the no longer needed node
//		spliceBinarySearchTreeNode(nextLarger);
//	}
//	return parentNode;
}

/**
 * Remove the node with this node data from the tree.
 *
 * @param node the root of a binary search tree
 * @param data of the node to remove
 * @return the parent node of the node removed or NULL if node not in the tree.
 */
BinaryTreeNode* removeBinarySearchTreeNode (BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode* nodeToRemove = findEqualBinarySearchTreeNode(node, data);
	if (nodeToRemove == (BinaryTreeNode*)NULL) {
		return (BinaryTreeNode*)NULL;
	}
	return removeBinarySearchTreeChildNode(nodeToRemove);
}

