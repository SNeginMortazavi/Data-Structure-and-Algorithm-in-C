# Grading for prog-assignment-5-neginmortazavi
**Class:** 2017SPCS5002SV<br>
**Date:** 2017-03-23<br>
**Grader:** pgust

## Total: 50/50
## Comments


* resetBinaryTreeNodeIterator()
  * No need to reset itr->size — that doesn’t change for life of iterator

* getBinaryTreeItrAvailable()
  * Counting the nodes on each call is way too expensive
    * Should initialize itr->size = UNAVAILABLE and cache it on first call

* getPrevBinaryTreeNode()
  * I’m not following the use of two iterator copies
    * Need additional comments to explain
    * Readers shouldn’t have to figure it out on their own
  * Iterator copies dynamically allocated but not freed
   * Creating more “garbage” for every iteration
   * Use local iterators and copy on assignment instead

* hasPrevBinaryTreeNode()
  * It seems like there are simpler ways to compute this:
    * call getPrevBinaryTreeNodeItr() with iterator copy and check NULL
    * return true if itr->count > 0