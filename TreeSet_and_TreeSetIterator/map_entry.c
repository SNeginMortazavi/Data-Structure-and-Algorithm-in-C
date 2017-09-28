/*
 * map_entry.c
 *
 * @since 2017-03-15

 */

#include <stdio.h>
#include <string.h>
#include "map_entry.h"

/**
 * Compares two TreeMapEntry objects.
 *
 * @param entry1 the first TreeMapEntry
 * @param entry2 the second TreeMapEntry
 * @return < 0 if entry1 < entry2, =0 if entry1 == entry2, >0 if entry1 > entry2
 */
int compareMapEntry(MapEntry* entry1, MapEntry* entry2) {
	return strcmp(entry1->key, entry2->key);
}

/**
 * Compares two TreeMapEntry objects.
 *
 * @param val1 the first TreeMapValue
 * @param val2 the second TreeMapValue
 * @return < 0 if entry1 < entry2, =0 if entry1 == entry2, >0 if entry1 > entry2
 */
int compareMapValue(MapValue* val1, MapValue* val2) {
	return strcmp(val1->valuestr, val2->valuestr);
}


