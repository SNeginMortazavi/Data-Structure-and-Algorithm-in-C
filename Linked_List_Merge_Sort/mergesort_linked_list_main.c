/*
 * mergesort_linked_list_main.c
 *
 * This file exercises the Merge Sort method for sorting singly linked lists.
 *
 * @since 2017-04-09
 * @author philip gust
 */
#include <stdlib.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "mergesort_linked_list.h"

/**
 * Test mergeSortLinkedListTD() with empty list
 */
static void test_emptyLinkedListTD(void) {
	LinkedListNode* list = (LinkedListNode*)NULL;
	LinkedListNode* sortedList = mergeSortLinkedListTD(list);
	CU_ASSERT_PTR_NULL(sortedList);
}

/**
 * Test mergeSortLinkedListBU() with empty list
 */
static void test_emptyLinkedListBU(void) {
	LinkedListNode* list = (LinkedListNode*)NULL;
	LinkedListNode* sortedList = mergeSortLinkedListBU(list);
	CU_ASSERT_PTR_NULL(sortedList);
}

/**
 * Test mergeSortLinkedListTD() with single list
 */
static void test_oneItemLinkedListTD(void) {
	LinkedListNode* list =
		&(LinkedListNode){"01", (LinkedListNode*)NULL};
	LinkedListNode* sortedList = mergeSortLinkedListTD(list);
	CU_ASSERT_PTR_NOT_NULL(sortedList);
	if (sortedList->next != (LinkedListNode*)NULL) {
		CU_ASSERT_PTR_NULL(sortedList->next);
		CU_ASSERT_STRING_EQUAL(sortedList->data, "01");
	}
}

/**
 * Test mergeSortLinkedListBU() with single list
 */
static void test_oneItemLinkedListBU(void) {
	LinkedListNode* list =
		&(LinkedListNode){"01", (LinkedListNode*)NULL};
	LinkedListNode* sortedList = mergeSortLinkedListBU(list);
	CU_ASSERT_PTR_NOT_NULL(sortedList);
	if (sortedList->next != (LinkedListNode*)NULL) {
		CU_ASSERT_PTR_NULL(sortedList->next);
		CU_ASSERT_STRING_EQUAL(sortedList->data, "01");
	}
}

/**
 * Test mergeSortLinkedListTD() with two-node list
 */
static void test_twoItemLinkedListTD(void) {
	LinkedListNode* list =
		&(LinkedListNode){"02",
		&(LinkedListNode){"01", (LinkedListNode*)NULL}};

	const char* expected[] = {"01", "02"};
	LinkedListNode* sortedList = mergeSortLinkedListTD(list);
	LinkedListNode* p = sortedList;
	for (int i = 0; i < 2; i++) {
		CU_ASSERT_PTR_NOT_NULL(p);
		if (p == (LinkedListNode*)NULL) {
			break;
		}
		CU_ASSERT_STRING_EQUAL(p->data, expected[i]);
		p = p->next;
	}
}

/**
 * Test mergeSortLinkedListBU() with two-node list
 */
static void test_twoItemLinkedListBU(void) {
	LinkedListNode* list =
		&(LinkedListNode){"02",
		&(LinkedListNode){"01", (LinkedListNode*)NULL}};

	const char* expected[] = {"01", "02"};
	LinkedListNode* sortedList = mergeSortLinkedListBU(list);
	LinkedListNode* p = sortedList;
	for (int i = 0; i < 2; i++) {
		CU_ASSERT_PTR_NOT_NULL(p);
		if (p == (LinkedListNode*)NULL) {
			break;
		}
		CU_ASSERT_STRING_EQUAL(p->data, expected[i]);
		p = p->next;
	}
}

/**
 * Test mergeSortLinkedListTD() with six-node list
 */
static void test_sixItemLinkedListTD(void) {
	LinkedListNode* list =
		&(LinkedListNode){"03",
		&(LinkedListNode){"02",
		&(LinkedListNode){"20",
		&(LinkedListNode){"05",
		&(LinkedListNode){"10",
		&(LinkedListNode){"15",
		 (LinkedListNode*)NULL}}}}}};

	const char* expected[] = {"02", "03", "05", "10", "15", "20"};
	LinkedListNode* sortedList = mergeSortLinkedListTD(list);
	LinkedListNode* p = sortedList;
	for (int i = 0; i < 6; i++) {
		CU_ASSERT_PTR_NOT_NULL(p);
		if (p == (LinkedListNode*)NULL) {
			break;
		}
		CU_ASSERT_STRING_EQUAL(p->data, expected[i]);
		p = p->next;
	}
}

/**
 * Test mergeSortLinkedListBU() with six-node list
 */
static void test_sixItemLinkedListBU(void) {
	LinkedListNode* list =
		&(LinkedListNode){"03",
		&(LinkedListNode){"02",
		&(LinkedListNode){"20",
		&(LinkedListNode){"05",
		&(LinkedListNode){"10",
		&(LinkedListNode){"15",
		 (LinkedListNode*)NULL}}}}}};

	const char* expected[] = {"02", "03", "05", "10", "15", "20"};
	LinkedListNode* sortedList = mergeSortLinkedListBU(list);
	LinkedListNode* p = sortedList;
	for (int i = 0; i < 6; i++) {
		CU_ASSERT_PTR_NOT_NULL(p);
		if (p == (LinkedListNode*)NULL) {
			break;
		}
		CU_ASSERT_STRING_EQUAL(p->data, expected[i]);
		p = p->next;
	}
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
	CU_pSuite pSuite = CU_add_suite("NodeGraph Tests", NULL, NULL);

	// add the tests to the suite
	CU_add_test(pSuite, "test_emptyLinkedListTD", test_emptyLinkedListTD);
	CU_add_test(pSuite, "test_singleLinkedListTD", test_oneItemLinkedListTD);
	CU_add_test(pSuite, "test_twoItemLinkedListTD", test_twoItemLinkedListTD);
	CU_add_test(pSuite, "test_sixLinkedListTD", test_sixItemLinkedListTD);

	CU_add_test(pSuite, "test_emptyLinkedListBU", test_emptyLinkedListBU);
	CU_add_test(pSuite, "test_singleLinkedListBU", test_oneItemLinkedListBU);
	CU_add_test(pSuite, "test_twoItemLinkedListBU", test_twoItemLinkedListBU);
	CU_add_test(pSuite, "test_sixLinkedListBU", test_sixItemLinkedListBU);

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
