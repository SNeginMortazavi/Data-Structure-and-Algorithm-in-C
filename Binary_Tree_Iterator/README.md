A binary tree iterator is an iterator that visits every node in the tree in infix order. It is initialized with the root of the tree. Each time it is called, it returns the next node in the tree. Once it has visited all the tree nodes, it returns NULL on subsequent calls.

When the BinaryTreeNodeIterator iterates over a binary search tree, it returns the node values from lowest to highest.

The binary tree iterator must maintain sufficient state between calls that it can resume where it left off at the end of the previous call. The iterator state machine is closely related to the state machine of the binary tree node depth-first crawler. In fact, the depth-first tree crawler code, minus the code that calls the callbacks, is a good starting point for implementing getNextBinaryTreeNode().

A new repository "prog-assignment-5-template" contains the same code for binary tree that we have been using, with the addition of two new files. The file "binary_tree_node_iterator.h" contains the structure and function definitions for a binary tree node iterator. The file "binary_tree_node_iterator.c" contains stubs for the iterator functions that you will implement.

For now, do not worry about the methods for backward traversal. Have the getPreviousBinaryTreeNode() method return NULL and the hasPreviousBinaryTreeNode() return false.

For the binaryTreeIteratorAvailable() method, use the binaryTreeSize() method to get the total number of nodes in the tree, and subtract the count maintained by the iterator. Getting the size is an expensive operation, so you can either get it while initializing the iterator, or the first time the binaryTreeIteratorAvailable() function is called, and record it in the size field of the iterator.