/*
 * map_entry.c
 *
 * This file contains implementations of comparison and hashing
 * functions for a Map.
 *
 * @since 2017-03-22
 * @author philip gust
 */

#include <stdio.h>
#include <string.h>
#include "map_entry.h"

/**
 * Compares two MapEntry objects.
 *
 * @param entry1 the first MapEntry
 * @param entry2 the second MapEntry
 * @return < 0 if entry1 < entry2, =0 if entry1 == entry2, >0 if entry1 > entry2
 */
int compareMapEntry(MapEntry* entry1, MapEntry* entry2) {
	return compareMapKey(entry1->key, entry2->key);
}

/**
 * Compares two MapKey objects
 *
 * @param entry1 the first Mapkey
 * @param entry2 the second MapKey
 * @return < 0 if key1 < key2, =0 if key1 == key2, >0 if key1 > key2
 */
int compareMapKey(MapKey key1, MapKey key2) {
	GraphNodeVertex* k1 = (GraphNodeVertex*)key1;
	GraphNodeVertex* k2 = (GraphNodeVertex*)key2;
	return (k1 < k2) ? -1 : (k1 > k2);
}

/**
 * Compares two MapEntry objects.
 *
 * @param val1 the first MapValue
 * @param val2 the second MapValue
 * @return < 0 if entry1 < entry2, =0 if entry1 == entry2, >0 if entry1 > entry2
 */
int compareMapValue(MapValue* val1, MapValue* val2) {
	return strcmp(val1->valuestr, val2->valuestr);
}

/**
 * Compute the hash code for the map entry key.
 *
 * @param key of the MapEntry
 */
int getMapEntryKeyHashCode(MapKey key) {
	// reinterpret pointer as a long
	long l = *(long*)((GraphNodeVertex*)key);

	// treats the upper and lower halves of the long
	// as separate values, and combined by XORing
	int hashCode = (int) ((l >> 32) ^ l);
	return hashCode;
}

