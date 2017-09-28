/*
 * messagepriorityqueue_main.c
 *
 * This file tests the MessagePriorityQueue, MessageQueue, and
 * Message types and functions.
 *
 *  @since 2017-02-01
 *  @author Philip Gust
 */
#include <stdlib.h>
#include <time.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "messagepriorityqueue.h"

/**
 * Unit tests for Message
 */
static void testMessage(void) {
	// test creation of string message with null string
	char* messageStr = (char*)NULL;
	Message* msg = createStringMessage(messageStr);
	CU_ASSERT_PTR_NOT_NULL(msg);
	CU_ASSERT_EQUAL(msg->msgType, stringMessage);
	CU_ASSERT_PTR_NULL(msg->strMsg.msgstr);

	// delete the message and ensure the string field is null
	deleteMessage(msg);
	CU_ASSERT_EQUAL(msg->msgType, 0);
	CU_ASSERT_PTR_NULL(msg->strMsg.msgstr);  // dicey

	// test allocation of string message with non-null string
	messageStr = "Hello";
	msg = createStringMessage(messageStr);
	CU_ASSERT_PTR_NOT_NULL(msg);
	CU_ASSERT_EQUAL(msg->msgType, stringMessage);
	CU_ASSERT_PTR_NOT_NULL(msg->strMsg.msgstr);
	CU_ASSERT_NOT_EQUAL(msg->strMsg.msgstr, messageStr);
	CU_ASSERT_STRING_EQUAL(msg->strMsg.msgstr, "Hello");

	// delete the message and ensure the string field is null
	deleteMessage(msg);
	CU_ASSERT_EQUAL(msg->msgType, 0);
	CU_ASSERT_PTR_NULL(msg->strMsg.msgstr);  // dicey

	// test allocation of block message with a non-null block
	unsigned int blkSize = 3;
	int blkFmt = 1;
	unsigned char blkBytes[] = {0xff, 0x20, 0xab};
	msg = createBlockMessage(blkSize, blkFmt, blkBytes);
	CU_ASSERT_PTR_NOT_NULL(msg);
	CU_ASSERT_EQUAL(msg->msgType, blockMessage);
	CU_ASSERT_EQUAL(msg->blkMsg.blkFormat, blkFmt);
	CU_ASSERT_EQUAL(msg->blkMsg.blkSize, blkSize);
	CU_ASSERT_PTR_NOT_NULL(msg->blkMsg.blkBytes);
	CU_ASSERT_NOT_EQUAL(blkBytes, msg->blkMsg.blkBytes);
	for (int i = 0; i < 3; i++) {
		CU_ASSERT_EQUAL(msg->blkMsg.blkBytes[i], blkBytes[i]);
	}

	// delete the message and ensure the string field is null
	deleteMessage(msg);
	CU_ASSERT_EQUAL(msg->msgType, 0);
	CU_ASSERT_PTR_NULL(msg->blkMsg.blkBytes);  // dicey

	// test creation of status message with null string
	unsigned long timeStamp = time(NULL);
	unsigned int statusCode = 200;
	char* statusMsgStr = (char*)NULL;
	msg = createStatusMessage(timeStamp, statusCode, statusMsgStr);
	CU_ASSERT_PTR_NOT_NULL(msg);
	CU_ASSERT_EQUAL(msg->msgType, statusMessage);
	CU_ASSERT_EQUAL(msg->statusMsg.timeStamp, timeStamp);
	CU_ASSERT_EQUAL(msg->statusMsg.statusCode, statusCode);
	CU_ASSERT_PTR_NULL(msg->statusMsg.statusMessage);

	// delete the message and ensure the string field is null
	deleteMessage(msg);
	CU_ASSERT_EQUAL(msg->msgType, 0);
	CU_ASSERT_EQUAL(msg->statusMsg.statusCode, 0);  // dicey
	CU_ASSERT_EQUAL(msg->statusMsg.timeStamp, 0);  // dicey
	CU_ASSERT_PTR_NULL(msg->statusMsg.statusMessage);  // dicey

	// test allocation of status message with non-null string
	statusMsgStr = "Operation successful";
	msg = createStatusMessage(timeStamp, statusCode, statusMsgStr);
	CU_ASSERT_PTR_NOT_NULL(msg);
	CU_ASSERT_EQUAL(msg->msgType, statusMessage);
	CU_ASSERT_EQUAL(msg->statusMsg.timeStamp, timeStamp);
	CU_ASSERT_EQUAL(msg->statusMsg.statusCode, statusCode);
	CU_ASSERT_PTR_NOT_NULL(msg->statusMsg.statusMessage);
	CU_ASSERT_NOT_EQUAL(msg->statusMsg.statusMessage, statusMsgStr);
	CU_ASSERT_STRING_EQUAL(msg->statusMsg.statusMessage,statusMsgStr);

	// delete the message and ensure the string field is null
	deleteMessage(msg);
	CU_ASSERT_EQUAL(msg->msgType, 0);
	CU_ASSERT_EQUAL(msg->statusMsg.statusCode, 0);  // dicey
	CU_ASSERT_EQUAL(msg->statusMsg.timeStamp, 0);  // dicey
	CU_ASSERT_PTR_NULL(msg->statusMsg.statusMessage);  // dicey
}

