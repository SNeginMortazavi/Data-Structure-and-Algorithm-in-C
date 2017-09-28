A tree walker is a function that visits every node in a tree. At each node, the tree walker calls a user specified function that performs some action using the node. The function could collect and return a group of nodes, perform some calculation that accumulates across the nodes, or even modify the values of the nodes.

Tree walkers can traverse a tree in either depth-first or breadth-first order. A depth-first traversal visits a node and all its children before visiting any siblings of the node at the same level. A breadth-first traversal visits all nodes at one level before descending to the next level.

At each node, the tree walker passes to the user specified traversal function the node being visited, the traversal state, and function-specific data that is passed to the tree walker along with the traversal function. Not all traversal functions require user data to operate or return results.

The binary tree code we have been using in class includes both a depth-first tree walker function binaryTreeTraverseDepthFirst() and a breadth-first tree walker function binaryTreeTraverseBreadthFirst(). Both expect as parameters the root node of a tree, a user specfied traversal function, and traversal function specific data. Typedefs for the traversal function and the traversal function data. The traversal function is resposible for casting the traversal function data to the appropriate type, which the caller must supply. The traversal function passd in can be null, in which case the tree walkers visit each node but perform no action.

The template code for this assignment is located in the NEU CCS GitHub repository 2017SPCS5002SV/prog-assignment-4-template.

There are several parts to this assignment.

For the purposes of this exercise, add a const char* field strval to the BinaryTreeNodeData struct in binary_tree.h. We will be testing our code using string node values. We can enhance this once all the code is running correctly
The binaryTreeTraverseBreadthFirst() function requires a supporting queue of BinaryTreeNode-s. Provide an implementation in a separate file, "binary_tree_node_queue.c" and "binary_tree_node_queue.h" in your project. Include "binary_tree_node_queue.h" in "binary_tree.c". Implement the following functions:
BinaryTreeNodeQueue* newBinaryTreeNodeQueue(void)
void deleteBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue)
void enqueueBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue, BinaryTreeNode* node);
BinaryTreeNode* dequeueBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue)
bool isEmptyBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue)
int getNumElementsBinaryTreeNodeQueue(BinaryTreeNodeQueue* queue)
After reviewing how binaryTreeTraverseDepthFirst() and binaryTreeTraverseBreadthFirst() call their traversal functions with the current node, traversal state, and the user specified traversal data, implement the following traversal callback functions in a separate file named "traversal_callbacks.c". A test program will call these functions.
/**
 * Write prefix order expression string to traversal data string buffer
 *
 * @param node the visited tree node
 * @param tState the state of the traversal
 * @param isLeaf true of node is a leaf
 * @param tData the traversal data -- must be a string buffer
 */
void toPostfix(
     BinaryTreeNode* node,
     DepthFirstTraversalState tState,
     DepthFirstTraversalData tData)
                 
/**
 * Write prefix order expression string to traversal data string buffer.
 *
 * @param node the visited tree node
 * @param tState the state of the traversal
 * @param tData the traversal data -- must be a string buffer
 */
void toPrefix(
     BinaryTreeNode* node,
     DepthFirstTraversalState tState,
     DepthFirstTraversalData tData)
                 
/**
 * Write infix order expression string to traversal data string buffer.
 *
 * @param node the visited tree node
 * @param tState the state of the traversal
 * @param tData the traversal data -- must be a string buffer
 */
void toInfix(
     BinaryTreeNode* node,
     DepthFirstTraversalState tState,
     DepthFirstTraversalData tData)
                 
/**
 * Enqueues just the leaf nodes in the tree in a BinaryTreeNodeQueue
 * using in the queue breadth-first traversal.
 *
 * @param node the visited tree node
 * @param tData the traversal data -- BinaryTreeNodeQueue
 */
void getLeafNodes(
     BinaryTreeNode* node,
     BreadthFirstTraversalData tData)
                 
A main program and unit tests are contained in the "binary_tree_main.c" file. Your implementation must pass all the unit tests. Here is an example of how the depth- and breadth-first traversal function would be called for the toPrefix() and getLeafNodes() functions:

BinaryTreeNode* theTree = ...;

char exprStr[100]; 
strcpy(exprStr,""); // initialize
binaryTreeTraverseDepthFirst(theTree, toPostfix, exprStr);
//print postfix expression

BinaryTreeNodeQueue queue = createBinaryTreeNodeQueue();
binaryTreeTraverseBreadthFirst(theTree, getLeafNodes, queue);
// print child node values
deleteBinaryTreeNodeQueue(queue);  // free queue when done.
				      	   	 
Thare are many other very intresting operations that can be implemented in terms of a tree walker, such as counting the number of nodes in the tree, or determining the height of the tree. You are encourage to explore some of these on your own. We will discuss some others once you have turned in your assignment.