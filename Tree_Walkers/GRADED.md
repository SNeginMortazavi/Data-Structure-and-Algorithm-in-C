# Grading for prog-assignment-4-neginmortazavi
**Class:** 2017SPCS5002SV<br>
**Date:** 2017-03-18<br>
**Grader:** pgust

## Total: 49/50
## Comments

* binary_tree_node_queue.c,.h (9/10)
  * Do not ignore compiler warnings of wrong pointer type
    * Should compare to (BinaryTreeNode**)NULL rather than (BinaryTreeNode*)NULL
  * deleteBinaryTreeNodeQueue()
    * Do not call deleteBinaryTreeNode() for remaining nodes in queue
      * Collection does not “own” nodes and is not entitled to delete them
        * It can only remove them from the collection

  * isEmptyBinaryTreeNodeQueue()
    * Simplify this to
```c
return (queue->numElements == 0);
```

* toPostfix() (10/10)

* toPrefix() (10/10)

* toInfix() (10/10)

* getLeafNodes() (10/10)

