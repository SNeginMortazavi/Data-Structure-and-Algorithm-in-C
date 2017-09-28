/*
 * avl_tree.c
 *
 *  These algorithms are based on ones in the "AVL tree" Wikipedia article
 *  (https://en.wikipedia.org/wiki/AVL_tree).
 *
 *  @since 2017-03-01
 *  @author Philip Gust
 */
#include <stdio.h>
#include "binary_search_tree_impl.h"

/**
 * Perform single left rotation on a parentNode that is right-heavy and
 * its right outer subtree, or a single right rotation on a parentNode
 * that is left-heavy and its left outer subtree
 *
 * @param outerNode the outer subtree node to to rotate about
 * @return new root of rotated subtree
 */
static BinaryTreeNode* singleRotate(BinaryTreeNode* outerNode) {
	// parameterizing algorithm using concept of inner- and outer-link
	// enables the same code to perform left rotation on a right-heavy
	// right subtree or right rotation on a left-heavy left subtree.
	BinaryTreeNodeLink outerLink = linkOfBinaryTreeNodeChild(outerNode);
	BinaryTreeNodeLink innerLink = otherBinaryTreeNodeChildLink(outerLink);

    // outerNode is by 2 higher than its sibling
	BinaryTreeNode* parentNode= outerNode->linkTo[parentLink];

 	 // Inner child of outerChildNode
 	 BinaryTreeNode* innerChildNode = outerNode->linkTo[innerLink];
     parentNode->linkTo[outerLink] = innerChildNode;
     if (innerChildNode != (BinaryTreeNode*)NULL) {
         innerChildNode->linkTo[parentLink] = parentNode;
     }

     outerNode->linkTo[innerLink] = parentNode;
     parentNode->linkTo[parentLink] = outerNode;

     if (outerNode->balanceFactor == 0) {
         // 1st case only happens with deletion, not insertion:
         parentNode->balanceFactor = +1;   // now higher
         outerNode->balanceFactor = -1;   // now lower than parentNode
     } else {
    	 // 2nd case happens with insertion or deletion:
         parentNode->balanceFactor = 0;
         outerNode->balanceFactor = 0;
     }

     return outerNode; // return new root of rotated subtree
 }

/**
 * Perform right then left rotation on a parentNode that is left-heavy and
 * its left inner subtree, or left then right rotation on a parentNode
 * that is right-heavy and its right inner subtree.
 *
 * @param outerNode the outer subtree node for the first rotation.
 * @return new root of rotated subtree
 */
static BinaryTreeNode* doubleRotate(BinaryTreeNode* outerNode) {
	// parameterizing algorithm using concept of inner- and outer-link
	// enables the same code to perform a right and then left rotation
	// on a parent node that is left-heavy and its left inner subtree,
	// or left then right rotation on a parent node that is right-heavy
	// and its right inner subtree.
	BinaryTreeNodeLink outerLink = linkOfBinaryTreeNodeChild(outerNode);
	BinaryTreeNodeLink innerLink = otherBinaryTreeNodeChildLink(outerLink);

	// outerNode is 2 higher than its sibling
	BinaryTreeNode* parentNode= outerNode->linkTo[parentLink];

	 // innerChildNode is by 1 higher than sibling
	 BinaryTreeNode* innerChildNode = outerNode->linkTo[innerLink];

	 BinaryTreeNode* outerGrandChildNode = innerChildNode->linkTo[outerLink];
	 outerNode->linkTo[innerLink] = outerGrandChildNode;
	 if (outerGrandChildNode != (BinaryTreeNode*)NULL) {
		 outerGrandChildNode->linkTo[parentLink] = outerNode;
	 }
	 innerChildNode->linkTo[outerLink] = outerNode;
	 outerNode->linkTo[parentLink] = innerChildNode;

	 // second rotation
	 BinaryTreeNode* innerGrandChildNode = innerChildNode->linkTo[innerLink];
	 parentNode->linkTo[outerLink] = innerGrandChildNode;
	 if (innerGrandChildNode != (BinaryTreeNode*)NULL) {
	 	 innerGrandChildNode->linkTo[parentLink] = parentNode;
	 }
	 innerChildNode->linkTo[innerLink] = parentNode;
	 parentNode->linkTo[parentLink] = innerChildNode;

	 if (innerChildNode->balanceFactor == 0) {
		// inner node balanced: only happens with deletion, not insertion
		parentNode->balanceFactor = 0;
		outerNode->balanceFactor = 0;
	 } else if (innerChildNode->balanceFactor == outerNode->balanceFactor) {
		 // inner node is interior heavy: happens with insertion or deletion
		 parentNode->balanceFactor = 0;
		 outerNode->balanceFactor = -innerChildNode->balanceFactor;
	 } else {
		 // inner node is exterior heavy: happens with insertion or deletion
		 parentNode->balanceFactor = -innerChildNode->balanceFactor;
		 outerNode->balanceFactor = 0;
	 }
	innerChildNode->balanceFactor = 0;  // new root is balanced

	return innerChildNode; // return new root of rotated subtree
}

