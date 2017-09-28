#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "message.h"

/**
 * A struct representing a MessageQueue.
 */
typedef struct {
    Message** messages; // array of message pointers
    int numElements;    // number of elements in the queue
    int size;           // length of allocated array
} MessageQueue;

/**
 * Add a number to the queue.
 */
void enqueueMQ(MessageQueue* queue, Message* message);

/**
 * Remove and return the first element in the queue.
 */
Message* dequeueMQ(MessageQueue* queue);

/**
 * Create a new message queue
 */
MessageQueue* createQueueMQ();

/**
 * Deallocate the memory for the queue.
 */
void deleteQueueMQ(MessageQueue* queue);

/**
 * Get the current number of elements in the queue.
 */
int getNumElementsMQ(MessageQueue* queue);

#endif