/**
 * Unit tests for MessageQueue
 */
static void testMessageQueue(void) {
	//// test empty queue
	// create a message queue
	MessageQueue* mq = createQueueMQ();
	CU_ASSERT_PTR_NOT_NULL(mq);
	CU_ASSERT_PTR_NOT_NULL(mq->messages);
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), 0);

	// dequeue message from empty queue
	CU_ASSERT_PTR_NULL(dequeueMQ(mq));
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), 0);

	// delete message queue
	deleteQueueMQ(mq);
	CU_ASSERT_PTR_NULL(mq->messages);			// dicey
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), 0);	// dicey
	CU_ASSERT_EQUAL(mq->size, 0);  				// dicey

	//// test single message on queue
	// create message queue and enqueue message
	mq = createQueueMQ();
	Message* msg = createStringMessage("0");
	enqueueMQ(mq, msg);
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), 1);
	CU_ASSERT_PTR_EQUAL(mq->messages[0], msg);
	CU_ASSERT_TRUE((mq->size > 0));

	// dequeue a message
	CU_ASSERT_PTR_EQUAL(dequeueMQ(mq), msg);
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), 0);
	deleteMessage(msg);

	// dequeue message from empty queue
	CU_ASSERT_PTR_NULL(dequeueMQ(mq));
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), 0);

	// delete message queue
	deleteQueueMQ(mq);
	CU_ASSERT_PTR_NULL(mq->messages);			// dicey
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), 0);	// dicey
	CU_ASSERT_EQUAL(mq->size, 0);				// dicey

	//// over-fill queue test
	mq = createQueueMQ();
	char msgtext[10];
	int qsize = mq->size;
	for (int i = 0; i <= qsize; i++) {
		sprintf(msgtext, "%d", i);
		msg = createStringMessage(msgtext);
		enqueueMQ(mq, msg);
	}
	// verify that the queue expanded
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), qsize+1);
	CU_ASSERT_TRUE((mq->size > qsize))

	// dequeue first message
	Message* msg0 = dequeueMQ(mq);
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), qsize);
	CU_ASSERT_PTR_NOT_NULL(msg0);
	CU_ASSERT_STRING_EQUAL(msg0->strMsg.msgstr, "0");

	// dequeue second message
	Message* msg1 = dequeueMQ(mq);
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), qsize-1);
	CU_ASSERT_PTR_NOT_NULL(msg1);
	CU_ASSERT_STRING_EQUAL(msg1->strMsg.msgstr, "1");

	// delete message queue
	deleteQueueMQ(mq);
	CU_ASSERT_PTR_NULL(mq->messages);			// dicey
	CU_ASSERT_EQUAL(getNumElementsMQ(mq), 0);  	// dicey
	CU_ASSERT_EQUAL(mq->size, 0);				// dicey

	// ensure last message enqueued in loop was freed: msgstr is null
	CU_ASSERT_PTR_NULL(msg->strMsg.msgstr);			// dicey
}

