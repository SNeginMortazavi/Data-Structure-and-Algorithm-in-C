/*
 * binary_tree_main.c
 *
 * This file provides the unit tests for a binary tree iterator.
 *
 * @since 2017-02-15

 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "tree_set.h"
#include "tree_set_iterator.h"

TreeSet* makeTreeSet(char** entries, int nEntries) {
	TreeSet* set = createTreeSet();

	for (int i = 0; i < nEntries; i++) {
		addTreeSetKey(set, entries[i]);
	}

	return set;
}

/**
 * Test of binary tree iterator for empty (NULL) expr tree
 */
static void testTreeSet(void) {
	char* entries[] = {
		"key1","key3", "key4", "key2"
	};
	int nEntries = 4;
	TreeSet* set = makeTreeSet(entries, nEntries);
	CU_ASSERT_EQUAL(getTreeSetSize(set), nEntries);

	// test all keys present
	for (int i = 0; i < nEntries; i++) {
		CU_ASSERT_TRUE(containsTreeSetKey(set, entries[i]));
	}
	CU_ASSERT_FALSE(containsTreeSetKey(set, "unknownKey"));

	// test iterator
	const char* prevKey = "";
	TreeSetIterator* itr = createTreeSetIterator(set);
	for (int i = 0;i < nEntries; i++) {
		CU_ASSERT_TRUE(hasNextTreeSetKey(itr));
		const char* key = getNextTreeSetKey(itr);
		CU_ASSERT_PTR_NOT_NULL(key);
		if (key != (char*)NULL) {
			// make sure this key is greater than previous one;
			CU_ASSERT_TRUE(strcmp(prevKey, key) < 0);
			prevKey = key;
		}
	}
	CU_ASSERT_EQUAL(getTreeSetIteratorCount(itr), nEntries);
	CU_ASSERT_EQUAL(getTreeSetIteratorAvailable(itr), 0);
	freeTreeSetIterator(itr);
	CU_ASSERT_PTR_NULL(itr->mapIterator);   // dicey

	// test putAllTreeSetEntries() replacing values
	char* entries2[] = {
		"key3","key2", "key4"
	};
	int nEntries2 = 3;
	TreeSet* set2 = makeTreeSet(entries2, nEntries2);
	CU_ASSERT_EQUAL(getTreeSetSize(set2), nEntries2);

	bool changed = addAllTreeSetKeys(set, set2);
	CU_ASSERT_FALSE(changed);

	bool containsAll = containsAllTreeSetKeys(set, set2);
	CU_ASSERT_TRUE(containsAll);

	bool containsAll2 = containsAllTreeSetKeys(set2, set);
	CU_ASSERT_FALSE(containsAll2);

	bool retainAll = retainAllTreeSetKeys(set2, set);
	CU_ASSERT_FALSE(retainAll);

	bool retainAll2 = retainAllTreeSetKeys(set, set2);
	CU_ASSERT_TRUE(retainAll2);
	CU_ASSERT_EQUAL(getTreeSetSize(set), nEntries2);

	bool removeAll = removeAllTreeSetKeys(set, set2);
	CU_ASSERT_TRUE(removeAll);
	CU_ASSERT_EQUAL(getTreeSetSize(set), 0);

	bool removeAll2 = removeAllTreeSetKeys(set2, set);
	CU_ASSERT_FALSE(removeAll2);
	CU_ASSERT_EQUAL(getTreeSetSize(set2), nEntries2);

	bool retainAll3 = retainAllTreeSetKeys(set2, set);
	CU_ASSERT_TRUE(retainAll3);
	CU_ASSERT_EQUAL(getTreeSetSize(set2), 0);

	TreeSet* set3 = makeTreeSet(entries2, nEntries2);
	CU_ASSERT_EQUAL(getTreeSetSize(set3), nEntries2);
	clearTreeSet(set3);
	CU_ASSERT_EQUAL(getTreeSetSize(set3), 0);
}

/**
 * Test all the functions for this application.
 *
 * @return test error code
 */
static int test_all(void) {
	// initialize the CUnit test registry -- only once per application
	CU_initialize_registry();

	// add a suite to the registry with no init or cleanup
	CU_pSuite pSuite = CU_add_suite("TreeSet Tests", NULL, NULL);

	// add the tests to the suite
	CU_add_test(pSuite, "testTreeSet", testTreeSet);

	// run all test suites using the basic interface
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	// display information on failures that occurred
	CU_basic_show_failures(CU_get_failure_list());

	// Clean up registry and return status
	CU_cleanup_registry();
	return CU_get_error();
}

/**
 * Main program to invoke test functions
 *
 * @return the exit status of the program
 */
int main(void) {

	// test all the functions
	CU_ErrorCode code = test_all();

	return (code == CUE_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}


