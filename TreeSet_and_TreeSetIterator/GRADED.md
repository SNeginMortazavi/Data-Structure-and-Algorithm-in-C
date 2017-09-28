# Grading for prog-assignment-6-neginmortazavi
**Class:** 2017SPCS5002SV<br>
**Date:** 2017-03-28<br>
**Grader:** pgust

## Total: 45/50
## Comments

* addTreeSetKey() (-2)
  * This may work, but it is *way* too complicated!
    * Completely re-implements TreeMap putTreeMapEntry()
    * Instead, simply call: “return putTreeMapEntry(set->map, key, ENTRY_VALUE);”
  * TreeSetIterator not freed
    
* addAllTreeSetKeys() (-1)
  * This may work, but it is *way* too complicated!
    * If containsAllTreeSetKeys() is false, call putAllTreeMapEntries()

* containsTreeSetKey()
  * No need to call underlying tree methods: use TreeMap methods instead
    * simplify to: “return containsTreeMapKey(set->map, key);”

* containsAllTreeSetKeys() (-1)
  * Iterator is not freed if returning from the loop
    * Add call to FreeTreeSetIterator() there, or break from loop with false = flag

* isTreeSetEmpty()
  * No need to use underlying tree structures: use TreeMap methods instead
    * simplify to: “return getTreeMapSize(set->map);”

* isTreeSetEmpty()
  * No need to call underlying tree methods: use TreeMap methods instead
    * simplify to: “return isTreeMapEmpty(set->map);”

* removeTreeSetKey() (-1)
  * This may work, but it is *way* too complicated!
    * Completely re-implements TreeMap removeTreeMapEntryForKey()
    * Simplify to: “removeTreeMapEntryForKey(set->map, key) != (MapValue*)NULL)”

* retainAllTreeSetKeys()
  * Cannot delete items from set with active iterator (will discuss in class)
    * BinaryTreeIterator.curNode has been removed and so is now “dead”
      * As a result, so is iterator to the set

* hasPrevTreeSetKey()
  * call hasPrevTreeMapEntry() instead of underlying hasPrevTreeSetNode()

* resetTreeSetIterator()
  * Call resetTreeMapIterator() instead of underlying resetBinaryTreeIterator()

* getTreeSetIteratorCount()
  * Call getTreeMapIteratorCount() instead of underlying getBinaryTreeIteratorCount().

* getTreeSetIteratorAvailable()
  * call getTreeMapIteratorAvailable() instead of underlying getBinaryTreeIteratorAvailable()
