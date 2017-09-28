/**
* This file contains the functions for CS 5002 assignment2.
*
* messagequeue.c
*
* @since Feb 7, 2017
* @author Negin
*/

#include <stdlib.h>
#include "messagequeue.h"
#include <assert.h>

/**
 * This function adds a member to queue.
 *
 * @param queue a pointer to MessageQueue which is the type of our queue.
 * @param message a pointer to Message* which is the member that we want to add in queue
 * @return does not return anything, just updates queue with the new member inside.
 */
void enqueueMQ(MessageQueue* queue, Message* message) {
	//check if queue is not NULL
	assert(queue != NULL);
	//check if number of elements is less than size of allocated memory for array of queue
	assert(queue->numElements <= queue->size );
	//check if the message that is going to be enqueued is not NULL
	assert(message != NULL);

	//reallocate storage if queue->numElements >= queue->size
	if(queue->numElements == queue->size){
		int newSize;
		Message** newMessages;
		newSize = queue->size * 2;
		newMessages = (Message**)realloc(queue->messages, sizeof(Message*) * newSize);
		assert(newMessages != NULL);
		queue->size = newSize;
		queue->messages = newMessages;
	}

	(queue->messages)[queue->numElements++] = message;

}

/**
 * This function Remove and return the first element in the queue.
 *
 * @param queue a pointer to MessageQueue which is the type of our queue.
 * @return the dqueued which is the type of Message* and shows the first element
 * that is removed from queue.
 */
Message* dequeueMQ(MessageQueue* queue) {
	//check if queue is empty
	if(queue->numElements == 0)
		return (Message*)NULL;
	Message* dqueued;
	dqueued = queue->messages[0];

	for (int i = 0; i < queue->numElements; i++)
	{
		queue->messages[i] = queue->messages[i + 1];
	}

	queue->numElements--;
	return dqueued;
}

/**
 * This function Creates a new message queue
 *
 * @return the created queue which is the type of MessageQueue*
 */
MessageQueue* createQueueMQ() {
	MessageQueue* queue;
	//allocate memory for queue
	queue = (MessageQueue*)(malloc(sizeof(MessageQueue)));

	//check if queue is not NULL
	assert(queue != NULL);

	//set the small enough size for array of queue
	queue->size = 16;

	//set the number of elements in array of queue to zero
	queue->numElements = 0;

	//allocate array of queue
	queue->messages = (Message**)malloc(queue->size * sizeof(Message*));

	//check if array of queue is not NULL
	assert(queue->messages != NULL);

	return queue;
}

/**
 * This function Deallocate the memory for the queue.
 *
 * @param queue a pointer to MessageQueue which is the type of our queue.
 * @return it does not return anything, it is freeing the resources of queue
 */
void deleteQueueMQ(MessageQueue* queue) {
	for(int i = 0; i < queue->numElements; i++)
	{
		//free each element of array of queue
		deleteMessage(queue->messages[i]);
	}

	//free array of queue
	free(queue->messages);

	//make sure array sets to NULL
	queue->messages = NULL;

	//set the size of allocated memory to zero
	queue->size = 0;

	//set the number of element in array of queue to zero
	queue->numElements = 0;
	free(queue);

}

/**
 * This function Get the current number of elements in the queue.
 *
 * @param queue a pointer to MessageQueue which is the type of our queue.
 * @return the number of elements in queue
 */
int getNumElementsMQ(MessageQueue* queue) {
	return queue->numElements;
}
