/*
 * messagequeue.c
 *
 * The functions in this file implement a MessageQueue that enables instances
 * of Message to be enqueued and dequeued on a first-in first-out (FIFO) order.
 * The MessageQueue can grow to accommodate any number of messages.
 *
 * @since Feb 1, 2017
 * @author phil
 */
#include <stdlib.h>
#include <assert.h>
#include "messagequeue.h"

// allows DEFAULT_QUEUE_SIZE to be changed at compilation
#ifndef DEFAULT_QUEUE_SIZE
#define DEFAULT_QUEUE_SIZE 16
#endif

/**
 * Add a number to the queue.
 *
 * @param queue the message queue
 * @param the message to enqueue
 */
void enqueueMQ(MessageQueue* queue, Message* message) {
	assert( queue != (MessageQueue*)NULL );
	assert( message != (Message*)NULL) ;

	if (queue->numElements == queue->size) {
		// extend message array if at capacity by doubling the size
		int newSize = 2 * queue->size;
		queue->messages =
				realloc(queue->messages, newSize * sizeof(Message*));
		assert(queue->messages != (Message**)NULL);
		queue->size = newSize;
	}

	// add to end of queue
	queue->messages[queue->numElements++] = message;
}

/**
 * Remove and return the first element in the queue.
 *
 * @param queue the MessageQueue
 * @return the dequeued message, or NULL if no messages on queue
 */
Message* dequeueMQ(MessageQueue* queue) {
	assert( queue != (MessageQueue*)NULL );

	// no messages to dequeue
	if (queue->numElements == 0) {
		return (Message*)NULL;
	}

	// message at head of queue to return
	Message *message = queue->messages[0];

	// remove the message from the queue
	for (int i = 1; i < queue->numElements; i++) {
		queue->messages[i-1] = queue->messages[i];
	}
	queue->numElements--;

	return message;
}

/**
 * Create a new message queue
 *
 * @return the new MessageQueue
 */
MessageQueue* createQueueMQ() {
	MessageQueue* queue =  (MessageQueue*)malloc(sizeof(MessageQueue));
	assert( queue != (MessageQueue*)NULL );

	// create message array
	queue->messages = (Message**)malloc(DEFAULT_QUEUE_SIZE * sizeof(Message*));
	assert ( queue->messages != (Message**)NULL );

	// initialize other fields
	queue->numElements = 0;
	queue->size = DEFAULT_QUEUE_SIZE;

	return queue;
}

/**
 * Deallocate the memory for the queue.
 *
 * @param queue the MessageQueue
 */
void deleteQueueMQ(MessageQueue* queue) {
	assert( queue != (MessageQueue*)NULL );

	if (queue->messages != (Message**)NULL) {
		for (int i = 0; i < queue->numElements; i++) {
			deleteMessage(queue->messages[i]);
			queue->messages[i] = (Message*)NULL;
		}
		free(queue->messages);

		// reset the fields
		queue->messages = (Message**)NULL;
		queue->size = 0;
		queue->numElements = 0;

		free(queue);
	}
}

/**
 * Get the current number of elements in the queue.
 *
 * @param queue the MessageQueue
 */
int getNumElementsMQ(MessageQueue* queue) {
	assert( queue != (MessageQueue*)NULL );

	return queue->numElements;
}
