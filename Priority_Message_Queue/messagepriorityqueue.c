/**
* This file contains the functions for CS 5002 assignment2.
*
* messagepriorityqueue.c
*
* @since Feb 7, 2017
* @author Negin
*/
#include <stdio.h>
# include<stdlib.h>
#include "messagepriorityqueue.h"
#include<assert.h>

/**
 * This function adds a member to queue.
 *
 * @param queue a pointer to MessagePriorityQueue* which is the type of our priority queue.
 * @param message a pointer to Message* which is the member that we want to add in priority queue
 * @param priority which is of enum type, shows the priority of each message in queue.
 * @return does not return anything, just updates priority queue with the new added
 * member
 *
 */
void enqueueMPQ(MessagePriorityQueue* queue, Message* message, Priority priority) {

	switch(priority){
			case (Priority)lowest:
				enqueueMQ(queue->msgQueues[priority], message);
				break;
			case (Priority)low:
				enqueueMQ(queue->msgQueues[priority], message);
				break;
			case (Priority)high:
				enqueueMQ(queue->msgQueues[priority], message);
				break;
			case (Priority)highest:
				enqueueMQ(queue->msgQueues[priority], message);
				break;
		}
}

/**
 * This function Removes and returns the first element in the priority queue.
 *
 * @param queue a pointer to MessagePriorityQueue* which is the type of our priority queue.
 * @return the dPriorityQueue which is the type of Message* and shows the first element
 * that is removed from priority queue.
 */
Message* dequeueMPQ(MessagePriorityQueue* queue) {
	Message* dPriorityQueue;
	for (Priority p = highest; p <= lowest; p++) {
		Message* msg = dequeueMQ(queue->msgQueues[p]);
		if(msg != NULL){
			return msg;
		}
	}
	return NULL;
}

/**
 * This function Creates a new message priority queue
 *
 * @return the created priority queue which is the type of MessagePriorityQueue*
 */
MessagePriorityQueue* createQueueMPQ() {
	int mPriority = (Priority)lowest - (Priority)highest + 1;
    MessagePriorityQueue* priorityQueue;

    //allocate memory for priority queue
    priorityQueue = (MessagePriorityQueue*)(malloc(sizeof(MessagePriorityQueue)));

    //check if the priority queue is not NULL
    assert(priorityQueue != NULL);

    //allocate memory for array of priority queue with specified size of mPriority
	priorityQueue->msgQueues = (MessageQueue**)(malloc(mPriority * sizeof(MessageQueue*)));

	for(int priority = (Priority)highest; priority <= (Priority)lowest; priority++){
		priorityQueue->msgQueues[priority] = createQueueMQ();
	}

	return priorityQueue;
}

/**
 * This function Deallocate the memory for the priority queue.
 *
 * @param queue a pointer to MessagePriorityQueue* which is the type of our priority queue.
 * @return it does not return anything, it is freeing the resources of priority queue
 */
void deleteQueueMPQ(MessagePriorityQueue* queue) {

	int mPriority = (Priority)lowest - (Priority)highest + 1;

	//free each element of priority queue array
	for (int i = 0; i < mPriority; i++){
		deleteQueueMQ(queue->msgQueues[i]);
	}

	//free priority queue array
	free(queue->msgQueues);

	//make sure priority queue array is NULL
	queue->msgQueues = NULL;
	mPriority = 0;
	free(queue);

}

/**
 * This function Get the current number of elements in the queue.

 * @param queue a pointer to MessagePriorityQueue* which is the type of our priority queue.
 * @param priority which is of enum type, shows the priority of each message in queue.
 * @return the current number of elements in specified queue based on given priority
 */
int getNumElementsForPriorityMPQ(MessagePriorityQueue* queue, Priority priority) {
	int cnt = 0;
	cnt = getNumElementsMQ(queue->msgQueues[priority]);
	return cnt;
}

/**
 * This function Get the current number of elements in the queue.

 * @param queue a pointer to MessagePriorityQueue* which is the type of our priority queue.
 * @return the total number of elements in priority queue
 */
int getNumElementsMPQ(MessagePriorityQueue* queue) {
	int cnt = 0;
	int mPriority = (Priority)lowest - (Priority)highest + 1;
	for (int i = 0; i < mPriority; i++){
	cnt = cnt + getNumElementsMQ(queue->msgQueues[i]);
	}

	return cnt;
}
