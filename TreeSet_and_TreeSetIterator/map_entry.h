/*
 * map_entry.h
 *
 * @since 2017-03-15

 */

#ifndef MAP_ENTRY_H_
#define MAP_ENTRY_H_

#include <stdlib.h>
#include <stdbool.h>

/**
 * Structure that defines a MapEntry value.
 */
typedef struct {
  // something
	char* valuestr;   // for development purposes
} MapValue;

/**
 * Structure that defines a Map entry
 */
typedef struct {
	const char* key;
	MapValue* value;
} MapEntry;

/**
 * Compares two TreeMapEntry objects.
 *
 * @param entry1 the first MapEntry
 * @param entry2 the second MapEntry
 * @return < 0 if entry1 < entry2, =0 if entry1 == entry2, >0 if entry1 > entry2
 */
int compareMapEntry(MapEntry* entry1, MapEntry* entry2);

/**
 * Compares two TreeMapEntry objects.
 *
 * @param val1 the first MapValue
 * @param val2 the second MapValue
 * @return < 0 if entry1 < entry2, =0 if entry1 == entry2, >0 if entry1 > entry2
 */
int compareMapValue(MapValue* val1, MapValue* val2);

#endif /* TREE_MAP_ENTRY_H */
