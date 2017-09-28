/*
 * messagepriorityqueue.h
 *
 *  Created on: Feb 1, 2017
 *      Author: phil
 */

#ifndef MESSAGEPRIORITYQUEUE_H_
#define MESSAGEPRIORITYQUEUE_H_

#include "messagequeue.h"

/**
 * The priorities for the MessagePriorityQueue
 */
typedef enum {
	highest,
	high,
	low,
	lowest
} Priority;

/**
 * The MessagePriorityQueue is an array of MessageQueue pointers
 */
typedef struct {
	MessageQueue** msgQueues;
} MessagePriorityQueue;

/**
 * Add a number to the queue.
 */
void enqueueMPQ(MessagePriorityQueue* queue, Message* message, Priority priority);

/**
 * Remove and return the first element in the queue.
 */
Message* dequeueMPQ(MessagePriorityQueue* queue);

/**
 * Create a new message priority queue
 */
MessagePriorityQueue* createQueueMPQ();

/**
 * Deallocate the memory for the queue.
 */
void deleteQueueMPQ(MessagePriorityQueue* queue);

/**
 * Get the current number of elements in the queue.
 */
int getNumElementsForPriorityMPQ(MessagePriorityQueue* queue, Priority priority);

/**
 * Get the current number of elements in the queue.
 */
int getNumElementsMPQ(MessagePriorityQueue* queue);

#endif /* MESSAGEPRIORITYQUEUE_H_ */
