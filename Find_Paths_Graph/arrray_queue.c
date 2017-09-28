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
#include "array_queue.h"


// allows DEFAULT_QUEUE_SIZE to be changed at compilation
#ifndef DEFAULT_QUEUE_SIZE
#define DEFAULT_QUEUE_SIZE 16
#endif

/**
 * Add a data as the last element in the queue.
 *
 * @param queue the queue
 * @param result result copied to this location if data available
 * @return the result or null if no data available
 */
void pushArrayQueueData(ArrayQueue* queue, QueueData data) {
	addLastArrayQueueData(queue, data);
}

/**
 * Add a data as the last element of the queue.
 *
 * @param queue the queue
 * @param data the data to enqueue
 */
void enqueueArrayQueueData(ArrayQueue* queue, QueueData data) {
	addLastArrayQueueData(queue, data);
}

/**
 * Add data as the last element of the queue.
 *
 * @param queue the queue
 * @param the data to enqueue
 */
void addLastArrayQueueData(ArrayQueue* queue, QueueData data) {
	assert( queue != (ArrayQueue*)NULL );

	if (queue->size == queue->capacity) {
		// extend queue array if at capacity by doubling the size
		int newCapacity = 2 * queue->capacity;
		queue->data =
				(QueueData*)realloc(queue->data, newCapacity * sizeof(QueueData));
		assert(queue->data != (QueueData*)NULL);
		queue->capacity = newCapacity;
	}

	// add to end of queue
	queue->data[queue->size++] = data;
}

/**
 * Add data as the first element of the queue.
 *
 * @param queue the queue
 * @param the data to enqueue
 */
void addFirstArrayQueueData(ArrayQueue* queue, QueueData data) {
	assert( queue != (ArrayQueue*)NULL );

	if (queue->size == queue->capacity) {
		// extend queue array if at capacity by doubling the size
		int newCapacity = 2 * queue->capacity;
		queue->data =
				(QueueData*)realloc(queue->data, newCapacity * sizeof(QueueData));
		assert(queue->data != (QueueData*)NULL);
		queue->capacity = newCapacity;
	}

	// move data up the queue array
	for (int i = queue->size-1; i >= 0; i--) {
		queue->data[i+1] = queue->data[i];
	}
	// add to front of queue
	queue->data[0] = data;

	// queue now has one more item
	queue->size++;
}

/**
 * Remove and return the first element in the queue.
 *
 * @param queue the queue
 * @param result result copied to this location if data available
 * @return the result or null if no data available
 */
QueueData* dequeueArrayQueueData(ArrayQueue* queue, QueueData *result) {
	return removeFirstArrayQueueData(queue, result);
}

/**
 * Remove and return the first element in the queue.
 *
 * @param queue the queue
 * @param result element copied to this location if data available
 * @return the result or null if no data available
 */
QueueData* removeFirstArrayQueueData(ArrayQueue* queue, QueueData *result) {
	assert( queue != (ArrayQueue*)NULL );

	// no data to dequeue
	if (queue->size == 0) {
		return (QueueData*)NULL;
	}

	// data at head of queue to return
	if (result != (QueueData*)NULL) {
		*result = queue->data[0];
	}
	// remove the data from the queue
	for (int i = 1; i < queue->size; i++) {
		queue->data[i-1] = queue->data[i];
	}
	queue->size--;

	return result;
}

/**
 * Remove and return as the last element of the queue.
 *
 * @param queue the queue
 * @param result element copied to this location if data available
 * @return the result or null if no data available
 */
QueueData* popArrayQueueData(ArrayQueue* queue, QueueData* data) {
	return removeLastArrayQueueData(queue, data);
}

/**
 * Remove and return as the last element of the queue.
 *
 * @param queue the queue
 * @param result element copied to this location if data available
 * @return the result or null if no data available
 */
QueueData* removeLastArrayQueueData(ArrayQueue* queue, QueueData* result) {
	assert( queue != (ArrayQueue*)NULL );

	// no data to dequeue
	if (queue->size == 0) {
		return (QueueData*)NULL;
	}

	// size is index of data element to return
	queue->size--;

	// data at tail of queue to return
	if (result != (QueueData*)NULL) {
		*result = queue->data[queue->size];
	}

	return result;
}

/**
 * Create a new ArrayQueue
 *
 * @return the new ArrayQueue
 */
ArrayQueue* createArrayQueue() {
	ArrayQueue* queue =  (ArrayQueue*)malloc(sizeof(ArrayQueue));
	assert( queue != (ArrayQueue*)NULL );

	// create queue array
	queue->data = (QueueData*)malloc(DEFAULT_QUEUE_SIZE * sizeof(QueueData));
	assert ( queue->data != (QueueData*)NULL);

	// initialize other fields
	queue->size = 0;
	queue->capacity = DEFAULT_QUEUE_SIZE;

	return queue;
}

/**
 * Free the memory for the queue.
 *
 * @param queue the GraphNodeVertexQueue
 */
void freeArrayQueue(ArrayQueue* queue) {
	assert( queue != (ArrayQueue*)NULL );

	if (queue->data != (QueueData*)NULL) {
		free(queue->data);

		// reset the fields
		queue->data = (QueueData*)NULL;
		queue->capacity = 0;
		queue->size = 0;

		free(queue);
	}
}

/**
 * Get the current number of elements in the queue.
 *
 * @param queue the ArrayQueue
 */
int getArrayQueueSize(ArrayQueue* queue) {
	assert( queue != (ArrayQueue*)NULL );

	return queue->size;
}

/**
 * Determines whether queue is empty
 *
 * @param queue the ArrayQueue
 */
bool isEmptyArrayQueue(ArrayQueue* queue) {
	assert( queue != (ArrayQueue*)NULL );

	return queue->size == 0;
}

/**
 * Clears the queue.
 *
 * @param queue the ArrayQueue
 */
void clearArrayQueue(ArrayQueue* queue) {
	queue->size = 0;
}

