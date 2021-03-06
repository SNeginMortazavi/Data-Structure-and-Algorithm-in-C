/*
 * tree_set.h
 *
 * This file provides the implementations of a TreeSet, which is
 * a Set that is backed by an AVL binary search tree.
 *
 * @since 2017-03-15

 */

#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "avl_tree.h"
#include "tree_set.h"
#include "tree_set_iterator.h"
#include "tree_map.h"
#include "tree_map_iterator.h"
#include "binary_tree.h"
#include <assert.h>

/**
 * The value assigned to all MapEntry value fields
 */
static MapValue* ENTRY_VALUE = &(MapValue){""};

/**
 * Create new empty TreeSet.
 */
TreeSet* createTreeSet(void) {
	TreeSet* set = (TreeSet*)malloc(sizeof(TreeSet));
	set->map = createTreeMap();
	return set;
}

/**
 * Frees a TreeSet.
 *
 * @param set the TreeSet to free
 */
void freeTreeSet(TreeSet* set) {
	clearTreeSet(set);
	free(set);
}

/**
 * Removes all of the keys from this set.
 *
 * @param set the TreeSet
 */
void clearTreeSet(TreeSet* set) {
	freeBinaryTree(set->map->searchTree);
	set->map->searchTree = (BinaryTreeNode*)NULL;
	set->map->size = 0;
}

/**
 * Adds the specified key to this set if it is not already present.
 *
 * @param set the TreeSet
 * @param key the entry key to check
 * @return true if the key was added, false otherwise
 */
bool addTreeSetKey(TreeSet* set, const char* key) {
	bool keyWasAdded = false;
	TreeSetIterator* itr = createTreeSetIterator(set);
	const char* keyEntry = getNextTreeSetKey(itr);
	while (keyEntry != (const char*)NULL) {
		const char* myKey = (const char*)NULL;
		if(myKey == key){
			keyWasAdded = false;
			break;
		}
		keyEntry = getNextTreeSetKey(itr);
	}
	BinaryTreeNodeData* newData = (BinaryTreeNodeData*)malloc(sizeof(BinaryTreeNodeData));
	newData->entry.key = key;
	newData->entry.value = ENTRY_VALUE;
	set->map->searchTree = addAvlTreeNode(set->map->searchTree, newData);
	set->map->size++;
	keyWasAdded = true;

	return keyWasAdded;
}

/**
 * Adds all keys to this set that are present in the other set.
 *
 * @param set the TreeSet
 * @param otherSet the other TreeSet
 * @return true if the set was modified as a result of this call
 */
bool addAllTreeSetKeys(TreeSet* set, TreeSet* otherSet) {
	TreeSetIterator* itr = createTreeSetIterator(otherSet);
	const char* keyEntry = getNextTreeSetKey(itr);
	bool flag = false;

	while (keyEntry != (const char*)NULL) {
		if(!containsTreeSetKey(set, keyEntry)){
			BinaryTreeNodeData* newData = (BinaryTreeNodeData*)malloc(sizeof(BinaryTreeNodeData));
			newData->entry.key = keyEntry;
			newData->entry.value = ENTRY_VALUE;
			set->map->searchTree = addAvlTreeNode(set->map->searchTree, newData);
			set->map->size++;
			return (MapValue*)NULL;
			flag = true;
		}
		keyEntry = getNextTreeSetKey(itr);
	}

	freeTreeSetIterator(itr);
	return flag;
}

/**
 * Returns true if this set contains the specified key.
 *
 * @param set the TreeSet
 * @param key the entry key to check
 * @return true if the set contains the key, false otherwise
 */
bool containsTreeSetKey(TreeSet* set, const char* key) {
	BinaryTreeNodeData data = {{key}};
	BinaryTreeNode* node = findEqualBinarySearchTreeNode(set->map->searchTree, &data);
	return (node != (BinaryTreeNode*)NULL);
}

/**
 * Returns true if this set contains all the keys from the other set.
 *
 * @param set the TreeSet
 * @param key the entry key to check
 * @return true if the set contains all the keys, false otherwise
 */
bool containsAllTreeSetKeys(TreeSet* set, TreeSet* otherSet) {
	TreeSetIterator* itr = createTreeSetIterator(otherSet);
	const char* keyEntry = getNextTreeSetKey(itr);
	while (keyEntry != (const char*)NULL) {
		if(!containsTreeSetKey(set, keyEntry)){
			return false;
		}
		keyEntry = getNextTreeSetKey(itr);
	}
	freeTreeSetIterator(itr);
	return true;
}

/**
 * Returns the size of the set.
 *
 * @param set the TreeSet
 * @return the size of the TreeSet
 */
int getTreeSetSize(TreeSet* set) {
	return set->map->size;
}

/**
 * Returns true if this set contains no keys.
 *
 * @param set the TreeSet
 * @return true of the set is entry, false otherwise
 */
bool isTreeSetEmpty(TreeSet* set) {
	return (set->map->searchTree == (BinaryTreeNode*)NULL);
}

/**
 * Removes the specified element from this set if it is present.
 *
 * @param set the TreeSet
 * @param key the entry key to check
 * @return true if the key was removed, false otherwise
 */

bool removeTreeSetKey(TreeSet* set, const char* key) {
	// first method using MapValue
	MapValue* myEntry = removeTreeMapEntryForKey(set->map, key);
	if (myEntry == NULL) {
		return false;
	}
	return true;

	/* second method using TreeSetIterator
	 *
	 *
	TreeSetIterator* itr = createTreeSetIterator(set);
	const char* keyEntry = getNextTreeSetKey(itr);
	while (keyEntry != (const char*)NULL) {
		if (containsTreeSetKey(set, key)) {
			set->map->searchTree =
			removeAvlTreeNode(set->map->searchTree, &(BinaryTreeNodeData){{key,ENTRY_VALUE}} );
			set->map->size--;
			keyEntry = getNextTreeSetKey(itr);
			return true;
		}
	}
	freeTreeSetIterator(itr);
	return false;*/
}

/**
 * Removes all elements from this set that are present in the other set.
 *
 * @param set the TreeSet
 * @param key the entry key to check
 * @return true if the set changed as a result of this call
 */

bool removeAllTreeSetKeys(TreeSet* set, TreeSet* otherSet) {
	TreeSetIterator* itr = createTreeSetIterator(set);
	bool flag = false;
	const char* keyEntry = getNextTreeSetKey(itr);
	while (keyEntry != (const char*)NULL) {
		if (containsTreeSetKey(otherSet, keyEntry)) {
			removeTreeSetKey(set, keyEntry);
			flag = true;
		}
		keyEntry = getNextTreeSetKey(itr);
	}
	freeTreeSetIterator(itr);
	return flag;
}

/**
 * Retains only the elements in this set that are present in the other set.
 *
 * @param set the TreeSet
 * @param key the entry key to check
 * @return true if the set changed as a result of this call
 */

bool retainAllTreeSetKeys(TreeSet* set, TreeSet* otherSet) {
	TreeSetIterator* itr = createTreeSetIterator(set);
	const char* keyEntry = getNextTreeSetKey(itr);
	bool flag = false;
	while (keyEntry != (const char*)NULL) {
		if(!containsTreeSetKey(otherSet, keyEntry)){
			removeTreeSetKey(set, keyEntry);
			flag = true;
		}
		keyEntry = getNextTreeSetKey(itr);
	}

	freeTreeSetIterator(itr);
	return flag;
}

