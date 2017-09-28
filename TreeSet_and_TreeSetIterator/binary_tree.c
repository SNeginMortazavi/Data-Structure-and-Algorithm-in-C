/*
 * binary_tree.c
 *
 *  @since 2017-02-17
 *  @author Philip Gust
 */
#include <stdlib.h>
#include <assert.h>
#include "binary_tree.h"
//#include "binary_tree_node_queue.h"

/**
 * Adds a BinaryTreeNode as a child of the parent node.
 *
 * @param child the child node o add
 * @param parent the parent of the child
 * @param whichChild one of {leftNode, rightNode}
 * @return a new BinaryTreeNode
 */
bool addBinaryTreeNodeAfter(
		BinaryTreeNode* child,
		BinaryTreeNode* parent,
		BinaryTreeNodeLink whichChild) {
	if (parent->linkTo[whichChild] != (BinaryTreeNode*)NULL) {
		return false;
	}
	parent->linkTo[whichChild] = child;
	child->linkTo[parentLink] = parent;
	return true;
}

/**
 * Free the node storage for the binary tree specified by root.
 * Data must be freed by caller.
 *
 * @param root the root of a binary tree
 */
void freeBinaryTree(BinaryTreeNode* root) {
	if (root != (BinaryTreeNode*)NULL) {
		freeBinaryTree(root->linkTo[leftLink]);
		freeBinaryTree(root->linkTo[rightLink]);
		deleteBinaryTreeNode(root);
	}
}

/**
 * Return the BinaryTreeNodeLink for a child of a parent node.
 * The childNode must be a child of the parent node.
 *
 * @param parentNode the parentNode
 * @param childNode the child node
 * @return leftLink if the child is a left child, rightLink if
 *  parentNode is a right child, or parentLink if childNode or
 *  parentNode if childNode is not a child of the parentNode.
 */
BinaryTreeNodeLink linkOfParentBinaryTreeNodeChild(
		BinaryTreeNode* parentNode, BinaryTreeNode* childNode) {
	BinaryTreeNodeLink whichLink = parentLink;
	if (parentNode != (BinaryTreeNode*)NULL) {
		if (parentNode->linkTo[rightLink] == childNode) {
			whichLink = rightLink;;
		} else if (parentNode->linkTo[leftLink] == childNode) {
			whichLink = leftLink;
		}
	}
	return whichLink;
}

/**
 * Return the BinaryTreeNodeLink for a child of a parent node.
 *
 * @param childNode the child node
 * @return leftLink if the child is a left child, or rightLink if
 *   the child is a rightLink; or parentLink if child is a root.
 */
BinaryTreeNodeLink linkOfBinaryTreeNodeChild(BinaryTreeNode* childNode) {
	BinaryTreeNode* parentNode = childNode->linkTo[parentLink];
	return linkOfParentBinaryTreeNodeChild(parentNode, childNode);
}

/**
 * Find the root of a binary tree from a node.
 * @param node the node
 * @return the root node
 */
BinaryTreeNode* findBinaryTreeNodeRoot(BinaryTreeNode* node) {
	BinaryTreeNode* n = node;
	if (n != (BinaryTreeNode*)NULL) {
		while (n->linkTo[parentLink] != (BinaryTreeNode*)NULL) {
			n = n->linkTo[parentLink];
		}
	}
	return n;
}
/**
 *
 * Returns depth of a binary tree node to its root node. The depth of a node
 * is the number of edges from the node to the tree's root node. A root node
 * will have a depth of 0.
 *
 * @param node a node in the tree
 * @return the depth of the node to the tree root
 */
int binaryTreeNodeDepth(BinaryTreeNode* node) {
	int depth = 0;
	for (BinaryTreeNode* cur = node;
		 cur != (BinaryTreeNode*)NULL; cur = cur->linkTo[parentLink]) {
		depth++;
	}
	return depth;
}


/**
 * Returns height of a binary tree from the root node. The height of a node
 * is the number of edges on the longest path from the node to a leaf. A leaf
 * node will have a height of 0. A NULL node will have a height of -1.
 *
 * @param node a node in the tree
 * @return the height of the node to the tree root
 */
int binaryTreeHeight(BinaryTreeNode* node) {
	int height = -1;
	if (node != (BinaryTreeNode*)NULL) {
		int lHeight = binaryTreeHeight(node->linkTo[leftLink]);
		int rHeight = binaryTreeHeight(node->linkTo[rightLink]);
		height = 1 + ((lHeight > rHeight) ? lHeight : rHeight);
	}
	return height;
}

/**
 * Returns number of nodes in a binary tree from the root node.
 *
 * Note: This is recursive implementation
 *
 * @param node the root node in the tree
 * @return the number of nodes in the tree
 */
int binaryTreeSize(BinaryTreeNode* node) {
	int size = 0;
	if (node != (BinaryTreeNode*)NULL) {
		size = 1 + binaryTreeSize(node->linkTo[leftLink])
		         + binaryTreeSize(node->linkTo[rightLink]);
	}
	return size;
}

