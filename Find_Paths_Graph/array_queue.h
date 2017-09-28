#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_

#include <stdbool.h>
#include "graph_node_vertex.h"

/**
 * The data for the queue
 */
typedef struct {
	GraphNodeVertex* node;
} QueueData;
/**
 * A struct representing a ArrayQueue.
 */
typedef struct {
    QueueData* data;		// array of node pointers
    int size;               // number of elements in the queue
    int capacity;           // length of allocated array
} ArrayQueue;

/**
 * Add a data as the last element in the queue.
 *
 * @param queue the queue
 * @param data the data to enqueue
 */
void enqueueArrayQueueData(ArrayQueue* queue, QueueData data);

/**
 * Remove and return the first element in the queue.
 *
 * @param queue the queue
 * @param result result copied to this location if data available
 * @return the result or null if no data available
 */
QueueData* dequeueArrayQueueData(ArrayQueue* queue, QueueData* result);

/**
 * Add a data as the last element in the queue.
 *
 * @param queue the queue
 * @param result result copied to this location if data available
 * @return the result or null if no data available
 */
void pushArrayQueueData(ArrayQueue* queue, QueueData data);

/**
 * Remove and return as the last element of the queue.
 *
 * @param queue the queue
 * @param result element copied to this location if data available
 * @return the result or null if no data available
 */
QueueData* popArrayQueueData(ArrayQueue* queue, QueueData* data);


/**
 * Add data as the last element of the queue.
 *
 * @param queue the queue
 * @param the data to enqueue
 */
void addLastArrayQueueData(ArrayQueue* queue, QueueData data);

/**
 * Add data as the first element of the queue.
 *
 * @param queue the queue
 * @param the data to enqueue
 */
void addFirstArrayQueueData(ArrayQueue* queue, QueueData data);

/**
 * Remove and return the first element in the queue.
 *
 * @param queue the queue
 * @param result element copied to this location if data available
 * @return the result or null if no data available
 */
QueueData* removeFirstArrayQueueData(ArrayQueue* queue, QueueData *result);

/**
 * Remove and return as the last element of the queue.
 *
 * @param queue the queue
 * @param result element copied to this location if data available
 * @return the result or null if no data available
 */
QueueData* removeLastArrayQueueData(ArrayQueue* queue, QueueData* result);

/**
 * Create a new queue
 */
ArrayQueue* createArrayQueue();

/**
 * Free the memory for the queue.
 */
void freeArrayQueue(ArrayQueue* queue);

/**
 * Get the current size of the queue.
 */
int getArrayQueueSize(ArrayQueue* queue);

/**
 * Determines whether queue is empty
 *
 * @param queue the ArrayQueue
 * @return true if the queue is empty, false otherwise
 */
bool isEmptyArrayQueue(ArrayQueue* queue);

/**
 * Clears the queue.
 *
 * @param queue the ArrayQueue
 */
void clearArrayQueue(ArrayQueue* queue);

#endif /* ARRAY_QUEUE_H_ */
