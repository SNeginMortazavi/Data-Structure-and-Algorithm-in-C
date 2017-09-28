/*
 * messagepriorityqueue.c
 *
 * The functions in this file implement a MessagePriorityQueue that
 * uses a separate MessageQueue instances for messages of each Priority.
 *
 * @since Feb 1, 2017
 * @author phil
 */
#include <stdlib.h>
#include <assert.h>
#include "messagepriorityqueue.h"

/**
 * Add a message to the queue.
 *
 * @param queue the message priority queue
 * @param message the message to enqueue
 * @param the priority of the message
 *
 */
void enqueueMPQ(MessagePriorityQueue* queue, Message* message, Priority priority) {
	assert( queue != (MessagePriorityQueue*)NULL );
	assert( message != (Message*)NULL );

	// enqueue the message on the specified queue
	enqueueMQ(queue->msgQueues[priority], message);
}

/**
 * Remove and return the first element in the queue.
 *
 * @param queue the message priority queue
 * @return the message from the first non-empty queue
 */
Message*  dequeueMPQ(MessagePriorityQueue* queue) {
	assert( queue != (MessagePriorityQueue*)NULL );

	Message* msg = (Message*)NULL;

	// dequeue message from the first non-empty queue
	for (Priority p = highest; p <= lowest; p++) {
		msg =  dequeueMQ(queue->msgQueues[p]);
		// found message to dequeue
		if (msg != (Message*)NULL) {
			break;
		}
	}

	// return the message if found
	return msg;
}

/**
 * Create a new message priority queue
 *
 * @return the message priority queue
 */
MessagePriorityQueue* createQueueMPQ() {
	// allocate priority message queue
	MessagePriorityQueue* mpqueue =
			(MessagePriorityQueue*)malloc(sizeof(MessagePriorityQueue));
	assert( mpqueue != (MessagePriorityQueue *)NULL );

	// allocate array for message queues
	int nPriorities = (Priority)lowest - (Priority)highest + 1;
	mpqueue->msgQueues =
			(MessageQueue**)malloc(nPriorities * sizeof(MessageQueue*));
	assert( mpqueue->msgQueues != (MessageQueue**)NULL);

	// allocate message queue for each priority
	for (Priority p = highest; p <= lowest; p++) {
		mpqueue->msgQueues[p] = createQueueMQ();
	}

	return mpqueue;
}

/**
 * Deallocate the memory for the queue.
 *
 * @param queue the message priority queue
 */
void deleteQueueMPQ(MessagePriorityQueue* queue) {
	if (queue == (MessagePriorityQueue*)NULL) return;

	// delete the message queues
	for (Priority p = highest; p <= lowest; p++) {
		deleteQueueMQ(queue->msgQueues[p]);
		queue->msgQueues[p] = (MessageQueue*)NULL;
	}

	// free the message queue array
	free(queue->msgQueues);
	queue->msgQueues = (MessageQueue**)NULL;

	// finally free the queue
	free(queue);
}

/**
 * Get the current number of messages in the queue.
 *
 * @param queue the message priority queue
 * @param priority the selected priority
 * @return the number of messages in the selected message queue
 */
int getNumElementsForPriorityMPQ(MessagePriorityQueue* queue, Priority priority) {
	assert( queue != (MessagePriorityQueue*)NULL );

	return queue->msgQueues[priority]->numElements;
}

/**
 * Get the current number of elements in the queue.
 *
 * @param queue the message priority queue
 * @return the number of messages for all priorities;
 */
int getNumElementsMPQ(MessagePriorityQueue* queue) {
	assert( queue != (MessagePriorityQueue*)NULL );

	// add the size of all the queues
	int nElements = 0;
	for (Priority p = highest; p <= lowest; p++) {
		nElements+= queue->msgQueues[p]->numElements;
	}

	return nElements;
}