/**
 * Returns number of nodes in a binary tree from the root node.
 *
 * Note: This is an iterative implementation
 *
 * @param node the root node in the tree
 * @return the number of nodes in the tree
 */
int binaryTreeSize2(BinaryTreeNode* node) {
	int size = 0;

	BinaryTreeNode* cur = node;
	BinaryTreeNodeLink prvLink = parentLink;

	while (cur != (BinaryTreeNode*)NULL) {
		BinaryTreeNodeLink nxtLink;

		if (prvLink == parentLink) {  // coming from parent
			size++; // count node on entry from parent
			if (cur->linkTo[leftLink] != (BinaryTreeNode*)NULL) {
				nxtLink = leftLink;
			} else if (cur->linkTo[rightLink] != (BinaryTreeNode*)NULL) {
				nxtLink = rightLink;
			} else {
				nxtLink = parentLink;
			}

		} else if (prvLink == leftLink) { // coming from left child
			if (cur->linkTo[rightLink] != (BinaryTreeNode*)NULL) {
				nxtLink = rightLink;
			} else {
				nxtLink = parentLink;
			}

		} else {  // prvLink == rightLink coming from right child
			nxtLink = parentLink;
		}
		prvLink = (nxtLink == parentLink)
				? linkOfBinaryTreeNodeChild(cur) : parentLink;
		// stop after root node even if the tree is a subtree
		cur = (cur == node && nxtLink == parentLink)
				? (BinaryTreeNode*)NULL : cur->linkTo[nxtLink];

	}
	return size;
}

/**
 * Traverses the tree depth-first. Callback is called
 * during traversal when traversal enters from parent,
 * when traversal returns from the left child, and when
 * traversal returns from right child.
 *
 * @param node the root node in the tree
 * @param callback the depth first traversal callback
 * @param callbackData the traversal callback data
 */
void binaryTreeTraverseDepthFirst(
		BinaryTreeNode* node,
		DepthFirstTraversalCallback callback,
		DepthFirstTraversalData callbackData) {

	BinaryTreeNode* cur = node;
	BinaryTreeNodeLink prvLink = parentLink;

	while (cur != (BinaryTreeNode*)NULL) {
		BinaryTreeNodeLink nxtLink;

		if (prvLink == parentLink) {  // coming from parent
			// notify coming from parent node
			if (callback != NULL) {
				callback(cur, fromParent, callbackData);
			}

			if (cur->linkTo[leftLink] != (BinaryTreeNode*)NULL) {
				nxtLink = leftLink;
			} else if (cur->linkTo[rightLink] != (BinaryTreeNode*)NULL) {
				// fake return from non-existent left node
				if (callback != NULL) {
					callback(cur, fromLeft, callbackData);
				}

				nxtLink = rightLink;
			} else {
				nxtLink = parentLink;
			}

		} else if (prvLink == leftLink) { // coming from left child
			// notify return from left node
			if (callback != NULL) {
				callback(cur, fromLeft, callbackData);
			}

			if (cur->linkTo[rightLink] != (BinaryTreeNode*)NULL) {
				nxtLink = rightLink;
			} else {
				// notify return from non-existent right node
				if (callback != NULL) {
					callback(cur, fromRight, callbackData);
				}

				nxtLink = parentLink;
			}

		} else {  // prvLink == rightLink coming from right child
			// notify return from right node
			if (callback != NULL) {
				callback(cur, fromRight, callbackData);
			}

			nxtLink = parentLink;
		}
		prvLink = (nxtLink == parentLink)
				? linkOfBinaryTreeNodeChild(cur) : parentLink;
		// stop after root node even if the tree is a subtree
		cur = (cur == node && nxtLink == parentLink)
				? (BinaryTreeNode*)NULL : cur->linkTo[nxtLink];
	}
}

/**
 * Traverse a binary tree breadth-first. Callback is called
 * during traversal when visits a node during bredth-first
 * traversal.
 *
 * @param node the root node in the tree
 * @param callback the depth first traversal callback
 * @param callbackData the traversal callback data
 *
 */
void binaryTreeTraverseBreadthFirst(
		BinaryTreeNode* node,
		BreadthFirstTraversalCallback callback,
		BreadthFirstTraversalData callbackData) {
//	BinaryTreeNodeQueue* q= newBinaryTreeNodeQueue();
//	if (node != (BinaryTreeNode*)NULL) {
//		enqueueBinaryTreeNodeQueue(q, node);
//	}
//	while (!isEmptyBinaryTreeNodeQueue(q)) {
//		BinaryTreeNode* cur = dequeueBinaryTreeNodeQueue(q);
//
//		if (cur->linkTo[leftLink] != (BinaryTreeNode*)NULL) {
//			enqueueBinaryTreeNodeQueue(q, cur->linkTo[leftLink]);
//		}
//		if (cur->linkTo[rightLink] != (BinaryTreeNode*)NULL) {
//			enqueueBinaryTreeNodeQueue(q, cur->linkTo[rightLink]);
//		}
//
//		if (callback != NULL) {
//			callback(cur, callbackData);
//		}
//	}
//	deleteBinaryTreeNodeQueue(q);
}