/**
 * Rebalance tree after inserting insertNode.
 *
 * @param insertNode the node that was inserted
 * @return the new root of the tree after rebalancing.
 */
static BinaryTreeNode* retraceAfterInsert(BinaryTreeNode* insertedNode) {
	BinaryTreeNode* curNode = insertedNode;

	// Loop (possibly up to the root)
	for (BinaryTreeNode *grandParentNode,
						* parentNode = curNode->linkTo[parentLink];
			parentNode != (BinaryTreeNode*)NULL;
			parentNode = grandParentNode) {

		// save parent of parentNode
		grandParentNode = parentNode->linkTo[parentLink];

		// record child link of new current node
		BinaryTreeNodeLink childLink = linkOfBinaryTreeNodeChild(curNode);

		// parameterizing algorithm using concept of interior- and exterior
		// balance enables the same code work when a child has been added to
		// either subtree that causes that subtree to become over-balanced.
		// exterior is left (-1) for a left child link, right for a right link
		int exteriorBalance = (childLink == leftLink) ? -1 : 1;
		int interiorBalance = -exteriorBalance;

		// note: parentNode->balanceFactor has not yet been updated!
		if (parentNode->balanceFactor == exteriorBalance) {
	        // parentNode now out of AVL balance (+ or - 2)
			// Save parent of parentNode around rotations
            if (curNode->balanceFactor == interiorBalance) {
            	// curNode is heavy to interior of tree on its side
            	// (balance factors updated during rotation)
            	curNode = doubleRotate(curNode);
            } else {
            	// curNode is heavy to exterior of tree on its side
            	// (balance factors updated during rotation)
            	curNode = singleRotate(curNode);
            }

    		// After a rotation adapt parent link:
    	    // newParentNode is the new root of the rotated subtree
    	    curNode->linkTo[parentLink] = grandParentNode;
    	    if (grandParentNode != (BinaryTreeNode*)NULL) {
    	    	// NOTE: grandparent node points to parent as a child, but
    	    	// parent's parent node no longer points to grandparent node
				BinaryTreeNodeLink whichChildLink =
					linkOfParentBinaryTreeNodeChild(grandParentNode, parentNode);
				grandParentNode->linkTo[whichChildLink] = curNode;
    	    }
    	    break;
        } else if (parentNode->balanceFactor == interiorBalance) {
        	// curNode's height increase is absorbed at parentNode
        	parentNode->balanceFactor = 0;
        	curNode = parentNode;
    		break;

        } else { // parentNode balanced before updating factor
	        // increase parentNode height by 1 to exterior of tree
            parentNode->balanceFactor = exteriorBalance;
        	curNode = parentNode;
        }
	}

	// return new root of tree
	return findBinaryTreeNodeRoot(curNode);
}

/**
 * Rebalance tree after deleting a node from a parent node.
 * After deletion, one or both child nodes are null.
 *
 * If both child links are null, then the left child was deleted
 * if the parent balance was -1, and the right child was delete if
 * the parent balance was 1. Otherwise, which child was deleted
 * can be determined by which child is null.
 *
 * @param parentOfDeletedNode the parent of the node that was deleted
 * @return the new root of the tree after rebalancing.
 */