/**
 * Unit tests for MessagePriorityQueue.
 */
static void testMessagePriorityQueue(void) {
	//// test empty queue
	// create a message queue
	MessagePriorityQueue* mpq = createQueueMPQ();
	CU_ASSERT_PTR_NOT_NULL(mpq);
	CU_ASSERT_PTR_NOT_NULL(mpq->msgQueues);
	CU_ASSERT_EQUAL(getNumElementsMPQ(mpq), 0);

	// dequeueue message from empty queue
	CU_ASSERT_PTR_NULL(dequeueMPQ(mpq));

	// delete message queue
	deleteQueueMPQ(mpq);
	CU_ASSERT_PTR_NULL(mpq->msgQueues);			// dicey

	//// test single message on queue
	// create message queue and enqueue message
	mpq = createQueueMPQ();
	Message* msg = createStringMessage("0.0");
	enqueueMPQ(mpq, msg, (Priority)high);
	CU_ASSERT_EQUAL(getNumElementsMPQ(mpq), 1);
	CU_ASSERT_EQUAL(getNumElementsForPriorityMPQ(mpq, (Priority)high), 1);

	// dequeue a message
	CU_ASSERT_PTR_EQUAL(dequeueMPQ(mpq), msg);
	CU_ASSERT_EQUAL(getNumElementsMPQ(mpq), 0);
	deleteMessage(msg);

	// dequeue message from empty queue
	CU_ASSERT_PTR_NULL(dequeueMPQ(mpq));
	CU_ASSERT_EQUAL(getNumElementsMPQ(mpq), 0);

	// delete message queue
	deleteQueueMPQ(mpq);
	CU_ASSERT_PTR_NULL(mpq->msgQueues);			// dicey

	//// Enqueue 3 messages for each priority
	mpq = createQueueMPQ();
	char msgtext[10];
	for (Priority p = highest; p <= lowest; p++) {
		for (int i = 0; i < 3; i++) {
			sprintf(msgtext, "%d.%d", p, i);
			msg = createStringMessage(msgtext);
			enqueueMPQ(mpq, msg, p);
		}
	}

	// ensure that each queue has 3 messages
	CU_ASSERT_EQUAL(getNumElementsMPQ(mpq), 12);
	CU_ASSERT_EQUAL(getNumElementsForPriorityMPQ(mpq,(Priority)highest), 3);
	CU_ASSERT_EQUAL(getNumElementsForPriorityMPQ(mpq,(Priority)high), 3);
	CU_ASSERT_EQUAL(getNumElementsForPriorityMPQ(mpq,(Priority)low), 3);
	CU_ASSERT_EQUAL(getNumElementsForPriorityMPQ(mpq,(Priority)lowest), 3);

	// verify that the messages dequeue in the right order
	for (Priority p = highest; p <= lowest; p++) {
		for (int i = 0; i < 3; i++) {
			sprintf(msgtext, "%d.%d", p, i);
			msg = dequeueMPQ(mpq);
			CU_ASSERT_PTR_NOT_NULL(msg);
			CU_ASSERT_STRING_EQUAL(msg->strMsg.msgstr, msgtext);
			deleteMessage(msg);
		}
	}
	CU_ASSERT_EQUAL(getNumElementsMPQ(mpq), 0);

	// delete message queue
	deleteQueueMPQ(mpq);
	CU_ASSERT_PTR_NULL(mpq->msgQueues);			// dicey

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
	CU_pSuite pSuite = CU_add_suite("function_tests", NULL, NULL);

	// add the tests to the suite
	CU_add_test(pSuite, "test_message", testMessage);
	CU_add_test(pSuite, "test_messageQueue", testMessageQueue);
	CU_add_test(pSuite, "test_messagePriorityQueue", testMessagePriorityQueue);

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

