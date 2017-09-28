/*
 * tree_map.h
 *
 * This file provides the structures and function declarations of a TreeMap,
 * which is a Map that is backed by an AVL binary search tree.
 *
 * @since 2017-03-15

 */

#ifndef TREE_MAP_H_
#define TREE_MAP_H_

#include <stdlib.h>
#include <stdbool.h>
#include "binary_search_tree.h"
#include "map_entry.h"

/**
 * Structure that defines a TreeMap. All entries are private
 */
typedef struct {
	BinaryTreeNode* searchTree;
	int size;
} TreeMap;

// temporary for development only
typedef MapEntry* MapEntrySet;
typedef const char* StringSet;
typedef MapValue* MapValueCollection;

/**
 * Create new empty TreeMap.
 */
TreeMap* createTreeMap(void);

/**
 * Frees a TreeMap.
 *
 * @param map the TreeMap to free
 */
void freeTreeMap(TreeMap* map);

/**
 * Removes all of the mappings from this map.
 *
 * @param map the TreeMap
 */
void clearTreeMap(TreeMap* map);

/**
 * Returns true if this map contains a mapping for the specified key.
 *
 * @param map the TreeMap
 * @param key the entry key to check
 */
bool containsTreeMapKey(TreeMap* map, const char* key);

/**
 * Returns true if this map maps one or more keys to the specified value.
 *
 * @param map the TreeMap
 * @param value the entry value to check
 */
bool containsTreeMapValue(TreeMap* map, MapValue* value);


/**
 * Returns a Set view of the mappings contained in this map.
 *
 * @param map the TreeMap
 * @return the set of TreeMap entries for the map
 */
MapEntrySet* getTreeMapEntrySet(TreeMap* map);

/**
 * Returns the entry to which the specified key is mapped, or null if
 * this map contains no mapping for the key.
 *
 * @param map the TreeMap
 * @param key the entry key for the value to get
 * @return the MapEntry for the given key
 */
MapEntry* getTreeMapEntry(TreeMap* map, const char* key);

/**
 * Returns the value to which the specified key is mapped, or null if
 * this map contains no mapping for the key.
 *
 * @param map the TreeMap
 * @param key the entry key for the value to get
 * @return the value for the given key
 */
MapValue* getTreeMapValue(TreeMap* map, const char* key);

/**
 * Returns true if this map contains no key-value mappings.
 *
 * @param map the TreeMap
 * @return true of the map is entry, false otherwise
 */
bool isTreeMapEmpty(TreeMap* map);

/**
 * Returns a Set view of the keys contained in this map.
 *
 * @param map the TreeMap
 * @return the set of key strings in the map
 */
StringSet* getTreeMapKeySet(TreeMap* map);

/**
 * Associates the specified value with the specified key in this map
 *
 * @param map the TreeMap
 * @param key the key for the value to put
 * @param value the TreeMapValue for the key
 * @return the previous value for the key, or NULL for a new entry
 */
MapValue* putTreeMapEntry(TreeMap* map, const char* key, MapValue* value);

/**
 * Copies all of the mappings from the specified map to this map
 *
 * @param map the TreeMap
 * @param aMap another map whose entries will be added to the map
 * @todo What happens with values for entries whose keys are duplicates.
 */
void putAllTreeMapEntries(TreeMap* map, TreeMap* aMap);

/**
 * Removes the mapping for a key from this map if it is present
 *
 * @param map the TreeMap
 * @param key the key for the value to remove
 * @return the value of the entry that was removed
 */
MapValue* removeTreeMapEntryForKey(TreeMap* map, const char* key);

/**
 * Returns the number of key-value mappings in this map.
 *
 * @param map the TreeMap
 * @return the number of entries in the map
 */
int getTreeMapSize(TreeMap* map);


/**
 * Returns a Collection view of the values contained in this map.
 *
 * @param map the TreeMap
 * @return a collection of values in the map
 */
MapValueCollection* getTreeMapValues(TreeMap* map);


/**
 * Returns the key-value mapping associated with the first (least) key
 * in this map, or null if the map is empty.
 *
 * @param map the TreeMap
 * @return the entry for the first (least key) entry in the map
 */
MapEntry* getFirstTreeMapEntry(TreeMap* map);

/**
 * Returns the first (least) key in this map, or null if the map is empty.
 *
 * @param map the TreeMap
 * @return the key for the first (least) key in the map
 */
const char* getFirstTreeMapKey(TreeMap* map);

/**
 * Returns the key-value mapping associated with the last (greatest) key
 * in this map, or null if the map is empty.
 *
 * @param map the TreeMap
 * @return the entry for the last (greatest key) entry in the map
 */
MapEntry* getLastTreeMapEntry(TreeMap* map);

/**
 * Returns the last (greatest) key in this map, or null if the map is empty.
 *
 * @param map the TreeMap
 * @return the last (greatest) key in the map
 */
const char* getLastTreeMapKey(TreeMap* map);

/**
 * Returns a key-value mapping associated with the greatest key less than
 * or equal to the given key, or null if there is no such key.
 *
 * @param map the TreeMap
 * @return the entry for greatest key less than or equal to given key
 */
MapEntry* getTreeMapFloorEntry(TreeMap* map, const char* key);

/**
 * Returns a the greatest key less than or equal to the given key, or
 * null if there is no such key.
 *
 * @param map the TreeMap
 * @return the greatest key less than or equal to given key
 */
const char* getTreeMapFloorKey(TreeMap* map, const char* key);

/**
 * Returns a view of the portion of this map whose keys are less than
 * or equal to fromKey.
 *
 * @param map the TreeMap
 * @param key the key greater or equal to the keys in the returned map
 * @return a TreeMap whose keys are less than or equal key
 */
TreeMap* getHeadTreeMap(TreeMap* map, const char* key);


/**
 * Returns a key-value mapping associated with the least key strictly
 * greater than the given key, or null if there is no such key.
 *
 * @param map the TreeMap
 * @param key the greatest key strictly less than the key of the returned entry
 * @return the entry whose key is strictly greater than the given key
 */
MapEntry* getHigherTreeMapEntry(TreeMap* map, char* key);

/**
 * Returns the least key strictly greater than the given key, or null
 * if there is no such key.
 *
 * @param map the TreeMap
 * @param key the greatest key strictly less than the returned key
 * @return the key that is strictly greater than the given key
 */
const char* getHigherTreeMapKey(TreeMap* map, const char* key);

/**
 * Returns a key-value mapping associated with the greatest key strictly
 * less than the given key, or null if there is no such key.
 *
 * @param map the TreeMap
 * @param key the least key strictly greater than the returned key
 * @return the entry whose key is strictly less than the given key
 */
MapEntry* getLowerKeyMapEntry(TreeMap* map, char* key);

/**
 * Returns the greatest key strictly less than the given key, or null if
 * there is no such key.
 *
 * @param map the TreeMap
 * @param key the least key strictly greater than the returned key
 * @return the key that is strictly less than the given key
 */
const char* getLowerKeyMapKey(TreeMap* map, const char* key);

/**
 * Returns a view of the portion of this map whose keys are greater than
 * or equal to fromKey.
 *
 * @param map the TreeMap
 * @param key the key less than or equal to the keys in the returned map
 * @return a TreeMap whose keys are greater than or equal key
 */
TreeMap* getTailTreeMap(TreeMap* map, const char* fromKey);

#endif /* TREE_MAP_H_ */