static BinaryTreeNode* retraceAfterDelete(
		BinaryTreeNode* parentOfDeletedNode) {

	BinaryTreeNode* curNode = (BinaryTreeNode*)NULL;
	BinaryTreeNodeLink childLink = leftLink;
	if (   parentOfDeletedNode->balanceFactor == 1
		|| parentOfDeletedNode->linkTo[rightLink] == (BinaryTreeNode*)NULL) {
		childLink = rightLink;
	}

	// Loop (possibly up to the root)
	for (BinaryTreeNode *grandParentNode,
						*parentNode = parentOfDeletedNode;
		 parentNode != (BinaryTreeNode*)NULL; parentNode = grandParentNode) {

		// save parent of parentNode
		grandParentNode = parentNode->linkTo[parentLink];

		// parameterizing algorithm using concept of interior- and exterior
		// balance enables the same code work on when a left child has been
		// removed and the parent is right over-balanced, or a right child
		// has been removed and the parent is left over-balanced.
		int exteriorBalance = (childLink == leftLink) ? -1 : 1;
		int interiorBalance = -exteriorBalance;

		// note: parentNode->balanceFactor has not yet been updated!
		if (parentNode->balanceFactor == interiorBalance) {
			// parentNode now out of AVL balance (+ or - 2)
			// rebalance around sibling
			BinaryTreeNodeLink siblingLink = otherBinaryTreeNodeChildLink(childLink);
			BinaryTreeNode* siblingNode = parentNode->linkTo[siblingLink];
			if (siblingNode->balanceFactor == exteriorBalance) {
				// sibling is heavy to exterior of tree on its side
            	// (balance factors updated during rotation)
				curNode = doubleRotate(siblingNode);
			} else {
				// sibling is heavy to interior of tree on its side
            	// (balance factors updated during rotation)
				curNode = singleRotate(siblingNode);
			}

			// After a rotation, adopt parent link:
			// curNode the new root of the rotated subtree
			curNode->linkTo[parentLink] = grandParentNode;
			if (grandParentNode != (BinaryTreeNode*)NULL) {
				BinaryTreeNodeLink whichChildLink =
						linkOfBinaryTreeNodeChild(parentNode);
				grandParentNode->linkTo[whichChildLink] = curNode;
				if (siblingNode->balanceFactor == 0) {
					break;  // height unchanged: leave the loop
				}
			}

		} else if (parentNode->balanceFactor == 0) {
			// curNode's height decrease is absorbed at parentNode
			curNode = parentNode;
			curNode->balanceFactor = interiorBalance;
			break;

		} else { // parentNode->balanceFactor == exteriorBalance
			curNode = parentNode;
			curNode->balanceFactor = 0;
		}

		// record child link of new current node
		childLink = linkOfBinaryTreeNodeChild(curNode);
	}

	// return new root of tree
	return findBinaryTreeNodeRoot(curNode);
}

/**
 * Add a node to an AVL tree.
 *
 * @param node the root of the binary tree
 * @param data the node data for the new node (takes ownership of data)
 * @return the new node or NULL if already in the tree
 */
BinaryTreeNode* addAvlTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode* root;
	BinaryTreeNode* newNode = addBinarySearchTreeNode(node, data);

	if (newNode == (BinaryTreeNode*)NULL) {
		// not found -- return current root
		root = findBinaryTreeNodeRoot(node);
	} else {
		// retrace to rebalance tree
		root = retraceAfterInsert(newNode);
	}
	return root;
}

/**
 * Remove a node from an AVL tree.
 *
 * @param node the root of the binary tree
 * @param data the node data for the new node (takes ownership of data)
 * @return the root of the tree
 */
BinaryTreeNode* removeAvlTreeNode(BinaryTreeNode* node, BinaryTreeNodeData* data) {
	BinaryTreeNode* root;
	BinaryTreeNode* deleteNode = findEqualBinarySearchTreeNode(node, data);
	if (deleteNode == (BinaryTreeNode*)NULL) {
		// not found -- return current root
		root = findBinaryTreeNodeRoot(node);
	} else {
		BinaryTreeNode* nodeParent = removeBinarySearchTreeChildNode(deleteNode);
		if (nodeParent == (BinaryTreeNode*)NULL) {
			root = (BinaryTreeNode*)NULL;
		} else {
			root = retraceAfterDelete(nodeParent);
		}
	}
	return root;
}
