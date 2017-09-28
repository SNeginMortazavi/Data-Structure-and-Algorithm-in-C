/*
 * map_entry.h
 *
 * This file contains definitions of types and functions for a Map.
 *
 * @since 2017-03-15
 * @author philip gust
 */

#ifndef MAP_ENTRY_H_
#define MAP_ENTRY_H_

#include <stdlib.h>
#include <stdbool.h>
#include "graph_node_vertex.h"

/**
 * Structure that defines a MapEntry value.
 */
typedef struct {
  // something
	char* valuestr;   // for development purposes
} MapValue;

/**
 * Type of the map key.
 */
typedef GraphNodeVertex* MapKey;

/**
 * Structure that defines a Map entry
 */
typedef struct {
	MapKey key;				// the key that identifies the map entry
	MapValue* value;		// the map entry value
} MapEntry;

/**
 * Compares two MapEntry objects.
 *
 * @param entry1 the first MapEntry
 * @param entry2 the second MapEntry
 * @return < 0 if entry1 < entry2, =0 if entry1 == entry2, >0 if entry1 > entry2
 */
int compareMapEntry(MapEntry* entry1, MapEntry* entry2);


/**
 * Compares two MapKey objects
 *
 * @param entry1 the first Mapkey
 * @param entry2 the second MapKey
 * @return < 0 if key1 < key2, =0 if key1 == key2, >0 if key1 > key2
 */
int compareMapKey(MapKey key1, MapKey key2);


/**
 * Compares two TreeMapEntry objects.
 *
 * @param val1 the first MapValue
 * @param val2 the second MapValue
 * @return < 0 if entry1 < entry2, =0 if entry1 == entry2, >0 if entry1 > entry2
 */
int compareMapValue(MapValue* val1, MapValue* val2);

/**
 * Compute the hash code for the map entry key.
 *
 * @param key key of the MapEntry
 */
int getMapEntryKeyHashCode(MapKey key);

#endif /* TREE_MAP_ENTRY_H */
